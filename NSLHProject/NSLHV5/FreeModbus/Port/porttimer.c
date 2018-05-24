/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: porttimer.c,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- static functions ---------------------------------*/
static void prvvTIMERExpiredISR( void );

/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortTimersInit( USHORT usTim1Timerout50us )
{
		uint16_t PrescalerValue = 0;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
		
		//定时器时间基配置说明
		//HCLK为72MHZ(硬件自动倍频，达到最大)
		//TIM1的分频系数为3599，时间基频率为72/(1+Prescaler)=20kz,基准为50us
		//TIM1最大计数值为usTim1Timerout50us
		PrescalerValue = (uint16_t) (SystemCoreClock / 20000) - 1; 
	
		TIM_DeInit(TIM1);                    					                    // 复位TIMx定时器 
		TIM_TimeBaseStructure.TIM_Period = (uint16_t) usTim1Timerout50us; // 每T秒更新一次子程序 T5<30
		TIM_TimeBaseStructure.TIM_Prescaler =PrescalerValue;              // 分频36000       
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;           // 时钟分频  
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;       // 计数方向向上计数
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                  // 重复计数  
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
		TIM_ARRPreloadConfig(TIM1, ENABLE);                               //预装载使能
	
		TIM_ClearFlag(TIM1, TIM_IT_Update); 
		TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);                         //关闭TIM1中断源 
		TIM_Cmd(TIM1, DISABLE);                                             //禁止定时器1
	
	
		NVIC_InitTypeDef NVIC_InitStructure;
	
		//设置中断向量表位置和偏移量  
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);    //向量表位于FLASH，向量表基地址的偏移量为0 
	
		//设置优先级分组：先占优先级和从优先级。
		//输入参数：优先级分组位长度
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  //先占优先级4位，从优先级0位
	
		NVIC_InitStructure.NVIC_IRQChannel =TIM1_UP_IRQn;          //TIM1中断   
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级3	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
		NVIC_Init(&NVIC_InitStructure);
    
		return TRUE;
}


inline void
vMBPortTimersEnable(  )
{
    /* Enable the timer with the timeout passed to xMBPortTimersInit( ) */
	  TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
		//设定定时器的初始值
		TIM_SetCounter(TIM1,0x0000);
		TIM_Cmd(TIM1, ENABLE);
}

inline void
vMBPortTimersDisable(  )
{
    /* Disable any pending timers. */
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);
		//设定定时器的初始值
		TIM_SetCounter(TIM1,0x0000);
		TIM_Cmd(TIM1, DISABLE);
}

/* Create an ISR which is called whenever the timer has expired. This function
 * must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
 * the timer has expired.
 */
static void prvvTIMERExpiredISR( void )
{
    ( void )pxMBPortCBTimerExpired(  );
}

void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
	{
		 TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		 prvvTIMERExpiredISR( );
	}
}
