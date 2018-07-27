/******************************************************************
** 文件名: utilities.c
** Copyright (c) 2003- 毛武斌
** 创建人: 毛武斌
** 日 期:
** 修改人:
** 日 期: 2003.7.3
** 
** 版 本: 1.0
*******************************************************************/
#include "api.h"

volatile __istate_t IntStatus; // status of GIE flag
volatile unsigned int IntsDisableCount; // count of performed disables
void __gie_disable(void)
{
  if(IntsDisableCount==0) 
  {
    IntStatus=__get_interrupt_state(); 
    __disable_interrupt();
  }
  IntsDisableCount++;
}
void __gie_enable(void) 
{
  if(IntsDisableCount > 0)
  {
    IntsDisableCount--;
  }
  
  if(IntsDisableCount == 0)
  {
    __enable_interrupt();
  }
}

void soft_delay1ms(unsigned long time)
{
  while (time--)
  {
    __delay_cycles(1000*BSP_CONFIG_CLOCK_MHZ);
  }
}


int uint2string(char *p_buf, unsigned long uint_16)
{
  if(uint_16 > 99999)
    uint_16 = 99999;
  *p_buf++ = '0' + uint_16/10000;
  uint_16 = uint_16%10000;
  *p_buf++ = '0' + uint_16/1000;
  uint_16 = uint_16%1000;
  *p_buf++ = '0' + uint_16/100;
  uint_16 = uint_16%100;
  *p_buf++ = '0' + uint_16/10;
  uint_16 = uint_16%10;
  *p_buf++ = '0' + uint_16;
  *p_buf = 0;
  return 0;
}

int ulong2string8ch(char *p_buf, unsigned long ulong_32)
{
  *p_buf++ = '0' + ulong_32/10000000;
  ulong_32 = ulong_32%10000000;
  *p_buf++ = '0' + ulong_32/1000000;
  ulong_32 = ulong_32%1000000;
  *p_buf++ = '0' + ulong_32/100000;
  ulong_32 = ulong_32%100000;
  *p_buf++ = '0' + ulong_32/10000;
  ulong_32 = ulong_32%10000;
  *p_buf++ = '0' + ulong_32/1000;
  ulong_32 = ulong_32%1000;
  *p_buf++ = '0' + ulong_32/100;
  ulong_32 = ulong_32%100;
  *p_buf++ = '0' + ulong_32/10;
  ulong_32 = ulong_32%10;
  *p_buf++ = '0' + ulong_32;
  *p_buf = 0;
  return 0;
}

int ulong2string10ch(char *p_buf, unsigned long ulong_32)
{
  *p_buf++ = '0' + ulong_32/1000000000;
  ulong_32 = ulong_32%1000000000;
  *p_buf++ = '0' + ulong_32/100000000;
  ulong_32 = ulong_32%100000000;
  *p_buf++ = '0' + ulong_32/10000000;
  ulong_32 = ulong_32%10000000;
  *p_buf++ = '0' + ulong_32/1000000;
  ulong_32 = ulong_32%1000000;
  *p_buf++ = '0' + ulong_32/100000;
  ulong_32 = ulong_32%100000;
  *p_buf++ = '0' + ulong_32/10000;
  ulong_32 = ulong_32%10000;
  *p_buf++ = '0' + ulong_32/1000;
  ulong_32 = ulong_32%1000;
  *p_buf++ = '0' + ulong_32/100;
  ulong_32 = ulong_32%100;
  *p_buf++ = '0' + ulong_32/10;
  ulong_32 = ulong_32%10;
  *p_buf++ = '0' + ulong_32;
  *p_buf = 0;
  return 0;
}

unsigned int charToUint(char*p_string, unsigned int cont)
{
  char s[5];
  unsigned int i;
  for(i=0; i<5; i++)
  {
    s[i]=0;
  }
  for(i=0; i<cont; i++)
  {
    s[4-i]=p_string[4-i] - '0';
  }
  i = 10000*s[0] + 1000*s[1] + 100*s[2] + 10*s[3] + s[4];
  return i;
}

