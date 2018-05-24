#include "stm32f10x.h"
#include "systick_timer.h"
#include "usart.h"
#include "timer.h"
#include "touchscreen.h"
#include "globe.h"

extern unsigned int   ReceivedNum;					     //���յ����ַ��ĸ���
extern char  SentBuffer[200];				             //���ͻ�����

void TIM2_IRQHandler(void)
{
	static int ScanTime = 3;                           //�˿ڹ���ɨ������3s
	//���ָ����TIM�жϷ�������Ƿ�������
  if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		{
			//RunTime������ʱ��ÿ��15s��ȡ�˿����ݺ�PID����
			if(TSTaskSel == TSNON)
				{
					ScanTime--;
					if(ScanTime == 0)
						{
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
									TSSentDataGeneration(16,TSReadPortsBuffer,SentBuffer);
									DE2=0;
									Usart2SendData(24,(char*)SentBuffer);
								}
							else if(TSTaskSel == SETDATA)
								{
									Usart2SendData(24,(char*)tx2);
								}
							else if(TSTaskSel == START)
								{
									Usart2SendData(24,(char*)tx3);
								}
							else if(TSTaskSel == TSSTOP)
								{
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

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_FLAG_Update);
		ValvePosition = ValveControl(RoomTempSv);
	}
}
