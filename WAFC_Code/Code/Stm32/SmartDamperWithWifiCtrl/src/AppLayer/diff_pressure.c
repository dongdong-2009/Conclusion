#include "diff_pressure.h"

float _pressure_Buf[DP_BUF_SIZE];
float _temperature_Buf[DP_BUF_SIZE];
float _weight[DP_BUF_SIZE]; //weight must normalized to sum up to 1
float _weight_sum_squared; // sum(_weight[i]*_weight[i])
unsigned int _DP_Buf_p; // _DP_Buf_p<DP_BUF_SIZE

u8 _DP_status;
HDTimer _DP_EXEMCU_Timer;
HDTimer _DP_Sampling_Timer;
HDTimer _DP_Output_Timer;

void DiffPressure_Init(void)
{
	unsigned int i;
	for (i=0;i<DP_BUF_SIZE;i++)
	{
		_weight[i]=1.0/DP_BUF_SIZE;
	}
	_weight_sum_squared = 1.0/DP_BUF_SIZE;
	
	D6F_PH_Init();
	
	_DP_status = DP_STATUS_READY;
	_DP_Output_Timer = GetTimeHD();
	_DP_Sampling_Timer = HDTimer_add_ms(_DP_Output_Timer,DP_SAMPLING_CLK_MS); 
	_DP_Output_Timer = HDTimer_add_ms(_DP_Output_Timer,DP_OUTPUT_CLK_MS*10); 
}

float DiffPressure_Filter(float buf[])
{
	unsigned int i;
	float r;
	
	r = 0.0;
	for (i=0;i<DP_BUF_SIZE;i++)
		r += buf[(_DP_Buf_p-i+DP_BUF_SIZE)%DP_BUF_SIZE]*_weight[i];
	return r;
}

float DiffPressure_Variance(float buf[], float buf_weighted_mean)
{
	unsigned int i;
	float r;
	float e;
	
	r = 0.0;
	for (i=0;i<DP_BUF_SIZE;i++)
	{
		e = buf[(_DP_Buf_p-i+DP_BUF_SIZE)%DP_BUF_SIZE] - buf_weighted_mean;
		r += e*e*_weight[i];
	}
	r = r/(1-_weight_sum_squared);
	return r;	
}

void DiffPressure_Task(void)
{
	if (_DP_status == DP_STATUS_READY) 
	{
		if (IsTimeExpiredHD(_DP_Sampling_Timer))
		{
			D6F_PH_EXE_MCU();
			_DP_EXEMCU_Timer = HDTimer_add_ms(GetTimeHD(),43);
			_DP_status = DP_STATUS_EXEMCU;
		}
	}
	else if (_DP_status == DP_STATUS_EXEMCU)
	{
		if (IsTimeExpiredHD(_DP_EXEMCU_Timer))
		{
			if((++_DP_Buf_p)>=DP_BUF_SIZE) _DP_Buf_p=0;
			_pressure_Buf[_DP_Buf_p] = D6F_PH_Pressure();
			_temperature_Buf[_DP_Buf_p] = D6F_PH_Temperature();
			_DP_Sampling_Timer = HDTimer_add_ms(GetTimeHD(),DP_SAMPLING_CLK_MS);
			_DP_status = DP_STATUS_READY;
		}
	}
	
	if (IsTimeExpiredHD(_DP_Output_Timer))
	{
		gModuleData.Pitot.DiffPressure = DiffPressure_Filter(_pressure_Buf); // Modbus Reg Addr 65
		gModuleData.Pitot.Temperature = DiffPressure_Filter(_temperature_Buf); // Modbus Reg Addr 75
		gModuleData.Pitot.Var_DiffPressure = DiffPressure_Variance(_pressure_Buf, gModuleData.Pitot.DiffPressure); // Modbus Reg Addr 77
		_DP_Output_Timer = HDTimer_add_ms(GetTimeHD(),DP_OUTPUT_CLK_MS);
	}
	
}
