#include "usart1.h"
#include "data.h"
#include "config.h"
unsigned char Receive_buffer[65]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//定义接收缓存
unsigned char send_buffer[65]={0x55,0x66,1,0,1,0,0,2,0,0,0x32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x66,0x55};
unsigned char buffercnt=0;
unsigned int v=1;
unsigned int kflag=0;
//unsigned int a=0,b=0;
unsigned char ss[6];
void uart1_init(void)
{
 UCSR1B = 0x00; //disable while setting baud rate
 UCSR1A = 0x00;
 UCSR1C = 0x36;
 UBRR1L = 0x67; //set baud rate lo
 UBRR1H = 0x00; //set baud rate hi
 UCSR1B = 0x98;
}

SIGNAL(SIG_UART1_RECV)
{
    Receive_buffer[buffercnt]=UDR1;
   if(Receive_buffer[0]==0x55)
    {
          buffercnt++;
		  switch(buffercnt)
		  {
		  case 3:if(Receive_buffer[2]!=1)buffercnt=0;break;
		  case 4:if(Receive_buffer[3]!=0)buffercnt=0;break;
		  case 5:if(Receive_buffer[4]!=1)buffercnt=0;break;
		  case 6:if(Receive_buffer[5]!=0)buffercnt=0;break;
		  case 7:if(Receive_buffer[6]!=0)buffercnt=0;break;
		  case 8:if(Receive_buffer[7]!=2)buffercnt=0;break;
		  // case 63:if(Receive_buffer[62]!=0x66)buffercnt=0;break;
		  case 65:if(Receive_buffer[64]!=0x55)buffercnt=0;getflag();break;
		  }
    }
}

void uart1_Tx(unsigned char data)
{
	while ( !( UCSR1A & (1<<UDRE1)) );
	UDR1 = data;
	while ( !( UCSR1A & (1<<TXC1)) );
	del(3);
}

void send_data1(unsigned int typeA,unsigned int data1,unsigned int data2,unsigned int data3,unsigned int data4,unsigned int data5,unsigned int data6,unsigned int data7,unsigned int data8,unsigned int data9,unsigned int data10,unsigned int data11,unsigned int data12)
{
    unsigned int i=0;
	buffercnt=0;
	switch(typeA)
	{
	case 0:
	send_buffer[9]=0x41;
	PORTB&=0xBF;
	for(i=0;i<65;i++) uart1_Tx(send_buffer[i]);
	PORTB|=0x40;
	break;
	
	case 1:
	send_buffer[9]=0x44;
	send_buffer[11]=data1;
	send_buffer[12]=data2;
	send_buffer[13]=data3;
	send_buffer[14]=data4;
	send_buffer[15]=data5;
	send_buffer[16]=data6;
	send_buffer[17]=data7;
	send_buffer[18]=data8;
	send_buffer[19]=data9;
	send_buffer[20]=data10;
	send_buffer[21]=data11;
	send_buffer[22]=data12;
	PORTB&=0xBF;
	for(i=0;i<65;i++) uart1_Tx(send_buffer[i]);
	PORTB|=0x40;
	break;
	
	case 2:
	send_buffer[9]=0x54;
	send_buffer[11]=data1;
	PORTB&=0xBF;
	for(i=0;i<65;i++) uart1_Tx(send_buffer[i]);
	PORTB|=0x40;
	break;
	
	case 3:
	send_buffer[9]=0x51;
	send_buffer[11]=data1;
	send_buffer[12]=data2;
	send_buffer[13]=data3;
	send_buffer[14]=data4;
	send_buffer[15]=data5;
	send_buffer[16]=data6;
	send_buffer[17]=data7;
	send_buffer[18]=data8;
	send_buffer[19]=data9;
	send_buffer[20]=data10;
	send_buffer[21]=data11;
	send_buffer[22]=data12;
	PORTB&=0xBF;
	for(i=0;i<65;i++) uart1_Tx(send_buffer[i]);
	PORTB|=0x40;
	break;
	
	case 4:
	send_buffer[9]=0x55;
	PORTB&=0xBF;
	for(i=0;i<65;i++) uart1_Tx(send_buffer[i]);
	PORTB|=0x40;
	break;
	
	default:
	break;
	}
	
}

void Reciver_process1(void)
{
 unsigned int i=0,sum=0;
// unsigned int data1=0,data2=0,data3=0,data4=0,data5=0,data6=0,data7=0,data8=0,data9=0,data10=0,data11=0,data12=0;
 unsigned int getT=0,getH=0;
 for(i=0;i<62;i++) sum=sum+Receive_buffer[i];
 if(Receive_buffer[62]==(sum%0x100))
 {
      switch(Receive_buffer[9])
     {
         case 0x41:
		 getT=returnT();
		 getH=returnH();
		 Receive_buffer[29]=getT/10000;
		 Receive_buffer[30]=getT%10000/100;
		 Receive_buffer[31]=getT%100;
		 Receive_buffer[32]=getH/10000;
		 Receive_buffer[33]=getH%10000/100;
		 Receive_buffer[34]=getH%100;
/*		 for(i=11;i<43;i++)
		 {
			 getsend(Receive_buffer[i],i);
		 }*/
		 break;
         case 0x44:break;
		 case 0x51:break;
         case 0x54:break;
         default: break;
      }
	}
}
/*
#pragma interrupt_handler timer2_ovf_isr:iv_TIM2_OVF
void timer2_ovf_isr(void)
{
// asm("sei");
 kflag++;
 if(kflag==4)
 {
 TCCR2 = 0x0;
 TCNT2 = 0; //reload counter high value
 buffercnt=0;
 kflag=0;
 }
}*/
