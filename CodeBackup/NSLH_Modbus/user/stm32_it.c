#include <stdio.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "runtimedata.h"
#include "systick_timer.h"
#include "usart.h"
#include "timer.h"
#include "protocol.h"
#include "touchscreen.h"
#include "globe.h"

extern u8 TimeFlag;

void TIM1_UP_IRQHandler(void)
{ 
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		TimerOverFlag=1;
		if(BegainRxFlag==1)
			{
				BegainRxFlag=0;
				BusyFlag=1;
				DealModBus();                 //modbus处理
				Uart1_RCnt=0;
				BusyFlag=0;
			}
	}
}

void USART1_IRQHandler(void)
{ 
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
		if(BusyFlag)return;
		
		TIM_Cmd(TIM1, DISABLE);  //关闭定时器
		TIM_SetCounter(TIM1,0);//清除计时
		
		Uart1_receive_buffer[Uart1_RCnt]=USART_ReceiveData(USART1);		//连续发送
		if(TimerOverFlag) //如果时间溢出 代表新的modbus 数据包开始
		{
			TimerOverFlag=0;
			BegainRxFlag=1;
			Uart1_RCnt++;
		}
		else if(BegainRxFlag)
		{
			Uart1_RCnt++;
		}
  }
  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  { 	 
	 if(Uart1_SCnt<Uart1_SendBuffSize)
	 {
	 	USART_SendData(USART1,Uart1_Send_buffer[Uart1_SCnt++]);
	 }
	 else
	 {
		Uart1_SCnt=0;
		Delay_ms(5);
		DE1=1;
		 
		USART_ITConfig(USART1,USART_IT_TXE,DISABLE);			  	//发送完成 关闭中断
	 }	 
  }
	TIM_Cmd(TIM1, ENABLE);  //关闭定时器
}

void TIM2_IRQHandler(void)
{
	static int ScanTime = 3;                           //端口固有扫描周期3s
	//检查指定的TIM中断发生与否，是否发生更新
  if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		{
			//RunTime无任务时，每隔15s读取端口数据和PID参数
			if(TSTaskSel == NON)
				{
					ScanTime--;
					if(ScanTime == 0)
						{
							TSreadPorts(TSReadPortsBuffer);
							ScanTime = 3;
						}
				}	
			else
			{
				//如果有任务，就进行对应的任务操作
				ScanTime = 3;
				TSDataProcess();	
			}
		}	   
	//清除中断标志位，TIM更新标志位
	TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
}

void USART2_IRQHandler(void)
{
	static unsigned int receivedCount = 0;
  char receivedData;
  char highByte,lowByte;
  char flag = 0;                     //the status flag of completion of receiving data
  int  isTrue = 0;	                  // Check Code is right?
	
	//判断串口是否发生指定中断，是否发生溢出错误中断
	if(USART_GetFlagStatus(USART2,USART_FLAG_ORE))
		{
			receivedData = Usart_GetChar(USART2);
			USART_ClearITPendingBit(USART2, USART_FLAG_ORE);//清除相应的标志位
		}
	//串口发生接收中断			
	if(USART_GetITStatus(USART2, USART_IT_RXNE))
		{
			receivedData = Usart_GetChar(USART2); 
			TSReceivedBuffer[receivedCount++] = receivedData;
			//接收到数据，最少2个字节
			if(receivedCount >= 2)
				{
					//判断接收指令包尾信息，包尾---0xff,0xff
					highByte = TSReceivedBuffer[receivedCount-2];   //包尾高字节
					lowByte =  TSReceivedBuffer[receivedCount-1];   //包尾低字节
					//包尾数据正确
					if((highByte==0x66)&&(lowByte==0x55))
						flag = 1;
				}
			if(flag)
				{
					flag = 0;
					ReceivedNum = receivedCount;	
					receivedCount = 0;
					//判断接收数据校验位是否正确					
					isTrue = CheckTSReceivedData(TSReceivedBuffer);
					if(isTrue)
						{
							//解析接收到数据
							TSPacketAnalysis(TSReceivedBuffer);
							if(TSTaskSel == READDATA)
								{
									TSSentDataGeneration(18,TSReadPortsBuffer,SentBuffer);
								}
							else if(TSTaskSel == START)
								{
									Usart2SendData(24,(char*)tx2);
								}
							else if(TSTaskSel == START)
								{
									TSControl=1;
									Delay_ms(10);
									Usart2SendData(24,(char*)tx3);
								}
							else if(TSTaskSel == TSSTOP)
								{
									TSControl=0;
									Delay_ms(10);
									Usart2SendData(24,(char*)tx4);
								}
						}		
				}		
		}
 //清除中断标志位
	USART_ClearITPendingBit(USART1, USART_IT_RXNE); 
}

void TIM3_IRQHandler(void)
{
	int count=0;                           
	//检查指定的TIM中断发生与否，是否发生更新
  if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		{
			TimeFlag=0;
			count++;
			if(count==600)
				{
					count=0;
					TimeFlag=1;
				}
				
		}	   
	//清除中断标志位，TIM更新标志位
	TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
}

