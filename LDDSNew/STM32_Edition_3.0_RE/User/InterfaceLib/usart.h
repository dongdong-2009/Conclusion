#ifndef _USART_H
#define _USART_H
#include <stdio.h>
#include "stm32f10x.h"

void Usart_Initi(void);
void Uart_Initi(void);

void  Usart_SendChar(char dat);
char  Usart_GetChar(USART_TypeDef* USARTx);
void  UsartSendData(int num,char* sendbuffer);
void  UartSendData(int num,char* sendbuffer) ;
void  Uart_SendChar(char dat);

void  TurnOnUart4(void);
void  TurnOffUart4(void);

void  TurnOnUsart(void);
void  TurnOffUsart(void);

#endif
