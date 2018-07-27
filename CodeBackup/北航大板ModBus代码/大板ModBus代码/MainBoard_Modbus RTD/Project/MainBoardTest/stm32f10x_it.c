/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "Globle.h"
#include "stm32f10x_tim.h"
u16 SumRec=0;//���յ���У���
u16 SumCal=0;//�����У���
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

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

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

void USART1_IRQHandler(void)
{ 
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
		 delay_ms(5);
		 DE1=1;
		 
		USART_ITConfig(USART1,USART_IT_TXE,DISABLE);			  	//������� �ر��ж�
	 }	 
  }
	TIM_Cmd(TIM2, ENABLE);  //�رն�ʱ��
}
/*ModBus ����CRC��Ĳ���Ϊ��

(1).Ԥ��16λ�Ĵ���ΪFFFFH���ƴ˼Ĵ���ΪCRC�Ĵ�����

(2).�ѵ�һ��8λ������CRC�Ĵ����ĵ�λ����򣬰ѽ������CRC�Ĵ�����

(3).�ѼĴ�������������һλ(����λ)����0����λ��������λ��

(4).������λΪ0���ظ���3��(�ٴ���λ)������λΪ1��CRC�Ĵ��������ʽA001��1010 0000 0000 0001���������

(5).�ظ�����3��4��ֱ������8�Σ���������8λ����ȫ�������˴���

(6).�ظ�����2������5��������һ��8λ���ݵĴ���

(7).���õ���CRC�Ĵ�����ΪCRC�롣(CRC�� = CRC_L +CRC_H)

*/
/*****************crcУ��**********************************************/

//crc���ɺ���������crc�洢��Ԥ�ȶ��ڵ�������

//���÷�ʽcrc16��ָ�����ݵ�ָ�룬��ҪУ������ݳ��ȣ�
u16 crc16(u8 *ptr,u8 len)
{
	unsigned long wcrc=0XFFFF;//Ԥ��16λcrc�Ĵ�������ֵȫ��Ϊ1
	int i=0,j=0;//�������
	for(i=0;i<len;i++)//ѭ������ÿ������
		{
			wcrc^=*ptr++;//����λ������crc�Ĵ������.ָ���ַ���ӣ�ָ���¸�����
			for(j=0;j<8;j++)//ѭ���������ݵ�
				{
					if(wcrc&0X0001)//�ж����Ƴ����ǲ���1�������1�������ʽ�������
						{
							wcrc=wcrc>>1^0XA001;//�Ƚ���������һλ��������Ķ���ʽ�������
						}
					else//�������1����ֱ���Ƴ�
						{
							wcrc>>=1;//ֱ���Ƴ�
						}
				}
		}
	return wcrc<<8|wcrc>>8;//�Ͱ�λ��ǰ���߰�λ�ں�
}

void delay_nms(u16 time)
{    
	 u16 i=0;  
	 while(time--)
	 {
			i=12000;  //�Լ�����
			while(i--) ;    
	 }
}

void zh_USART_SendData(u8 ch)
{
   
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//�ȴ���һ���ֽڷ������
    USART_SendData(USART1,ch);   
}
//����len���ֽ�
void zh_USART_SendString(u8* s,u8 len)
{
	  
    int i;
    for(i=0;i<len;i++)
    {
        zh_USART_SendData(s[i]);
    }
}

