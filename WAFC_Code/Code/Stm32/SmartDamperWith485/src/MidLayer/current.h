#ifndef __CURRENT_H
#define __CURRENT_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_adc.h"
#include "misc.h"
#include "stm32f10x_dma.h"
#include "adc.h"

void Servo_mA_Init(void);
float mA_Mean(void);

#endif
