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
#include "string.h"

extern u8 TimeFlag;

void TIM1_UP_IRQHandler(void)
{ 
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		TimerOverFlag=1;
		if(BegainRxFlag==1)
			{
				BegainRxFlag=0;
				BusyFlag=1;
				DealModBus();                 //modbus����
				Uart1_RCnt=0;
				BusyFlag=0;
			}
	}
}

void USART1_IRQHandler(void)
{ 
		//�жϴ����Ƿ���ָ���жϣ��Ƿ�����������ж�
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE))  //OverRun Error Interrupt 
		{
			USART_ReceiveData(USART1);
			USART_ClearFlag(USART1,USART_IT_ORE);   //�������ж�
			//USART_ClearITPendingBit(USART1, USART_FLAG_ORE);//�����Ӧ�ı�־λ
		}
		
		if(USART_GetFlagStatus(USART1,USART_FLAG_NE)!=RESET)  //Noise Error Interrupt
		{
			USART_ReceiveData(USART1);
			USART_ClearFlag(USART1,USART_FLAG_NE);
		}
		
		if(USART_GetFlagStatus(USART1,USART_FLAG_FE)!=RESET)   //Frame Error Interrupt
		{
			USART_ReceiveData(USART1);
			USART_ClearFlag(USART1,USART_FLAG_FE);
		}
		
		if(USART_GetFlagStatus(USART1,USART_FLAG_PE)!=RESET)   //Parity Error Interrupt
		{
			USART_ReceiveData(USART1);
			USART_ClearFlag(USART1,USART_FLAG_PE);
		}
	
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
					 //����жϱ�־λ
		USART_ClearFlag(USART1,USART_IT_RXNE);
		USART_ClearITPendingBit(USART1, USART_IT_RXNE); 
		if(BusyFlag)return;
		
		TIM_Cmd(TIM1, DISABLE);  //�رն�ʱ��
		TIM_SetCounter(TIM1,0);//�����ʱ
		
		Uart1_receive_buffer[Uart1_RCnt]=USART_ReceiveData(USART1);		//��������
		if(TimerOverFlag) //���ʱ����� �����µ�modbus ���ݰ���ʼ
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
		USART_ClearITPendingBit(USART1,USART_IT_TXE);		
	 if(Uart1_SCnt<Uart1_SendBuffSize)
	 {
	 	USART_SendData(USART1,Uart1_Send_buffer[Uart1_SCnt++]);
	 }
	 else
	 {
		Uart1_SCnt=0;
		Delay_ms(5);
		DE1=1;
		 
		USART_ITConfig(USART1,USART_IT_TXE,DISABLE);			  	//������� �ر��ж�
	 }	 
  }
	TIM_Cmd(TIM1, ENABLE);  //�رն�ʱ��
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

