/**
  ******************************************************************************
  * @file    bsp_usart1.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   usartӦ��bsp
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO-MINI STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "bsp_usart1.h"
//#include "stm32f10x_rcc.h"  main�������ͷ������
 /**
  * @brief  USART1 GPIO ����,����ģʽ���á�9600 8-N-1
  * @param  ��
  * @retval ��
  */

void Delay_MS(u16 dly)
{
	u16 i,j;
	for(i=0;i<dly;i++)
		for(j=1000;j>0;j--);
}





void delay_us(u16 dly1)
{
	u16 i;
	for(i=dly1;i>0;i--);
}

void  RCC_Configuration(void)
{
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	FLASH_SetLatency(FLASH_Latency_2);
	
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);

	RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while(RCC_GetSYSCLKSource()!=0x08);                                         

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //���������úõ�ֵ����ʼ��GPIOA�Ĺܽ�  
	
	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//���ö�HX711�Ĵ��ڿ��ƵĹܽţ�b11Ϊdout��b12Ϊsck,DOUTΪ���룬sckΪ���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  //���������úõ�ֵ����ʼ��GPIOA�Ĺܽ�  
	
	/* Configure sclk(PB.12) as output */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}
	
	
	
	
void USART1_Configuration(void)
{
	
	USART_InitTypeDef USART_InitStructure;
	
	/* config USART1 clock */
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	/* USART1 GPIO config */
	
	
	
	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;//������żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);//��ʼ������
	
	/* ʹ�ܴ���1�����ж� */
	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART1, ENABLE);//��������
}

//PB11 ΪDADAT, PB12Ϊsck
unsigned long Read_HX711(void)
{
	unsigned long val = 0;
	unsigned char i = 0;
	
	GPIO_SetBits(GPIOB,GPIO_Pin_11); //DOUT
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11));
	delay_us(1);
	
	for(i=0;i<24;i++)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		val = val << 1;
		delay_us(1);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		if(	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11))
		val++;		
		delay_us(2);	
	}
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	val=val^0x800000;
	delay_us(2);
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	delay_us(2);
	return val;
}


/// ����USART1�����ж�
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


/// �ض���c�⺯��printf��USART1
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ�USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);		
	
		return (ch);
}

/// �ض���c�⺯��scanf��USART1
int fgetc(FILE *f)
{
		/* �ȴ�����1�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
/*********************************************END OF FILE**********************/
