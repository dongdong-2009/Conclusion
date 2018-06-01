#include "stm32f10x_it.h"
#include "Globle.h"
#include "modbus.h"

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}


void TIM2_IRQHandler(void)   //TIM2�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		   TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ 
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
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE))
	{
		USART_ClearITPendingBit(USART1, USART_FLAG_ORE);//�����Ӧ�ı�־λ
	}
	
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
		if(BusyFlag)return;
		
		TIM_Cmd(TIM2, DISABLE);  //�رն�ʱ��
		TIM_SetCounter(TIM2,0);//�����ʱ
		
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
		 DE1=1;		 //���ڴ��ڽ���״̬
		 USART_ITConfig(USART1,USART_IT_TXE,DISABLE);			  	//������� �ر��ж�
	 }	 
  }
	TIM_Cmd(TIM2, ENABLE);  //�رն�ʱ��
}
