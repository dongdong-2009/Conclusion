#include "config.h"

/**
  * @brief  This function init the device .
  * @param  None
  * @retval None
  */
void Sys_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);    //向量表位于FLASH，向量表基地址的偏移量为0 
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	
	NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;            //TIM3中断 for PWM   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级4
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel =TIM2_IRQn;            //TIM2中断 for CO2  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级4 //TIM1的优先级比TIM2的优先级要高
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			 //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	/* Disable the Serial Wire Jtag Debug Port SWJ-DP */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	TimConfigure();
	UsartConfigure();

	BSP_GPIO_Init();
	BSP_USARTInit();
	BSP_SysTickCfg();
	MbTcp_Init();
	MbTcpApp_Init();
	Read_Param();
	Wifi_Init();
	WifiServer_TaskStart();
	
	//CO2_Init();
	#ifdef _DISPLAY_
	Display_Init();
	#endif
	Servo_Init();
	DiffPressure_Init();
	Damper_Init();
}



int main(void)
{
	uint32_t runTimer;
	uint32_t runFlag = 0;

	Sys_Init();
	
	runTimer = Get_Gtime();
	
	while(1)
	{		
		Servo_Task();
		WifiServer_Task();
		DiffPressure_Task();
		Damper_Task();
		
		#ifdef _DISPLAY_
		Display_Task();
		#endif
		
		if(IsTimeExpired(runTimer + 100))
		{
			runTimer = Get_Gtime();
			if(runFlag)
				BSP_GPIO_SetOut(GPIO_LED2,GPIO_LED2);
			else
				BSP_GPIO_SetOut(GPIO_LED2,0);

			runFlag ^= 1;
		}
		
		
//		if(IsTimeExpired(CO2Timer + 100))
//		{
//			CO2_Calculate();
//			CO2Timer = Get_Gtime();
//			Disp_Num(1,0,CO2value,5);
//			sprintf(str,"ppm");
//			OLED_P6x8Str(30,1,str);			
//			gModuleData.module[0].data_u32 = (unsigned int)CO2value;
//			CO2Timer = Get_Gtime();
//		}
		
	}
}
