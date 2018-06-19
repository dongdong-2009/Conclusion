#include "usart.h"

void UsartConfigure(void)
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
	
	//���ڽ���
	DE1=1;
	
	//USART Configuration
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
	
	USART_ClearFlag(USART1,USART_FLAG_TC);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
	USART_ITConfig(USART1,USART_IT_PE,ENABLE);
	USART_ITConfig(USART1,USART_IT_ERR,ENABLE);
  USART_Cmd(USART1, ENABLE); 
}

///*********************************************************************************************************
//* Functoin name:       Usart_GetCahr
//* Descriptions:        USART����һ���ַ�
//* input paraments:     USARTx���õ��Ĵ��ں�
//* output paraments:    ��    
//* Returned values:     dat:���յ�������
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
//* Descriptions:        USART����һ���ַ�
//* input paraments:     USARTx���õ��Ĵ��ں� 
//*						dat����Ҫ���͵�����
//* output paraments:    ��    
//* Returned values:     ��
//*	Remark:DEΪ1���ڽ���״̬��DEΪ0���ڷ���״̬
//*********************************************************************************************************/
void Usart_SendChar(char dat)
{  
	DE1=0;
	delay_ms(1);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//�ȴ���һ���ֽڷ������
  USART_SendData(USART1,dat);   	
}


///*********************************************************************************************************
//* Functoin name:       void UsartSendData(int num,char* sendbuffer)
//* Descriptions:        USART����num���ַ�
//* input paraments:     num���������ݵĸ���
//*					   sendbuffer�����������ݵĻ�������
//* output paraments:    ��    
//* Returned values:     ��
//*********************************************************************************************************/
void UsartSendData(uint8_t num,char* sendbuffer)
{
	int i;
  for(i=0;i<num;i++)
	{
		Usart_SendChar(sendbuffer[i]);
  }
}
