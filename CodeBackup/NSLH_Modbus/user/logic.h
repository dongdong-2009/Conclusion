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
#define ERVSAFfb                    0                    //ERV����1����ֵ
#define ERVEAFfb                    1										 //ERV����2����ֵ
#define CHWVfb                      2			               //��ˮ������ֵ
#define OffCoilTemp                 3                    //off-coil�¶�    

//RTD
#define CHWInTemp                   0                    //��ˮ�����¶�
#define CHWOutTemp                  1                    //��ˮ�����¶�

//DI
//1---Occupy State     0---Unoccupied mode 
#define LOCALORREMOTE               0                    //remote����localģʽ
#define OccuState                   1                    //occupy����״̬

//AO
#define ERVSAF                      0                    //����ERV����1
#define ERVEAF                      1                    //����ERV����2
#define CHWV                        2                    //������ˮ������
#define PTBFanSpeed                 3                    //����PTB�����ٶ�

//DO
#define PTBFan                      0                    //PTB���ȵ�Դ
#define ERVFan                      1                    //ERV���ȵ�Դ
#define NSLHAlarm                   2                    //������Ϣ

typedef enum _startselection
{
  TSstart   = 0x01,             //��ʾ������,��������
  BMSStart  = 0x02,	           //BMS���� 
  OccuStart = 0x03,	           //Occupined Sensor ����ģʽ  
}STARTSEL;

//ϵͳ״̬��־λ
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

u8 NSLH_Start(float ain[12],float aout[12],u8 din[8],u8 dout[8]);
u8 NSLH_BMSStart(float ain[12],float aout[12],u8 din[8],u8 dout[8]);
u8 NSLH_Stop(float ain[12],float aout[12],u8 din[8],u8 dout[8]);
u8 NSLH_Alarm(void);
void NSLH_OccMode(float ain[12],float aout[12],u8 din[8],u8 dout[8]);
void NSLH_Clear(float aout[12],u8 dout[8]);

void Get_value(float offcoilTemp,float chwIN,float chwOut,u8 occupined);
float PhysicalValue(float range, float data, float Pyhsicallow, float Pyhsicalhigh);

void CO2Control(float co2, float co2Sv);
//void TempContol(float Offcoilsv,float Offcoilpv,float Roomsv,float Roompv);
void ValveOpen(float value);
void RTContrPassive(float Offcoilsv,float Offcoilpv,float Roomsv,float Roompv);
void RTContrHybird(float Offcoilsv,float Offcoilpv,float Roomsv,float Roompv);


#endif
