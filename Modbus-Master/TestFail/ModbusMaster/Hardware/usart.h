#ifndef _USART_H
#define _USART_H

#include "Globle.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"

void UsartConfigure(void);
char Usart_GetChar(USART_TypeDef* USARTx);
void Usart_SendChar(char dat);
void UsartSendData(uint8_t num,char* sendbuffer);

#endif
