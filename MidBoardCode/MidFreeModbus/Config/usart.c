#include "usart.h"

void UsartConfigure(void)
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
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	//���ڽ���״̬
	DE2=1;
	
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
	
	USART_ITConfig(USART2,USART_IT_PE,ENABLE);
	USART_ITConfig(USART2,USART_IT_ERR,ENABLE);
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
	DE2=0;
	delay_ms(2);
	USART_ITConfig(USART2,USART_IT_TXE,ENABLE);
	USART_SendData(USART2,dat);
}


///*********************************************************************************************************
//* Functoin name:       void UsartSendData(int num,char* sendbuffer)
//* Descriptions:        USART����num���ַ�
//* input paraments:     num���������ݵĸ���
//*					   sendbuffer�����������ݵĻ�������
//* output paraments:    ��    
//* Returned values:     ��
//*********************************************************************************************************/
void UsartSendData(int num,char* sendbuffer)
{
	int i;
  for(i=0;i<num;i++)
	{
		Usart_SendChar(sendbuffer[i]);
  }
}
