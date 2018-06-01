#ifndef _USART_H
#define _USART_H

#include "stdio.h"	
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "io.h"

extern uint8_t Uart1_SCnt;
extern uint8_t Uart1_Send_buffer[150];
extern uint8_t Uart1_receive_buffer[150];
extern uint8_t Uart1_RCnt;
extern uint8_t Uart1_SendBuffSize;

#define DE1 PB_out(14)

void UsartConfigure(void);
void delay_nms(u16 time);
void zh_USART_SendData(u8 ch);
void zh_USART_SendString(u8* s,u8 len);

#endif
