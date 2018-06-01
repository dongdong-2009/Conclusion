#include "display.h"

extern WifiServer wifiServer;
extern WifiProStr wifiPro;

HDTimer _Display_Timer;
char str[STR_BUF_SIZE];

void Display_Init(void)
{
	OLED_Init();
	_Display_Timer = HDTimer_add_ms(GetTimeHD(),DISP_REFRESH_MS);
}	

void Display_Task(void)
{
	if (IsTimeExpiredHD(_Display_Timer))
	{
		sprintf(str,"P:%6.2f+/-%6.2f Pa",gModuleData.Pitot.DiffPressure,sqrt(gModuleData.Pitot.Var_DiffPressure));
		OLED_P6x8Str(0,2,str);
		sprintf(str,"Temp:     %8.2f C",gModuleData.Pitot.Temperature);
		OLED_P6x8Str(0,3,str);
		sprintf(str,"Damper:  %4.1f/%3.1f",gModuleData.Damper.Position,gModuleData.Damper.SetPoint);
		OLED_P6x8Str(0,4,str);
		sprintf(str,"Time:%14.3fs",GetTime_s());
		OLED_P6x8Str(0,5,str);
		
		//sprintf(str,"%hhX %hhX %hhX %hhX %hhX %hhX ",(char)wifiServer.state,(char)wifiPro.cfg_state, (char)wifiPro.client_state, (char)wifiPro.send_state, (char)wifiPro.server_state, (char)wifiPro.conntoap_state);
		//OLED_P6x8Str(0,6,str);
		
		_Display_Timer = HDTimer_add_ms(GetTimeHD(),DISP_REFRESH_MS);
		
	}
}

