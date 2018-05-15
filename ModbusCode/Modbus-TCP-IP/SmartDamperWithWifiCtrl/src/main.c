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
	
	//CO2_Init();
	OLED_Init();
	Servo_Init();
	D6F_PH_Init();
	
}



int main(void)
{
	uint32_t runTimer;
	uint32_t runFlag = 0;
	uint32_t servoTimer;
	uint32_t pressureTimer;
	float f1, f2, f3;
	char str[10];

	Sys_Init();
	
	runTimer = Get_Gtime();
	servoTimer = Get_Gtime();
	pressureTimer = Get_Gtime();
	
	while(1)
	{		
		WifiServer_Task();
		
		if(IsTimeExpired(runTimer + 100))
		{
			runTimer = Get_Gtime();
			if(runFlag)
				BSP_GPIO_SetOut(GPIO_LED2,GPIO_LED2);
			else
				BSP_GPIO_SetOut(GPIO_LED2,0);

			runFlag ^= 1;
		}
		
		if(IsTimeExpired(servoTimer + 1))
		{
			f1 = gModuleData.Damper.SetPoint;
			f2 = gModuleData.Damper.Open_PWM;
			f3 = gModuleData.Damper.Close_PWM;
			
			Servo_Pos(f1,f2,f3);
			gModuleData.Damper.Position = f1;
			servoTimer = Get_Gtime();
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
		
		if(IsTimeExpired(pressureTimer + 20))
		{
			gModuleData.Pitot.DiffPressure = D6F_PH_Pressure();
			gModuleData.Pitot.Temperature = D6F_PH_Temperature();
			sprintf(str,"%6.2f",gModuleData.Pitot.DiffPressure);
			OLED_P6x8Str(2,3, str);
			sprintf(str,"%6.2f",gModuleData.Pitot.Temperature);
			OLED_P6x8Str(2,5, str);
			pressureTimer = Get_Gtime();
		}
	}
}
