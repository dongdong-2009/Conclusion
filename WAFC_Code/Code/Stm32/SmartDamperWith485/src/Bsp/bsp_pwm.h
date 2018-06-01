#ifndef __BSP_PWM_H
#define __BSP_PWM_H

#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

void PWM_Init(void);
void PWM_Gen(u16 pwm_us); // pluse width in us, pwm = 1000 for 1ms pulse

#endif
