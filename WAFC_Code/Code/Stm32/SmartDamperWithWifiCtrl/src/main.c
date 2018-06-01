#include "config.h"
#undef __TEST__
//#define __TEST__

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
	
	/* Disable the Serial Wire Jtag Debug Port SWJ-DP */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	BSP_GPIO_Init();
	BSP_USARTInit();
	BSP_SysTickCfg();
	MbTcp_Init();
	MbTcpApp_Init();
	Read_Param();
	Wifi_Init();
	WifiServer_TaskStart();
	
	CO2_Init();
	#ifdef _DISPLAY_
	Display_Init();
	#endif
	Servo_Init();
	Pitot_Init();
	Damper_Init();
	
	Feedback_Init();
	
	Backup_Init();
	
}



int main(void)
{
	#ifdef __TEST__
	#endif 
	
	uint32_t runTimer;
	uint32_t runFlag = 0;

	Sys_Init();
	
	runTimer = Get_Gtime();
	
	#ifdef __TEST__
	#ifdef _DISPLAY_
	while(1);
	#endif
	#endif 
	
	while(1)
	{		
		Servo_Task();
		WifiServer_Task();
		Pitot_Task();
		Damper_Task();
		CO2_Task();
		#ifdef _DISPLAY_
		Display_Task();
		#endif
		Feedback_Task();
		Backup_Task();
		
		if(IsTimeExpired(runTimer + 100))
		{
			runTimer = Get_Gtime();
			if(runFlag)
				BSP_GPIO_SetOut(GPIO_LED2,GPIO_LED2);
			else
				BSP_GPIO_SetOut(GPIO_LED2,0);

			runFlag ^= 1;
		}
	}
}
