#ifndef _GPSGPRS_IO_H
#define _GPSGPRS_IO_H

/*----------------------------extern functions---------------------*/
void BSP_GPIO_Init(void);
void BSP_GPIO_SetOut(uint32_t ,uint32_t);

#define GPIO_ALL				0x03
#define GPIO_LED1				0x01
#define GPIO_LED2				0x02

#endif
/*----------------------end of file----------------------*/

