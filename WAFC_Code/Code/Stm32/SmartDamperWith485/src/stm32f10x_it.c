/**
  ******************************************************************************
  * @file    USART/Interrupt/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
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
#include "CO2.h"
#include "stm32f10x_tim.h"
#include "usart.h"
#include "modbus.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_Interrupt
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
  * @brief  This function handles PendSV_Handler exception.
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
//void SysTick_Handler(void)
//{
//;
//}

void TIM2_IRQHandler(void) // for CO2 PWM capture
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
	else if (TIM_GetITStatus(TIM2,TIM_IT_CC1) == SET)
	{
		CO2_IC1_Buf[CO2BufIdx] = TIM_GetCapture1(TIM2);  //frequency value
		CO2_IC2_Buf[CO2BufIdx] = TIM_GetCapture2(TIM2);  //duty cycle value
		CO2BufIdx++;
		if (CO2BufIdx >= CO2_BUF_SIZE) CO2BufIdx=0;
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
	}
}

void TIM3_IRQHandler(void) // for servo PWM generate
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
	else if (TIM_GetITStatus(TIM3,TIM_IT_CC1) == SET)
	{
		//TIM_SetCompare1(TIM3,1500);
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);		
	}
	TIM_ITConfig(TIM3, TIM_IT_CC1, DISABLE);
}

void USART1_IRQHandler(void)
{ 
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE))
	{
		USART_ClearITPendingBit(USART1, USART_FLAG_ORE);//清除相应的标志位
	}
	
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
		if(BusyFlag)return;
		
		TIM_Cmd(TIM4, DISABLE);  //关闭定时器
		TIM_SetCounter(TIM4,0);//清除计时
		
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
		 DE1=0;		 
		 USART_ITConfig(USART1,USART_IT_TXE,DISABLE);			  	//发送完成 关闭中断
	 }	 
  }
	TIM_Cmd(TIM4, ENABLE);  //关闭定时器
}

void TIM4_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		   TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源 
			 TimerOverFlag=1;
			 if(BegainRxFlag==1)
			 {
				 BegainRxFlag=0;
				 BusyFlag=1;
				 //Uart1_RCnt=8;
				 DealModBus();                 //modbus处理
				 Uart1_RCnt=0;
				 BusyFlag=0;
			 }
		}
}



/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
