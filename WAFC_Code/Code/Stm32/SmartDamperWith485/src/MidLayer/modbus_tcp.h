#ifndef _MODBUS_TCP_TY_H
#define _MODBUS_TCP_TY_H

#define MODBUS_MAX_DATA_LEN					256

#define MODBUS_FUNC_RD						0x03
#define MODBUS_FUNC_WR						0x10
#define MODBUS_FUNC_WR_SINGLE				0x06

#define MODBUS_FUNC_RD_ERR					0x90
#define MODBUS_FUNC_WR_ERR					0x83

#define COM_RECV_OK							0
#define COM_RECV_CRC_ERR					-1
#define COM_RECV_PID_ERR					-2
#define COM_RECV_NO_DATA					-3
#define COM_RECV_FUNC_ERR					-4
#define COM_RECV_DATALEN_ERR				-5
#define COM_RECV_REGNUM_ERR					-6
#define COM_RECV_REGADDR_ERR				-7
#define COM_RECV_RDWR_ERR					-8

/* ----------------------- MBAP Header --------------------------------------*/
/* 
* 
*<------------------------ MODBUS TCP/IP ADU(1) -------------------------> 
*<----------- MODBUS PDU (1') ----------------> 
*+-----------+---------------+------------------------------------------+ 
*  | TID | PID | Length | UID  |Code | Data                               | 
*  +-----------+---------------+------------------------------------------+ 
*  |     |     |        |      |                                            
* (2)   (3)   (4)      (5)    (6)                                           
* 
* (2)  ... MB_TCP_TID          = 0 (Transaction Identifier - 2 Byte)  
* (3)  ... MB_TCP_PID          = 2 (Protocol Identifier - 2 Byte) 
* (4)  ... MB_TCP_LEN          = 4 (Number of bytes - 2 Byte) 
* (5)  ... MB_TCP_UID          = 6 (Unit Identifier - 1 Byte) 
* (6)  ... MB_TCP_FUNC         = 7 (Modbus Function Code) 
* 
* (1)  ... Modbus TCP/IP Application Data Unit 
* (1') ... Modbus Protocol Data Unit 
*/

/** @addtogroup private global variables
  * @{
  */
typedef enum {
	WAIT_FOR_TID_0,
	WAIT_FOR_TID_1,
	WAIT_FOR_PID_0,
	WAIT_FOR_PID_1,
	WAIT_FOR_LEN_0,
	WAIT_FOR_LEN_1,
	WAIT_FOR_UID,
	WAIT_FOR_FUNC,
	WAIT_FOR_REGADDR,
	WAIT_FOR_REGADDR2,
	WAIT_FOR_REGNUM,
	WAIT_FOR_REGNUM2,
	WAIT_FOR_DATALEN,
	WAIT_FOR_DATA,
	WAIT_FOR_COMPLETE,
	RECV_ERR,
}RECV_PARSE_STATE;

typedef struct _MbTcpCommMsg{
	unsigned short tid;
	unsigned short pid;
	unsigned short pktLen;
	unsigned short uid;

	unsigned char funCode;
	unsigned char errCode;
	unsigned short regAddr;
	int regNum;
	unsigned int dataLen;
	unsigned int dataIdx;
	unsigned char regData[MODBUS_MAX_DATA_LEN];
} MbTcpCommMsg;

extern MbTcpCommMsg modbusMsg;


void MbTcp_Init(void);
int MbTcp_RecvFrame(char *pData, uint32_t recvLen);
#endif
/*----------------------------------end of file-------------------------------------------*/