unsigned int
clc_CRC(unsigned char *ps, unsigned char *pd, unsigned char n)
{
  unsigned char tmp = 0;
  unsigned char tmp2;
  while(n--)
  {
    tmp += *ps++;
  }
  tmp2 = tmp >> 4;
  if(tmp2 > 0x09)
  {
    *pd = tmp2 - 0x0A + 'A'; 
  }
  else
  {
    *pd = tmp2 + '0';
  }
  pd++;
  tmp2 = tmp & 0x0f;
  if(tmp2 > 0x09)
  {
    *pd = tmp2 - 0x0A + 'A'; 
  }
  else
  {
    *pd = tmp2 + '0';
  }
  return 0;
}

unsigned int iabs(int value)
{
  unsigned int return_value;
  if(value >= 0)
  {
    return_value = value; 
  }else
  {
    return_value = -value;
  }
  
  return return_value;
}

unsigned long sqrt32(register unsigned long h)
{
	register unsigned long x;
	register unsigned long y;
	register int i;
	
	x =
	y = 0;
	for (i = 0;  i < 32;  i++)
	{
		x = (x << 1) | 1;
		if (y < x)
			x -= 2;
		else
			y -= x;
		x++;
		y <<= 1;
		if ((h & 0x80000000))
			y |= 1;
		h <<= 1;
		y <<= 1;
		if ((h & 0x80000000))
			y |= 1;
		h <<= 1;
	}
	return  x;
}


unsigned long sqrt64(register unsigned long long h)
{
	unsigned long long x;
	unsigned long long y;
	unsigned char i;
	
	x =
	y = 0;
	for (i = 0;  i < 64;  i++)
	{
		x = (x << 1) | 1;
		if (y < x)
			x -= 2;
		else
			y -= x;
		x++;
		y <<= 1;
		if ((h & 0x8000000000000000))
			y |= 1;
		h <<= 1;
		y <<= 1;
		if ((h & 0x8000000000000000))
			y |= 1;
		h <<= 1;
	}
  
  x=x>>31;
  x=x+0x1;
  x=x>>1;
	return  x;
}

int my_atoi(const char *pch, int len)
{
  char buf[10];
  int ret;
  memcpy(buf, pch, len);
  buf[len] = 0;
  ret = atoi(buf);
  return ret;
}


static const int _code[] = {
		1,
		10,
		100,
		1000,
		10000
};

float BCD2FLOAT(uint8_t *bcd, int num) {
	float res = 0.0;

	while (num) {
		num--;
		res *= 100;
		res += BCD2BIN(bcd[num]);
//		bcd ++;
	}

	return res;
}
uint32_t BCD2INT(uint8_t *bcd, int num) {
	uint32_t res = 0;

	while (num) {
		num--;
		res *= 100;
		res += BCD2BIN(bcd[num]);
	}

	return res;
}

int FLOAT2BCD(float val,int integer,int decimal,uint8_t *bcd)
{
	uint32_t v = (uint32_t)(val*_code[decimal]);
	uint32_t width = integer + decimal;

	for (;width; width-=2) {
		*bcd = BIN2BCD(v%100);
		v /= 100;
		bcd ++;
	}

	return 0;
}



int INT2BCD(uint32_t in,uint8_t *out)
{
	out[0] = BIN2BCD((in%100));
	out[1] = BIN2BCD(((in%10000)/100));
	out[2] = BIN2BCD(((in%1000000)/10000));
	out[3] = BIN2BCD(((in%100000000)/1000000));

	return 4;
};


char calcFCS(char *msg, int len)
{
  int  i;
  char result = 0;

  for (i=0; i<len; ++i)
  {
    result ^= *(msg+i);
  }

  return result;
}

uint8_t ChkSum(uint8_t *in, int num) {
	uint8_t sum = 0;

	while (num--) {
		sum += *in++;
	}

	return sum;
}
