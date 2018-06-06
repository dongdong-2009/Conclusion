#include "stm32f10x.h"
#include "rtd.h"
#include "delay.h"
#include "Globle.h"
#include "stm32f10x_tim.h"

void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);



//  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
//	
//	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;     //ѡ���ж�ͨ��2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռʽ�ж����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //��Ӧʽ�ж����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                   //ʹ���ж�
	NVIC_Init(&NVIC_InitStructure);
}
void LedInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void UART_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	
	GPIO_InitTypeDef GPIO_InitStructure;

	
	RCC_APB2PeriphClockCmd(USART1_GPIO_CLK  , ENABLE);
	RCC_APB2PeriphClockCmd(USART2_GPIO_CLK  , ENABLE);
//	RCC_APB2PeriphClockCmd(USART3_GPIO_CLK  , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC  , ENABLE);
	
	RCC_APB2PeriphClockCmd(USART1_CLK  , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO  , ENABLE);
	
	RCC_APB1PeriphClockCmd(USART2_CLK  , ENABLE);
//	RCC_APB1PeriphClockCmd(USART3_CLK  , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4  , ENABLE);
	
  /*����1 RX�ܽ�����*/
  /* Configure USART1 Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = USART1_RxPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(USART1_GPIO, &GPIO_InitStructure);

  /*����2 RX�ܽ�����*/
  /* Configure USART2 Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = USART2_RxPin;
  GPIO_Init(USART2_GPIO, &GPIO_InitStructure);  

  /*����3 RX�ܽ�����*/
  /* Configure USART3 Rx as input floating */
//  GPIO_InitStructure.GPIO_Pin = USART3_RxPin;
//  GPIO_Init(USART3_GPIO, &GPIO_InitStructure);
	
	/*����4 RX�ܽ�����*/
  /* Configure USART3 Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_Init(GPIOC, &GPIO_InitStructure);



  /*����1 TX�ܽ�����*/ 
  /* Configure USART1 Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = USART1_TxPin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(USART1_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = USART2_TxPin;
  GPIO_Init(USART2_GPIO, &GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Pin = USART3_TxPin;
//  GPIO_Init(USART3_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  DE1=1;
	DE2=1;

/* USART1 and USART2 configuration */

  /* USART1 and USART2 configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;               /*���ò�����Ϊ115200*/
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;/*��������λΪ8*/
  USART_InitStructure.USART_StopBits = USART_StopBits_1;     /*����ֹͣλΪ1λ*/
  USART_InitStructure.USART_Parity = USART_Parity_No;        /*����żУ��*/
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;/*��Ӳ������*/
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  /*���ͺͽ���*/

  /*���ô���1 */
  USART_Init(USART1, &USART_InitStructure);
	USART_Init(USART2, &USART_InitStructure);
  
  /*���ô���3*/
	USART_InitStructure.USART_BaudRate = 115200;
	/*���ô���2*/
  
  USART_Init(USART3, &USART_InitStructure);
	USART_Init(UART4, &USART_InitStructure);
  			    
  /*ʹ�ܴ���1�ķ��ͺͽ����ж�*/
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
  /*ʹ�ܴ���2�ķ��ͺͽ����ж�*/
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//  USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
//  USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
//  USART_ITConfig(USART3, USART_IT_TXE, ENABLE);

  /* ʹ�ܴ���1 */
  USART_Cmd(USART1, ENABLE);
  /* ʹ�ܴ���2 */
  USART_Cmd(USART2, ENABLE);
  /* ʹ�ܴ���3 */
//  USART_Cmd(USART3, ENABLE);
//	/* ʹ�ܴ���3 */
//  USART_Cmd(UART4, ENABLE);

}


void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM2, //TIM2
		TIM_IT_Update ,
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����						 
}
void TIM4_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM4, //TIM2
		TIM_IT_Update ,
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx����						 
}
/*******************************************************************************
* Function Name  : Delay
* Description    : Inserts a delay time.
* Input          : nCount: specifies the delay time length.
* Output         : None
* Return         : None
*******************************************************************************/
//void Delay(vu32 nCount)
//{
//  for(; nCount != 0; nCount--);
//}
//void Delay_ms(uint16_t Nms)
//{    
//// SysTick->LOAD=(uint32_t)Nms*9000; //����װ�ؼĴ�����ֵ��9000ʱ��������1ms��ʱ�� 
//// SysTick->CTRL|=0x01;               //��ʼ���� (ͬʱѡ���ⲿʱ�ӣ��ر��ж�)   
//// while(!(SysTick->CTRL&(1<<16)));   //�ȴ�ʱ�䵽�� 
//// SysTick->CTRL=0X00000000;         //�رռ�����
//// SysTick->VAL=0X00000000;           //��ռ�����     
//   uint16_t i,j;
//   for(i=Nms*5;i>0;i--)
//   {
//   		for(j=2390;j>0;j--)
//		{
//			 ;
//		}
//    }
//}  

