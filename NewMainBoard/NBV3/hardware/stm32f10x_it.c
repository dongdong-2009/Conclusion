#include "stm32f10x_it.h"
#include "Globle.h"
#include "stm32f10x_tim.h"
#include "modbus.h"
#include "usart.h"

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
				Uart1_RCnt=8;
				DealModBus();                 //modbus处理
				Uart1_RCnt=0;
				BusyFlag=0;
			}
	}
}

void USART1_IRQHandler(void)
{
	//判断串口是否发生指定中断，是否发生溢出错误中断
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE))
		{
			USART_ClearITPendingBit(USART1, USART_FLAG_ORE);//清除相应的标志位
		}
		
	if(USART_GetFlagStatus(USART1,USART_FLAG_NE)!=RESET)
		{
			USART_ClearFlag(USART1,USART_FLAG_NE);
		}
		
	if(USART_GetFlagStatus(USART1,USART_FLAG_FE)!=RESET)
		{
			USART_ClearFlag(USART1,USART_FLAG_FE);
		}
		
	if(USART_GetFlagStatus(USART1,USART_FLAG_PE)!=RESET)
		{
			USART_ClearFlag(USART1,USART_FLAG_PE);
		}
		
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
		delay_ms(5);
		DE1=1;
		 
		USART_ITConfig(USART1,USART_IT_TXE,DISABLE);			  	//发送完成 关闭中断
	 }	 
  }
	TIM_Cmd(TIM1, ENABLE);  //关闭定时器
	
}

void TIM2_IRQHandler(void)
{
	//检查指定的TIM中断发生与否，是否发生更新
  if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		{
			TSDataProcess();	
		}	   
	//清除中断标志位，TIM更新标志位
	TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
}


void USART2_IRQHandler(void)
{ 
	static unsigned int receivedCount = 0;
  char receivedData;
  char flag = 0;                     //the status flag of completion of receiving data
  int  isTrue = 0;	                  // Check Code is right?

		//判断串口是否发生指定中断，是否发生溢出错误中断
	if(USART_GetFlagStatus(USART2,USART_FLAG_ORE))
		{
			receivedData = Usart_GetChar(USART2);
			USART_ClearITPendingBit(USART2, USART_FLAG_ORE);//清除相应的标志位
		}
		
		if(USART_GetFlagStatus(USART2,USART_FLAG_NE)!=RESET)
		{
			USART_ClearFlag(USART2,USART_FLAG_NE);
		}
		
		if(USART_GetFlagStatus(USART2,USART_FLAG_FE)!=RESET)
		{
			USART_ClearFlag(USART2,USART_FLAG_FE);
		}
		
		if(USART_GetFlagStatus(USART2,USART_FLAG_PE)!=RESET)
		{
			USART_ClearFlag(USART2,USART_FLAG_PE);
		}
		
	//串口发生接收中断			
	if(USART_GetITStatus(USART2, USART_IT_RXNE))
		{
			 //清除中断标志位
			USART_ClearITPendingBit(USART2, USART_IT_RXNE); 
			receivedData = Usart_GetChar(USART2); 
			TSReceivedBuffer[receivedCount++] = receivedData;
			//接收到数据，最少2个字节
			if(receivedCount == 24)
				{
					if((TSReceivedBuffer[22]==0x66)&&(TSReceivedBuffer[23]==0x55))
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
							else if(TSTaskSel == SETDATA)
								{
									Usart2SendData(24,(char*)tx2);
								}
							else if(TSTaskSel == START)
								{
									TSControl=1;
									Usart2SendData(24,(char*)tx3);
								}
							else if(TSTaskSel == TSSTOP)
								{
									TSControl=0;
									Usart2SendData(24,(char*)tx4);
								}
						}		
				}		
		}
		
	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  {
		USART_ClearITPendingBit(USART2,USART_IT_TXE);
		delay_ms(10);
		DE2=1;
		USART_ITConfig(USART2,USART_IT_TXE,DISABLE);			  	//发送完成 关闭中断
  }
	
}


