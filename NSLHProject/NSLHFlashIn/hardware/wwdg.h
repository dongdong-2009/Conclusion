#ifndef __WWDG_H
#define __WWDG_H

#include "stm32f10x.h"

/* �궨�� --------------------------------------------------------------------*/
#define FLASH_ADDR_FLAG           0x08010000     //FLASH��ַ - ��־λ
#define FLASH_ADDR_DATA           0x08010002     //FLASH��ַ - ����

extern uint8_t WriteBuf[20];    //д�������
extern uint8_t ReadBuf[20];     //����������

//�洢��״̬��
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

void WWDG_Init(u8 tr,u8 wr,u32 prv);  //��ʼ��WWDG
void WWDG_Set_Counter(u8);            //����WWDG�ļ�������ι��
void WWDG_NVIC_Init(void);            //��ʼ�����ڿ��Ź��ж����ȼ�����	
void FlashDataPack(void);             //״̬�����װ
void FlashDataRead(void);             //״̬�����ȡ

#endif
