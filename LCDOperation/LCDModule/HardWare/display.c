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


void xianshi(void)//��ʾ��Ϣ
{    
	u8 idstr[5];
	BACK_COLOR=WHITE;
	POINT_COLOR=BLACK;	
	LCD_ShowString(0,2,200,16,16,"ID:");
	inttohex(0x1943,idstr);	  
	LCD_ShowString(60,2,200,16,16,idstr);
	LCD_ShowString(0,75,200,32,32,"32X16 ASCII");		
	
	//��ʾ32*32����
	showhanzi32(0,20,0);	 //��
	showhanzi32(40,20,1);	 //��
	showhanzi32(80,20,2);    //��
	//��ʾ16*16����
	showhanzi16(0,55,0);	  //ר
	showhanzi16(20,55,1);	  //ע
	showhanzi16(40,55,2);	  //��
	showhanzi16(60,55,3);	  //ʾ
	showhanzi16(80,55,4);	  //��
	showhanzi16(100,55,5);	//��
}

void showqq(void) //��ʾȫ��QQ
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

