#include "usart.h"

void NVIC_Configuration(void);
void Usart_GPIO_Configuration(void);
void Uart_GPIO_Configuration(void) ;
void delay_usart(void);
/*********************************************************************************************************
* Functoin name:       Usart_SendChar
* Descriptions:        USART����һ���ַ�
* input paraments:     USARTx���õ��Ĵ��ں�
*						dat����Ҫ���͵�����
* output paraments:    ��    
* Returned values:     ��
*********************************************************************************************************/
void Usart_SendChar(char dat)
{  
    GPIO_SetBits(GPIOA,GPIO_Pin_8);	//����״̬
	delay_usart();
	USART_SendData(USART1,dat);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);  //����״̬
    delay_usart();
}



/*********************************************************************************************************
* Functoin name:       Uart_SendChar
* Descriptions:        UART����һ���ַ�
* input paraments:     UARTx���õ��Ĵ��ں�
*						dat����Ҫ���͵�����
* output paraments:    ��    
* Returned values:     ��
*********************************************************************************************************/
void Uart_SendChar(char dat)
{  
    GPIO_SetBits(GPIOD,GPIO_Pin_7);	//����״̬
	delay_usart();
	USART_SendData(USART2,dat);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC) == RESET);
	GPIO_ResetBits(GPIOD,GPIO_Pin_7);  //����״̬
    delay_usart();
}




/*********************************************************************************************************
* Functoin name:       void UsartSendData(int num,char* sendbuffer)
* Descriptions:        USART����num���ַ�
* input paraments:     num���������ݵĸ���
*					   sendbuffer�����������ݵĻ�������
* output paraments:    ��    
* Returned values:     ��
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
* Descriptions:        USART����num���ַ�
* input paraments:     num���������ݵĸ���
*					   sendbuffer�����������ݵĻ�������
* output paraments:    ��    
* Returned values:     ��
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
* Descriptions:        USART����һ���ַ�
* input paraments:     USARTx���õ��Ĵ��ں�
* output paraments:    ��    
* Returned values:     dat:���յ�������
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
* Descriptions:        ���USARTͨ�ŵ����г�ʼ��
*                      ������NVIC�ж�Ƕ�� TIM1��ʱ���ж� USART1��ʼ��						  
* input paraments:     ��
* output paraments:    ��    
* Returned values:     ��
*********************************************************************************************************/
void Usart_Initi(void)
{
    NVIC_Configuration();
	Usart_GPIO_Configuration();
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);  //ʹUSART1�����ڽ���״̬
}

void Uart_Initi(void)
{
   NVIC_Configuration();
	Uart_GPIO_Configuration();
    GPIO_SetBits(GPIOD,GPIO_Pin_7); //ʹUART4�����ڽ���״̬
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
* Descriptions:        ��ʼ��USart
*					   ������ʱ�ӡ�IO��USART������ʽ����
* input paraments:     ��  
* output paraments:    ��    
* Returned values:     ��
*********************************************************************************************************/				   
void Usart_GPIO_Configuration(void)
{ 
 	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;

	// ��GPIOA��USART1��ʱ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	  
   
        
	//����USART1��IO��ʼ��	GPIOA 9--TX 10--RX 8--DE

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

	//����USART1���ó�ʼ��

	USART_DeInit(USART1);
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStruct); 

    USART_ClearFlag(USART1,USART_FLAG_TC);   
    //ʹ��USART1�����жϺ�ʹ��USART1
   USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1,ENABLE);
}



/*********************************************************************************************************
* Functoin name:       Uart_GPIO_Configuration
* Descriptions:        ��ʼ��Uart
*					   ������ʱ�ӡ�IO��UART������ʽ����
* input paraments:     ��  
* output paraments:    ��    
* Returned values:     ��
*********************************************************************************************************/				   
void Uart_GPIO_Configuration(void)
{ 
 	GPIO_InitTypeDef   GPIO_InitStruct;
	USART_InitTypeDef  USART_InitStruct;

   	// ��GPIOC��UART4��ʱ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
   	//����UART4 ��IO��ʼ��	

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

	//����UART4 ���ó�ʼ��


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
 NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);//�����ж�������  
 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //����, һ��������ֻ��ʹ��һ�ַ��鷽ʽ
  
 NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; //USART1�ж�
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�1
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
 NVIC_Init(&NVIC_InitStructure); 


 NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //USART2�ж�
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�2
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
 NVIC_Init(&NVIC_InitStructure); 

  

  NVIC_InitStructure.NVIC_IRQChannel =TIM1_UP_IRQn; //TIM1�ж�   
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //��ռ���ȼ�3 	
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
 NVIC_Init(&NVIC_InitStructure);



 NVIC_InitStructure.NVIC_IRQChannel =TIM2_IRQn;//TIM2�ж�   
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4; //��ռ���ȼ�4 //TIM1�����ȼ���TIM2�����ȼ�Ҫ��
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
 NVIC_Init(&NVIC_InitStructure);

 NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;//TIM3�ж�   
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5; //��ռ���ȼ�5 //TIM3
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
 NVIC_Init(&NVIC_InitStructure);

 NVIC_InitStructure.NVIC_IRQChannel =TIM4_IRQn;//TIM4�ж�   
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6; //��ռ���ȼ�6 //TIM4
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
 NVIC_Init(&NVIC_InitStructure);

 NVIC_InitStructure.NVIC_IRQChannel =TIM5_IRQn;//TIM2�ж�   
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7; //��ռ���ȼ�7 //TIM5
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
 NVIC_Init(&NVIC_InitStructure);
}					 

/*********************************************************************************************************
*                                        End Of File
*********************************************************************************************************/