//void USART2_IRQHandler(void)
//{
//	char flag=0;
//	int IsTrue=0;
//	static unsigned int receivedCount=0;
//	char receivedData;
//	
//	//	//�жϴ����Ƿ���ָ���жϣ��Ƿ�����������ж�
//	if(USART_GetFlagStatus(USART2,USART_FLAG_ORE))
//		{
//			receivedData = Usart_GetChar(USART2);
//			USART_ClearITPendingBit(USART2, USART_FLAG_ORE);//�����Ӧ�ı�־λ
//		}
//		
//	if(USART_GetITStatus(USART2, USART_IT_RXNE))
//	{
//		USART_ClearITPendingBit(USART2, USART_IT_RXNE); 
//		receivedData = Usart_GetChar(USART2); 
//		TSReceivedBuffer[receivedCount++] = receivedData;
//			//���յ����ݣ�����2���ֽ�
//		if(receivedCount == 24)
//		{
//			if((TSReceivedBuffer[22]==0x66)&&(TSReceivedBuffer[23]==0x55))
//			{
//				flag=1;
//			}
//		}
//		if(flag)
//		{
//			ReceivedNum = receivedCount;	
//			receivedCount=0;
//			IsTrue = CheckTSReceivedData(TSReceivedBuffer);
//			if(IsTrue)
//			{
//				TSPacketAnalysis(TSReceivedBuffer);
//				if(TSTaskSel == READDATA)
//				{
//					TSSentDataGeneration(18,TSReadPortsBuffer,SentBuffer);
//				}
//				else if(TSTaskSel == SETDATA)
//				{
//					DE2=0;
//					Uart2_SCnt=0;
//					Uart2_SendBuffSize=24;
//					memcpy(Uart2_Send_buffer,tx2,24);
//					USART_ITConfig(USART2,USART_IT_TXE,ENABLE);
//				}
//				else if(TSTaskSel == START)
//				{
//					DE2=0;
//					TSControl=1;
//					Uart2_SCnt=0;
//					Uart2_SendBuffSize=24;
//					memcpy(Uart2_Send_buffer,tx3,24);
//					USART_ITConfig(USART2,USART_IT_TXE,ENABLE);
//				}
//				else if(TSTaskSel == TSSTOP)
//				{
//					DE2=0;
//					TSControl=0;
//					Uart2_SCnt=0;
//					Uart2_SendBuffSize=24;
//					memcpy(Uart2_Send_buffer,tx4,24);
//					USART_ITConfig(USART2,USART_IT_TXE,ENABLE);
//				}
//			}
//		}
//		
//		else
//		{
//			Uart2_RCnt=0;
//		}
//	}
//	
//	if(USART_GetITStatus(USART2, USART_IT_TXE))
//	{
//		USART_ClearITPendingBit(USART2, USART_IT_TXE);
//		if(Uart2_SCnt<Uart2_SendBuffSize)
//		{
//			USART_SendData(USART2,Uart2_Send_buffer[Uart2_SCnt++]);
//		}
//		else
//		{
//			Uart2_SCnt=0;
//			DE2=1;
//			USART_ITConfig(USART2,USART_IT_TXE,DISABLE);
//		}
//	}
//	
//}


void USART2_IRQHandler(void)
{
	static unsigned int receivedCount = 0;
  char receivedData;
  char flag = 0;                     //the status flag of completion of receiving data
  int  isTrue = 0;	                  // Check Code is right?
	
	//�жϴ����Ƿ���ָ���жϣ��Ƿ�����������ж�
	if(USART_GetFlagStatus(USART2,USART_FLAG_ORE))
		{
			receivedData = Usart_GetChar(USART2);
			USART_ClearITPendingBit(USART2, USART_FLAG_ORE);//�����Ӧ�ı�־λ
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
		
	//���ڷ��������ж�			
	if(USART_GetITStatus(USART2, USART_IT_RXNE))
		{
			 //����жϱ�־λ
			USART_ClearITPendingBit(USART2, USART_IT_RXNE); 
			receivedData = Usart_GetChar(USART2); 
			TSReceivedBuffer[receivedCount++] = receivedData;
			//���յ����ݣ�����2���ֽ�
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
		Delay_ms(10);
		DE2=1;
		USART_ITConfig(USART2,USART_IT_TXE,DISABLE);			  	//������� �ر��ж�
  }
}

//void TIM3_IRQHandler(void)
//{
//	int count=0;                           
//	//���ָ����TIM�жϷ�������Ƿ�������
//  if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
//		{
//			TimeFlag=0;
//			count++;
//			if(count==600)
//				{
//					count=0;
//					TimeFlag=1;
//				}
//				
//		}	   
//	//����жϱ�־λ��TIM���±�־λ
//	TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
//}

void TIM3_IRQHandler(void)
{
	static int ScanTime = 3;                           //�˿ڹ���ɨ������3s
	//���ָ����TIM�жϷ�������Ƿ�������
  if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		{
			//RunTime������ʱ��ÿ��6s��ȡ�˿����ݺ�PID����
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
	TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);   
}
