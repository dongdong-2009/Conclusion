#include "damper.h"

HDTimer _Damper_Timer;

void Damper_Init(void)
{
	_Damper_Timer = HDTimer_add_ms(GetTimeHD(),DAMPER_CLK_MS);
	
}

void Damper_Task(void)
{
	float dpos_sp=0.0;
	float dpos_now=0.0;

	if (IsTimeExpiredHD(_Damper_Timer))
	{
		if (gModuleData.Damper.SetPointSrc == DAMPER_SP_SRC_FBCTRL)
			dpos_sp = gModuleData.PIDCtrl.U;
		else if (gModuleData.Damper.SetPointSrc == DAMPER_SP_SRC_MANUAL)
			dpos_sp = gModuleData.Damper.SetPoint;
		
		if (dpos_sp>90.0) dpos_sp=90.0;
		if (dpos_sp<0.0) dpos_sp=0.0;
		gModuleData.Damper.SetPoint = dpos_sp;
		
		if (gModuleData.Damper.Mode == DAMPER_MODE_TRACKING)
		{
			dpos_now = dpos_sp;
			gModuleData.Damper.Position = dpos_now;
		}
		_Damper_Timer = HDTimer_add_ms(GetTimeHD(),DAMPER_CLK_MS);
		
	}

}
