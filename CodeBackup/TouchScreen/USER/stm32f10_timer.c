
#include "stm32f10_timer.h"


void TimeRcc_Configuration(void)
{  	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);

//	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
}
void TimeGPIO_Configuration(void)
{
  	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct); 
}

void Time_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef        TIM_ICInitStructure;

	TIM_DeInit(TIM1); 
    TIM_DeInit(TIM2); 
    TIM_DeInit(TIM3); 
    TIM_DeInit(TIM4);
//	TIM_DeInit(TIM5);
    TimeRcc_Configuration();
	TimeGPIO_Configuration();

	TIM_TimeBaseStructure.TIM_Period = 2;        // 2.5ms     
    TIM_TimeBaseStructure.TIM_Prescaler = (36000-1);    // 分频36000       
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // 时钟分频  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方向向上计数
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM1, TIM_FLAG_Update); 
	TIM_Cmd(TIM1, ENABLE); 
   
	TIM_TimeBaseStructure.TIM_Period = 1999; 
	TIM_TimeBaseStructure.TIM_Prescaler = 36;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // 时钟分频  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方向向上计数
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
////setting input capture mode to capture falling edge in channel 1 with 8 samples filter
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x00;
	TIM_ICInit(TIM2,&TIM_ICInitStructure);
	TIM_PWMIConfig(TIM2,&TIM_ICInitStructure);
	TIM_SelectInputTrigger(TIM2,TIM_TS_TI2FP2);
	TIM_SelectSlaveMode(TIM2,TIM_SlaveMode_Reset);
	TIM_SelectMasterSlaveMode(TIM2,TIM_MasterSlaveMode_Enable);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); 
   	TIM_Cmd(TIM2,ENABLE);//Enable and start the timer 

	TIM_TimeBaseStructure.TIM_Period = 1500;        // 5s     
    TIM_TimeBaseStructure.TIM_Prescaler = (36000-1);    // 分频36000       
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // 时钟分频  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方向向上计数
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM4, TIM_FLAG_Update); 
	TIM_Cmd(TIM4, ENABLE); 

	TIM_TimeBaseStructure.TIM_Period = 1000;        // 2.5ms     
    TIM_TimeBaseStructure.TIM_Prescaler = (36000-1);    // 分频36000       
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // 时钟分频  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方向向上计数
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM3, TIM_FLAG_Update); 
	TIM_Cmd(TIM3, ENABLE); 
//        
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

void Tim1ST(void)
{
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); 
}



void Tim2SP(void)
{
 //  TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE); 
   TIM_ITConfig(TIM2, TIM_IT_CC2, DISABLE); 
//	 	TIM_ITConfig(TIM2, TIM_IT_CC1, DISABLE); 
}
void Tim2ST(void)
{
  // TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); 
   		TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE); 
//	 	TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE); 

}

void Tim5SP(void)
{
    TIM_ITConfig(TIM5, TIM_IT_Update, DISABLE); 
}
void Tim5ST(void)
{
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE); 
}


void Tim1SP(void)
{
    TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE); 
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
