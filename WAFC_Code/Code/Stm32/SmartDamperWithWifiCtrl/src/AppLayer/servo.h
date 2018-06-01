#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#include "bsp_systimer.h"
#include "bsp_pwm.h"
#include "bsp_adc.h"
#include "modbus_app.h"

#define SERVO_DIR_INC 0x01
#define SERVO_DIR_DEC 0x00

#define MA_OUTPUT_CLK_MS 20
#define SERVO_STEP_CLK_MS 500
#define MA_BLOCK_THRESHOLD 1000
#define IN_RANGE(x,lb,ub) (((lb) <= (x)) && ((x) <= (ub)))
#define ANGLE_MAX 90.0
#define ANGLE_MIN 0.0
#define ANGLE_RANGE 90.0

void Servo_Init(void);
void Servo_Position(float angle);
float Servo_mA_Mean(void);
void Servo_Task(void);

#endif

