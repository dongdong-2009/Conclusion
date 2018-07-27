#include "stm32f10x.h"
#include <stdio.h>
#include "analogin.h"

#define SPI_MISO_AI_PORT	GPIOA
#define SPI_MISO_AI_PIN		GPIO_Pin_6

#define SPI_MOSI_AI_PORT	GPIOA
#define SPI_MOSI_AI_PIN		GPIO_Pin_7

#define SPI_SCLK_AI_PORT	GPIOA
#define SPI_SCLK_AI_PIN		GPIO_Pin_5

#define SPI_CS_AI_0_PORT	GPIOA
#define SPI_CS_AI_0_PIN		GPIO_Pin_1

#define SPI_CS_AI_1_PORT	GPIOA
#define SPI_CS_AI_1_PIN		GPIO_Pin_2

#define SPI_CS_AI_2_PORT	GPIOA
#define SPI_CS_AI_2_PIN		GPIO_Pin_3

#define SPI_CS_AI_3_PORT	GPIOA
#define SPI_CS_AI_3_PIN		GPIO_Pin_4

#define SPI_MISO_RTD_PORT	GPIOG
#define SPI_MISO_RTD_PIN	GPIO_Pin_14

#define SPI_MOSI_RTD_PORT	GPIOG
#define SPI_MOSI_RTD_PIN	GPIO_Pin_15

#define SPI_SCLK_RTD_PORT	GPIOG
#define SPI_SCLK_RTD_PIN	GPIO_Pin_13

#define SPI_CS_RTD_0_PORT	GPIOB
#define SPI_CS_RTD_0_PIN	GPIO_Pin_7

#define SPI_CS_RTD_1_PORT	GPIOB
#define SPI_CS_RTD_1_PIN	GPIO_Pin_8

#define SPI_AI_CS0_CLR()	GPIO_ResetBits(SPI_CS_AI_0_PORT,SPI_CS_AI_0_PIN)
#define SPI_AI_CS0_SET()	GPIO_SetBits(SPI_CS_AI_0_PORT,SPI_CS_AI_0_PIN)

#define SPI_AI_CS1_CLR()	GPIO_ResetBits(SPI_CS_AI_1_PORT,SPI_CS_AI_1_PIN)
#define SPI_AI_CS1_SET()	GPIO_SetBits(SPI_CS_AI_1_PORT,SPI_CS_AI_1_PIN)

#define SPI_AI_CS2_CLR()	GPIO_ResetBits(SPI_CS_AI_2_PORT,SPI_CS_AI_2_PIN)
#define SPI_AI_CS2_SET()	GPIO_SetBits(SPI_CS_AI_2_PORT,SPI_CS_AI_2_PIN)

#define SPI_AI_CS3_CLR()	GPIO_ResetBits(SPI_CS_AI_3_PORT,SPI_CS_AI_3_PIN)
#define SPI_AI_CS3_SET()	GPIO_SetBits(SPI_CS_AI_3_PORT,SPI_CS_AI_3_PIN)

#define SPI_AI_MOSI_CLR()	GPIO_ResetBits(SPI_MOSI_AI_PORT,SPI_MOSI_AI_PIN)
#define SPI_AI_MOSI_SET()	GPIO_SetBits(SPI_MOSI_AI_PORT,SPI_MOSI_AI_PIN)

#define SPI_AI_SCLK_CLR()	GPIO_ResetBits(SPI_SCLK_AI_PORT,SPI_SCLK_AI_PIN)
#define SPI_AI_SCLK_SET()	GPIO_SetBits(SPI_SCLK_AI_PORT,SPI_SCLK_AI_PIN)

#define SPI_AI_MISO_PIN()	((GPIO_ReadInputDataBit(SPI_MISO_AI_PORT,SPI_MISO_AI_PIN)==Bit_SET)?1:0)

#define SPI_RTD_CS0_CLR()	GPIO_ResetBits(SPI_CS_RTD_0_PORT,SPI_CS_RTD_0_PIN)
#define SPI_RTD_CS0_SET()	GPIO_SetBits(SPI_CS_RTD_0_PORT,SPI_CS_RTD_0_PIN)

