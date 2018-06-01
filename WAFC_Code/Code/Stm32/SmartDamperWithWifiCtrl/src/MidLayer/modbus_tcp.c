#include <stm32f10x.h>
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#include "modbus_tcp.h"

/** @addtogroup extern global variables
  * @{
  */


/** @addtogroup private global variables
  * @{
  */

MbTcpCommMsg modbusMsg;
RECV_PARSE_STATE recvState; 


/**
  * @brief:	 初始化
  * @param:	 None
  * @retval:   None
  */
void MbTcp_Init(void)
{
	recvState = WAIT_FOR_TID_0; 
}

/**
  * @brief:	接收并解析报文,不支持多帧传输
  * @param:	
  * @retval:   0：OK;<0:fail
  */
int MbTcp_RecvFrame(char *pData, uint32_t recvLen)
{
	int ret = COM_RECV_NO_DATA;
	unsigned char readByte;
	unsigned int i = 0;

	while(recvLen > 0)
	{
		readByte = (uint8_t)(pData[i]);

		switch(recvState)
		{
			case WAIT_FOR_TID_0:
				modbusMsg.tid = readByte;
				modbusMsg.tid <<= 8;				
				recvState = WAIT_FOR_TID_1; 
				recvLen--;
				break;
			case WAIT_FOR_TID_1:
				modbusMsg.tid |= readByte;					
				recvState = WAIT_FOR_PID_0; 
				recvLen--;
				break;
			case WAIT_FOR_PID_0:
				modbusMsg.pid = readByte;
				modbusMsg.pid <<= 8;				
				recvState = WAIT_FOR_PID_1; 
				recvLen--;
				break;
			case WAIT_FOR_PID_1:
				modbusMsg.pid |= readByte;
				if(modbusMsg.pid != 0)
				{
					recvState = WAIT_FOR_TID_0; 
					ret = COM_RECV_PID_ERR;
				}
				else	
					recvState = WAIT_FOR_LEN_0; 				
				recvLen--;
				break;
			case WAIT_FOR_LEN_0:
				modbusMsg.pktLen = readByte;
				modbusMsg.pktLen <<= 8;				
				recvState = WAIT_FOR_LEN_1; 
				recvLen--;
				break;
			case WAIT_FOR_LEN_1:
				modbusMsg.pktLen |= readByte;
				recvState = WAIT_FOR_UID; 
				recvLen--;
				break;
			case WAIT_FOR_UID:
				modbusMsg.uid = readByte;
				recvState = WAIT_FOR_FUNC; 				
				recvLen--;
				break;
			case WAIT_FOR_FUNC:
				modbusMsg.funCode = readByte;
				if((modbusMsg.funCode == MODBUS_FUNC_RD) || \
					(modbusMsg.funCode == MODBUS_FUNC_WR) || \
					(modbusMsg.funCode == MODBUS_FUNC_WR_SINGLE))
				{
					//modbusMsg.wr = readByte;
					recvState = WAIT_FOR_REGADDR;
				}
				else
				{
					recvState = WAIT_FOR_TID_0;
					ret = COM_RECV_FUNC_ERR; 
				}
				recvLen--;
				break;
			case WAIT_FOR_REGADDR:
				recvLen--;
				modbusMsg.regAddr = readByte;
				modbusMsg.regAddr <<= 8;				
				recvState = WAIT_FOR_REGADDR2;
				break;
			case WAIT_FOR_REGADDR2:
				recvLen--;
				modbusMsg.regAddr |= readByte;				
				recvState = WAIT_FOR_REGNUM;
				break;
			case WAIT_FOR_REGNUM:
				recvLen--;
				recvState = WAIT_FOR_REGNUM2;
				if(modbusMsg.funCode == MODBUS_FUNC_WR_SINGLE)
				{
					modbusMsg.regData[0] = readByte;
				}
				else
				{
					modbusMsg.regNum = readByte;
					modbusMsg.regNum <<= 8;				
					
				}
				break;
			case WAIT_FOR_REGNUM2:
				recvLen--;
				modbusMsg.regNum |= readByte;
				
				switch(modbusMsg.funCode)
				{
					case MODBUS_FUNC_RD:
						recvState = WAIT_FOR_TID_0; 
						ret = COM_RECV_OK;
						break;
					case MODBUS_FUNC_WR_SINGLE:
						modbusMsg.regData[1] = readByte;
						modbusMsg.regNum = 1;
						recvState = WAIT_FOR_TID_0; 
						ret = COM_RECV_OK;
						break;
					default:
						recvState = WAIT_FOR_DATALEN;
						break;
				}
				break;
			case WAIT_FOR_DATALEN:
				recvLen--;
				modbusMsg.dataLen = readByte;

				if(readByte == 0)
				{
					recvState = WAIT_FOR_TID_0;
					break;
				}
				modbusMsg.dataIdx = 0;
				recvState = WAIT_FOR_DATA; 
				break;
			case WAIT_FOR_DATA:
				if(modbusMsg.dataLen >= MODBUS_MAX_DATA_LEN)
				{
					recvState = WAIT_FOR_TID_0;
					ret = COM_RECV_DATALEN_ERR;
					recvLen = 0;
					break;
				}
				if(recvLen == modbusMsg.dataLen)
				{
					memcpy(modbusMsg.regData,&(pData[i]),recvLen);
					recvState = WAIT_FOR_TID_0;
					ret = COM_RECV_OK;
				}
				else
				{
					recvState = WAIT_FOR_TID_0;
					ret = COM_RECV_DATALEN_ERR;
				}
				recvLen = 0;
				break;
			default:
				recvState = WAIT_FOR_TID_0;
				break;
		}
		
		i++;
	}
	
	//每次收到的都将是一封完整的Modbus报文，否则会引起混乱
	recvState = WAIT_FOR_TID_0;
	
	return ret;
}

