#ifndef __OLED_H
#define __OLED_H
#include "stdio.h"
#include "bsp_hwConfig.h"

#define OLED_DC		PA_out(8)	// PA8
#define OLED_SCL	PC_out(7)	// PC7
#define OLED_RST	PC_out(9)	// PC9	
#define OLED_SDA	PC_out(8)	// PC8	

void OLED_Init(void);//initialization
void OLED_P6x8Str(unsigned char x,unsigned char y, char ch[]);
void OLED_Fill(unsigned char dat);

void Disp_Char(unsigned char y,unsigned char x,unsigned char asc);
void Disp_Num(unsigned char y, unsigned char x, unsigned int num,unsigned char N);

#endif

