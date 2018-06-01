#include "CO2.h"

u16 _CO2_Sampling_Period[CO2_BUF_SIZE];
u16 _CO2_Reading_Buf[CO2_BUF_SIZE];
unsigned int _CO2_Buf_p; // _CO2_Buf_p<DP_BUF_SIZE
HDTimer _CO2_Output_Timer;
HDTimer _CO2_Reset_Timer;

void PWM_Capture_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct); 
	
	TIM_DeInit(TIM2);
	
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
	TIM_TimeBaseStructure.TIM_Prescaler = 3600;//resolution 1/20ms = 3600/72M, 20,000 counts/s
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x00;
	TIM_ICInit(TIM2,&TIM_ICInitStructure);
	
	TIM_PWMIConfig(TIM2,&TIM_ICInitStructure);
	TIM_SelectInputTrigger(TIM2,TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM2,TIM_SlaveMode_Reset);
	TIM_SelectMasterSlaveMode(TIM2,TIM_MasterSlaveMode_Enable);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);
	TIM_Cmd(TIM2,ENABLE);
}

void CO2_Init()
{
	int i;
	
	PWM_Capture_Init();
	_CO2_Output_Timer = HDTimer_add_ms(GetTimeHD(),CO2_OUTPUT_CLK_MS*10);
	_CO2_Buf_p = 0;
	for (i=0;i<CO2_BUF_SIZE;i++)
	{
		_CO2_Sampling_Period[i] = 20080;
		_CO2_Reading_Buf[i] = 8040;
	}
}

void TIM2_IRQHandler(void) // for CO2 PWM capture
{
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
	else if (TIM_GetITStatus(TIM2,TIM_IT_CC1) == SET)
	{
		if (++_CO2_Buf_p >= CO2_BUF_SIZE) _CO2_Buf_p=0;
		_CO2_Sampling_Period[_CO2_Buf_p] = TIM_GetCapture1(TIM2);//frequency value
		_CO2_Reading_Buf[_CO2_Buf_p] = TIM_GetCapture2(TIM2);//duty cycle value
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
	}
}

u16 _PWM2PPM(u16 TH, u16 TT)
{
	int temp;
	//temp = (int)TH-40;
	temp = ((int)TH-40)*2000/((int)TT-80);
	return (u16)temp + gModuleData.CO2.Bias;
}

u16 CO2PPM(void)
{
	// currently no filtering and averaging for CO2 readings
	return _PWM2PPM(_CO2_Reading_Buf[_CO2_Buf_p], _CO2_Sampling_Period[_CO2_Buf_p]);
}

void CO2_AutoReset(void)
{
	if (gModuleData.VentCtrl.Mode == VENTCTRL_MODE_UNOCCUPIED)
	{
		if (IsTimeExpiredHD(_CO2_Reset_Timer))
			gModuleData.CO2.Bias += (short)403 - (short)CO2PPM();
	}
	else
	{
		_CO2_Reset_Timer = HDTimer_add_s(GetTimeHD(),CO2_AUTORESET_DELAY_S);
	}
}

void CO2_Task(void)
{
	if (IsTimeExpiredHD(_CO2_Output_Timer))
	{
		if (gModuleData.CO2.MeasureSrc == CO2_MEASURE_SRC_SENSOR)
		{
			gModuleData.CO2.Measure = CO2PPM();
		}
		CO2_AutoReset();
		_CO2_Output_Timer = HDTimer_add_ms(GetTimeHD(),CO2_OUTPUT_CLK_MS);
	}
}
