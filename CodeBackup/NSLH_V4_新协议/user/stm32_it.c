#include <stdio.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "runtimedata.h"
#include "systick_timer.h"
#include "usart.h"
#include "timer.h"
#include "protocol.h"
#include "touchscreen.h"
extern u8 TimeFlag;

void TIM1_UP_IRQHandler(void)
{
	static int ScanTime = 3;                           //端口固有扫描周期3s
	//检查指定的TIM中断发生与否，是否发生更新
  if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
		{
			//RunTime无任务时，每隔15s读取端口数据和PID参数
			if(TaskSel == NON)
				{
					ScanTime--;
					if(ScanTime == 0)
						{
							readPorts(ReadPortsBuffer);
							readPID(ReadPIDBuffer);
							ScanTime = 3;
						}
				}	
			else
			{
				//如果有任务，就进行对应的任务操作
				ScanTime = 3;
				DataProcess();	
			}
		}	   
	//清除中断标志位，TIM更新标志位
	TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);   
}


void USART1_IRQHandler(void)
{
	static unsigned int receivedCount = 0;
  char receivedData;
  char highByte,lowByte;
  char flag = 0;                     //the status flag of completion of receiving data
  int  isTrue = 0;	                  // Check Code is right?
  int i;
	
	//判断串口是否发生指定中断，是否发生溢出错误中断
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE))
		{
			receivedData = Usart_GetChar(USART1);
			USART_ClearITPendingBit(USART1, USART_FLAG_ORE);//清除相应的标志位
		}
	//串口发生接收中断			
	if(USART_GetITStatus(USART1, USART_IT_RXNE))
		{
			receivedData = Usart_GetChar(USART1); 
			ReceivedBuffer[receivedCount++] = receivedData;
			//接收到数据，最少2个字节
			if(receivedCount >= 2)
				{
					//判断接收指令包尾信息，包尾---0xff,0xff
					highByte = ReceivedBuffer[receivedCount-2];   //包尾高字节
					lowByte =  ReceivedBuffer[receivedCount-1];   //包尾低字节
					//包尾数据正确
					if((highByte & lowByte & 0xff) == 0xff)
						flag = 1;
				}
			if(flag)
				{
					flag = 0;
					ReceivedNum = receivedCount;	
					receivedCount = 0;
					//判断接收数据校验位是否正确					
					isTrue = CheckReceivedData(ReceivedBuffer);
					if(isTrue)
						{
							//解析接收到数据
							PacketHeaderAnalysis(ReceivedBuffer);
							if(StageSel == RUNTIME)
								{
									if(TaskSel == READPORTS)
										{
											SentDataGeneration(165,ReadPortsBuffer,SentBuffer);
											UsartSendData(LENGTH+165+2,SentBuffer);
										}
									else if(TaskSel == READPID)
										{
											SentDataGeneration(96,ReadPIDBuffer,SentBuffer);		  
											UsartSendData(LENGTH+96+2,SentBuffer);
										}
									else if(TaskSel == WRITEPORTS)
										{
											UsartSendData(ReceivedNum,ReceivedBuffer);
											for(i=0;i<104;i++)
												WritePortsBuffer[i] = ReceivedBuffer[i+LENGTH];
										}
									else if(TaskSel == WRITEPID)
										{
											UsartSendData(ReceivedNum,ReceivedBuffer);
											for(i=0;i<97;i++)
												WritePIDBuffer[i] = ReceivedBuffer[i+LENGTH];
										}
									}
								}		
							}		
						}
 //清除中断标志位
	USART_ClearITPendingBit(USART1, USART_IT_RXNE); 
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
	int count=0;                           //端口固有扫描周期3s
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
