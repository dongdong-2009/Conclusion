#ifndef __LED_H
#define __LED_H	 

#include "stm32f10x.h"

#define LED_RED(n)		GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)n)
#define LED_ON(n)	GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)n)

void LED_Init(void);		//≥ı ºªØ
		 				    
#endif
