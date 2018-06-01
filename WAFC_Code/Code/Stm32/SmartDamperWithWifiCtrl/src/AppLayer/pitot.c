#include "pitot.h"

HDTimer _Pitot_Timer;

void Pitot_Init(void)
{
	_Pitot_Timer = HDTimer_add_ms(GetTimeHD(),PITOT_CLK_MS);
	DiffPressure_Init();
	
}

void Pitot_Task(void)
{
	StructPitotZone *p = &gModuleData.Pitot;
	
	DiffPressure_Task();
	
	if (IsTimeExpiredHD(_Pitot_Timer))
	{
		if (gModuleData.Flow.MeasureSrc == FLOW_MEASURE_SRC_PITOT)
		{
			gModuleData.Flow.Measure = p->SizeCoeff*sqrt((p->DiffPressure-p->PressureBias)/p->AmpCoeff*p->TempCoeff);
		}
		_Pitot_Timer = HDTimer_add_ms(GetTimeHD(),PITOT_CLK_MS);
	}
}
