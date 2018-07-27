#ifndef __MCP3208_H
#define __MCP3208_H

#include "stm32f10x_gpio.h"
#include <stdio.h>  
#include <math.h>


#define mcp3208_clk1   GPIO_Pin_0 
#define mcp3208_clk2   GPIO_Pin_0

#define mcp3208_Dout1  GPIO_Pin_2
#define mcp3208_Dout2  GPIO_Pin_1

#define mcp3208_Din1   GPIO_Pin_1
#define mcp3208_Din2   GPIO_Pin_2

#define mcp3208_cs1	   GPIO_Pin_3
#define mcp3208_cs2	   GPIO_Pin_3

#define POWER_PT   2.4865

extern void delay_ms(u16 nms);
void ADCRcc_Configuration(void);
void ADCGPIO_Configuration(void);
void mcp3208_Configuration(void);
u16 mcp3208_chanOne(u8 channel);
u16 mcp3208_chanTwo(u8 channel);
u16 mcp3208_adc(u8 port);
float readSenor(u8 port,float range);
float chanvalue12(float volt);
float chanvalue13(float volt);
float chanvalue14(float volt);
float chanvalue15(float volt);
float readTemp(u8 port);
void APortCIn(float aarr[16],float range[12]);
float APortIn(u8 port, float range);
#endif
