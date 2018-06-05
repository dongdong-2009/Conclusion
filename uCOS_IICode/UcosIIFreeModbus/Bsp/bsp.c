#include "bsp.h"

void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;                              //定义外部高速晶体启动状态枚举变量；
	RCC_DeInit();                                              //复位RCC寄存器到默认值；
	RCC_HSEConfig(RCC_HSE_ON);                                 //打开外部的高速晶振； 
	HSEStartUpStatus = RCC_WaitForHSEStartUp();                //等待外部高速时钟准备好
	if(HSEStartUpStatus == SUCCESS)
		{
			RCC_HCLKConfig(RCC_SYSCLK_Div1);                         //配置AHB
			RCC_PCLK2Config(RCC_HCLK_Div1);                          //配置APB2 
			RCC_PCLK1Config(RCC_HCLK_Div2);                          //配置APB1 
			//RCC_ADCCLKConfig(RCC_PCLK2_Div4);	      
			RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);     //PLL=8M*9=72M
			RCC_PLLCmd(ENABLE);                                      //时能PLL
			while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);      //等待PLL就绪	      
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);               //配置系统时钟=PLL	  
			while(RCC_GetSYSCLKSource() != 0x08);                    //检查PLL时钟是否作为系统时钟	       
		}
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

void BSP_Initializes(void)
{
	RCC_Configuration();
	LedInit();
	delay_init();
}

