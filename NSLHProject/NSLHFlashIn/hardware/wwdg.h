#ifndef __WWDG_H
#define __WWDG_H

#include "stm32f10x.h"

/* 宏定义 --------------------------------------------------------------------*/
#define FLASH_ADDR_FLAG           0x08010000     //FLASH地址 - 标志位
#define FLASH_ADDR_DATA           0x08010002     //FLASH地址 - 数据

extern uint8_t WriteBuf[20];    //写入的数据
extern uint8_t ReadBuf[20];     //读出的数据

//存储的状态量
extern u16 RoomTempSv;
extern u16 TempSPSet_Unocc;	
extern u16 ERVCmd;
extern u16 IBSCommand;
extern u16 ScheduleComm;
extern u16 PurgeCmd;
extern u16 ValveCmd;
extern u16 PDVComm;
extern u8 RunStatus;
extern u16 OccSta;

void WWDG_Init(u8 tr,u8 wr,u32 prv);  //初始化WWDG
void WWDG_Set_Counter(u8);            //设置WWDG的计数器，喂狗
void WWDG_NVIC_Init(void);            //初始化窗口看门狗中断优先级配置	
void FlashDataPack(void);             //状态命令封装
void FlashDataRead(void);             //状态命令读取

#endif
