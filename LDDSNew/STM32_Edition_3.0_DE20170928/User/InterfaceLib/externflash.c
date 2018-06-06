#include "stm32f10x.h"
#include <stdio.h>
#include "externflash.h"  

#define FLASH_PORT	GPIOE

#define FLASH_IIC_WP_PORT	FLASH_PORT
#define FLASH_IIC_WP_PIN	GPIO_Pin_2

#define FLASH_IIC_SCL_PORT	FLASH_PORT
#define FLASH_IIC_SCL_PIN	GPIO_Pin_3

#define FLASH_IIC_SDA_PORT	FLASH_PORT
#define FLASH_IIC_SDA_PIN	GPIO_Pin_4


#define FLASH_IIC_WP_CLR()	GPIO_ResetBits(FLASH_IIC_WP_PORT,FLASH_IIC_WP_PIN)
#define FLASH_IIC_WP_SET()	GPIO_SetBits(FLASH_IIC_WP_PORT,FLASH_IIC_WP_PIN)

#define FLASH_IIC_SCL_CLR()	GPIO_ResetBits(FLASH_IIC_SCL_PORT,FLASH_IIC_SCL_PIN)
#define FLASH_IIC_SCL_SET()	GPIO_SetBits(FLASH_IIC_SCL_PORT,FLASH_IIC_SCL_PIN)

#define FLASH_IIC_SDA_CLR()	GPIO_ResetBits(FLASH_IIC_SDA_PORT,FLASH_IIC_SDA_PIN)
#define FLASH_IIC_SDA_SET()	GPIO_SetBits(FLASH_IIC_SDA_PORT,FLASH_IIC_SDA_PIN)

#define FLASH_IIC_SDA()	((GPIO_ReadInputDataBit(FLASH_IIC_SDA_PORT,FLASH_IIC_SDA_PIN)==Bit_SET)?1:0)
#define FLASH_IIC_SCL() ((GPIO_ReadInputDataBit(FLASH_IIC_SCL_PORT,FLASH_IIC_SCL_PIN)==Bit_SET)?1:0)

char writeByte(char data);
char readByte(void);
void start(void);
void stop(void);
void delay(void);
void delay_ms(void);
void init(void);
void ack(void);
void noack(void);

void Flash_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	init();
}

void FlashPageWrite(unsigned int addr,char* data,int num)
{
   char highAddr,lowAddr;
   int cnt = 0;
   while(cnt<num)
   {
      highAddr = (addr&0xff00)>>8;
	  lowAddr = (addr&0x00ff);
      start();
      writeByte(0xa0);  
      writeByte(highAddr);
      writeByte(lowAddr);
	  do
	  {
	    writeByte(data[cnt]);
	    cnt++;
		addr++;
	  }
      while((addr&0x7f) && (cnt<num));
	  stop();
      delay_ms();
   }
}

void FlashPageRead(unsigned int addr, char* data,int num)
{
   char highAddr,lowAddr;
   int cnt = 0;
   highAddr = (addr&0xff00)>>8;
   lowAddr = (addr&0x00ff);
   start();
   writeByte(0xa0);  
   writeByte(highAddr);
   writeByte(lowAddr);
   start();
   writeByte(0xa1);
   while(cnt<num-1)
   {
	  data[cnt] = readByte();
	  ack();
	  cnt++;
   }
   data[cnt] = readByte();
   noack();
   stop();
   delay_ms();  
}

void FlashByteWrite(unsigned int addr,char data)
{
   char highAddr = (addr&0xff00)>>8;
   char lowAddr = (addr&0x00ff);
   char bit = 1;
   start();
   bit = writeByte(0xa0);  
   bit = writeByte(highAddr);
   bit = writeByte(lowAddr);
   bit = writeByte(data);
   while(bit);
   stop();
}

char FlashByteRead(unsigned int addr)
{
   char data = 0;
   char highAddr = (addr&0xff00)>>8;
   char lowAddr	= (addr&0x00ff);
   start();
   writeByte(0xa0);
   writeByte(highAddr);
   writeByte(lowAddr);

   start();
   writeByte(0xa1);
   data = readByte();
   noack();
   stop();
   return data;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
char writeByte(char data)    //       写一个字节
{
    char i,temp,bit = 1;
    temp = data;

	if(FLASH_IIC_SCL())
	  FLASH_IIC_SCL_CLR();

    for(i=0;i<8;i++)
    {  
	   if(temp & 0x80)
		 FLASH_IIC_SDA_SET();
	   else
		 FLASH_IIC_SDA_CLR();  
       delay();
       FLASH_IIC_SCL_SET();;
       delay();
	   FLASH_IIC_SCL_CLR();
	   temp=temp<<1;  
    }
	FLASH_IIC_SDA_SET();      //release sda line
	delay();
	FLASH_IIC_SCL_SET();
	delay();
	bit = FLASH_IIC_SDA();
    FLASH_IIC_SCL_CLR();
    delay();

	return bit;
}

char readByte(void)
{
  	char i,data = 0;

	if(FLASH_IIC_SCL())
	  FLASH_IIC_SCL_CLR();

	for(i=0;i<8;i++)
	{
	   delay();
	   FLASH_IIC_SCL_SET();
       delay();
	   data<<=1;
       data = data | FLASH_IIC_SDA();
	   FLASH_IIC_SCL_CLR();
	}

	return data;
}

void init(void)
{
  FLASH_IIC_WP_CLR();
  delay();
  FLASH_IIC_SCL_CLR();	   //scl = 0
  delay();
}

void start(void)
{
  if(FLASH_IIC_SCL())
     FLASH_IIC_SCL_CLR(); //scl = 0

  FLASH_IIC_SDA_SET();	   //sda = 1
  delay();
  FLASH_IIC_SCL_SET();	   //scl = 1
  delay();
  FLASH_IIC_SDA_CLR();	   //sda = 0
  delay();
  FLASH_IIC_SCL_CLR();	   //scl = 0
}

void stop(void)
{
  if(FLASH_IIC_SCL())
     FLASH_IIC_SCL_CLR();	//scl = 0 

  FLASH_IIC_SDA_CLR();	   //sda = 0
  delay();
  FLASH_IIC_SCL_SET();	   //scl = 1
  delay();
  FLASH_IIC_SDA_SET();
  delay();
}

void ack(void)
{
    if(FLASH_IIC_SCL())
	   FLASH_IIC_SCL_CLR();

   	FLASH_IIC_SDA_CLR();	 //应答信号
	delay();
	FLASH_IIC_SCL_SET();
    delay();
	FLASH_IIC_SCL_CLR();
    delay();
	FLASH_IIC_SDA_SET();
}

void noack(void)
{
    if(FLASH_IIC_SCL())
	   FLASH_IIC_SCL_CLR();

   	FLASH_IIC_SDA_SET();	 //应答信号
	delay();
	FLASH_IIC_SCL_SET();
    delay();
	FLASH_IIC_SCL_CLR();
    delay();
}

void delay(void)
{
  int i;
  for(i=0;i<500;i++);
}

void delay_ms(void)
{
  int j;
  int i;
  for(i=0;i<100;i++)
  for(j=0;j<5000;j++);
}

