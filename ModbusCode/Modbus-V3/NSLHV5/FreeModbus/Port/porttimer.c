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
		
		//��ʱ��ʱ�������˵��
		//HCLKΪ72MHZ(Ӳ���Զ���Ƶ���ﵽ���)
		//TIM1�ķ�Ƶϵ��Ϊ3599��ʱ���Ƶ��Ϊ72/(1+Prescaler)=20kz,��׼Ϊ50us
		//TIM1������ֵΪusTim1Timerout50us
		PrescalerValue = (uint16_t) (SystemCoreClock / 20000) - 1; 
	
		TIM_DeInit(TIM1);                    					                    // ��λTIMx��ʱ�� 
		TIM_TimeBaseStructure.TIM_Period = (uint16_t) usTim1Timerout50us; // ÿT�����һ���ӳ��� T5<30
		TIM_TimeBaseStructure.TIM_Prescaler =PrescalerValue;              // ��Ƶ36000       
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;           // ʱ�ӷ�Ƶ  
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;       // �����������ϼ���
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                  // �ظ�����  
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
		TIM_ARRPreloadConfig(TIM1, ENABLE);                               //Ԥװ��ʹ��
	
		TIM_ClearFlag(TIM1, TIM_IT_Update); 
		TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);                         //�ر�TIM1�ж�Դ 
		TIM_Cmd(TIM1, DISABLE);                                             //��ֹ��ʱ��1
	
	
		NVIC_InitTypeDef NVIC_InitStructure;
	
		//�����ж�������λ�ú�ƫ����  
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);    //������λ��FLASH�����������ַ��ƫ����Ϊ0 
	
		//�������ȼ����飺��ռ���ȼ��ʹ����ȼ���
		//������������ȼ�����λ����
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  //��ռ���ȼ�4λ�������ȼ�0λ
	
		NVIC_InitStructure.NVIC_IRQChannel =TIM1_UP_IRQn;          //TIM1�ж�   
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�3	
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
		//�趨��ʱ���ĳ�ʼֵ
		TIM_SetCounter(TIM1,0x0000);
		TIM_Cmd(TIM1, ENABLE);
}

inline void
vMBPortTimersDisable(  )
{
    /* Disable any pending timers. */
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);
		//�趨��ʱ���ĳ�ʼֵ
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
