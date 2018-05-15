#ifndef __LOGIC_H
#define __LOGIC_H

#include "stm32f10x.h"
#include "digital_io.h"
#include "systick_timer.h"
#include "adc.h" 
#include "dac.h"
#include "rtd.h"
#include "timer.h"
#include "algorithm.h"

//AI
#define ERVSAFfb                    0                    //ERV风扇1反馈值
#define ERVEAFfb                    1										 //ERV风扇2反馈值
#define CHWVfb                      2			               //冷水阀反馈值
#define OffCoilTemp                 3                    //off-coil温度    

//RTD
#define CHWInTemp                   0                    //冷水进口温度
#define CHWOutTemp                  1                    //冷水出口温度

//DI
//1---Occupy State     0---Unoccupied mode 
#define LOCALORREMOTE               0                    //remote还是local模式
#define OccuState                   1                    //根据Occupined Sensor来获取运行状态：有人或无人
#define BMSSignal                   2                    //BMS 启动信号  1---Start  0---OFF
#define FANFault                    3										 //Fan fault

//AO
#define PTBFan1                     0                    //控制PTB风扇
#define ERVFan	                    1                    //控制ERV风扇
#define CHWV                        2                    //控制冷水阀开度
#define PTBFan                     	3                    //控制PTB风扇
#define PTBFanSpeed                 4                    //控制PTB风扇速度
#define ERVSAF                      5
#define ERVEAF                      6

//DO
#define NSLHAlarm                   2                    //报警信息

extern u8 TimeFlag;
extern u8 UnOccupined;
extern u8 ReceiveFlag;
extern u8 TSControl;
extern u8 TempPassive;

typedef enum _startselection
{
  TSstart   = 0x01,             //显示屏启动,正常启动
  BMSStart  = 0x02,	           //BMS启动 
  OccuStart = 0x03,	           //Occupined Sensor 启动模式  
}STARTSEL;

//系统状态标志位
extern u8 systemStatus;

extern float ADC_data[12];
extern float ADC_value[12];
extern float RTD_value[4];
extern float DAC_data[8];
extern u8 DI_data[8];
extern u8 DO_data[8];

extern u8 TimeFlag;
extern u8 UnOccupined;
extern u8 ReceiveFlag;
extern u8 TSControl;
extern u8 TempPassive;
extern u8 BMSControl;

extern float off_coilTemp;
extern float off_coilTempSv;
extern float chwInTemp;
extern float chwOutTemp;
extern float RoomTemp;
extern float RoomTempSv;
extern float CO2;
extern float CO2Sv;
extern float valve;
extern float FanSpeed;

extern u8 PTBFANRUN;
extern u8 ERVFANRUN;

u8 NSLH_Start(float ain[12],float aout[12],u8 din[8],u8 dout[8]);
u8 NSLH_BMSStart(float ain[12],float aout[12],u8 din[8],u8 dout[8]);
u8 NSLH_Stop(float ain[12],float aout[12],u8 din[8],u8 dout[8]);
u8 NSLH_Alarm(void);
void NSLH_UnOccMode(float ain[12],float aout[12],u8 din[8],u8 dout[8]);
void NSLH_Clear(float aout[12],u8 dout[8]);

void Get_value(float offcoilTemp,float chwIN,float chwOut,u8 occupined,u8 BMS);
float PhysicalValue(float range, float data, float Pyhsicallow, float Pyhsicalhigh);

void CO2Control(float co2, float co2Sv);
//void TempContol(float Offcoilsv,float Offcoilpv,float Roomsv,float Roompv);
void ValveOpen(float value);
void RTContrPassive(float Offcoilsv,float Offcoilpv,float Roomsv,float Roompv);
void RTContrHybrid(float Offcoilsv,float Offcoilpv,float Roomsv,float Roompv);


#endif
