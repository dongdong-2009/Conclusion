#include "usart.h"

void NVIC_Configuration(void);
void Usart_GPIO_Configuration(void);
void Uart_GPIO_Configuration(void) ;
void delay_usart(void);
/*********************************************************************************************************
* Functoin name:       Usart_SendChar
* Descriptions:        USART发送一个字符
* input paraments:     USARTx：用到的串口号
*						dat：需要发送的数据
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/
void Usart_SendChar(char dat)
{  
    GPIO_SetBits(GPIOA,GPIO_Pin_8);	//发送状态
	delay_usart();
	USART_SendData(USART1,dat);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);  //接收状态
    delay_usart();
}



/*********************************************************************************************************
* Functoin name:       Uart_SendChar
* Descriptions:        UART发送一个字符
* input paraments:     UARTx：用到的串口号
*						dat：需要发送的数据
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/
void Uart_SendChar(char dat)
{  
    GPIO_SetBits(GPIOD,GPIO_Pin_7);	//发送状态
	delay_usart();
	USART_SendData(USART2,dat);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC) == RESET);
	GPIO_ResetBits(GPIOD,GPIO_Pin_7);  //接收状态
    delay_usart();
}




/*********************************************************************************************************
* Functoin name:       void UsartSendData(int num,char* sendbuffer)
* Descriptions:        USART发送num个字符
* input paraments:     num：发送数据的个数
*					   sendbuffer：待发送数据的缓存数组
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/
void UsartSendData(int num,char* sendbuffer)
{
   int i;
   for(i=0;i<num;i++)
   {
     Usart_SendChar(sendbuffer[i]); 
   }
}


/*********************************************************************************************************
* Functoin name:       void UsartSendData(int num,char* sendbuffer)
* Descriptions:        USART发送num个字符
* input paraments:     num：发送数据的个数
*					   sendbuffer：待发送数据的缓存数组
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/
void UartSendData(int num,char* sendbuffer)
{
   int i;
   for(i=0;i<num;i++)
   {
     Uart_SendChar(sendbuffer[i]); 
   }
}





void delay_usart(void)
{
    u8 i=25;
    while(i--);
}
/*********************************************************************************************************
* Functoin name:       Usart_GetCahr
* Descriptions:        USART接收一个字符
* input paraments:     USARTx：用到的串口号
* output paraments:    无    
* Returned values:     dat:接收到的数据
*********************************************************************************************************/
char Usart_GetChar(USART_TypeDef* USARTx)
{
	char dat;
//	while(!USART_GetFlagStatus(USARTx,USART_FLAG_RXNE));
	dat = (char)(USART_ReceiveData(USARTx)&0xff);	
	return dat;		
}

/*********************************************************************************************************
* Functoin name:       Usart_Total_Initi
* Descriptions:        完成USART通信的所有初始化
*                      包括：NVIC中断嵌套 TIM1定时与中断 USART1初始化						  
* input paraments:     无
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/
void Usart_Initi(void)
{
    NVIC_Configuration();
	Usart_GPIO_Configuration();
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);  //使USART1常处于接收状态
}

void Uart_Initi(void)
{
   NVIC_Configuration();
	Uart_GPIO_Configuration();
    GPIO_SetBits(GPIOD,GPIO_Pin_7); //使UART4常处于接收状态
}

void  TurnOnUsart(void)
{
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_8);  
}
void  TurnOffUsart(void)
{
   	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}


void  TurnOnUart4(void)
{
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//	GPIO_SetBits(GPIOD,GPIO_Pin_7);
}
void  TurnOffUart4(void)
{
   	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
//	GPIO_SetBits(GPIOD,GPIO_Pin_7); 
}
/*********************************************************************************************************
* Functoin name:       Usart_GPIO_Configuration
* Descriptions:        初始化USart
*					   包括：时钟、IO、USART工作方式配置
* input paraments:     无  
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/				   
void Usart_GPIO_Configuration(void)
{ 
 	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;

	// 打开GPIOA与USART1的时钟

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	  
   
        
	//串口USART1的IO初始化	GPIOA 9--TX 10--RX 8--DE

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);	

	//串口USART1配置初始化

	USART_DeInit(USART1);
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStruct); 

    USART_ClearFlag(USART1,USART_FLAG_TC);   
    //使能USART1接收中断和使能USART1
   USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1,ENABLE);
}



/*********************************************************************************************************
* Functoin name:       Uart_GPIO_Configuration
* Descriptions:        初始化Uart
*					   包括：时钟、IO、UART工作方式配置
* input paraments:     无  
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/				   
void Uart_GPIO_Configuration(void)
{ 
 	GPIO_InitTypeDef   GPIO_InitStruct;
	USART_InitTypeDef  USART_InitStruct;

   	// 打开GPIOC与UART4的时钟

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
   	//串口UART4 的IO初始化	

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	//串口UART4 配置初始化


	USART_DeInit(USART2);
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART2, &USART_InitStruct); 


    USART_ClearFlag(USART2,USART_FLAG_TC);   

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);


}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// <Functoin Descriptions> Complete the configuration of nested interrupts: USART1 USART4 TIM1--TIM5 
///<input paraments>    Null
/// <output paraments>  Null   
/// <Return values>     Null
////////////////////////////////////////////////////////////////////////////////////////////////////  
void NVIC_Configuration(void)
{
 NVIC_InitTypeDef NVIC_InitStructure; 
 NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);//设置中断向量表  
 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //分组, 一个工程中只能使用一种分组方式
  
 NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; //USART1中断
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级1
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
 NVIC_Init(&NVIC_InitStructure); 


 NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //USART2中断
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级2
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
 NVIC_Init(&NVIC_InitStructure); 

  

  NVIC_InitStructure.NVIC_IRQChannel =TIM1_UP_IRQn; //TIM1中断   
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //抢占优先级3 	
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
 NVIC_Init(&NVIC_InitStructure);



 NVIC_InitStructure.NVIC_IRQChannel =TIM2_IRQn;//TIM2中断   
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4; //抢占优先级4 //TIM1的优先级比TIM2的优先级要高
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
 NVIC_Init(&NVIC_InitStructure);

 NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;//TIM3中断   
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5; //抢占优先级5 //TIM3
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
 NVIC_Init(&NVIC_InitStructure);

 NVIC_InitStructure.NVIC_IRQChannel =TIM4_IRQn;//TIM4中断   
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6; //抢占优先级6 //TIM4
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
 NVIC_Init(&NVIC_InitStructure);

 NVIC_InitStructure.NVIC_IRQChannel =TIM5_IRQn;//TIM2中断   
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7; //抢占优先级7 //TIM5
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
 NVIC_Init(&NVIC_InitStructure);
}					 

/*********************************************************************************************************
*                                        End Of File
*********************************************************************************************************/



