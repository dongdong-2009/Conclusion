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
#include "stm32f10x_usart.h"
#include "delay.h"
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


u8 nCount;
u8 mCount;
u8 UIreceivedCount = 0;
u8 receivedCount = 0;
u8 receiveFlag=0 ;
u8 UIreceiveFlag=0 ;
u16 SumRec=0;//接收到的校验和
u16 SumCal=0;//计算的校验和
//char ReadPortsBuffer[132]={0};
//char WritePortsBuffer[104]={0};
//char ReadPIDBuffer[96]={0};
//char WritePIDBuffer[97]={0};

unsigned int timercnt=0;

u8  ReceivedBuffer[24]={0};
u8  ReceivedBufTemp[24]={0};
u8  SentBuffer[24]={0};
u8   num=0;
u8 format=0;

void  Usart_SendChar(char dat);
//void  UsartSendData(int num,char* sendbuffer);

unsigned int  ReceivedNum = 0  ;

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


void TIM2_IRQHandler(void)
{
				 
  if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  { 
   	 TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update); 
	   DataProcess();

  }	    	   

   
}

/*定时器4中断处理，clean the receive buffer*/
void TIM4_IRQHandler(void)
{     
   u8 i;
   if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
   {
      TIM_ClearITPendingBit(TIM4,TIM_FLAG_Update); 
	  
	  mCount++;
	  if(mCount==0x25)			  //22
	  {
	     mCount=0;
	     for(i=0;i<24;i++)
		 {
		    ReceivedBufTemp[i]=0x00; 
		 }
         num=0;  		
         TIM_ITConfig(TIM4, TIM_IT_Update, DISABLE); 
	  }		
   }
}

void USART1_IRQHandler(void)
{ 
     u8 i=0,isTrue=0;

    if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)
    {
        USART_ClearFlag(USART1,USART_FLAG_ORE); //读SR其实就是清除标志
        USART_ReceiveData(USART1);		
    }

    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
    {
        ReceivedBufTemp[num]=USART_ReceiveData(USART1);
        num++;
        
		if(num==1)
        {
            TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
        }
		 USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }     
    if(num==24)
    {
        num=0;
        format=1;
        if((ReceivedBufTemp[0]!=0x55)||(ReceivedBufTemp[2]!=0x08)||(ReceivedBufTemp[23]!=0x55))
            format=0;

		if(format==1)
	        isTrue =  CheckReceivedData(ReceivedBufTemp);

        if(format&isTrue)
        {
            for(i=0;i<24;i++) 
                ReceivedBuffer[i]=ReceivedBufTemp[i];
		     	SendProcess();
				num=0;
				isTrue=0;
        }
		else
		num=0;

}
       DE1=1;
	   USART_ITConfig(USART1,USART_IT_TXE,DISABLE);			  	//发送完成 关闭中断


}
void Usart_SendChar(char dat)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//等待上一个字节发送完毕
    USART_SendData(USART1,dat);   
}

void EXTI15_10_IRQHandler(void)
{

}
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
