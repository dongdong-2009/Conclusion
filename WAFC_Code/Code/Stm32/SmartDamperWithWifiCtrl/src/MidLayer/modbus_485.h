#ifndef _MODBUS_485_H
#define _MODBUS_485_H

#define MB485_STATE_				0x00
#define MB485_STATE_RECV		0x01
#define MB485_STATE_SEND		0x02

typedef struct _Mb485_Server
{
	unsigned char TaskState;
}Mb485_Server;


void Mb485_Init(void);
void Mb485_Task(void);
unsigned char Mb485_ReceiveFrame(void);

#endif
