#include "touch.h"
#include "LCD.h"
#include "config.h"

struct tp_pix_  tp_pixad,tp_pixlcd;
//unsigned int LX=0,LY=0;
char SetTem=25;

void spistar(void)
{
 	 CS_H;
	 DCLK_H;
	 DIN_H;
	 DCLK_H;
}

void WriteCharTo7843(unsigned char num)
{
 	 char count=0,icount=0x80;
	 DCLK_L;
	 for(count=0;count<8;count++)
	 {
		 if((num&icount)==0)DIN_L;
		 else DIN_H;
		 icount>>=1;
		 DCLK_L; asm("nop"); asm("nop"); asm("nop");
		 DCLK_H; asm("nop"); asm("nop"); asm("nop"); 
	 }
}

unsigned int ReadFromCharFrom7843(void)
{
 	 char count=0;
	 unsigned int Num=0;
	 for(count=0;count<12;count++)
	 {
		 DCLK_H;asm("nop"); asm("nop"); asm("nop");
		 DCLK_L;asm("nop"); asm("nop"); asm("nop");
		 if((PIND&0x10)!=0) Num++;
		 Num<<=1;
	 }
	 return(Num);
}

unsigned int ADS_Read_AD(unsigned int CMD)
{
	unsigned int l;
	CS_L;
	WriteCharTo7843(CMD);
	DCLK_H; asm("nop"); asm("nop"); asm("nop"); asm("nop");
	DCLK_L; asm("nop"); asm("nop"); asm("nop"); asm("nop");
	l=ReadFromCharFrom7843();
	CS_H;
	return l;
}

unsigned int ADS_Read_XY(unsigned char xy)
{
	unsigned int i, j;
	unsigned int buf[READ_TIMES];
	unsigned int sum=0;
	unsigned int temp;
	for(i=0;i<READ_TIMES;i++)
	{
		buf[i]=ADS_Read_AD(xy);
	}
	for(i=0;i<READ_TIMES-1; i++)//≈≈–Ú
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//…˝–Ú≈≈¡–
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;
}

unsigned char Read_ADS(unsigned int *x,unsigned int *y)
{
	unsigned int xtemp,ytemp;
	xtemp=ADS_Read_XY(CMD_RDX);
	ytemp=ADS_Read_XY(CMD_RDY);
	if(xtemp<100||ytemp<100)return 0;
	*x=xtemp;
	*y=ytemp;
	return 1;
}

unsigned char Read_ADS2(unsigned int *x,unsigned int *y)
{
    unsigned int x1,y1;
    unsigned int x2,y2;
 	char flag;
    flag=Read_ADS(&x1,&y1);   
    if(flag==0)return(0);
    flag=Read_ADS(&x2,&y2);
    if(flag==0)return(0);
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))&&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }else return 0;
}

unsigned char Read_TP_Once(void)
{
	unsigned char re=0;
	unsigned int x1,y1;
	while(re==0)
	{
		while(!Read_ADS2(&tp_pixad.x,&tp_pixad.y));
		delayms(10);
		while(!Read_ADS2(&x1,&y1));
		if(tp_pixad.x==x1&&tp_pixad.y==y1)
		{
			re=1;
		}
	}
	return re;
}

unsigned char Convert_Pos(void)
{
	unsigned char l=0;
	if(Read_ADS2(&tp_pixad.x,&tp_pixad.y)==1)
	{
		l=1;
		tp_pixlcd.x=tp_pixad.x>chx?((unsigned long)tp_pixad.x-chx)*1000/vx:(chx-(unsigned long)tp_pixad.x)*1000/vx;
		tp_pixlcd.y=tp_pixad.y>chy?((unsigned long)tp_pixad.y-chy)*1000/vy:(chy-(unsigned long)tp_pixad.y)*1000/vy;
	}
	return l;
}

char function(void)
{
	 Convert_Pos();
	 if((((tp_pixlcd.x)>100)&&((tp_pixlcd.x)<190))&&(((tp_pixlcd.y)>200)&&((tp_pixlcd.y)<280)))return 1;
	 else if((((tp_pixlcd.x)>230)&&((tp_pixlcd.x)<320))&&(((tp_pixlcd.y)>200)&&((tp_pixlcd.y)<280)))return 2;
	 else if((((tp_pixlcd.x)>320)&&((tp_pixlcd.x)<479))&&(((tp_pixlcd.y)>151)&&((tp_pixlcd.y)<281)))return 3;
	 else return 0;
}