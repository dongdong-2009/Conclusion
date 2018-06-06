#include"LCD.h"
#include "ziku.h"
#include "config.h"
#include <avr/pgmspace.h>

unsigned int BACK_COLOR, POINT_COLOR;

void LCD_Writ_Bus(char VH,char VL) 
{
	DATAH=VH;
	DATAL=VL;
	LCD_WR_L;
	LCD_WR_H;
}

void LCD_WR_DATA(int da)
{
    LCD_RS_H;
	LCD_Writ_Bus(da>>8,da);
}

void LCD_WR_REG(int da)
{
    LCD_RS_L;
	LCD_Writ_Bus(da>>8,da);
}

void LCD_WR_REG_DATA(int reg,int da)
{
    LCD_WR_REG(reg);
	LCD_WR_DATA(da);
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
	LCD_WR_REG(0x002A);
	LCD_WR_DATA(x1>>8);
	LCD_WR_DATA(x1&0x00ff);
	LCD_WR_DATA(x2>>8);
	LCD_WR_DATA(x2&0x00ff);
    LCD_WR_REG(0x002b);
	LCD_WR_DATA(y1>>8);
	LCD_WR_DATA(y1&0x00ff);
	LCD_WR_DATA(y2>>8);
	LCD_WR_DATA(y2&0x00ff);
	LCD_WR_REG(0x002c);
}

void Lcd_Init(void)
{
   	LCD_CS_H;
    LCD_REST_H;
    delayms(5);	
	LCD_REST_L;
	delayms(5);	
	LCD_REST_H;
	LCD_CS_H;
	LCD_RD_H;
	LCD_WR_H;
	delayms(5);	
	LCD_CS_L;  //打开片选使能

	LCD_WR_REG(0x00E2);	//PLL multiplier, set PLL clock to 120M
	LCD_WR_DATA(0x002d);	    //N=0x36 for 6.5M, 0x23 for 10M crystal
	LCD_WR_DATA(0x0002);
	LCD_WR_DATA(0x0004);
	LCD_WR_REG(0x00E0);  // PLL enable
	LCD_WR_DATA(0x0001);
	delayms(1);	
	LCD_WR_REG(0x00E0);
	LCD_WR_DATA(0x0003);
	delayms(5);	
	LCD_WR_REG(0x0001);  // software reset
	delayms(5);	
	LCD_WR_REG(0x00E6);	//PLL setting for PCLK, depends on resolution
	LCD_WR_DATA(0x0000);
	LCD_WR_DATA(0x00ff);
	LCD_WR_DATA(0x00be);

	LCD_WR_REG(0x00B0);	//LCD SPECIFICATION
	LCD_WR_DATA(0x0020);
	LCD_WR_DATA(0x0000);
	LCD_WR_DATA((HDP>>8)&0X00FF);  //Set HDP
	LCD_WR_DATA(HDP&0X00FF);
    LCD_WR_DATA((VDP>>8)&0X00FF);  //Set VDP
	LCD_WR_DATA(VDP&0X00FF);
    LCD_WR_DATA(0x0000);
	delayms(5);	

	LCD_WR_REG(0x00B4);	//HSYNC
	LCD_WR_DATA((HT>>8)&0X00FF);  //Set HT
	LCD_WR_DATA(HT&0X00FF);
	LCD_WR_DATA((HPS>>8)&0X00FF);  //Set HPS
	LCD_WR_DATA(HPS&0X00FF);
	LCD_WR_DATA(HPW);			   //Set HPW
	LCD_WR_DATA((LPS>>8)&0X00FF);  //SetLPS
	LCD_WR_DATA(LPS&0X00FF);
	LCD_WR_DATA(0x0000);

	LCD_WR_REG(0x00B6);	//VSYNC
	LCD_WR_DATA((VT>>8)&0X00FF);   //Set VT
	LCD_WR_DATA(VT&0X00FF);
	LCD_WR_DATA((VPS>>8)&0X00FF);  //Set VPS
	LCD_WR_DATA(VPS&0X00FF);
	LCD_WR_DATA(VPW);  //Set VPW
	LCD_WR_DATA((FPS>>8)&0X00FF);  //Set FPS
	LCD_WR_DATA(FPS&0X00FF);

	LCD_WR_REG(0x0036); //rotation
	LCD_WR_DATA(0x0000);

	LCD_WR_REG(0x00F0); //pixel data interface
	LCD_WR_DATA(0x0003);

	delayms(5);	

	LCD_WR_REG(0x0029); //display on

	LCD_WR_REG(0x00BE); //set PWM for B/L
	LCD_WR_DATA(0x0006);
	LCD_WR_DATA(0x00f0);
	LCD_WR_DATA(0x0001);
	LCD_WR_DATA(0x00f0);
	LCD_WR_DATA(0x0000);
	LCD_WR_DATA(0x0000);

	LCD_WR_REG(0x00d0); 
	LCD_WR_DATA(0x000d);

    //----------LCD RESET---GPIO0-------------------//
	LCD_WR_REG(0x00B8);
	LCD_WR_DATA(0x0000);    //GPIO3=input, GPIO[2:0]=output
	LCD_WR_DATA(0x0001);    //GPIO0 normal

	LCD_WR_REG(0x00BA);
	LCD_WR_DATA(0x0000);  
}

