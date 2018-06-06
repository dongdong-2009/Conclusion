
#include "stm32f10_timer.h"


void TimeRcc_Configuration(void)
{  	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
}

void Time_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_DeInit(TIM1); 
  TIM_DeInit(TIM2); 
  TIM_DeInit(TIM3); 
  TIM_DeInit(TIM4);
  TimeRcc_Configuration();

	  TIM_TimeBaseStructure.TIM_Period = 5;        // 2.5ms     
    TIM_TimeBaseStructure.TIM_Prescaler = (36000-1);    // 分频36000       
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // 时钟分频  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方向向上计数
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM1, TIM_FLAG_Update); 
	TIM_Cmd(TIM1, ENABLE); 
    
    TIM_TimeBaseStructure.TIM_Period = 5;        // 2.5ms     
    TIM_TimeBaseStructure.TIM_Prescaler = (18000-1);    // 分频18000       
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // 时钟分频  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方向向上计数
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM2, TIM_FLAG_Update); 
	TIM_Cmd(TIM2, ENABLE); 

    TIM_TimeBaseStructure.TIM_Period = 2000;        // 5
    TIM_TimeBaseStructure.TIM_Prescaler = (36000-1);    // 分频36000       
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // 时钟分频  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方向向上计数
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM3, TIM_FLAG_Update); 
	TIM_Cmd(TIM3, ENABLE); 


	TIM_TimeBaseStructure.TIM_Period = 60000;        // 5s     
    TIM_TimeBaseStructure.TIM_Prescaler = (36000-1);    // 分频36000       
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // 时钟分频  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方向向上计数
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM4, TIM_FLAG_Update); 
	TIM_Cmd(TIM4, ENABLE); 
        
}

void Tim3ST(void)
{
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 
}
void Tim3SP(void)
{
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE); 
}

void Tim4ST(void)
{
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); 
}

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
   }while((temp&0x01)&&(!(temp&(1<<16))));
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
   }while((temp&0x01)&&(!(temp&(1<<16))));
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
