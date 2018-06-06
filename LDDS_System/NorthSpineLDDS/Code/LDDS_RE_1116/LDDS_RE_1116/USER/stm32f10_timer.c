#include "stm32f10_timer.h"

//定时器工作时钟信息配置   配置定时器1-4
void TimeRcc_Configuration(void)
{  	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
}

//Timer1-4定时器基本信息配置
void Time_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_DeInit(TIM1);                                            //初始化
  TIM_DeInit(TIM2); 
  TIM_DeInit(TIM3); 
  TIM_DeInit(TIM4);
  TimeRcc_Configuration();

	//定时器1定时2.5ms
	TIM_TimeBaseStructure.TIM_Period = 5;                       //2.5ms     
  TIM_TimeBaseStructure.TIM_Prescaler = (36000-1);            //分频36000       
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数方向向上计数
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM1, TIM_FLAG_Update); 
	TIM_Cmd(TIM1, ENABLE); 
    
	//定时器2定时信息配置
  TIM_TimeBaseStructure.TIM_Period = 5;        // 2.5ms     
  TIM_TimeBaseStructure.TIM_Prescaler = (18000-1);    // 分频18000       
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // 时钟分频  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方向向上计数
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM2, TIM_FLAG_Update); 
	TIM_Cmd(TIM2, ENABLE); 

	//定时器3配置信息，定时1s
  TIM_TimeBaseStructure.TIM_Period = 2000;        // 5
  TIM_TimeBaseStructure.TIM_Prescaler = (36000-1);    // 分频36000       
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // 时钟分频  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方向向上计数
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM3, TIM_FLAG_Update); 
	TIM_Cmd(TIM3, ENABLE); 

	//定时器4配置信息
	TIM_TimeBaseStructure.TIM_Period = 60000;        // 5s     
  TIM_TimeBaseStructure.TIM_Prescaler = (36000-1);    // 分频36000       
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // 时钟分频  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方向向上计数
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM4, TIM_FLAG_Update); 
	TIM_Cmd(TIM4, ENABLE);         
}

//开启定时器3 START  使能Timer3中断源
void Tim3ST(void)
{
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 
}

//关闭定时器3  stop
void Tim3SP(void)
{
	TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE); 
}

//开启定时器4   使能Timer4中断源
void Tim4ST(void)
{
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); 
}

//关闭定时器4
void Tim4SP(void)
{
	TIM_ITConfig(TIM4, TIM_IT_Update, DISABLE); 
}

void delay_us(u32 nus)
{
	u32 temp;
  SysTick->LOAD=9*nus;
  SysTick->VAL=0x00;
  SysTick->CTRL=0x01;
  do
  {
		temp=SysTick->CTRL;
  } while((temp&0x01)&&(!(temp&(1<<16))));
  SysTick->CTRL=0x00;
  SysTick->VAL=0x00;
}

void delay_ms(u16 nms)
{
  u32 temp;
  SysTick->LOAD=9000*nms;
  SysTick->VAL=0x00;
  SysTick->CTRL=0x01;
  do
  {                                                                                                                                             
		temp=SysTick->CTRL;
  } while((temp&0x01)&&(!(temp&(1<<16))));
  SysTick->CTRL=0x00;
  SysTick->VAL=0x00;
}

void delay_s(u8 ns)
{
  u16 i;
  for(i=0;i<ns*10;i++)
  {
		delay_ms(100);
  }
}
