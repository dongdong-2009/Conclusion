#ifndef _AD_H
#define _AD_H
#include "stm32f10x.h"
void ADC1_GPIO_Config(void);
void ADC1_Mode_Config(void);
float ReadAdOfChannel(u8 ch,u8 mode);
void ADC_allchannels(float *adc_value,char* flag);

#endif



