#include "usart.h"
#include "string.h"
#include "mb_port.h"

//void prvvUARTTxReadyISR( void );
//void prvvUARTRxISR( void );

void USART1_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	
	// ��GPIOA��USART1��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//����USART1��IO��ʼ��	GPIOA 9--TX 10--RX 11--DE
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
	
	
	//����USART1���ó�ʼ��
	USART_DeInit(USART1);
	//���ڲ����ʵ���Ϣ���ã�USART1��USART2������ͬ
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStruct);
	USART_Cmd(USART1,ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	//�����ж�������λ�ú�ƫ����  
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);    //������λ��FLASH�����������ַ��ƫ����Ϊ0 
	
	//�������ȼ����飺��ռ���ȼ��ʹ����ȼ���
	//������������ȼ�����λ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  //��ռ���ȼ�4λ�������ȼ�0λ
  
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;          //USART1�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�1
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
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //���ͺͽ���ʹ��
		USART_Init(USART1, &USART_InitStructure);                                       //��ʼ������2
		//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);                                  	//�����ж�ʹ��
		USART_Cmd(USART1, ENABLE);                                                      //ʹ��ʱ����2
		//USART_ClearITPendingBit(UART5, USART_IT_TC);                                   //����ж�TCλ

		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	         //����2�ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;    //��ռ���ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	         //�����ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           	 //IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);                              //����ָ���Ĳ�����ʼ��VIC�Ĵ���

		rs485_ctrl_init();
		RS_485_RX_EN();
	}
	else if(USARTx==USART2)
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
	
		//��GPIOD��USART2��ʱ�ӣ�ͬʱ��Ҫӳ��ܽ�
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
	
		//USART2�ܼ����� PD5--TX PD6--RX PD7--DE
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
	
		USART_InitStructure.USART_BaudRate = 9600;//һ������Ϊ9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

		USART_Init(USART2, &USART_InitStructure);
	
		USART_ClearFlag(USART2,USART_FLAG_TC);
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
		USART_Cmd(USART2, ENABLE);
		
		rs485_ctrl_init();
		RS_485_RX_EN();
	}
}

//UASRT1���жϺ���
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	//u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
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

//UASRT2���жϺ���
void USART2_IRQHandler(void)                	//����1�жϷ������
{
	//u8 Res;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
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
			if(*timeFlag==0)	return 0;		//��ʱ��
		}
		else
		{
			*buff = (uint8_t)USART2->DR;
			if(*buff=='\r')	return 1;
			buff++;
			len--;
		}
	}
	return 1;												//�������
}

