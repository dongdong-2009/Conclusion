#include "display.h"

extern WifiServer wifiServer;
extern WifiProStr wifiPro;

HDTimer _Display_Timer;
HDTimer _Display_Init_Timer;
char str[STR_BUF_SIZE];

void Display_Init(void)
{
	OLED_Init();
	_Display_Timer = HDTimer_add_ms(GetTimeHD(),DISP_REFRESH_MS);
	_Display_Init_Timer = GetTimeHD();
}	

void Display_Task(void)
{
//	float abc;
//	u8 MARK;
	
	if (IsTimeExpiredHD(_Display_Timer))
	{
		sprintf(str,"P:%6.2f+/-%6.2f Pa",gModuleData.Pitot.DiffPressure,sqrt(gModuleData.Pitot.Var_DiffPressure));
		OLED_P6x8Str(0,2,str);
		sprintf(str,"Temp:    %8.2f C",gModuleData.Pitot.Temperature);
		OLED_P6x8Str(0,3,str);
		sprintf(str,"Damper:  %4.1f/%3.1f",gModuleData.Damper.Position,gModuleData.Damper.SetPoint);
		OLED_P6x8Str(0,4,str);
		sprintf(str,"Current: %8.1fmA",gModuleData.Servo.Current);
		OLED_P6x8Str(0,5,str);
		sprintf(str,"CO2:  %4dppm",gModuleData.CO2.Measure);
		OLED_P6x8Str(0,6,str);
		sprintf(str,"Time:%14.3fs",GetTime_s());
		OLED_P6x8Str(0,7,str);

		_Display_Timer = HDTimer_add_ms(GetTimeHD(),DISP_REFRESH_MS);
		
	}
}

