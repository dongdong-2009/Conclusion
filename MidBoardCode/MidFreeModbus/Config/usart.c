#include "usart.h"

void UsartConfigure(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	//打开GPIOD和USART2的时钟，同时需要映射管脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
	
	//USART2管家配置 PD5--TX PD6--RX PD7--DE
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	//处于接收状态
	DE2=1;
	
	//USART Configuration
	USART_DeInit(USART2);
	
	USART_InitStructure.USART_BaudRate = 9600;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART2, &USART_InitStructure);
	
	USART_ClearFlag(USART2,USART_FLAG_TC);
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
  USART_Cmd(USART2, ENABLE); 
	
	USART_ITConfig(USART2,USART_IT_PE,ENABLE);
	USART_ITConfig(USART2,USART_IT_ERR,ENABLE);
}

///*********************************************************************************************************
//* Functoin name:       Usart_GetCahr
//* Descriptions:        USART接收一个字符
//* input paraments:     USARTx：用到的串口号
//* output paraments:    无    
//* Returned values:     dat:接收到的数据
//*********************************************************************************************************/
char Usart_GetChar(USART_TypeDef* USARTx)
{
	char dat;
	//while(!USART_GetFlagStatus(USARTx,USART_FLAG_RXNE));
	dat = (char)(USART_ReceiveData(USARTx)&0xff);	
	return dat;		
}

///*********************************************************************************************************
//* Functoin name:       Usart_SendChar
//* Descriptions:        USART发送一个字符
//* input paraments:     USARTx：用到的串口号 
//*						dat：需要发送的数据
//* output paraments:    无    
//* Returned values:     无
//*	Remark:DE为1处于接收状态，DE为0处于发送状态
//*********************************************************************************************************/
void Usart_SendChar(char dat)
{  
	DE2=0;
	delay_ms(2);
	USART_ITConfig(USART2,USART_IT_TXE,ENABLE);
	USART_SendData(USART2,dat);
}


///*********************************************************************************************************
//* Functoin name:       void UsartSendData(int num,char* sendbuffer)
//* Descriptions:        USART发送num个字符
//* input paraments:     num：发送数据的个数
//*					   sendbuffer：待发送数据的缓存数组
//* output paraments:    无    
//* Returned values:     无
//*********************************************************************************************************/
void UsartSendData(int num,char* sendbuffer)
{
	int i;
  for(i=0;i<num;i++)
	{
		Usart_SendChar(sendbuffer[i]);
  }
}
