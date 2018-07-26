#ifndef __SYSCONFIG_H
#define __SYSCONFIG_H

#include "digital_io.h"
#include "systick_timer.h"
#include "adc.h" 
#include "dac.h"
#include "rtd.h"
#include "usart.h"
#include "timer.h"
#include "logic.h"
#include "globe.h"
#include "touchscreen.h"

//ȫ�ֱ�������Ҫ������BMSͨ��
u16 CHWTemp=0;
u16 DPValue=0;
u16 ValveFb=0;
u16 OccSta=0;
u16 ECS=0;

//С��ͨ�Ŷ��������
char TSReceivedBuffer[24];
char TSReadPortsBuffer[18];
char TSSendBuffer[22]={0};
char TSwriteRegister[12]={0};
char TSSentCheckCode=0;         //���������ݵ�Ч����
volatile TSTASKSEL TSTaskSel = TSNON;
u8 tx1[24]={0x55,0x66,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x55};
u8 tx2[24]={0x55,0x66,0x02,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x10,0x66,0x55};
u8 tx3[24]={0x55,0x66,0x03,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x10,0x66,0x55};
u8 tx4[24]={0x55,0x66,0x04,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x10,0x66,0x55};

//ϵͳ״̬������
u8 RunStatus=0;               //ϵͳ����״̬
u8 AlarmFlag=0;               //ϵͳ����λ
	
//BMS WriteCommand
u16 ScheduleComm=0;
u16 IBSCommand=0;
u16 PDVComm=0;
	
	
unsigned int  ReceivedNum = 0;
char  SentBuffer[200];

u16 CO2=0;
u16 CO2Sv=0;
u16 RoomTemp=0;
u16	RoomTempSv=250;
u16 RoomHum=0;
u16 RoomHumSv=600;
		
//PID control parameters
float error=0;
float ValvePosition=0.0;
float VavleFeedback=0.0;
float Para[3]={0.05,0.02,15};

u16 ValveCmd=0;							// 14, ������ȫ�������ִ�п����߼�
u16 ERVCmd=0;							  // 15; ERV����ȫ�������ִ�п����߼�
u16 ERVState=0;							// 16; ERV״̬������0Ϊ�أ�1Ϊȫ����������ֵΪ����2-100

u8 ForceValveFlag=0;        //ǿ�ƿ�����־λ
u8 ERVFlag=0;               //ǿ�ƿ�ERV��־λ

u16 PurgeCmd=0;							// 17; Purge�������0Ϊ�أ�1Ϊȫ����������10����
u16 TempSPSet_Unocc=250;				// 18; ����ģʽ���¶��趨ֵ	 
u16 SpareSet1=0;							// 19; ���ò�������1��0-100
u16 SpareSet2=1;							// 20; ���ò�������2��0-100
u16 SpareSet3=0;							// 21; ���ò�������3��0-100

void InitialSys(void);
void RCC_Configuration(void);
void IWDG_Configuration(void);
void RegMap(void);
void normal(void);
#endif
