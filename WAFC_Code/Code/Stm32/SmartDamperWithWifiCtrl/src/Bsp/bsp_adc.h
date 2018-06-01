#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_adc.h"
#include "core_cm3.h"
#include "misc.h"
#include "stm32f10x_dma.h"
#include "bsp_systimer.h"
#include "bsp_hwConfig.h"

#define ADC_BUF_SIZE 50

void Current_ADC_Init(void);
void DMA1_Channel1_IRQHandler(void);
HDTimer Get_ADC_Refresh_Time(void);

#endif


