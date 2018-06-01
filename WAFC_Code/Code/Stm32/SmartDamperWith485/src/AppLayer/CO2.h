#ifndef __CO2_H
#define __CO2_H

#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#define CO2_BUF_SIZE 50

extern u8 CO2BufIdx;
extern u16 CO2_IC1_Buf[CO2_BUF_SIZE];
extern u16 CO2_IC2_Buf[CO2_BUF_SIZE];

void CO2_Init(void);
u16 _PWM2PPM(u16 TH, u16 TT);
u16 CO2PPM(void);

#endif
