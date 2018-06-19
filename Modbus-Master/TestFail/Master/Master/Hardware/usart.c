#include "usart.h"
#include "string.h"
#include "mb_port.h"

//void prvvUARTTxReadyISR( void );
//void prvvUARTRxISR( void );

void USART1_Init()
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
	USART_Cmd(USART1,ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	//设置中断向量表位置和偏移量  
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);    //向量表位于FLASH，向量表基地址的偏移量为0 
	
	//设置优先级分组：先占优先级和从优先级。
	//输入参数：优先级分组位长度
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  //先占优先级4位，从优先级0位
  
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;          //USART1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
	
	RS_485_TX_EN();
}

void USART1_SendData(u8 ch)
{
//	RS_485_TX_EN;
	
	USART_SendData(USART1,ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==0);
	
//	RS_485_RX_EN;
}

void USART1_SendNData(u8 *str,u16 len)
{
 	u16 i = 0;
	RS_485_TX_EN();
	for(i = 0;i<len;i++)
	{			
		USART_SendData(USART1,str[i]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==0);
	}	
	RS_485_RX_EN();
}

void USART1_SendString(u8 *str)
{
	RS_485_TX_EN();
	while(*str)
	{
		USART_SendData(USART1,*str);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==0);
		str++;
	}
	RS_485_RX_EN();
}

void rs485_ctrl_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void USART_Configuration(USART_TypeDef *USARTx,uint32_t bdrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	if(USARTx==USART1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		USART_InitStructure.USART_BaudRate = bdrate;
		USART_InitStructure.USART_WordLength=USART_WordLength_8b;
		USART_InitStructure.USART_StopBits=USART_StopBits_1;
		USART_InitStructure.USART_Parity=USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //发送和接受使能
		USART_Init(USART1, &USART_InitStructure);                                       //初始化串口2
		//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);                                  	//接收中断使能
		USART_Cmd(USART1, ENABLE);                                                      //使能时串口2
		//USART_ClearITPendingBit(UART5, USART_IT_TC);                                   //清除中断TC位

		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	         //串口2中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;    //抢占优先级3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	         //子优先级3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           	 //IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);                              //根据指定的参数初始化VIC寄存器

		rs485_ctrl_init();
		RS_485_RX_EN();
	}
	else if(USARTx==USART2)
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
	
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//		GPIO_Init(GPIOD, &GPIO_InitStructure);
		
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
		
		rs485_ctrl_init();
		RS_485_RX_EN();
	}
}

//UASRT1的中断函数
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	//u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		//prvvUARTRxISR();
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	else if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
	{
		//prvvUARTTxReadyISR();
		USART_ClearITPendingBit(USART1, USART_IT_TXE);
	}
}

//UASRT2的中断函数
void USART2_IRQHandler(void)                	//串口1中断服务程序
{
	//u8 Res;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		//prvvUARTRxISR();
		Receive_IRQ();
	}
	else if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
	{
		USART_ClearITPendingBit(USART2, USART_IT_TC);
		//prvvUARTTxReadyISR();
		Send_IRQ();
	}
}

void UART5_SendNData(u8 *str,u16 len)
{
 	unsigned int i = 0;
	for(i = 0;i < len;i++)
	{			
		USART_SendData(USART2,*str);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==0);
		str++;
	}	
}

void UART5_SendData(u8 ch)
{
	USART_SendData(USART2,ch);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==0);
}

void UART5_SendString(u8 *str)
{
	while(*str)
	{
		USART_SendData(USART2,*str);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==0);
		str++;
	}
}

u8 GetString(u8 *buff,u8 len,u16 *timeFlag,u16 timeout)
{
	*timeFlag=timeout*2;
	while (len)
	{
		if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET)
		{
			if(*timeFlag==0)	return 0;		//超时了
		}
		else
		{
			*buff = (uint8_t)USART2->DR;
			if(*buff=='\r')	return 1;
			buff++;
			len--;
		}
	}
	return 1;												//接收完成
}

