#ifndef __PITOT_H
#define __PITOT_H			    
#include "bsp_systimer.h"
#include "diff_pressure.h"
#include "math.h"

#define PITOT_CLK_MS 500

void Pitot_Init(void);
void Pitot_Task(void);

#endif
