#ifndef _TIMER_H
#define _TIMER_H

#include "stm32f10x.h"


/* 宏定义 --------------------------------------------------------------------*/
#define TIM4_COUNTER_CLOCK        1000000                  //计数时钟(1M次/秒)
                                                           //预分频值
#define TIM4_PRESCALER_VALUE      (72000000/1000000 - 1)
#define TIM4_PERIOD_TIMING        (10 - 1)                 //定时周期（相对于计数时钟:1周期 = 1计数时钟）

/* 函数申明 ------------------------------------------------------------------*/
void TIMER_Initializes(void);
void TIMDelay_N10us(uint16_t Times);
void TIMDelay_Nms(uint16_t Times);


#endif /* _TIMER_H */
