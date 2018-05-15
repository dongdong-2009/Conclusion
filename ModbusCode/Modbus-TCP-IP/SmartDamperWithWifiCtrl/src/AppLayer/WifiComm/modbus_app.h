#ifndef _MODBUS_APP_TY_H
#define _MODBUS_APP_TY_H

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

typedef struct _RegTable
{
	unsigned int offset;
	unsigned int regAddr;
	unsigned int dataSize;
}RegTable;

//全局数据区
extern MbTcpAppData gModuleData;

//functions
void MbTcpApp_Init(void);
void MbTcpApp_Pro(char *recvData,uint32_t len,char *txData,uint32_t *txLen);

#endif