#define SPI_RTD_CS1_CLR()	GPIO_ResetBits(SPI_CS_RTD_1_PORT,SPI_CS_RTD_1_PIN)
#define SPI_RTD_CS1_SET()	GPIO_SetBits(SPI_CS_RTD_1_PORT,SPI_CS_RTD_1_PIN)


#define SPI_RTD_MOSI_CLR()	GPIO_ResetBits(SPI_MOSI_RTD_PORT,SPI_MOSI_RTD_PIN)
#define SPI_RTD_MOSI_SET()	GPIO_SetBits(SPI_MOSI_RTD_PORT,SPI_MOSI_RTD_PIN)

#define SPI_RTD_SCLK_CLR()	GPIO_ResetBits(SPI_SCLK_RTD_PORT,SPI_SCLK_RTD_PIN)
#define SPI_RTD_SCLK_SET()	GPIO_SetBits(SPI_SCLK_RTD_PORT,SPI_SCLK_RTD_PIN)

#define SPI_RTD_MISO_PIN()	((GPIO_ReadInputDataBit(SPI_MISO_RTD_PORT,SPI_MISO_RTD_PIN)==Bit_SET)?1:0)

void delay(void){
    volatile int ___j = 100;	
    while(___j--);	
}

void delay_rtd(void){
    volatile int ___j = 500;	
    while(___j--);	
}

struct _adc_data adc_buffer[4];

struct _rtd_data rtd_buffer[2]; // 存放两个测温模块的数据，共4个温度传感器。
const uint8_t cmd[12] = {0x01, 0x02, 0x03};

void analog_in_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = (SPI_MOSI_AI_PIN) |
      (SPI_SCLK_AI_PIN) |
          (SPI_CS_AI_0_PIN) |
              (SPI_CS_AI_1_PIN) |
                  (SPI_CS_AI_2_PIN) |
                      (SPI_CS_AI_3_PIN);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  GPIO_InitStructure.GPIO_Pin = (SPI_MISO_AI_PIN);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  SPI_AI_CS0_SET();
  SPI_AI_CS1_SET();
  SPI_AI_CS2_SET();
  SPI_AI_CS3_SET();
  SPI_AI_SCLK_CLR();
}

void rtd_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = (SPI_MOSI_RTD_PIN) | (SPI_SCLK_RTD_PIN) ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
    
  GPIO_InitStructure.GPIO_Pin = (SPI_MISO_RTD_PIN);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
    
  GPIO_InitStructure.GPIO_Pin =  (SPI_CS_RTD_0_PIN) | (SPI_CS_RTD_1_PIN) ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
    
  SPI_RTD_SCLK_CLR();
  delay_rtd();
  SPI_RTD_CS0_SET();
  SPI_RTD_CS1_SET();
}

uint8_t analog_in_read_write_byte(uint8_t c)
{
	int i;
  uint8_t res = 0;
    
  SPI_AI_SCLK_CLR();
  for(i = 0; i < 8; ++i)
	{
		res <<= 1;
    if(c&0x80)
			SPI_AI_MOSI_SET();
    else
      SPI_AI_MOSI_CLR();
    delay();
    SPI_AI_SCLK_SET();
    delay();
    SPI_AI_SCLK_CLR();
    delay();
    if(SPI_AI_MISO_PIN())
			res |= 1;
    c <<= 1;
  }    
  return res;
}

uint8_t rtd_read_write_byte(uint8_t c)
{
	int i;
  uint8_t res = 0;
  //SPI_RTD_SCLK_CLR();
  for (i = 0; i < 8; ++i)
	{
		res <<= 1;
    SPI_RTD_SCLK_SET();
    if(c&0x80)
		{
			SPI_RTD_MOSI_SET();
    }
    else
		{
			SPI_RTD_MOSI_CLR();
    }
        
    delay_rtd();
    SPI_RTD_SCLK_CLR();
    delay_rtd();
    if(SPI_RTD_MISO_PIN())
		{
			res |= 1;
    }
			c <<= 1;
  }
  return res;
}

