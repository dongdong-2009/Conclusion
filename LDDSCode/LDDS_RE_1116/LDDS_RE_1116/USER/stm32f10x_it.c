/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "logic.h"
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

//num---format---address---pattern---autom     ����53���ֽ�����
//autom---automanual,��������״̬�����Զ����ͣ������ֶ����� 
//��ʼ��
frame frm=
{
	0x00,
  0x00,
  0x00,
  0x00,
  0x00   
};

//num---format---pattern         ����24���ֽ�����
//��ʼ��
disframe disfrm=
{
	0x00,
  0x00,
  0x00
};

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
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

//��ʱ��1����ʱ���USART1������
void TIM1_UP_IRQHandler(void)
{
	u8 i;
  if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)    //�ж϶�ʱ��1�ж��Ƿ���
  {
		TIM_ClearITPendingBit(TIM1,TIM_FLAG_Update); 	   //����жϴ�����λ
	  nCount++;
	  if(nCount==0x17)                                 //��ʱʱ��                 
	  {
			nCount=0;
	    for(i=0;i<53;i++)                              //���USART1�л���������
			{
				usart1_buff[i]=0x00; 
			}
			frm.num=0;
			TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);    //�رն�ʱ��1�ж�
	  }		
  }  
}

//��ʱ��2����ʱ���USART2������
/*��ʱ��2�жϴ���*/
void TIM2_IRQHandler(void)
{
	u8 i;
  if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)         //�ж϶�ʱ��2�ж��Ƿ���
  {
		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);          //�����ʱ��2�ж�����λ
	  mCount++;
	  if(mCount==0x50)                                      //��ʱʱ�����
	  {
			mCount=0;
	    for(i=0;i<24;i++)                                   //���USART2������
			{
				usart2_buff[i]=0x00; 
			}
      disfrm.num=0;  		
      TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);        //��ֹ��ʱ��2�ж�ʹ��
	  }	 
  }
}


/*��ʱ��3�жϴ�����Ҫ�����ڽ�������*/
void TIM3_IRQHandler(void)
{     
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)      //�ж϶�ʱ��3�ж��Ƿ���
  {
		TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);       //�����ʱ��3�ж�����λ
		dataProcess();                                     //������ݴ���
		dataResponseLocal();                               //С�����ݴ���
		//concentration=ConCalculate();
  }  
}

/*����1�жϴ���*/
void USART1_IRQHandler(void)
{
	u8 i;
	
  if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)         //���USART��������־λ
  {
		USART_ClearFlag(USART1,USART_FLAG_ORE);                   //��SR��ʵ���������־   ���USART�������жϱ�־λ�������������־λ
    USART_ReceiveData(USART1);                                //����USART1������յ�������    
  }
	
  if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)          //���USART�������ݼĴ����ǿձ�־λ
  {
		usart1_buff[frm.num]=USART_ReceiveData(USART1);           //��USART�����ݴ���ڻ�����
    frm.num++;
    if(frm.num==1)
    {
			TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);              //ʹ�ܶ�ʱ��1�жϣ���մ���1����������     
    }
    USART_ClearITPendingBit(USART1,USART_IT_RXNE);            //��������жϱ�־λ
  }
	
	//���յ�����������
  if(frm.num==53)
  {
		frm.num=0;
    frm.format=1;
		
		//֡ͷ��֡β
    if((usart1_buff[0]!=0x55)||(usart1_buff[1]!=0x66)||(usart1_buff[51]!=0x66)||(usart1_buff[52]!=0x55))
			frm.format=0;
		
		//��ַ��Ϣ��ȷ
    if((usart1_buff[2]==address1[0])&&(usart1_buff[3]==address1[1])&&(usart1_buff[4]==address1[2])&&(usart1_buff[5]==address1[3])&&(usart1_buff[6]==address1[4])&&(usart1_buff[7]==address1[5]))
			frm.address=1;
	 	else
	    frm.format=0;
		
		//������յ����ݱ�Ϊtransfer data��DE��RE֮������ݽ���
    if(usart1_buff[9]==0x57)
		  frm.pattern=5;  
		else
		  frm.format=0;
		
		//���Local����remote
    if(usart1_buff[49]==0x00)
      frm.autom=0;
	  else if(usart1_buff[49]==0x01)
	    frm.autom=1;
	  else
	    frm.format=0; 
		
		//������ȷ��Ϊtransfer data 
    if(frm.format)
    {
			if(frm.pattern==5)
	    {
				if(frm.address==1)
				{
					for(i=0;i<53;i++) 
	        dataCbuff[i]=usart1_buff[i];     //�����ڻ��������� ת�浽dataCbuff��
				}
		  }
     }
				 
		 //������ȷ������LOCALģʽ
    if(frm.format&&(!frm.autom))
    {
			Usart_Tx();                    //ʹ�����ݷ���λ
      usart_senddata(TX9);           //��������TX9
      Usart_Rx();                    //ʹ�����ݽ���λ��ʹ����ʱ�̴��ڽ���״̬
    }
  }
	//SendInformation();
}

