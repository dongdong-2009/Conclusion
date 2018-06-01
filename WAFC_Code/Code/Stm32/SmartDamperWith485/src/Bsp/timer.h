#ifndef _TIMER_H
#define _TIMER_H

#include "stm32f10x.h"


/* �궨�� --------------------------------------------------------------------*/
#define TIM4_COUNTER_CLOCK        1000000                  //����ʱ��(1M��/��)
                                                           //Ԥ��Ƶֵ
#define TIM4_PRESCALER_VALUE      (72000000/1000000 - 1)
#define TIM4_PERIOD_TIMING        (10 - 1)                 //��ʱ���ڣ�����ڼ���ʱ��:1���� = 1����ʱ�ӣ�

/* �������� ------------------------------------------------------------------*/
void TIMER_Initializes(void);
void TIMDelay_N10us(uint16_t Times);
void TIMDelay_Nms(uint16_t Times);


#endif /* _TIMER_H */
