#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>

void Delay_MS(u16 dly);
void delay_us(u16 dly);
void USART1_Configuration(void);
unsigned long Read_HX711(void);
void GPIO_Configuration(void);
void  RCC_Configuration(void);
void NVIC_Configuration(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif /* __USART1_H */
