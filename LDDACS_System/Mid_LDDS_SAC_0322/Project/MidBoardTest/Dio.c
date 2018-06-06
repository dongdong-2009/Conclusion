#include "Dio.h"
#include "Globle.h"

void DiGpioCfg(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //使能PE端口时钟

	GPIO_InitStructure.GPIO_Pin = Di0_Pin|Di1_Pin|Di2_Pin|Di3_Pin;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(Di_Port, &GPIO_InitStructure);
}

void DoMuxGpioCfg(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //使能PA端口时钟
	
	GPIO_ResetBits(Do_Port,Do1_Pin|Do2_Pin|Do3_Pin|Do4_Pin);
	
	GPIO_InitStructure.GPIO_Pin = Do1_Pin|Do2_Pin|Do3_Pin|Do4_Pin;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(Do_Port, &GPIO_InitStructure);
}

u8 GetDiMap(char* DiREG)
{
	u16 temp; 
	u8 i;
	temp=GPIO_ReadInputData(Di_Port);
	
	for(i=0;i<8;i++)
	{
		DiREG[i]=temp&0x01;       
		temp>>=1;
	}

	return (temp>>8)&0xff;
}

u8 DI_onechannel(u8 channel)
{
  u16 DiMap;
  u8  DiValue=0; 
//  char temp[8];
  DiMap=GetDiMap(DI_data); 
  DiMap>>=channel;
  DiValue =DiMap&0x01;	  

  return DiValue;

}
void DO_onechannel(u8 channel,u8 State)
{
	switch(State)
	{
		case SpdtOFF:
								switch(channel)
								{
									case 1:GPIO_ResetBits(Do_Port,Do1_Pin);break;
									case 2:GPIO_ResetBits(Do_Port,Do2_Pin);break;
									case 3:GPIO_ResetBits(Do_Port,Do3_Pin);break;
									case 4:GPIO_ResetBits(Do_Port,Do4_Pin);break;

									default:break;									
								}
								break;
		case SpdtON:
								switch(channel)
								{
									case 1:GPIO_SetBits(Do_Port,Do1_Pin);break;
									case 2:GPIO_SetBits(Do_Port,Do2_Pin);break;
									case 3:GPIO_SetBits(Do_Port,Do3_Pin);break;
									case 4:GPIO_SetBits(Do_Port,Do4_Pin);break;

									default:break;									
								}
								break;
		default:break;
	}
}

void DioCfg(void)
{
	DoMuxGpioCfg();
	DiGpioCfg();
}


