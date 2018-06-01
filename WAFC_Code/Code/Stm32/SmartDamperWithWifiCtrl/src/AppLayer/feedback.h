#ifndef __FEEDBACK_H
#define __FEEDBACK_H			    

#include "bsp_systimer.h"
#include "modbus_app.h"

#define FEEDBACK_DEFAULT_MS 1000

void Feedback_Init(void);
void Feedback_Task(void);

#endif
