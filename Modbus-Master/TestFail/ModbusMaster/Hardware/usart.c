#include "usart.h"

void UsartConfigure(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	
	// 打开GPIOA与USART1的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//串口USART1的IO初始化	GPIOA 9--TX 10--RX 11--DE
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
	//处于接收
	DE1=1;
	
	//USART Configuration
	//串口USART1配置初始化
	USART_DeInit(USART1);
	//串口波特率等信息设置，USART1和USART2配置相同
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStruct);
	
	USART_ClearFlag(USART1,USART_FLAG_TC);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
	USART_ITConfig(USART1,USART_IT_PE,ENABLE);
	USART_ITConfig(USART1,USART_IT_ERR,ENABLE);
  USART_Cmd(USART1, ENABLE); 
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
	DE1=0;
	delay_ms(1);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//等待上一个字节发送完毕
  USART_SendData(USART1,dat);   	
}


///*********************************************************************************************************
//* Functoin name:       void UsartSendData(int num,char* sendbuffer)
//* Descriptions:        USART发送num个字符
//* input paraments:     num：发送数据的个数
//*					   sendbuffer：待发送数据的缓存数组
//* output paraments:    无    
//* Returned values:     无
//*********************************************************************************************************/
void UsartSendData(uint8_t num,char* sendbuffer)
{
	int i;
  for(i=0;i<num;i++)
	{
		Usart_SendChar(sendbuffer[i]);
  }
}
