#include "bsp_pwm.h"

void PWM_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	TIM_DeInit(TIM3);
	
	//周期20ms 频率50Hz    0.02s
	TIM_TimeBaseStructure.TIM_Period = 19999;
	TIM_TimeBaseStructure.TIM_Prescaler = 72;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_OCStructInit(&TIM_OCInitStructure);      //恢复初始
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //PWM模式1
	TIM_OCInitStructure.TIM_Pulse =0;             //脉冲值，即输出都是低电平
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //极性为高
	
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);   //预载使能
	TIM_ARRPreloadConfig(TIM3,ENABLE);                   //使能TIM3在ARR上的预装载寄存器
	
	TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	TIM_CtrlPWMOutputs(TIM3, ENABLE);
}

void PWM_Gen(u16 pwm_us)
{
	TIM_SetCompare1(TIM3,pwm_us);
}

