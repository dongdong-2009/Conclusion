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
	static int ScanTime = 3;                           //�˿ڹ���ɨ������3s
	//���ָ����TIM�жϷ�������Ƿ�������
  if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
		{
			//RunTime������ʱ��ÿ��15s��ȡ�˿����ݺ�PID����
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
				//��������񣬾ͽ��ж�Ӧ���������
				ScanTime = 3;
				DataProcess();	
			}
		}	   
	//����жϱ�־λ��TIM���±�־λ
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
	
	//�жϴ����Ƿ���ָ���жϣ��Ƿ�����������ж�
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE))
		{
			receivedData = Usart_GetChar(USART1);
			USART_ClearITPendingBit(USART1, USART_FLAG_ORE);//�����Ӧ�ı�־λ
		}
	//���ڷ��������ж�			
	if(USART_GetITStatus(USART1, USART_IT_RXNE))
		{
			receivedData = Usart_GetChar(USART1); 
			ReceivedBuffer[receivedCount++] = receivedData;
			//���յ����ݣ�����2���ֽ�
			if(receivedCount >= 2)
				{
					//�жϽ���ָ���β��Ϣ����β---0xff,0xff
					highByte = ReceivedBuffer[receivedCount-2];   //��β���ֽ�
					lowByte =  ReceivedBuffer[receivedCount-1];   //��β���ֽ�
					//��β������ȷ
					if((highByte & lowByte & 0xff) == 0xff)
						flag = 1;
				}
			if(flag)
				{
					flag = 0;
					ReceivedNum = receivedCount;	
					receivedCount = 0;
					//�жϽ�������У��λ�Ƿ���ȷ					
					isTrue = CheckReceivedData(ReceivedBuffer);
					if(isTrue)
						{
							//�������յ�����
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
 //����жϱ�־λ
	USART_ClearITPendingBit(USART1, USART_IT_RXNE); 
}

void TIM2_IRQHandler(void)
{
	static int ScanTime = 3;                           //�˿ڹ���ɨ������3s
	//���ָ����TIM�жϷ�������Ƿ�������
  if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		{
			//RunTime������ʱ��ÿ��15s��ȡ�˿����ݺ�PID����
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
				//��������񣬾ͽ��ж�Ӧ���������
				ScanTime = 3;
				TSDataProcess();	
			}
		}	   
	//����жϱ�־λ��TIM���±�־λ
	TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
}

void USART2_IRQHandler(void)
{
	static unsigned int receivedCount = 0;
  char receivedData;
  char highByte,lowByte;
  char flag = 0;                     //the status flag of completion of receiving data
  int  isTrue = 0;	                  // Check Code is right?
	
	//�жϴ����Ƿ���ָ���жϣ��Ƿ�����������ж�
	if(USART_GetFlagStatus(USART2,USART_FLAG_ORE))
		{
			receivedData = Usart_GetChar(USART2);
			USART_ClearITPendingBit(USART2, USART_FLAG_ORE);//�����Ӧ�ı�־λ
		}
	//���ڷ��������ж�			
	if(USART_GetITStatus(USART2, USART_IT_RXNE))
		{
			receivedData = Usart_GetChar(USART2); 
			TSReceivedBuffer[receivedCount++] = receivedData;
			//���յ����ݣ�����2���ֽ�
			if(receivedCount >= 2)
				{
					//�жϽ���ָ���β��Ϣ����β---0xff,0xff
					highByte = TSReceivedBuffer[receivedCount-2];   //��β���ֽ�
					lowByte =  TSReceivedBuffer[receivedCount-1];   //��β���ֽ�
					//��β������ȷ
					if((highByte==0x66)&&(lowByte==0x55))
						flag = 1;
				}
			if(flag)
				{
					flag = 0;
					ReceivedNum = receivedCount;	
					receivedCount = 0;
					//�жϽ�������У��λ�Ƿ���ȷ					
					isTrue = CheckTSReceivedData(TSReceivedBuffer);
					if(isTrue)
						{
							//�������յ�����
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
 //����жϱ�־λ
	USART_ClearITPendingBit(USART1, USART_IT_RXNE); 
}

void TIM3_IRQHandler(void)
{
	int count=0;                           //�˿ڹ���ɨ������3s
	//���ָ����TIM�жϷ�������Ƿ�������
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
	//����жϱ�־λ��TIM���±�־λ
	TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
}
