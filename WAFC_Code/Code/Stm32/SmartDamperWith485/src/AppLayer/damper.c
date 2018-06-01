#include "damper.h"

HDTimer _Damper_Timer;

void Damper_Init(void)
{
	_Damper_Timer = HDTimer_add_ms(GetTimeHD(),DAMPER_CLK_MS);
	
}

void Damper_Task(void)
{
	float dpos_sp;
	float dpos_now;
	
	if (IsTimeExpiredHD(_Damper_Timer))
	{
		dpos_sp = gModuleData.Damper.SetPoint;
		dpos_now = gModuleData.Damper.Position;
		if (dpos_sp>90.0) dpos_sp=90.0;
		if (dpos_sp<0.0) dpos_sp=0.0;
		
		if (dpos_sp > dpos_now) //increase angle
		{
			if ((dpos_sp - dpos_now) < DAMPER_STEP_ANGLE) // in one-step reachable range
				dpos_now = dpos_sp;
			else
				dpos_now = dpos_now + DAMPER_STEP_ANGLE;
		}
		else //decrease angle
		{
			if ((dpos_now - dpos_sp) < DAMPER_STEP_ANGLE) // in one-step reachable range
				dpos_now = dpos_sp;
			else
				dpos_now = dpos_now - DAMPER_STEP_ANGLE;
		}
		gModuleData.Damper.Position = dpos_now;
		
		_Damper_Timer = HDTimer_add_ms(GetTimeHD(),DAMPER_CLK_MS);
	}
}
