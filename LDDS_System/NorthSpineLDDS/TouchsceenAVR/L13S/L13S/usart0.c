#include "usart0.h"
#include "data.h"
#include "config.h"

unsigned char Receive_buffer0[52]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//定义接收缓存
unsigned char Send_data[53]={0x55,0x66,1,0,1,0,0,1,0,0x41,0x26,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x66,0x55};
unsigned char Back_seto[53]={0x55,0x66,1,0,1,0,0,1,0,0x44,0x26,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,79,0x66,0x55};
unsigned char Back_sett[53]={0x55,0x66,1,0,1,0,0,1,0,0x54,0x26,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,95,0x66,0x55};
unsigned char Back_spid[53]={0x55,0x66,1,0,1,0,0,1,0,0x51,0x26,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,92,0x66,0x55};
unsigned char Back_bpid[53]={0x55,0x66,1,0,1,0,0,1,0,0x61,0x26,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x66,0x55};
unsigned char Back_eror[53]={0x55,0x66,1,0,1,0,0,1,0,0xaa,0x26,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0,202,0x66,0x55};
unsigned char buffercnt0=0;
int kflag0=0;
void uart0_init(void)
{
	UCSR0B = 0x00; //disable while setting baud rate
	UCSR0A = 0x00;
	UCSR0C = 0x36;
	UBRR0L = 0x67; //set baud rate lo
	UBRR0H = 0x00; //set baud rate hi
	UCSR0B = 0x98;
}


SIGNAL(SIG_UART0_RECV)
{
    Receive_buffer0[buffercnt0]=UDR0-0x33;
    if(Receive_buffer0[0]==0x66)
    {
		
        buffercnt0++;
		switch(buffercnt0)
		{
			case 1:break;
			case 2:if(Receive_buffer0[1]!=1)buffercnt0=0;break;
			case 3:if(Receive_buffer0[2]!=0)buffercnt0=0;break;
			case 4:if(Receive_buffer0[3]!=1)buffercnt0=0;break;
			case 5:if(Receive_buffer0[4]!=0)buffercnt0=0;break;
			case 6:if(Receive_buffer0[5]!=0)buffercnt0=0;break;
			case 7:if(Receive_buffer0[6]!=1)buffercnt0=0;else TCNT0 = 0x64;TCCR0 = 0x07; break;
			case 52:Reciver_process0();TCCR1B = 0x05;TCNT0 = 0;buffercnt0=0;kflag0=0;
			break;
		}
    }
}

void uart0_Tx(unsigned char data)
{
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
	while ( !( UCSR0A & (1<<TXC0)) );
	del(1);
}

void send_data0(unsigned typeA)
{
    unsigned int i=0;
	asm("cli");
	switch(typeA)
	{
		case 0:
		PORTE&=0xFB;
		for(i=0;i<53;i++)uart0_Tx(Send_data[i]+0x33);
		PORTE|=0x04;
		break;
		
		case 1:
		PORTE&=0xFB;
		for(i=0;i<53;i++)uart0_Tx(Back_seto[i]+0x33);
		PORTE|=0x04;
		break;
		
		case 2:
		PORTE&=0xFB;
		for(i=0;i<53;i++)uart0_Tx(Back_sett[i]+0x33);
		PORTE|=0x04;
		break;
	
		case 3:
		PORTE&=0xFB;
		for(i=0;i<53;i++)uart0_Tx(Back_spid[i]+0x33);
		PORTE|=0x04;
		break;
	
		case 4:
		PORTE&=0xFB;
		for(i=0;i<53;i++)uart0_Tx(Back_bpid[i]+0x33);
		PORTE|=0x04;
	
		case 5:
		PORTE&=0xFB;
		for(i=0;i<53;i++)uart0_Tx(Back_eror[i]+0x33);
		PORTE|=0x04;
	
		default:
		break;
	}
	asm("sei");
	delayms(300);
}

void Reciver_process0(void)
{
      switch(Receive_buffer0[8])
     {
         case 0x41:usarS();send_data0(0);break;
         case 0x44:usarH(Receive_buffer0[10],Receive_buffer0[11],Receive_buffer0[12],Receive_buffer0[13],Receive_buffer0[14],Receive_buffer0[15],Receive_buffer0[16],Receive_buffer0[17],Receive_buffer0[18],Receive_buffer0[19],Receive_buffer0[20],Receive_buffer0[21]);break;
		 case 0x51:usarP(Receive_buffer0[10],Receive_buffer0[11],Receive_buffer0[12],Receive_buffer0[13],Receive_buffer0[14],Receive_buffer0[15],Receive_buffer0[16],Receive_buffer0[17],Receive_buffer0[18],Receive_buffer0[19],Receive_buffer0[20],Receive_buffer0[21]);break;
         case 0x54:usarT(Receive_buffer0[10]);break;
         default: send_data0(5);break;
      }
}

ISR(SIG_OVERFLOW0)
{
	asm("sei");
	kflag0++;
	if(kflag0==8)
	{
		TCCR0 = 0x0;
		TCNT0 = 0; //reload counter high value
		buffercnt0=0;
		kflag0=0;
	}
}

void getsend(unsigned char getdata,unsigned char i)
{
	Send_data[i]=getdata;
}

void getsensor(unsigned int getTem,unsigned int getHum,unsigned int locflag)
{
	Send_data[11]=getTem/10000;
	Send_data[12]=getTem%10000/100;
	Send_data[13]=getTem%100;
	Send_data[14]=getHum/10000;
	Send_data[15]=getHum%10000/100;
	Send_data[16]=getHum%100;
	Send_data[49]=locflag;
}

void getdo(unsigned char do1,unsigned char do2)
{
	if(do1==1)Send_data[36]|=0x80;
	else if(do1==0)Send_data[36]&=0x7f;
	
	if(do2==1)Send_data[36]|=0x40;
	else if(do2==0)Send_data[36]&=0xbf;
}