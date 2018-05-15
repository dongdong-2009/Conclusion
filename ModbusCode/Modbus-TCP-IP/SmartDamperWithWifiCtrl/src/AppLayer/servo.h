#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

extern u16 PWMvalue;
extern u16 ADCdata;
extern u16 ADCBuff;

void Servo_Init(void);
void Tim3_Sartt(void);

void Servo_Pos(float angle, u16 PWM_0, u16 PWM_C);

void CurrentConfig(void);

#endif

