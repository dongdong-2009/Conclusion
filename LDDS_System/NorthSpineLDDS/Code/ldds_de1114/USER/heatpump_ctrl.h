#ifndef __HEATPUMP_CTRL_H
#define __HEATPUMP_CTRL_H

#include "stm32f10_timer.h"
#include "stm32f10_gpio.h"
#include "stm32f10x.h"


 
#define EEVSTART         6
#define DIRECTION        5
#define OUTPULSE         4

#define EEV_FUll_STEP    250
#define EEV_REF_STEP     200




void EEV_initial(void);
void EEV_close(void);
void EEV_Ajust(u8 eevStep,u8 direction);

// direction open:1  close:0;

#endif
