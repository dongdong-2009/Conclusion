#include "stm32f10x_it.h"
#include "Globle.h"
#include "stm32f10x_tim.h"
#include "modbus.h"
#include "usart.h"

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
				Uart1_RCnt=8;
				DealModBus();                 //modbus����
				Uart1_RCnt=0;
				BusyFlag=0;
			}
	}
}

void USART1_IRQHandler(void)
{
	//�жϴ����Ƿ���ָ���жϣ��Ƿ�����������ж�
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE))
		{
			USART_ClearITPendingBit(USART1, USART_FLAG_ORE);//�����Ӧ�ı�־λ
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
	 if(Uart1_SCnt<Uart1_SendBuffSize)
	 {
	 	USART_SendData(USART1,Uart1_Send_buffer[Uart1_SCnt++]);
	 }
	 else
	 {
		Uart1_SCnt=0;
		delay_ms(5);
		DE1=1;
		 
		USART_ITConfig(USART1,USART_IT_TXE,DISABLE);			  	//������� �ر��ж�
	 }	 
  }
	TIM_Cmd(TIM1, ENABLE);  //�رն�ʱ��
	
}

void TIM2_IRQHandler(void)
{
	//���ָ����TIM�жϷ�������Ƿ�������
  if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		{
			TSDataProcess();	
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
		USART_ITConfig(USART2,USART_IT_TXE,DISABLE);			  	//������� �ر��ж�
  }
	
}


