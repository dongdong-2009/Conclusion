


#ifndef  UTILITIES_H
#define  UTILITIES_H
#include "stdint.h"

#define ABS(a) ((a) < 0 ? -(a) : a)


void 
__gie_disable(void);
void 
__gie_enable(void); 
int 
uint2string(char *p_buf, unsigned long uint_16);
int 
ulong2string8ch(char *p_buf, unsigned long ulong_32);
int 
ulong2string10ch(char *p_buf, unsigned long ulong_32);
unsigned int 
charToUint(char*p_string, unsigned int cont);
unsigned int // 计算校验码 ps:字符串，pd: 返回校验码，占用2字节，n: 字符串长度
clc_CRC(unsigned char *ps, unsigned char *pd, unsigned char n);

unsigned int iabs(int value);
unsigned long sqrt32(register unsigned long h);
unsigned long sqrt64(register unsigned long long h);
int my_atoi(const char *pch, int len);
int my_itoa(char *pch, int value, int len);
int INT2BCD(uint32_t in,uint8_t *out);
uint32_t BCD2INT(uint8_t *bcd, int num) ;
int FLOAT2BCD(float val,int integer,int decimal,uint8_t *bcd);
float BCD2FLOAT(uint8_t *bcd, int num);
char calcFCS(char *msg, int len);
uint8_t ChkSum(uint8_t *in, int num);
#define BIN2BCD(val)    ((((val)/10)<<4) + (val)%10)
#define BCD2BIN(val)    (((val)&15) + ((val)>>4)*10)

#endif