/*����1��������*/
void usart_senddata(u8 arr[])
{	
	u8 i;
  for(i=0;i<53;i++)
	{
		USART_ClearFlag(USART1,USART_FLAG_TC);                        //������ݷ�����ɱ�־λ
	  USART_SendData(USART1,arr[i]);                                //��������
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	}
}

/*����2�жϴ���*/
void USART2_IRQHandler(void)
{
	u8 i;
  if(USART_GetFlagStatus(USART2,USART_FLAG_ORE)==SET)                   //���USART��������־λ      
  {
		USART_ClearFlag(USART2,USART_FLAG_ORE);                             //��SR��ʵ���������־  ���USART��������־λ
    USART_ReceiveData(USART2);		                                      //����2��������
  }
	
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)                    //���ڽ������ݼĴ����ǿձ�־λ
  {
		usart2_buff[disfrm.num]=USART_ReceiveData(USART2);                  //�����ݴ洢�ڴ���2���ݻ�����
    disfrm.num++;
    if(disfrm.num==1)
    {
			TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);                        //ʹ�ܶ�ʱ��2����մ���2���ݻ���
    }
    USART_ClearITPendingBit(USART2,USART_IT_RXNE);                      //�������2�������ݷǿձ�־λ
  }   
	//�����������
  if(disfrm.num==24)
  {
		disfrm.num=0;
    disfrm.format=1;
		
		//֡ͷ��֡β����
    if((usart2_buff[0]!=0x55)||(usart2_buff[1]!=0x66)||(usart2_buff[22]!=0x66)||(usart2_buff[23]!=0x55))
			disfrm.format=0;
		
		//�ж���������
    if(usart2_buff[2]==0x01)
		  disfrm.pattern=1;
		else if(usart2_buff[2]==0x02)
		  disfrm.pattern=2;
		else if(usart2_buff[2]==0x03)
		{ 
			disfrm.pattern=3;
			localControl=1; 		
		}
    else if(usart2_buff[2]==0x04)
		{
			disfrm.pattern=4;
			localControl=0; 
		}
		else
		  disfrm.format=0;
    if(CRC_check(usart2_buff,USTART,USTOP)!=usart2_buff[21])
			disfrm.format=0;
    if(disfrm.format)
		{
			for(i=0;i<24;i++) 
      { 
				dataUbuff[i]=usart2_buff[i];                        //����2����ת��
		  }
		}
		if(disfrm.format)
    {
			Uart_Tx();                                           //ʹ�ܴ������ݷ���λ
      i=disfrm.pattern;
      switch(i)
      {
				//case 1: usart2_senddata(tx1);delay_ms(100);usart2_senddata2(TX1);delay_ms(100);usart2_senddata2(TX2);break;
				case 1: usart2_senddata(tx1);delay_ms(500);usart2_senddata2(TX1);delay_ms(500);usart2_senddata2(TX2);break;            //����С��ʹ������
        case 2: usart2_senddata(tx2);break;
        case 3: usart2_senddata(tx3);break;		            //start
        case 4: usart2_senddata(tx4);break;               //stop      
        default:break;
      }
      Usart_Rx();                                         //ʹ�ܴ������ݽ���λ��ʹ����ʱ�̴��ڽ���װ��
    } 
  }    
}

/*����2��������*/
//����С�����
void usart2_senddata(u8 arr[])
{
	u8 i;
  for(i=0;i<24;i++)
	{
		USART_ClearFlag(USART2,USART_FLAG_TC);
    delay_us(1000);
	  USART_SendData(USART2,arr[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	}
}

//���ʹ�����
void usart2_senddata2(u8 arr[])
{
	u8 i;
  for(i=0;i<53;i++)
	{
		USART_ClearFlag(USART2,USART_FLAG_TC);
    delay_us(1000);
	  USART_SendData(USART2,arr[i]+0x33);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	}
}

//void SendInformation()
//{
//	int Format=1;                        //���ݸ�ʽ
//	int Address=0;                       //���ݵ�ַ
//	
//	//�ж�����֡ͷ֡β
//	if((TX9[0]!=0x55)||(TX9[1]!=0x66)||(TX9[51]!=0x66)||(TX9[52]!=0x55))
//		Format=0;		
//  
//	//�ж����ݵ�ַ��Ϣ
//	if((TX9[2]==address1[0])&&(TX9[3]==address1[1])&&(TX9[4]==address1[2])&&(TX9[5]==address1[3])&&(TX9[6]==address1[4])&&(TX9[7]==address1[5]))
//		Address=1;
//	else
//		Format=0;	
//	
//	if(Format==1)
//	{
//		//����ΪTransfer Data,��RE��DE֮�佻��ͨ�ŵ�����
//		if(TX9[9]==0x57)
//		{
//			if(Address==1)
//			{
//				Usart_Tx();                    //ʹ�����ݷ���λ
//				usart_senddata(TX9);           //��������TX9
//				Usart_Rx();                    //ʹ�����ݽ���λ��ʹ����ʱ�̴��ڽ���״̬				
//			}
//		}
//	}  
//}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
