#ifndef __OLED_H
#define __OLED_H
#include "io.h"
#include "stdio.h"

//#define OLED_SCL	PA_out(8)	// PA8
//#define OLED_DC		PCout(7)	// PC7	
//#define OLED_RST	PCout(8)	// PC8	
//#define OLED_SDA	PCout(9)	// PC9	

#define OLED_DC		PA_out(8)	// PA8
#define OLED_SCL	PCout(7)	// PC7
#define OLED_RST	PCout(9)	// PC9	
#define OLED_SDA	PCout(8)	// PC8	

void OLED_Init(void);//initialization
void OLED_P6x8Str(unsigned char x,unsigned char y, char ch[]);
void OLED_Fill(unsigned char dat);
void Disp_Char(unsigned char y,unsigned char x,unsigned char asc);
void Disp_Num(unsigned char y, unsigned char x, unsigned int num,unsigned char N);

#endif

