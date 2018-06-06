#include "Sensor.h"
#include "LCD.h"
#include "data.h"
unsigned int Sflag=1;

unsigned char DHTReadByte(void)//从DHT11中读一个字节
{
  unsigned char i,Data=0 ; 
  unsigned int Jflag1=0,Jflag2=0;  
  Sflag=1;
      DDRB&=0X7f;             //设置PD7为输ru
 for(i=0;i<8;i++)
	 {
		 while((!(PINB&0X80))&&(Jflag1<50000))Jflag1++; //等待50us低电平数据位间隙过去，等高电平到?	     
		 //延时40us ，延时必须（26-28us）
		 TCNT3H = 0xFF;
 		 TCNT3L = 0xF2;
		 TCCR3B = 0x03; 
		 while(Sflag);
	     Sflag=1;
			Data<<=1;						
		  if((PINB&0X80)!=0)  //如果40us以后采集到数据还是高电平，则输出为高电平
			 {
			  Data|=0X01;
			  }
		  else
			 {
			  Data|=0X00; 
			 }
		  while((PINB&0X80)&&(Jflag2<50000))Jflag2++;//等50us低电平到来 ,然后去读下一位数据
	  }
	 return(Data);
}

void DHTReadData(void)//读DHT11中的数据
{
 	
 	char ss[6];
	unsigned char i;
	unsigned char Data[5]={0,0,0,0,0};
	unsigned int Jflag1=0,Jflag2=0,Jflag3=0;  
	DDRB|=0X80;
	Sflag=1;  
	PORTB&=0X7f;      //发送启动信号
	TCNT3H = 0xFF;  //拉低至少 500us
 	TCNT3L = 0x6B;
	TCCR3B = 0x03;
 	while(Sflag);
	Sflag=1;

	PORTB|=0X80;  
	TCNT3H = 0xFF;
 	TCNT3L = 0xF9;
	TCCR3B = 0x03;
 	while(Sflag);
	Sflag=1;
	
	PORTB&=0X7f;
	DDRB&=0X7f;

	while((PINB&0X80)&&(Jflag1<50000))Jflag1++;    
	if(!(PINB&0X80))
	{
	    while((!(PINB&0X80))&&(Jflag2<50000))Jflag2++;
		while((PINB&0X80)&&(Jflag3<50000))Jflag3++; 
		for(i=0;i<5;i++)
	    {
	       	 Data[i]=DHTReadByte();
		}
		if(((Data[0]+Data[1]+Data[2]+Data[3])%0x100)==Data[4])
	    {
			inttostr((Data[2]*256+Data[3])/10,ss);
			showzifustr(100,80,ss,0xffff,0x3b35);
			inttostr((Data[0]*256+Data[1])/10,ss);
			showzifustr(330,80,ss,0xffff,0x32b2);
			getTandH(Data[2]*256+Data[3], Data[0]*256+Data[1]);
		}
	}
}

ISR(SIG_OVERFLOW3)
{
 TCCR3B = 0;
 TCNT3H = 0; //reload counter high value
 TCNT3L = 0; //reload counter low value
 Sflag=0;
}
