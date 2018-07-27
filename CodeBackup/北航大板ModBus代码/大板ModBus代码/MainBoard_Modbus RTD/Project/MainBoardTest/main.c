/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Main program body.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "rtd.h"
#include "ads1115.h"
#include "delay.h"
#include "DAC8554.h"
#include "MuxCfg.h"
#include "Dio.h"
#include "Pwm.h"
#include "Globle.h"
#include "stm32f10x_tim.h"
#include<stdlib.h>
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;
u8 count=0;
unsigned long int count1=0x00ff;
/* Private function prototypes -----------------------------------------------*/
void UART_Configuration(void);
void printfStr(char *str);
void SendStr4852(char *str);
void SendStr4851(char *str);
void printfFloat(float Dat);
void NVIC_Configuration(void);

void R485Test(void);
void AdDaTest(void);
void DioTest(void);
void RtdTest(void);
void LedInit(void);
void TIM2_Int_Init(u16 arr,u16 psc);
/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

int main(void)
{
	NVIC_Configuration();
	delay_init();
	delay_ms(500);
	RTD_init();
	stm32ads1115_1_init();
	DAC8554_GPIO_Config();
	MuxGpioCfg();
	DioCfg();
	UART_Configuration();
	LedInit();
	TIM2_Int_Init(20,7199); //定时器初始化为5ms中断一次
	
	PWM1_Init(100);                     //设置PWM1输出周期100*100us           
	PWM1_SetHighTime(70);               //设置PWM1输出高电平时间为70*100us 
	
	PWM2_Init(100);                     //设置PWM2输出周期100*100us  
	PWM2_SetHighTime(30);               //设置PWM2输出高电平时间为30*100us 
	


	while (1)
	{	
		delay_ms(500);
	
		LED=0;
		//R485Test();              //485电路测试 应该在硬件上将两路485连到一起
		AdDaTest();              //AD和DA 测试
		DioTest();               //Di和继电器测试
		RtdTest();               //RTD模块测试
	  LED=1;
		

	}
}
void R485Test(void)
{
	//****************************************************************************//
/////////////////////////////////////485测试////////////////////////////////////
	 printfStr("\r\n\r\n***************************RS4885 TEST******************************\r\n");delay_ms(10);
	 Uart4851_TestFlag=0;
	 Uart4852_TestFlag=0;
	 SendStr4852("HRTOUSART1 ");
	 delay_ms(50);
	 SendStr4851("HRTOUSART2 ");
	 delay_ms(50);
	
	 if(Uart4851_TestFlag)                 //输出485 ch1 状态
	 {
		 printfStr("485-1 test succeed!!\r\n");delay_ms(3);
	 }
	 else
	 {
		 printfStr("485-1 test failed!!\r\n");delay_ms(3);
	 }
	 
	 if(Uart4852_TestFlag)                 //输出485 ch2 状态
	 {
		 printfStr("485-2 test succeed!!\r\n");delay_ms(3);
	 }
	 else
	 {
		 printfStr("485-2 test failed!!\r\n");delay_ms(3);
	 }
}
void AdDaTest(void)
{
	float advalue[13];
	int i;
	u8 mode=MODE_VOLTAGE;
	//****************************************************************************//
/////////////////////////AD采集通道测试--电压/电流模式////////////////////////////////
  printfStr("\r\n\r\n***************************AD ch1-ch12 TEST******************************");delay_ms(10);
	for(i=1;i<13;i++)                                             //Ai1-Ai12设置为电压采样模式
	{
		AiChannelSetMux(i,MUX_VOLTAGE);
	}
	
	for(i=1;i<9;i++)                                              //A01-A08设置为电压/电流输出模式
	{
		AoChannelSetMux(i,MUX_VOLTAGE);
	}
	
	for(i=1;i<9;i++)                                             //channel Ao1-Ao8输出1~8V电压/1-8ma电流
	{
		SetAoOut(DAREG[i-1]/100.0,i,mode); 
	}
																																
	
	for(i=1;i<13;i++)               															//读取模拟通道数值
	{
		advalue[i]=ReadAdOfChannel(i,mode);
	}
	
	printfStr("\r\nAD Resault: \r\n AD1~12: ");  									//通过串口打印输出
	delay_ms(3);	
	for(i=1;i<13;i++)
	{
		printfFloat(advalue[i]);
		printfStr("  ");  delay_ms(2);					
		AdREG[i-1]=advalue[i]*100;          //更新modbus 映射寄存器 Ad ch1-ch12
	}
	printfStr("\r\n: ");delay_ms(2);
}
void DioTest(void)
{
	unsigned char DiMap;
	int i;
	//****************************************************************************//
//////////////////////////DIO端口输入输出测试////////////////////////////////////
																																		//设置继电器输出状态
	printfStr("\r\n\r\n***************************DIO TEST******************************\r\n");delay_ms(10);
	for(i=0;i<8;i++)
	{
		if(DoREG[i]==0)
		{
			SetSpdtState(i+1,SpdtOFF);
		}
		else
			SetSpdtState(i+1,SpdtON);
	}
	DiMap=GetDiMap();                                              //获取Di输入状态
	
	printfStr("DI Resault: \r\n DI1~8: ");                     //打印DI状态到串口输出
	delay_ms(3);
	printfStr("\r\nCH1 CH2 CH3 CH4 CH5 CH6 CH7 CH8 \r\n");
	delay_ms(3);
	for(i=0;i<8;i++)
	{
		if(DiMap&0x01)
		{
			printfStr("-H- ");delay_ms(1);
		}
		else
		{
			printfStr("-L- ");delay_ms(1);
		}
		DiREG[i]=DiMap&0x01;        //更新modbus 映射寄存器 Di ch1-ch8
		DiMap>>=1;
	}
	printfStr("\r\n: ");delay_ms(2);
			
}
void RtdTest(void)
{
	float temp[4]={0};
	
//*********************************************************************************//
//////////////////////////RTD模块测试输出////////////////////////////////////////////
	printfStr("\r\n\r\n***************************RTD TEST******************************\r\n");delay_ms(10);
	RTD_allchannels(temp);                                         //读取RTD通道数值
		
	printfStr("RTD Resault: \r\n RTD_0: ");delay_ms(3);				 //通过串口打印输出
	printfFloat(temp[0]);
	printfStr("℃\r\n RTD_1: ");delay_ms(2);
	printfFloat(temp[1]);
	printfStr("℃\r\n RTD_2: ");delay_ms(2);
	printfFloat(temp[2]);
	printfStr("℃\r\n RTD_3: ");delay_ms(2);
	printfFloat(temp[3]);
	printfStr("℃\r\n");delay_ms(2);
	
	RTDREG[0]=temp[0]*100;                  //更新modbus 映射寄存器 RTD ch1-ch4
	RTDREG[1]=temp[1]*100;
	RTDREG[2]=temp[2]*100;
	RTDREG[3]=temp[3]*100;
}
void printfFloat(float Dat)
{		
	int64_t  temp1,temp2;
	u8 Sflag;
	if(Dat<0)
	{
		temp1=((int64_t)(-Dat))%100000;
		temp2=((int64_t)((-Dat)*100000.0))%100000;
		Sflag='-';
	}
	else
	{
		temp1=((int64_t)(Dat))%100000;
		temp2=((int64_t)((Dat)*100000.0))%100000;
		Sflag='+';
	}
	Uart3_SendBuffSize=12;
	Uart3_Send_buffer[0]=Sflag;
	Uart3_Send_buffer[1]=temp1/10000+'0';
	Uart3_Send_buffer[2]=temp1%10000/1000+'0';
	Uart3_Send_buffer[3]=temp1%1000/100+'0';
	Uart3_Send_buffer[4]=temp1%100/10+'0';
  Uart3_Send_buffer[5]=temp1%10+'0';
	Uart3_Send_buffer[6]='.';
	Uart3_Send_buffer[7]=temp2/10000+'0';
	Uart3_Send_buffer[8]=temp2%10000/1000+'0';
	Uart3_Send_buffer[9]=temp2%1000/100+'0';
	Uart3_Send_buffer[10]=temp2%100/10+'0';
  Uart3_Send_buffer[11]=temp2%10+'0';
	Uart3_SCnt=0;
	USART_ITConfig(USART3,USART_IT_TXE,ENABLE);			  	//
	delay_ms(2);
			
}
void printfStr(char *str)
{		
	Uart3_SendBuffSize=0;
	while(*str!=0x00)
	{
		Uart3_Send_buffer[Uart3_SendBuffSize++]=*str;
		str++;
	}
	Uart3_SCnt=0;
	USART_ITConfig(USART3,USART_IT_TXE,ENABLE);			  	//
			
}
void SendStr4851(char *str)
{		
	DE1=0;
	delay_ms(1);
	Uart1_SendBuffSize=0;
	while(*str!=0x00)
	{
		Uart1_Send_buffer[Uart1_SendBuffSize++]=*str;
		str++;
	}
	Uart1_SCnt=0;
	USART_ITConfig(USART1,USART_IT_TXE,ENABLE);			  	//
			
}
void SendStr4852(char *str)
{		
	DE2=0;
	delay_ms(1);
	Uart2_SendBuffSize=0;
	while(*str!=0x00)
	{
		Uart2_Send_buffer[Uart2_SendBuffSize++]=*str;
		str++;
	}
	Uart2_SCnt=0;
	USART_ITConfig(USART2,USART_IT_TXE,ENABLE);			  	//
			
}
void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM2, //TIM2
		TIM_IT_Update ,
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设						 
}
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级

	 NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void LedInit()
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
	RCC_APB2PeriphClockCmd(USART3_GPIO_CLK  , ENABLE);
	
	RCC_APB2PeriphClockCmd(USART1_CLK  , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO  , ENABLE);
	
	RCC_APB1PeriphClockCmd(USART2_CLK  , ENABLE);
	RCC_APB1PeriphClockCmd(USART3_CLK  , ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);  
	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);  
  /*串口1 RX管脚配置*/
  /* Configure USART1 Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = USART1_RxPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(USART1_GPIO, &GPIO_InitStructure);

  /*串口2 RX管脚配置*/
  /* Configure USART2 Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = USART2_RxPin;
  GPIO_Init(USART2_GPIO, &GPIO_InitStructure);  

  /*串口3 RX管脚配置*/
  /* Configure USART3 Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = USART3_RxPin;
  GPIO_Init(USART3_GPIO, &GPIO_InitStructure);



  /*串口1 TX管脚配置*/ 
  /* Configure USART1 Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = USART1_TxPin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(USART1_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = USART2_TxPin;
  GPIO_Init(USART2_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = USART3_TxPin;
  GPIO_Init(USART3_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
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
  USART_InitStructure.USART_BaudRate = 9600;               /*设置波特率为115200*/
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;/*设置数据位为8*/
  USART_InitStructure.USART_StopBits = USART_StopBits_1;     /*设置停止位为1位*/
  USART_InitStructure.USART_Parity = USART_Parity_No;        /*无奇偶校验*/
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;/*无硬件流控*/
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  /*发送和接收*/

  /*配置串口1 */
  USART_Init(USART1, &USART_InitStructure);

  /*配置串口2*/
  USART_Init(USART2, &USART_InitStructure);
  /*配置串口3*/
	USART_InitStructure.USART_BaudRate = 115200;
  USART_Init(USART3, &USART_InitStructure);

  			    
  /*使能串口1的发送和接收中断*/
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
  /*使能串口2的发送和接收中断*/
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//  USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
//  USART_ITConfig(USART3, USART_IT_TXE, ENABLE);

  /* 使能串口1 */
  USART_Cmd(USART1, ENABLE);
  /* 使能串口2 */
  USART_Cmd(USART2, ENABLE);
  /* 使能串口3 */
  USART_Cmd(USART3, ENABLE);

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
//// SysTick->LOAD=(uint32_t)Nms*9000; //给重装载寄存器赋值，9000时，将产生1ms的时基 
//// SysTick->CTRL|=0x01;               //开始倒数 (同时选择外部时钟，关闭中断)   
//// while(!(SysTick->CTRL&(1<<16)));   //等待时间到达 
//// SysTick->CTRL=0X00000000;         //关闭计数器
//// SysTick->VAL=0X00000000;           //清空计数器     
//   uint16_t i,j;
//   for(i=Nms*5;i>0;i--)
//   {
//   		for(j=2390;j>0;j--)
//		{
//			 ;
//		}
//    }
//}  

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
