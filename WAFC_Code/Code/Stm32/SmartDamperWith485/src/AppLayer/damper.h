/*
damper levels  
*/
#ifndef __DAMPER_H
#define __DAMPER_H

#include "bsp_systimer.h"
#include "modbus_app.h"
#include "servo.h"

#define DAMPER_CLK_MS 500
#define DAMPER_STEP_ANGLE 5.0

void Damper_Init(void);
void Damper_Task(void);

#endif
