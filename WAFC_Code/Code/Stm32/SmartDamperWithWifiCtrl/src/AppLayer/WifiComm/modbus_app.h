#ifndef __MODBUS_APP_H
#define __MODBUS_APP_H

#define OFFSET(type, field) ((int)__INTADDR__(&(((type *)0)->field)))

#define FLOW_MEASURE_SRC_ 0x00
#define FLOW_MEASURE_SRC_PITOT 0x01
#define FLOW_MEASURE_SRC_MESH 0x02

#define FLOW_SP_SRC_ 0x00
#define FLOW_SP_SRC_MANUAL 0x01
#define FLOW_SP_SRC_VENT 0x02

#define DAMPER_SP_SRC_ 0x00 
#define DAMPER_SP_SRC_FBCTRL 0x01 
#define DAMPER_SP_SRC_MANUAL 0x02 

#define DAMPER_MODE_ 0x00
#define DAMPER_MODE_TRACKING 0x01
#define DAMPER_MODE_SELFCHECK 0x02

#define SERVO_MODE_ 0x00
#define SERVO_MODE_TRACKING 0x01
#define SERVO_MODE_BLOCKED 0x02

#define CO2_MEASURE_SRC_ 0x00
#define CO2_MEASURE_SRC_SENSOR 0x01
#define CO2_MEASURE_SRC_MANUAL 0x02

#define VENTCTRL_MODE_ 0x00
#define VENTCTRL_MODE_MANUAL 0x01
#define VENTCTRL_MODE_VENTILATING 0x02
#define VENTCTRL_MODE_ONDEMAND 0x03
#define VENTCTRL_MODE_UNOCCUPIED 0x04

#define FEEDBACK_SRC_ 0x00
#define FEEDBACK_SRC_FLOW 0x01
#define FEEDBACK_SRC_CO2 0x02

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
	unsigned short Mode;
} StructDamperZone;

typedef struct _StructServoZone
{
	unsigned short PWM;
	float Current;
	unsigned short PWM_Angle_0;
	unsigned short PWM_Angle_90;
	unsigned short Mode;
} StructServoZone;

typedef struct _StructPitotZone
{
	float DiffPressure;
	float AmpCoeff;
	float SizeCoeff;
	float TempCoeff;
	float PressureBias;
	float Temperature;
	float Var_DiffPressure;
} StructPitotZone;

typedef struct _StructCO2Zone
{
	unsigned short Measure;
	unsigned short MeasureSrc;
	short Bias;
	unsigned short Limit;
} StructCO2Zone;

typedef struct _StructVentiZone
{
	unsigned short Mode;
	float Kp_FlowSP;
	float MinFlow;
} StructVentiZone;

typedef struct _StructPIDCtrlZone
{
	float U;
	float LB;
	float UB;
	float Kp;
	float Ki;
	float G0;
	float G1;
	unsigned short FbSrc;
} StructPIDCtrlZone;

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
	StructVentiZone VentCtrl;
	StructPIDCtrlZone PIDCtrl;
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
void MbTcpApp_Pro(char *recvData,unsigned int len,char *txData,unsigned int *txLen);

#endif

