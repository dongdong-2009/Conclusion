#include "io.h"

void IO_OutPushPull_Init(GPIO_TypeDef *GPIOx, u8 GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed) //Output Push-pull mode
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA+(RCC_APB2Periph_GPIOB-RCC_APB2Periph_GPIOA)*(uint32_t)((GPIOx-GPIOA)/(GPIOB-GPIOA)), ENABLE); //Port linear mapping
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0<<GPIO_Pin;//Pin bit shift
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed;
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void IO_InPullUp_Init(GPIO_TypeDef *GPIOx, u8 GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed) //Input pull-up mode
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA+(RCC_APB2Periph_GPIOB-RCC_APB2Periph_GPIOA)*(uint32_t)((GPIOx-GPIOA)/(GPIOB-GPIOA)), ENABLE); //Port linear mapping
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0<<GPIO_Pin;//Pin bit shift
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed;
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void IO_Interrupt_Init(GPIO_TypeDef *GPIOx, u8 GPIO_Pin, EXTITrigger_TypeDef EXTI_Trigger, u8 PrePrior, u8 SubPrior)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	EXTI_ClearITPendingBit(EXTI_Line5);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA+(GPIO_PortSourceGPIOB-GPIO_PortSourceGPIOA)*(u8)((GPIOx-GPIOA)/(GPIOB-GPIOA)),GPIO_Pin);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	switch (GPIO_Pin)
	{
		case 0:
			NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;break;
		case 1:
			NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;break;
		case 2:
			NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;break;
		case 3:
			NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;break;
		case 4:
			NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;break;
		default:
			if (GPIO_Pin<10)  //5-9
				NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
			else //10-15
				NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
			break;
	}
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PrePrior;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPrior;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
	
void EXTI0_IRQHandler(void){}
void EXTI1_IRQHandler(void){}
void EXTI2_IRQHandler(void){}
void EXTI3_IRQHandler(void){}
void EXTI4_IRQHandler(void){}

void EXTI9_5_IRQHandler(void) // delay 10ms
{
	if(EXTI_GetITStatus(EXTI_Line5)==SET) //need to test if Line5 triggered the interrupt
	{
		EXTI_ClearITPendingBit(EXTI_Line5);
		TIMDelay_Nms(10);//delay for canceling fluctuation
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)==Bit_RESET)
		{
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==Bit_RESET)
				// PC_in(5)==0
			{
				GPIO_ResetBits(GPIOB,GPIO_Pin_5);
				//PB_out(5)=0
			}
			else
			{
				GPIO_SetBits(GPIOB,GPIO_Pin_5);
				//PB_out(5)=1;
			}
		}
	}
}

void EXTI15_10_IRQHandler(void){}

void WFI_SET(void) //wait for interrupt
{
	__ASM volatile("wfi");		  
}

void INTX_DISABLE(void)  // disable all interrupts
{		  
	__ASM volatile("cpsid i");
}

void INTX_ENABLE(void) // enable all interrupts
{
	__ASM volatile("cpsie i");		  
}

__ASM void MSR_MSP(u32 addr) // set stack address
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}