float readSenor(u8 port,float range)
{
	uint8_t *dp;
  int i,j,k;
  u16 AD_value;
  float AD_data;

  i=3-port/3;
  j=port%3;
   
  dp = (void *)&adc_buffer[i].b55;
  switch(i)
	{
		case 0:	SPI_AI_CS0_CLR(); break;
		case 1: SPI_AI_CS1_CLR(); break;
		case 2: SPI_AI_CS2_CLR(); break;
		case 3: SPI_AI_CS3_CLR(); break;
		default:break;
	}
	delay();
  for (k = 0; k < sizeof(struct _adc_data); ++k) 
	{
		dp[k] = analog_in_read_write_byte(0xff);
    delay();
	}
	switch(i)
	{
		case 0:	SPI_AI_CS0_SET(); break;
		case 1: SPI_AI_CS1_SET(); break;
		case 2: SPI_AI_CS2_SET(); break;
		case 3: SPI_AI_CS3_SET(); break;
		default:break;
	}   
	delay();
	dp = (void *)&adc_buffer[i].b55;
	switch(i)
	{
		case 0:	SPI_AI_CS0_CLR(); break;
		case 1: SPI_AI_CS1_CLR(); break;
		case 2: SPI_AI_CS2_CLR(); break;
		case 3: SPI_AI_CS3_CLR(); break;
		default:break;
	}   
  delay();
  for (k = 0; k < sizeof(struct _adc_data); ++k)
	{
		dp[k] = analog_in_read_write_byte(0xff);
    delay();
	}
	switch(i)
	{
		case 0:	SPI_AI_CS0_SET(); break;
		case 1: SPI_AI_CS1_SET(); break;
		case 2: SPI_AI_CS2_SET(); break;
		case 3: SPI_AI_CS3_SET(); break;
		default:break;
	}
  delay();
  AD_value=adc_buffer[i].data[j]; 
  switch(port)
  {
		case 0: AD_data = ((float)AD_value/108.0)*range; break;
		case 1: AD_data = ((float)AD_value/108.2)*range; break;
		case 2: AD_data = ((float)AD_value/108.5)*range; break;
		case 3: AD_data = ((float)AD_value/107.4)*range; break;
		case 4: AD_data = ((float)AD_value/107.6)*range; break;
		case 5: AD_data = ((float)AD_value/107.6)*range; break;
		case 6: AD_data = ((float)AD_value/107.7)*range; break;
		case 7: AD_data = ((float)AD_value/107.8)*range; break;
		case 8: AD_data = ((float)AD_value/107.8)*range; break;
		case 9: AD_data = ((float)AD_value/106.7)*range; break;
		case 10: AD_data = ((float)AD_value/106.5)*range; break;
		case 11: AD_data = ((float)AD_value/106.7)*range; break;
		default: break;
  }  
  return AD_data;
}

float readTemp(u8 port)
{
	uint8_t *dp;
  //uint8_t dp[8];
  int i;
  float T_data;
	//analog_in_init();
  delay_rtd();
  dp = (void *)&rtd_buffer[0].b55;
  SPI_RTD_CS0_CLR();
  delay_rtd();
  for (i = 0; i < sizeof(struct _rtd_data); ++i)
	{
		dp[i] = rtd_read_write_byte(cmd[i]);
    delay_rtd();
  }
  SPI_RTD_CS0_SET();	
	switch(port)
	{
		case 12: T_data= ((float)rtd_buffer[0].temp_1)/10; break;
		case 13: T_data= ((float)rtd_buffer[0].temp_2)/10; break;
		case 14: T_data= ((float)rtd_buffer[0].temp_3)/10; break;
		case 15: T_data= ((float)rtd_buffer[0].temp_4)/10; break;
		default:break;
	}
	return T_data; 
}

void APortCIn(float aarr[16],float range[12])
{
	u8 i;     
  for(i=0;i<12;i++)
  {          
		aarr[i]=readSenor(i,range[i]);
  }
  for(i=12;i<16;i++)
  {
		aarr[i]=readTemp(i);
  }
}

float APortIn(u8 port, float range)
{
	float analog;
	if(port<12)
		analog=readSenor(port,range); 
  else
		analog=readTemp(port);
  return analog;
}