void LCD_Clear(unsigned int Color)
{
	int Ci=0,Cj=0;
	Address_set(0,0,LCD_W-1,LCD_H-1);
    for(Ci=0;Ci<LCD_W;Ci++)
	 {
	  		for (Cj=0;Cj<LCD_H;Cj++)
	   		{
        	 	 LCD_WR_DATA(Color);
	    	}
	  }
}

void LCD_DrawPoint(unsigned int x,unsigned int y)
{
	Address_set(x,y,x,y);//设置光标位置 
	LCD_WR_DATA(POINT_COLOR); 	    
}

void LCD_Fill(unsigned int xsta,unsigned int ysta,unsigned int xend,unsigned int yend,unsigned int color)
{          
	unsigned int i,j; 
	Address_set(xsta,ysta,xend,yend);      //设置光标位置 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)LCD_WR_DATA(color);//设置光标位置
	} 					  	    
}

void LCD_DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
	unsigned int t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		}
		if(yerr>distance)
		{
			yerr-=distance; 
			uCol+=incy; 
		}
	}
}

void LCD_DrawRectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

void showzifu(unsigned int x,unsigned int y,char val,unsigned int dcolor,unsigned int bgcolor)
{  
	unsigned char i,j;
	unsigned int k=0;
//	unsigned char zikuPo;
//	*temp=pgm_read_byte(&ziku);
    Address_set(x,y,x+15,y+32); //设置区域
	k+=(val-32)*66;
	for(j=0;j<66;j++)
	{
		for(i=0;i<8;i++)
		{
		 	if((pgm_read_byte(&ziku[k])&(1<<(7-i)))!=0)
			{
				LCD_WR_DATA(dcolor);
			}
			else
			{
				LCD_WR_DATA(bgcolor);
			}
		}
		k++;
	 }
}


void showzifustr(unsigned int x,unsigned int y,char *str,unsigned int dcolor,unsigned int bgcolor)	  
{  
	unsigned int x1,y1;
	x1=x;
	y1=y;
	while(*str!='\0')
	{
		showzifu(x1,y1,*str,dcolor,bgcolor);
		x1+=18;
		str++;
		asm("nop");
	}
}


void showlogo(unsigned int x,unsigned int y,char val,unsigned int dcolor,unsigned int bgcolor)
{  
	unsigned char i,j;
	unsigned int k=0;
//	*temp=pgm_read_byte(&logo);
    Address_set(x,y,x+23,y+35); //设置区域
	k+=(val-0x30)*108;
	for(j=0;j<108;j++)
	{
		for(i=0;i<8;i++)
		{
		 	if((pgm_read_byte(&logo[k])&(1<<(7-i)))!=0)
			{
				LCD_WR_DATA(dcolor);
			}
			else
			{
				LCD_WR_DATA(bgcolor);
			}
		}
		k++;
	 }
}

void showlogostr(unsigned int x,unsigned int y,char *str,unsigned int dcolor,unsigned int bgcolor)
{
	while(*str!='\0')
	{
		showlogo(x,y,*str,dcolor,bgcolor);
		x+=24;
		str++;
	}
}

/*
void showzifuA(unsigned int x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor)
{
	unsigned char i,j,a;
	const unsigned char *temp=zikuA;
    Address_set(x,y,x+23,y+39); //设置区域
	temp+=(value-64)*120;
	for(j=0;j<120;j++)
	{
		for(i=0;i<8;i++)
		{
		 	if((*temp&(1<<(7-i)))!=0)
			{
				LCD_WR_DATA(dcolor);
			}
			else
			{
				LCD_WR_DATA(bgcolor);
			}
		}
		temp++;
	 }
}*/
/*
void showzifustrA(unsigned int x,unsigned int y,unsigned char *str,unsigned int dcolor,unsigned int bgcolor)	  
{  
	unsigned int x1,y1,i;
	x1=x;
	y1=y;
	
	while(*str!='\0')
	{
//		showzifuA(x1,y1,*str,dcolor,bgcolor);
		x1+=23;
		str++;
		asm("nop");
	}
}
*/
void inttostr(int dd,char *str)
{
	if((dd/10000)==0)str[0]=32;else str[0]=dd/10000+48;
	if(((dd/10000)==0)&&((dd/1000)==0))str[1]=32; else str[1]=(dd/1000)-((dd/10000)*10)+48;
	if(((dd/10000)==0)&&((dd/1000)==0)&&((dd/100)==0))str[2]=32; else str[2]=(dd/100)-((dd/1000)*10)+48;
	str[3]=(dd/10)-((dd/100)*10)+48;
	str[4]=dd-((dd/10)*10)+48;
	str[5]=0;
}

void inttostrA(int dd,char *str)
{
	if(((dd/10000)==0)&&((dd/1000)==0))str[0]=32; else str[0]=(dd/1000)-((dd/10000)*10)+48;
	if(((dd/10000)==0)&&((dd/1000)==0)&&((dd/100)==0))str[1]=32; else str[1]=(dd/100)-((dd/1000)*10)+48;
	str[2]=(dd/10)-((dd/100)*10)+48;
	str[3]=0x2E;
	str[4]=dd-((dd/10)*10)+48;
	str[5]=0;
}

void inttostrC(int dd,char *str)
{
	if(((dd/10000)==0)&&((dd/1000)==0)&&((dd/100)==0))str[0]=32; else str[0]=(dd/100)-((dd/1000)*10)+48;
	str[1]=(dd/10)-((dd/100)*10)+48;
	str[2]=dd-((dd/10)*10)+48;
	str[3]=0x24;
	str[4]=0x43;
	str[5]=0;
}