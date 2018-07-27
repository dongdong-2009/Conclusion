#ifndef __MODBUS_H
#define __MODBUS_H

#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"
#include "Globe.h"


//����ȫ�ֱ���
extern u8 RS485_RX_BUFF[2048];               //���ջ�����2048�ֽ�
extern u16 RS485_RX_CNT;                   //���ռ�����
extern u8 RS485_FrameFlag;                 //֡�������
extern u8 RS485_TX_BUFF[2048];               //���ͻ�����2048�ֽ�
extern u16 RS485_TX_CNT;                   //���ͼ�����

//Modbus�Ĵ����͵�Ƭ���Ĵ���ӳ���ϵ
extern vu32 *Modbus_InputIO[100];            //���뿪�����Ĵ���ָ��(����ʹ�õ���λ������)
extern vu32 *Modbus_OutputIO[100];           //����������Ĵ���ָ��(����ʹ�õ���λ������)
extern u16  *Modbus_HoldReg[1000];            //���ּĴ���

extern u32 CO2Value;
extern u32 CO2ValueSv;
extern u32 RoomTempPv;
extern u32 RoomTempSetValue;
extern u32 RoomHumPv;
extern u32 RoomHumSetValue;
extern u32 CHWTemp;
extern u32 DPValue;
extern u32 ValveFb;
extern u32 OccSta;
extern u32 ECS;

extern u16 CO2;
extern u16 CO2Sv;
extern u16 RoomTemp;
extern u16	RoomTempSv;
extern u16 RoomHum;

//������غ���
void Modbus_RegMap(void);
void RS485_Service(void);
void Modbus_02_Solve(void);
void Modbus_01_Solve(void);
void Modbus_05_Solve(void);
void Modbus_15_Solve(void);
void Modbus_03_Solve(void);
void Modbus_06_Solve(void);
void Modbus_16_Solve(void);

#endif
