#ifndef __24LC512_H
#define __24LC512_H

#include "myiic.h"

#define Page_Byte   128
#define Max_Addr    0xffff

#define LC512_Write_Addr  0xA0           //10100000 Ð´²Ù×÷
#define LC512_Read_Addr   0xA1           //10100001 ¶Á²Ù×÷

void LC512_WriteByte(u16 addr,u8 data);
u8 LC512_ReadByte(u16 addr);
void LC512_Write(u8 *buffer, u16 addr,u16 length);
void LC512_Read(u8 *buffer, u16 addr,u16 length);
void LC512_Clear(void);

#endif
