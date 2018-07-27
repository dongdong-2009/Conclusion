#ifndef __STM32_CONFIGH_H
#define __STM32_CONFIGH_H

#include "digital_io.h"
#include "systick_timer.h"
#include "adc.h" 
#include "dac.h"
#include "rtd.h"
#include "usart.h"
#include "timer.h"
#include "runtimedata.h"
#include "touchscreen.h"
#include "protocol.h"
#include "logic.h"

//data---���ź�ֵ��value---��������ֵ
float  TSRegister[12]={0};
float  Registers[16]={0};                 //�Ĵ���ֵ,�洢�Ƕ˿�������
float  ADC_value[12]={0};                 //ADC��������ֵ
float  ADC_data[12]={0};                  //ADC���ź�ֵ
float  RTD_value[4]={0};
float  DAC_value[8]={0};
float  DAC_data[8]={0};
u8   	 DI_data[8]={0};
u8     DO_data[8]={0};
float  Setpoint[3]={0};

//���ջ�����
//AOAM: analog output auto-manual
//REGAM: register auto-manual
LOOPSEL AOAM[8] = {OPENLOOP,OPENLOOP,OPENLOOP,OPENLOOP,OPENLOOP,OPENLOOP,OPENLOOP,OPENLOOP};
LOOPSEL REGAM[16];
PARAMS AOParams[8] = {{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0}};
//y = a*x +b
PARAMS AIParams[12] = {{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0}};

char ReadPortsBuffer[165];
char WritePortsBuffer[104];
char ReadPIDBuffer[96];
char WritePIDBuffer[97]; //HandleBit(1),PID1---PID4(24/each);

//����λ��ͨ�ţ�����λ��ʼ������
//volatile�������α���ͬ�̷߳��ʺ��޸ĵı�����ȷ��ָ�����Ϊ���������Ż���ʡ�ԣ���Ҫ��ÿ��ֱ�Ӷ�ֵ
unsigned int MCUaddress = 0;                //��MCU�ĵ�ַ������Ψһ�궨��MCU����Config��ȷ��
volatile STAGESEL StageSel = CONFIG;        //ͨ�Ŵ���USART1��ʱ���ã��׶�ѡ��
volatile TASKSEL TaskSel = NON;			        //Runtime������ѡ�� 
volatile MODESEL ModeSel = LOAD;		        //Config��ģʽѡ��
volatile LINESEL LineSel = ONLINE;
volatile char ReceivedState = 0;
unsigned int  ReceivedNum = 0;
char  ReceivedBuffer[4000];
char  SentBuffer[200];
	
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
u8 PannelControl=0;           //������
u8 PannelStatus=0;            //���״̬
u8 DeviceRun=0;               //��λ������
u8 TSControl=0;               //��ʾ������
u8 BMSControl=0;              //BMS����
u8 RunStatus=0;               //ϵͳ����״̬
u8 TimeFlag=0;                //����ʱ���־λ
u8 systemStatus=0;            //ϵͳ״̬
u8 SystemNormal=0;            //ϵͳ����ģʽ
u8 UnOccupined=1;               //ϵͳ����ģʽ
u8 AlarmFlag=0;               //ϵͳ����λ
u8 ReceiveFlag=0;             //���ݽ������
u8 TempPassive=1;             //�¶�Passiveģʽ��Hybridģʽ�л���־λ��1---Passive Mode��0---Hybrid Mode
volatile STARTSEL StartSel = TSstart;
	
	
//ȫ�ֱ���
float off_coilTemp=0.0;
float off_coilTempSv=17.0;
float chwInTemp=0.0;
float chwOutTemp=0.0;
float valve=0.0;            //���Ʒ��ſ���
float FanSpeed=0.0;         //����PTB�����ٶ�

float CO2=0.0;
float CO2Sv=0.0;
float RoomTemp=0.0;
float	RoomTempSv=0.0;
float RoomHum=0.0;
		
//PID����
float Kp;
float Ki;
float Kd;
	
void RCC_Configuration(void);

#endif
