#include "timer.h"

void TimConfigure(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能
	
	TIM_DeInit(TIM4);
	TIM_TimeBaseStructure.TIM_Period = 20; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 
	TIM_TimeBaseStructure.TIM_Prescaler =7199; //设置用来作为TIMx时钟频率除数的预分频值  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_ClearFlag(TIM4,TIM_IT_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);    //使能或者失能指定的TIM中断//TIM2 //使能
	TIM_Cmd(TIM4, ENABLE);             //使能定时器中断
}
