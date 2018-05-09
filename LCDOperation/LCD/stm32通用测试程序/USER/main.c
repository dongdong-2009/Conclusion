#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "24cxx.h"
#include "flash.h"
#include "touch.h"	  
  
u8 state=0;	   
void beepms(u16 va);  
void refshow(void);//刷新显示	
 
void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//清屏   
 	POINT_COLOR=BLUE;//设置字体为蓝色 
	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//显示清屏区域
  	POINT_COLOR=RED;//设置画笔蓝色 
}
void xianshi()//显示信息
{    
	u8 idstr[5];
	BACK_COLOR=WHITE;
	POINT_COLOR=RED;	
	LCD_ShowString(0,2,200,16,16,"ID:");
	inttohex(lcddev.id,idstr);	  
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
	showhanzi16(100,55,5);	  //案
}
void showqq() //显示全屏QQ
{ 
	u16 x,y; 
	x=0;
	y=110;
	while(y<lcddev.height-39)
	{
		x=0;
		while(x<lcddev.width-39)
		{
			showimage(x,y);	
			x+=40;
		}
		y+=40;
	 }


}
void refshow(void)	 //刷新显示
{
	switch(state)
	{
		case 0:
		LCD_Clear(WHITE);
	    xianshi();
    	showqq();
		break;
		case 1:
		LCD_Clear(BLACK); 
		break;
		case 2:
		LCD_Clear(RED);
		break;
		case 3:
		LCD_Clear(GREEN);
		break;
		case 4:
		LCD_Clear(BLUE);
		break;
	}	
}
void jiance(u8 key) //检测按键
{
	if(key==1)	//KEY_RIGHT按下,则执行校准程序
	{
		LCD_Clear(WHITE);//清屏
	    TP_Adjust();  //屏幕校准 
		TP_Save_Adjdata();	 
		Load_Drow_Dialog();
	}
	if(key==2)
	{
		state++;
		 if(state==5)
		 {
		 	state=0;
			LCD_Init();	   
		 }
		refshow();//刷新显示
	}

}	 
void beepms(u16 va)
{
	beep=1;
	delay_ms(va);
	beep=0;
}					
int main(void)
 {	 
	u16 i=0;	 
	u8 key=0;	
  	//配置IC与接口
	/*ID设置说明:目前已经包含的驱动如下：（只有如下列出的IC才支持，没有列出的不支持，本程序会不定期更新以便支持更多的IC）
	2.2寸并口S6D0164         lcddev.id=0x0164 
	2.4寸 S6d1121            lcddev.id=0x1121
	2.4寸9325/9328           lcddev.id=0x9325
	2.8寸9325/9328           lcddev.id=0x9325
	2.4/2.8/3.2寸并口/9341   lcddev.id=0x9341
	3.2寸1289                lcddev.id=0x8989
	3.2寸8347                lcddev.id=0x0047
	3.2寸8352A           lcddev.id=0x0052
	3.2寸8352B           lcddev.id=0x0065
	3.2寸9320            lcddev.id=0x9320
	3.5寸9486L		       lcddev.id=0x9486
	1963方案4.3寸        lcddev.id=0x1943
	工业级4.3寸          lcddev.id=0x0043
	1963方案5寸          lcddev.id=0x1905
	工业级5寸            lcddev.id=0x0050
	1963方案7寸          lcddev.id=0x1907
	工业级7寸            lcddev.id=0x0070
	工业级9寸            lcddev.id=0x0090  
	*/
	lcddev.bus16=1;    //总线接口，0-8位总线，1-16位总线，修改8位总线之前先确定你手里的屏是否是8位接口，目前只有2.4和2.8寸才有支持8位的版本，3.2寸以上均不支持8位总线 
	lcddev.id=0x1943;  //指定ID,0x1234为自动读ID,切记注意不是所有的屏都能读到ID,只有少部分驱动IC能读ID,比如4.3寸以及4.3寸以上的都不能读ID.


	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();			     //LED端口初始化
    SPI_Flash_Init();//初始化Flash;
	LCD_Init();	
	tp_dev.init();//触摸初始化
	KEY_Init();	 		
 	POINT_COLOR=RED;//设置字体为红色 	
	xianshi();
   	showqq();
	beepms(200);
	while(1)
	{ 
	   key=KEY_Scan(0);//扫描按键		   
	   tp_dev.scan(0); //扫描触摸		   	
			
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{
			if(state!=1)
			{
				LCD_Clear(WHITE);
			}
			while(key==0)
			{	
			
				key=KEY_Scan(0);//扫描按键
		    	tp_dev.scan(0);	
				if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
				{			
				 	if(tp_dev.x<lcddev.width&&tp_dev.y<lcddev.height)
					{	
						if(tp_dev.x>(lcddev.width-24)&&tp_dev.y<16)Load_Drow_Dialog();//清除
						else TP_Draw_Big_Point(tp_dev.x,tp_dev.y,RED);		//画图	  			   
					}
				}
							
			} 			
		}	   	    
	   jiance(key);//检测按键	 
		i++;
		if(i==65000)
		{
			i=0;
			LED0=!LED0;
		}
	}
}


