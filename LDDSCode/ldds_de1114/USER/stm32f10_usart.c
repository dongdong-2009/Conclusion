#include "stm32f10_usart.h"

//rcc-rcc-rcc-rcc-rcc-rcc-rcc-rcc-rcc-rcc-rcc//
void UsartRcc_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
}
//nvic-nvic-nvic-nvic-nvic-nvic-nvic-nvic-nvic-nvic//
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;//中断结构体
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);//设置中断向量表  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //分组


    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//设置串口1中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
    NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//设置串口2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
	NVIC_Init(&NVIC_InitStructure); 

	NVIC_InitStructure.NVIC_IRQChannel =TIM1_UP_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4; // 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel =TIM2_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5; // 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
	NVIC_Init(&NVIC_InitStructure);


    NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7; // 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
	NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel =TIM4_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 8; // 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
	NVIC_Init(&NVIC_InitStructure);


}
void UsartGPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

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
}
void Usart_Rx(void)
{
	delay_ms(1);  
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}
void Usart_Tx(void)
{	 
	delay_us(2500);
 	GPIO_SetBits(GPIOA,GPIO_Pin_8); 
}

void Uart_Rx(void)
{ 
	delay_ms(1);
	GPIO_SetBits(GPIOD,GPIO_Pin_7);
}
void Uart_Tx(void)
{
    delay_us(2500);	 
    GPIO_ResetBits(GPIOD,GPIO_Pin_7); 
}


void Usart_Configuration(void)
{
	USART_InitTypeDef USART_InitStruct;

	UsartRcc_Configuration();
	UsartGPIO_Configuration();
	NVIC_Configuration();
	USART_DeInit(USART1);
	USART_DeInit(USART2);

	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_9b;
	USART_InitStruct.USART_Parity = USART_Parity_Odd;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	
	USART_Init(USART1, &USART_InitStruct); 		 
	USART_ClearFlag(USART1,USART_FLAG_TC);
	USART_Cmd(USART1, ENABLE);	
		

	USART_Init(USART2, &USART_InitStruct);	
	USART_ClearFlag(USART2,USART_FLAG_TC);
	USART_Cmd(USART2, ENABLE);
}
void UsartST(void)
{
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 
    Usart_Rx();   
}
void UartST(void)
{
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    Uart_Rx();
} 
void UsartSP(void)
{
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
	Usart_Rx();     
} 
void UartSP(void)
{
    USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
    Uart_Rx();
}
