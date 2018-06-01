#ifndef __BACKUP_H
#define __BACKUP_H			    

#include "flash.h"

#define BACKUP_REFRESH_S 60
#define BACKUP_SIZE 500
#define BACKUP_NUM_SEC 2 //((BACKUP_SIZE-1)/BACKUP_SEC_DATA_SIZE+1)  
#define BACKUP_SEC_SIZE 4096
#define BACKUP_SEC_DATA_SIZE 255
#define BACKUP_SEC_ERRATA_SIZE 1920 //(BACKUP_SEC_SIZE-256)/2
#define BACKUP_SEC_ERRATA_ADDR(i) (256+i*2)

#define BACKUP_DATA_ADDR 0

typedef struct _BackupTable
{
	uint8_t *pData;
	unsigned int BackupAddr;
	unsigned int dataSize;
}BackupTable;

typedef struct _ErrataItem
{
	uint8_t Addr;
	uint8_t Val;
}ErrataItem;

void Backup_Init(void);
u16  Backup_GetErrataPos(u16 sec);
u16 Backup_Mark2Pos(u8 mark);
u8 Backup_Pos2Mark(u16 pos);
void Backup_Load_Sec(u8 *buf, u16 sec, u8 loc, u8 num);
void Backup_Load(u8 *buf, u32 Num, u32 Addr);
void Backup_Update_Sec(u8 *buf, u16 sec, u8 loc, u8 num);
void Backup_Update(u8 *buf, u32 Num, u32 Addr);

void Backup_Task(void);


#endif