void DealModBus(void)
{
	
	u16 REG0X03[24];//������0x03��Ӧ�ļĴ�����ַΪ0x0001-0x00019  AD12·+RTD4·+DI8·=24
	u16 REG0X06[16];//������0x06��Ӧ�ļĴ�����ַΪ0x0001-0x00010  DA8·+DO8·=16
	u16 DatLength=0;
	u16 StartRegAdd=0;
	u8 i,sendLen;
	if(Uart1_receive_buffer[0]!=modbus_deviceId)  //�˶Ա�����ַ
	{
		return; //��ַ����
	}
	SumCal=crc16(&Uart1_receive_buffer[0],Uart1_RCnt-2);//�����У���
	SumRec=(Uart1_receive_buffer[Uart1_RCnt-2]<<8)+Uart1_receive_buffer[Uart1_RCnt-1];//����Ĭ�Ͻ��յ���У���Ҳ�ǵͰ�λ��ǰ���߰�λ�ں�
	if(SumCal!=SumRec)
	{		
		         //У��ʹ���
		return ;
	}
	
	for(i=0;i<12;i++)            //AD�Ĵ�����ַ����0x0001~0x000C
	{
		REG0X03[i]=AdREG[i];
	}
	for(i=0;i<4;i++)            //RTD�Ĵ�����ַ����0x000D~0x0011
	{
		REG0X03[12+i]=RTDREG[i];
	}
	for(i=0;i<8;i++)            //DI�Ĵ�����ַ����0x00012~0x0019
	{
		REG0X03[16+i]=DiREG[i];
	}
	
	for(i=0;i<8;i++)            //DA�Ĵ�����ַ����0x0001~0x0008
	{
		REG0X06[i]=DAREG[i];
	}
	for(i=0;i<8;i++)            //DO�Ĵ�����ַ����0x0009~0x0010
	{
		REG0X06[8+i]=DoREG[i];
	}
	
	StartRegAdd=Uart1_receive_buffer[2]*256+Uart1_receive_buffer[3];//������ʵ�Ĵ�����ַ
	DatLength=Uart1_receive_buffer[4]*256+Uart1_receive_buffer[5];  //����Ĵ�����ַ����
	 
	
	sendLen=0;
	Uart1_Send_buffer[sendLen++]=modbus_deviceId;
	Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[1];
	
	
	switch(Uart1_receive_buffer[1])     //������
	{
		case 0x03:
							if((StartRegAdd+DatLength)>24)return;
							Uart1_Send_buffer[sendLen++]=DatLength*2;
							for(i=0;i<DatLength;i++)                     //��ȡ�������߶���Ĵ���
							{
								Uart1_Send_buffer[sendLen++]=REG0X03[StartRegAdd+i]>>8;
								Uart1_Send_buffer[sendLen++]=REG0X03[StartRegAdd+i];
							}
			        break;
		case 0x06:						                                //д�����Ĵ���
							if(StartRegAdd>=12)return;
							REG0X06[StartRegAdd]=Uart1_receive_buffer[4]*256+Uart1_receive_buffer[5];
							Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[2];
							Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[3];
							Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[4];
							Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[5];
							break;
		default:                           //��֧�ֵĹ�����
							Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[2];
							Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[3];
							Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[4];
							Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[5];
							Uart1_Send_buffer[1]=0x80;//���������λ��1
							Uart1_Send_buffer[2]=0x01; //�����쳣��Ϊ01-��Ч����
							break; 
	}
	SumCal=crc16(&Uart1_Send_buffer[0],sendLen);//�����У���
	Uart1_Send_buffer[sendLen++]=SumCal>>8;//crc���ֽ�
  Uart1_Send_buffer[sendLen++]=SumCal&0xff;//crc���ֽ�
	
	RS485MOED_S;                              //485���
  zh_USART_SendString(&Uart1_Send_buffer[0],sendLen);//������Ӧ֡
  delay_nms(2);
	RS485MOED_R;                              //485����
	
	for(i=0;i<8;i++)            //DA�Ĵ�����ַ����0x0001~0x0008
	{
		DAREG[i]=REG0X06[i];
	}
	for(i=0;i<8;i++)            //DO�Ĵ�����ַ����0x0009~0x0010
	{
		DoREG[i]=REG0X06[8+i];
	}
	
}
/**
  * @brief  This function handles USART2 global interrupt request.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
   if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
//	 USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//	 if(Uart2_RCnt<SendBuffSize)
//	 {
//		Uart2_receive_buffer[Uart2_RCnt]=USART_ReceiveData(USART2);		//��������
//		Uart2_RCnt++;
//		}
//	else
//			{
//	   	Uart2_RCnt=0;	
//		}
		Uart2_receive_buffer[Uart2_RCnt]=USART_ReceiveData(USART2);		//��������
		switch(Uart2_RCnt)
		{
			case 0:if(Uart2_receive_buffer[Uart2_RCnt]=='H')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 1:if(Uart2_receive_buffer[Uart2_RCnt]=='R')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 2:if(Uart2_receive_buffer[Uart2_RCnt]=='T')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 3:if(Uart2_receive_buffer[Uart2_RCnt]=='O')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 4:if(Uart2_receive_buffer[Uart2_RCnt]=='U')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 5:if(Uart2_receive_buffer[Uart2_RCnt]=='S')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 6:if(Uart2_receive_buffer[Uart2_RCnt]=='A')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 7:if(Uart2_receive_buffer[Uart2_RCnt]=='R')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 8:if(Uart2_receive_buffer[Uart2_RCnt]=='T')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 9:if(Uart2_receive_buffer[Uart2_RCnt]=='2'){Uart2_RCnt=0;Uart4852_TestFlag=1;}
							else Uart2_RCnt=0;break;
			default:break;
		}
  }
  
  if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  { 	 
	 if(Uart2_SCnt<Uart2_SendBuffSize)
	 {
	 	USART_SendData(USART2,Uart2_Send_buffer[Uart2_SCnt++]);
	 }
	 else
	 {
		Uart2_SCnt=0;
		 delay_ms(5);
		 DE2=1;
		USART_ITConfig(USART2,USART_IT_TXE,DISABLE);			  	//������� �ر��ж�
	 }	 
  }
}
void USART3_IRQHandler(void)
{
   if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
//	 USART_ClearITPendingBit(USART3,USART_IT_RXNE);
//	 if(Uart3_RCnt<SendBuffSize)
//	 {
//		Uart3_receive_buffer[Uart3_RCnt]=USART_ReceiveData(USART3);		//��������
//		Uart3_RCnt++;
//	}
//	else
//	{
//	   	Uart3_RCnt=0;	
//	}
		
		Uart3_receive_buffer[Uart3_RCnt]=USART_ReceiveData(USART3);		//��������
		switch(Uart3_RCnt)
		{
			case 0:if(Uart3_receive_buffer[Uart3_RCnt]=='O')Uart3_RCnt++;break;
			case 1:if(Uart3_receive_buffer[Uart3_RCnt]=='K')Wifi_TestFlag=1;Uart3_RCnt=0;break;
			default:break;
		}
  }
  
  if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
  { 	 
	 if(Uart3_SCnt<Uart3_SendBuffSize)
	 {
	 	USART_SendData(USART3,Uart3_Send_buffer[Uart3_SCnt++]);
	 }
	 else
	 {
		Uart3_SCnt=0;
		USART_ITConfig(USART3,USART_IT_TXE,DISABLE);			  	//������� �ر��ж�
	 }	 
  }
}



void TIM2_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		   TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
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

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
