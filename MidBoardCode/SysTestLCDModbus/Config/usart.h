#ifndef _USART_H
#define _USART_H

#include "Globle.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"

void UsartConfigure(void);
void delay_nms(u16 time);
void zh_USART_SendData(u8 ch);
void zh_USART_SendString(u8* s,u8 len);
char Usart_GetChar(USART_TypeDef* USARTx);
void Usart_SendChar(char dat);
void UsartSendData(int num,char* sendbuffer);

#endif
