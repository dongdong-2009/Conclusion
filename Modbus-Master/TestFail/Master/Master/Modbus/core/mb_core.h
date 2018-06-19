#ifndef __MB_CORE_H
#define __MB_CORE_H

#include "mb_type.h"

#define MB_ADDR_INDEX	0
#define MB_FUNCID_INDEX	1
#define MB_DATA_INDEX	2

#define FUNCID_READHDREG	0x03		//读保持寄存器
#define FUNCID_READIPREG	0x04		//读输入寄存器
#define FUNCID_WROHDREG		0x06		//写单保持寄存器
#define FUNCID_WRNHDREG		0x10		//写多保持寄存器

typedef enum
{
	EV_IDLE,                   /*!< Startup finished. */
	EV_M_SEND,          		   /*!< 主机发送 */
	EV_M_WAIT,                 /*!< 主机等待*/
	EV_M_RECEIVEING,           /*!< 主机接收中. */
	EV_M_RECEIVED,             /*!< 主机接收完毕 */
	EV_S_SEND, 								 /*!< 从机发送 */
	EV_S_RECEIVED,						 /*!< 从机接收完毕 */
	EV_S_RECEIVEING,           /*!< 从机接收完毕 */
} MB_EventType_t;



extern unsigned char MB_ADD;
extern unsigned short REG_HOLDING_START;
extern unsigned short REG_HOLDING_NREGS;
extern unsigned short REG_INPUT_START;
extern unsigned short REG_INPUT_NREGS;

extern unsigned char M_SendBuff[];
extern unsigned char M_ReceiveBuff[];
extern unsigned char S_SendBuff[];
extern unsigned char S_ReceiveBuff[];

extern unsigned short M_SendCnt;
extern unsigned short M_SendLen;
extern unsigned short S_SendCnt;
extern unsigned short S_SendLen;

extern unsigned short M_ReceiveCnt;
extern unsigned short S_ReceiveCnt;

extern unsigned short *usRegHoldingBuf;
extern unsigned short *usRegInputBuf;

extern mb_pro_t mb_pro_m;
extern mb_pro_t mb_pro_s;

extern unsigned long usTimerT35_50us;


unsigned char MB_EventInit( void );
unsigned char MB_EventPost( MB_EventType_t eEvent );
unsigned char MB_EventGet( MB_EventType_t * eEvent );
MB_EventType_t MB_EventState(void);

void MB_Poll(void);

void MB_M_FormatData(void);
void MB_S_Execute(unsigned char *buff,unsigned short len);
void MB_Init(unsigned long ulBaudRate);
void MB_RegInit(void);

#endif
