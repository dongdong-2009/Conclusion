#ifndef __MODBUS_H
#define __MODBUS_H

#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"
#include "Globe.h"


//定义全局变量
extern u8 RS485_RX_BUFF[2048];               //接收缓存区2048字节
extern u16 RS485_RX_CNT;                   //接收计数器
extern u8 RS485_FrameFlag;                 //帧结束标记
extern u8 RS485_TX_BUFF[2048];               //发送缓存区2048字节
extern u16 RS485_TX_CNT;                   //发送计数器

//Modbus寄存器和单片机寄存器映射关系
extern vu32 *Modbus_InputIO[100];            //输入开关量寄存器指针(这里使用的是位带操作)
extern vu32 *Modbus_OutputIO[100];           //输出开关量寄存器指针(这里使用的是位带操作)
extern u16  *Modbus_HoldReg[1000];            //保持寄存器

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

//定义相关函数
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
