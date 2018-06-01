#include "feedback.h"

HDTimer _Feedback_Timer;
float e_int;

void Feedback_Init(void)
{
	e_int = 0.0;
	
	_Feedback_Timer = HDTimer_add_ms(GetTimeHD(),FEEDBACK_DEFAULT_MS);
	
}

void Feedback_Task(void)
{
	float ref;
	float e;
	float u1;
	float u2;
	
	if (IsTimeExpiredHD(_Feedback_Timer))
	{
		if (gModuleData.PIDCtrl.FbSrc>0)
		{
			switch (gModuleData.PIDCtrl.FbSrc)
			{
				case FEEDBACK_SRC_FLOW:
					ref = gModuleData.Flow.SetPoint;
					e = ref - gModuleData.Flow.Measure;
					break;
				case FEEDBACK_SRC_CO2:
					ref = gModuleData.CO2.Limit;
					e = ref - gModuleData.CO2.Measure;
					break;
				default:
					ref = 0.0;
					e = 0.0;
					break;
			}
			e_int += e;
			u1 = e*gModuleData.PIDCtrl.Kp + gModuleData.PIDCtrl.G0 + gModuleData.PIDCtrl.G1*ref;
			u2 = u1 + e_int*gModuleData.PIDCtrl.Ki;
			if (u2 > gModuleData.PIDCtrl.UB) 
			{
				u2 = gModuleData.PIDCtrl.UB;
				e_int = (u2 - u1)/gModuleData.PIDCtrl.Ki;
			}
			if (u2 < gModuleData.PIDCtrl.LB)
			{
				u2 = gModuleData.PIDCtrl.LB;
				e_int = (u2 - u1)/gModuleData.PIDCtrl.Ki;
			}
			gModuleData.PIDCtrl.U = u2;
		}
		else
		{
			gModuleData.PIDCtrl.U = 0;
			e_int = 0.0;
		}
		_Feedback_Timer = HDTimer_add_ms(GetTimeHD(),FEEDBACK_DEFAULT_MS);
		
	}
}

