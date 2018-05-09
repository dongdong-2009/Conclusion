#include "display.h"

void inttohex(u16 value,u8 *hex)
{
	u16 x1;
	hex[0]=value/(16*16*16)+'0';
	x1=value%(16*16*16);
	hex[1]=x1/(16*16)+'0';
	x1=value%(16*16);
	hex[2]=x1/16+'0';
	x1=value%16;
	hex[3]=x1+'0';	
	hex[4]=' ';		 
}


void xianshi(void)//显示信息
{    
	u8 idstr[5];
	BACK_COLOR=WHITE;
	POINT_COLOR=BLACK;	
	LCD_ShowString(0,2,200,16,16,"ID:");
	inttohex(0x1943,idstr);	  
	LCD_ShowString(60,2,200,16,16,idstr);
	LCD_ShowString(0,75,200,32,32,"32X16 ASCII");		
	
	//显示32*32汉字
	showhanzi32(0,20,0);	 //淘
	showhanzi32(40,20,1);	 //晶
	showhanzi32(80,20,2);    //驰
	//显示16*16汉字
	showhanzi16(0,55,0);	  //专
	showhanzi16(20,55,1);	  //注
	showhanzi16(40,55,2);	  //显
	showhanzi16(60,55,3);	  //示
	showhanzi16(80,55,4);	  //方
	showhanzi16(100,55,5);	//案
}

void showqq(void) //显示全屏QQ
{ 
	u16 x,y; 
	x=0;
	y=110;
	while(y<LCD_H-39)
	{
		x=0;
		while(x<LCD_W-39)
		{
			showimage(x,y);	
			x+=40;
		}
		y+=40;
	 }

}

