#ifndef __LOGIC_H
#define __LOGIC_H

#include "stm32f10x.h"

//AI
#define DIFFPRE                   	3										   //压差
#define CHWVfb                      11			               //冷水阀反馈值   

//RTD
#define CHWOutTemp                  2                    //冷水出口温度

//AO
#define PTBFan1                     4                    //控制PTB风扇
#define ERVFan	                    7                    //控制ERV风扇
#define CHWV                        2                    //控制冷水阀开度
#define PTBFan2                    	3                    //控制PTB风扇，大房间有6台PTB，分两个端口控制

//DO
#define NSLHAlarm                   2                    //报警信息

extern u16 RoomTemp;
extern u16 RoomTempSv;
extern u16 CO2;
extern u16 CO2Sv;

u8 NSLH_Alarm(void);
u8 NSLH_Start(void);
u8 NSLH_Stop(void);
u8 OccupanyMode(void);   //有人模式
u8 Unoccupanied(void);   //无人模式
void NSLH_Clear(void);
void CO2Control(void);
void RoomTempControl(float value);

#endif
