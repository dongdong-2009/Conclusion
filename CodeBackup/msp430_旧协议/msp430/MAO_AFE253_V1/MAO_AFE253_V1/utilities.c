/******************************************************************
** 文件名: utilities.c
** Copyright (c) 2003- 毛武斌
** 创建人: 毛武斌
** 日 期:
** 修改人:
** 日 期: 2003.7.3
**  0 
*******************************************************************/ 
#include  "device.h"
#include "type_def.h"
#include "Utilities.h"

const unsigned int table[5] = {10000,1000,100,10,1};
const char hex[] = "0123456789ABCDEF";


unsigned char IntStatus; // status of GIE flag
unsigned char IntsDisableCount; // count of performed disables
void __gie_disable(void)
{
  if(IntsDisableCount==0) 
  {
    IntStatus=__get_SR_register(); 
    __disable_interrupt();
  }
  IntsDisableCount++;
}
void __gie_enable(void) 
{
  if((--IntsDisableCount==0)&&(IntStatus&0x0008)) 
  {
    __enable_interrupt();
  }
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



void soft_delay1ms(unsigned long time)
{
  while (time--)
  {
    __delay_cycles(1000*MCLK);
  }
}

char *int2str(int conved)
{
  static char temp[8];
  int  conv_temp1,conv_temp2;
  unsigned int i,index = 0;
  conv_temp1 = conved;

  if(conv_temp1 < 0)     //小于零，添加"-"
  {
    temp[index] = '-';
    index++;
    conv_temp1 = -conv_temp1;  //转正
  }
  
  for(i = 0;i<5;i++)
  {    
    conv_temp2 = conv_temp1/table[i];  //保存整除结果
    conv_temp1 = conv_temp1%table[i];  //保存余数
    temp[index++] = hex[conv_temp2];
  }
  temp[index++] = 0;
  
  if(conved < 0)
  {
    i = 1;
    while(temp[i] == '0')
    {
      i++;
    }
    i--;
    temp[i] = '-';
    return(&temp[i]);
  }
  else
  {
    i = 0;
    while(temp[i] == '0')
    {
      i++;
    }
    //i--;
    return(&temp[i]);
    //return(&temp[0]);
  }
}
