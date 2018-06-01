#include "current.h"

extern u16 _ADC_buf[ADC_BUF_SIZE];
HDTimer _mA_Output_Timer;

void Servo_mA_Init(void)
{
	unsigned int i;
	
	Current_ADC_Init();
	_mA_Output_Timer = GetTimeHD();
}

float mA_Mean(void)
{
	unsigned int i;
	unsigned int sum_ADC_buf;
	
	sum_ADC_buf = 0;
	for (i=0;i<ADC_BUF_SIZE;i++)
		sum_ADC_buf += _ADC_buf[i];
	return (float)sum_ADC_buf*0.805664/ADC_BUF_SIZE; //(float)sum_ADC_buf*3.3/4096*1000/ADC_BUF_SIZE;
}


