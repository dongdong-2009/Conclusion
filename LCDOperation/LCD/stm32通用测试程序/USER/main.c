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
void refshow(void);//ˢ����ʾ	
 
void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//����   
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//��ʾ��������
  	POINT_COLOR=RED;//���û�����ɫ 
}
void xianshi()//��ʾ��Ϣ
{    
	u8 idstr[5];
	BACK_COLOR=WHITE;
	POINT_COLOR=RED;	
	LCD_ShowString(0,2,200,16,16,"ID:");
	inttohex(lcddev.id,idstr);	  
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
	showhanzi16(100,55,5);	  //��
}
void showqq() //��ʾȫ��QQ
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
void refshow(void)	 //ˢ����ʾ
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
void jiance(u8 key) //��ⰴ��
{
	if(key==1)	//KEY_RIGHT����,��ִ��У׼����
	{
		LCD_Clear(WHITE);//����
	    TP_Adjust();  //��ĻУ׼ 
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
		refshow();//ˢ����ʾ
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
  	//����IC��ӿ�
	/*ID����˵��:Ŀǰ�Ѿ��������������£���ֻ�������г���IC��֧�֣�û���г��Ĳ�֧�֣�������᲻���ڸ����Ա�֧�ָ����IC��
	2.2�粢��S6D0164         lcddev.id=0x0164 
	2.4�� S6d1121            lcddev.id=0x1121
	2.4��9325/9328           lcddev.id=0x9325
	2.8��9325/9328           lcddev.id=0x9325
	2.4/2.8/3.2�粢��/9341   lcddev.id=0x9341
	3.2��1289                lcddev.id=0x8989
	3.2��8347                lcddev.id=0x0047
	3.2��8352A           lcddev.id=0x0052
	3.2��8352B           lcddev.id=0x0065
	3.2��9320            lcddev.id=0x9320
	3.5��9486L		       lcddev.id=0x9486
	1963����4.3��        lcddev.id=0x1943
	��ҵ��4.3��          lcddev.id=0x0043
	1963����5��          lcddev.id=0x1905
	��ҵ��5��            lcddev.id=0x0050
	1963����7��          lcddev.id=0x1907
	��ҵ��7��            lcddev.id=0x0070
	��ҵ��9��            lcddev.id=0x0090  
	*/
	lcddev.bus16=1;    //���߽ӿڣ�0-8λ���ߣ�1-16λ���ߣ��޸�8λ����֮ǰ��ȷ������������Ƿ���8λ�ӿڣ�Ŀǰֻ��2.4��2.8�����֧��8λ�İ汾��3.2�����Ͼ���֧��8λ���� 
	lcddev.id=0x1943;  //ָ��ID,0x1234Ϊ�Զ���ID,�м�ע�ⲻ�����е������ܶ���ID,ֻ���ٲ�������IC�ܶ�ID,����4.3���Լ�4.3�����ϵĶ����ܶ�ID.


	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();			     //LED�˿ڳ�ʼ��
    SPI_Flash_Init();//��ʼ��Flash;
	LCD_Init();	
	tp_dev.init();//������ʼ��
	KEY_Init();	 		
 	POINT_COLOR=RED;//��������Ϊ��ɫ 	
	xianshi();
   	showqq();
	beepms(200);
	while(1)
	{ 
	   key=KEY_Scan(0);//ɨ�谴��		   
	   tp_dev.scan(0); //ɨ�败��		   	
			
		if(tp_dev.sta&TP_PRES_DOWN)			//������������
		{
			if(state!=1)
			{
				LCD_Clear(WHITE);
			}
			while(key==0)
			{	
			
				key=KEY_Scan(0);//ɨ�谴��
		    	tp_dev.scan(0);	
				if(tp_dev.sta&TP_PRES_DOWN)			//������������
				{			
				 	if(tp_dev.x<lcddev.width&&tp_dev.y<lcddev.height)
					{	
						if(tp_dev.x>(lcddev.width-24)&&tp_dev.y<16)Load_Drow_Dialog();//���
						else TP_Draw_Big_Point(tp_dev.x,tp_dev.y,RED);		//��ͼ	  			   
					}
				}
							
			} 			
		}	   	    
	   jiance(key);//��ⰴ��	 
		i++;
		if(i==65000)
		{
			i=0;
			LED0=!LED0;
		}
	}
}


