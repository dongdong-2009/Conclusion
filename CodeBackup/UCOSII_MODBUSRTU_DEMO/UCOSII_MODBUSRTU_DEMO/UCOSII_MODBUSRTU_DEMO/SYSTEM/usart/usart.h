#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

void uart_init(u32 bound);
void USART_SendString(u8 *str,u8 len);
#endif


