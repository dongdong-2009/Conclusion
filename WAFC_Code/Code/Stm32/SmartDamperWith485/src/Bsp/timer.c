#include "timer.h"

/************************************************
函数名称 ： TIMER_Initializes
功    能 ： TIMER初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMER_Initializes(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  /* TIM4时基单元配置 */
  TIM_TimeBaseStructure.TIM_Prescaler = TIM4_PRESCALER_VALUE;        //预分频值
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        //向上计数模式
  TIM_TimeBaseStructure.TIM_Period = TIM4_PERIOD_TIMING;             //定时周期(自动从装载寄存器ARR的值)
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            //时钟分频因子
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* 使能预分频值 */
  TIM_ARRPreloadConfig(TIM4, ENABLE);                                //使能重载值TIM4_PRESCALER_VALUE
}

/************************************************
函数名称 ： TIMDelay_N10us
功    能 ： 定时器延时N个10us
参    数 ： Times --- N值
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMDelay_N10us(uint16_t Times)
{
  TIM4->CR1 |= TIM_CR1_CEN;                                          //启动定时器
  while(Times--)
  {
    while((TIM4->SR & TIM_FLAG_Update) == RESET);
    TIM4->SR &= ~TIM_FLAG_Update;                                    //清除标志
  }
  TIM4->CR1 &= ~TIM_CR1_CEN;                                         //关闭定时器
}

/************************************************
函数名称 ： TIMDelay_Nms
功    能 ： 定时器延时Nms
参    数 ： Times --- N值
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMDelay_Nms(uint16_t Times)
{
  while(Times--)
  {
    TIMDelay_N10us(100);
  }
}
