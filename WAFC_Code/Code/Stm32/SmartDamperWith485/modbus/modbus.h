#ifndef _MODBUS_H
#define _MODBUS_H

#include "stdint.h"
#include "usart.h"
//#include "modbus_app.h"

#define modbus_deviceId  0x01
#define RS485MOED_R  GPIO_ResetBits(GPIOB,GPIO_Pin_14)
#define RS485MOED_S  GPIO_SetBits(GPIOB,GPIO_Pin_14)

extern uint16_t ReadReg[100];
extern uint16_t WriteReg[100];

extern uint16_t AdREG[12];                  //modbus Ó³Éä¼Ä´æÆ÷ Ad ch1-ch12
extern uint16_t DiREG[8];                   //modbus Ó³Éä¼Ä´æÆ÷ Di ch1-ch8
extern uint16_t DoREG[8];                   //modbus Ó³Éä¼Ä´æÆ÷ D0 ch1-ch8
extern uint16_t DAREG[8];                   //modbus Ó³Éä¼Ä´æÆ÷ Da ch1-ch8
extern int16_t  RTDREG[4];                  //modbus Ó³Éä¼Ä´æÆ÷ RTD ch1-ch4

extern uint8_t TimerOverFlag;
extern uint8_t BegainRxFlag;
extern uint8_t BusyFlag;

#define OFFSET(type, field) ((int)__INTADDR__(&(((type *)0)->field)))

typedef struct _StructSysZone
{
	unsigned short Version;
	unsigned short SubVersion;
}StructSysZone;

typedef struct _StructFlowZone
{
	float Measure;
	unsigned short MeasureSrc;
	float SetPoint;
	unsigned short SetPointSrc;
} StructFlowZone;

typedef struct _StructDamperZone
{
	float Position;
	float SetPoint;
	unsigned short SetPointSrc;
	unsigned short Open_PWM;
	unsigned short Close_PWM;
} StructDamperZone;

typedef struct _StructServoZone
{
	unsigned short PWM;
	float Current;
} StructServoZone;

typedef struct _StructPitotZone
{
	float DiffPressure;
	float AmpCoeff;
	float SizeCoeff;
	float TempCoeff;
	float PressureBias;
	float Temperature;
} StructPitotZone;

typedef struct _StructCO2Zone
{
	unsigned short Measure;
	unsigned short MeasureSrc;
	float Kp_FlowSP;
} StructCO2Zone;

typedef struct _StructFBCtrlZone
{
	float Kp;
} StructFBCtrlZone;

typedef struct _StructTerminalZone
{
	float Flow;
	float Damper;
	unsigned short CO2;
} StructTerminalZone;

typedef struct _StructFanZone
{
	float Speed;
	float Pressure;
} StructFanZone;

typedef struct _RegTable
{
	unsigned int offset;
	unsigned int regAddr;
	unsigned int dataSize;
}RegTable;

typedef struct _MbTcpAppData
{
	StructSysZone Sys;
	StructFlowZone Flow;
	StructDamperZone Damper;
	StructServoZone Servo;
	StructPitotZone Pitot;
	StructCO2Zone CO2;
	StructFBCtrlZone FBCtrl;
	StructTerminalZone Terminal[10];
	StructFanZone Fan;
}MbTcpAppData;

extern MbTcpAppData gModuleData;

void MbTcpApp_Init(void);
void DealModBus(void);
u16 crc16(u8 *ptr,u8 len);

#endif
