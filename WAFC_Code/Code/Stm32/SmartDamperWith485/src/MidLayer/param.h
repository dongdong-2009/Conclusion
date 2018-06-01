#ifndef _MID_PARAM_TY_H
#define _MID_PARAM_TY_H

typedef struct _Param
{
	uint32_t first_word;
	char wifi_rap_ssid[32];
	char wifi_rap_pwd[32];
}Param;

extern Param param;

void Read_Param(void);
uint32_t Save_Param(void);
#endif

