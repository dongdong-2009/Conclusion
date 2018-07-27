/*
* gpio.h
*
*  Created on: 2013-4-20
*      Author: zjm
*/

#ifndef GPIO_H_
#define GPIO_H_

#include "api.h"

#define IO_LED1 1  
#define IO_LED2 2

#define IO_1_BIT  BIT1
#define IO_1_POUT P2OUT

#define IO_2_BIT  BIT2
#define IO_2_POUT P2OUT





#define _IO_PIN(B)  IO_##B##_PIN
#define _IO_POUT(B) IO_##B##_POUT
#define _IO_BIT(B)  IO_##B##_BIT

#define _SET_IO(V)     _IO_POUT(V) |= _IO_BIT(V)
#define _CLR_IO(V)     _IO_POUT(V) &= ~_IO_BIT(V)

#define IO_TOGGLE(V)  _IO_POUT(V) ^= _IO_BIT(V)
#define IO_GET(V)     ((_IO_PIN(V) & _IO_BIT(V))?1:0)
#define IO_SET(B,V)   ((V == 1)?(_SET_IO(B)):(_CLR_IO(B)))

typedef struct
{
    volatile unsigned char *POUT;
    unsigned int        pin;
} GPIO_PORT_OUT;
typedef struct
{
    volatile READ_ONLY unsigned char *PIN;
    unsigned int        pin;
} GPIO_PORT_IN;

void GpioInit(void);

#endif /* GPIO_H_ */
