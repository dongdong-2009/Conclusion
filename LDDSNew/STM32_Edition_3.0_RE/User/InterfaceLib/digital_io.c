#include <stdio.h>
#include <stdint.h>
#include "stm32f10x.h"
#include "digital_io.h"


#define HIGH 0x01
#define LOW  0x00

#define DO0  0x00
#define DO1  0x01
#define DO2  0x02
#define DO3  0x03
#define DO4  0x04
#define DO5  0x05
#define DO6  0x06
#define DO7  0x07

#define cont  DO0
#define DI0  0x00
#define DI1  0x01
#define DI2  0x02
#define DI3  0x03
#define DI4  0x04
#define DI5  0x05
#define DI6  0x06
#define DI7  0x07

void GpioRcc_Configuration(void);
void Gpio_Configuration(void);

/*-----------------------------interface function definition-------------------------------*/
 void IO_Configuration(void)
 {
    GpioRcc_Configuration();
	Gpio_Configuration();
 }

void DO_onechannel(uint8_t port,char level)
{
   uint16_t channel;
   switch(port)
   {
      case DO0: channel = GPIO_Pin_8;break;
	  case DO1: channel = GPIO_Pin_9;break;
	  case DO2: channel = GPIO_Pin_10;break;
	  case DO3: channel = GPIO_Pin_11;break;
	  case DO4: channel = GPIO_Pin_12;break;
	  case DO5: channel = GPIO_Pin_13;break;
	  case DO6: channel = GPIO_Pin_14;break;
	  case DO7: channel = GPIO_Pin_15;break;
	  default: break;
   }
   if(level == HIGH )
     GPIO_SetBits(GPIOE,channel);
   else if(level == LOW)
	 GPIO_ResetBits(GPIOE,channel);     
}

void DO_allchannels(uint8_t* DO_data)
{
  GPIO_Write(GPIOE,(uint16_t)(*DO_data << 8)&0xff00);
}


void DI_onechannel(uint8_t port,char* DI_data)
{
   uint16_t channel;	 
   switch(port)
   {
      case DI0: channel = GPIO_Pin_8;break;
	  case DI1: channel = GPIO_Pin_9;break;
	  case DI2: channel = GPIO_Pin_10;break;
	  case DI3: channel = GPIO_Pin_11;break;
	  case DI4: channel = GPIO_Pin_12;break;
	  case DI5: channel = GPIO_Pin_13;break;
	  case DI6: channel = GPIO_Pin_14;break;
	  case DI7: channel = GPIO_Pin_15;break;
	  default: break;
   }
  DI_data[port] = (char)GPIO_ReadInputDataBit(GPIOF,channel);
}

void DI_allchannels(char* DI_data)
{
  uint8_t i;
  uint16_t channel = 0x0100;
  for(i=0;i<8;i++)
  {
    DI_data[i] = (char)GPIO_ReadInputDataBit(GPIOF,(uint16_t)(channel<<i));
  }
}
/*-----------------------------local function definition-------------------------------*/
void GpioRcc_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOE,ENABLE);	
}

void Gpio_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;	

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin =GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
}
/*-----------------------------End of source file-------------------------------------*/
