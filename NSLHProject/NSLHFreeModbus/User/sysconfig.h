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

//全局变量，需要用来与BMS通信
u16 CHWTemp=0;
u16 DPValue=0;
u16 ValveFb=0;
u16 OccSta=0;
u16 ECS=0;

//小板通信定义相关量
char TSReceivedBuffer[24];
char TSReadPortsBuffer[18];
char TSSendBuffer[22]={0};
char TSwriteRegister[12]={0};
char TSSentCheckCode=0;         //待发送数据的效验码
volatile TSTASKSEL TSTaskSel = TSNON;
u8 tx1[24]={0x55,0x66,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x55};
u8 tx2[24]={0x55,0x66,0x02,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x10,0x66,0x55};
u8 tx3[24]={0x55,0x66,0x03,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x10,0x66,0x55};
u8 tx4[24]={0x55,0x66,0x04,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x10,0x66,0x55};

//系统状态量定义
u8 RunStatus=0;               //系统运行状态
u8 AlarmFlag=0;               //系统报警位
	
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

u16 ValveCmd=0;							// 14, 阀紧急全开命令，不执行控制逻辑
u16 ERVCmd=0;							  // 15; ERV紧急全开命令，不执行控制逻辑
u16 ERVState=0;							// 16; ERV状态反馈，0为关，1为全开，其余数值为开度2-100

u8 ForceValveFlag=0;        //强制开阀标志位
u8 ERVFlag=0;               //强制开ERV标志位

u16 PurgeCmd=0;							// 17; Purge开关命令，0为关，1为全开；开持续10分钟
u16 TempSPSet_Unocc=250;				// 18; 无人模式下温度设定值	 
u16 SpareSet1=0;							// 19; 备用参数设置1，0-100
u16 SpareSet2=1;							// 20; 备用参数设置2，0-100
u16 SpareSet3=0;							// 21; 备用参数设置3，0-100

void InitialSys(void);
void RCC_Configuration(void);
void IWDG_Configuration(void);
void RegMap(void);
void normal(void);
#endif
