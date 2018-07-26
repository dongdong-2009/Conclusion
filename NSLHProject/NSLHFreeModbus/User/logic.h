#ifndef __LOGIC_H
#define __LOGIC_H

#include "stm32f10x.h"

//AI
#define DIFFPRE                   	3										   //ѹ��
#define CHWVfb                      11			               //��ˮ������ֵ   

//RTD
#define CHWOutTemp                  2                    //��ˮ�����¶�

//AO
#define PTBFan1                     4                    //����PTB����
#define ERVFan	                    7                    //����ERV����
#define CHWV                        2                    //������ˮ������
#define PTBFan2                    	3                    //����PTB���ȣ��󷿼���6̨PTB���������˿ڿ���

//DO
#define NSLHAlarm                   2                    //������Ϣ

extern u16 RoomTemp;
extern u16 RoomTempSv;
extern u16 CO2;
extern u16 CO2Sv;

u8 NSLH_Alarm(void);
u8 NSLH_Start(void);
u8 NSLH_Stop(void);
u8 OccupanyMode(void);   //����ģʽ
u8 Unoccupanied(void);   //����ģʽ
void NSLH_Clear(void);
void CO2Control(void);
void RoomTempControl(float value);

#endif
