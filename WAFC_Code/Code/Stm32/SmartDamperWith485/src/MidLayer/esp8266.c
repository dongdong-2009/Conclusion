#include "esp8266.h"


/*----------------global variables--------------------*/
//用于解析IPD报文
typedef struct _IpdPktStr
{
	uint8_t ipdDate[ESP8266_IPD_DATA_LEN];
	uint32_t ipdIdx;
	
	char ipdLenStr[8];
	uint32_t ipdLenStrIdx;
	uint32_t ipdLen;
	
	char ipdIdStr[8];
	uint32_t ipdIdIdx;
	uint32_t ipdId;

	char ipdIp[32];
	char ipdIpIdx;
}IpdPktStr;

IpdPktStr esp8266IpdPkt;

char esp8266RespBuf[ESP8266_RXBUF_SIZE];
char esp8266ErrResp[6]="ERROR";
char esp8266ErrResp2[6]="FAIL";

uint32_t esp8266SendState;
uint32_t esp8266RespBufOff;
uint32_t esp8266RespStrlen;
uint32_t esp8266RespStrNum;
uint32_t esp8266RespRecvNum;
uint32_t esp8266RespErrStrNum;
uint32_t esp8266RespErr2StrNum;
uint32_t esp8266SendTimer;
uint32_t esp8266IpdPktState;

WifiRecvBuf ipdDatatBuf;


/**
  * @brief  Esp8266 init
  * @param  波特率
  * @retval 1
  */
uint32_t Esp8266_Init(uint32_t ulWantedBaud)
{		
	esp8266SendState = ESP8266_SEND_CMD;
	esp8266SendTimer = 0;
	esp8266RespBufOff = 0;
	esp8266RespStrlen = 0;
	esp8266RespStrNum = 0;
	esp8266RespRecvNum = 0;
	esp8266RespErrStrNum = 0;
	esp8266IpdPktState = IPD_H1;
	
	memset(esp8266RespBuf,0,ESP8266_RXBUF_SIZE);

	Esp8266_IPDBufInit(&ipdDatatBuf);
	
	BSP_WifiUart_HwInit(ulWantedBaud);

	return 1;
}

/**
  * @brief  Esp8266 send cmd
  * @param  buffer and len
  * @retval None
  */
uint32_t Esp8266_SendCmd(char * cmd,uint32_t len)
{
#if 1
	char *pxNext;
	uint32_t ret = 1;

	/* Send each character in the string, one at a time. */
	pxNext = ( char * ) cmd;

	while( len )
	{
		if(BSP_USART_TxBufIn(&uartTxBuf[WIFI_UART],*pxNext) == 0)
		{
			ret = 0;
			break;
		}
		pxNext++;
		len--;
	}

	//置位uart中断
	WIFI_USART_TYPE->CR1 |= USART_FLAG_TXE;
	
	return ret;
#else
	BSP_USART3_PollSend((uint8_t *)cmd, len);
	return 0;
#endif
}

/**
  * @brief  Esp8266 从串口缓冲区读取一个字符
  * @param  buffer and character
  * @retval None
  */

uint32_t Esp8266_GetChar( uint8_t *pcRxedChar)
{
	if(BSP_USART_RxBufOut(&uartRxBuf[WIFI_UART],(uint8_t *)pcRxedChar) != 0)
	{
		return 1;
	}
	else
		return 0;
	
}

/**
  * @brief  init the buffer
  * @param  None
  * @retval None
  */
void Esp8266_IPDBufInit (WifiRecvBuf *buf) 
{
	buf->rear  = 0;
	buf->front = 0;
}

/**
  * @brief   put a character into the buffer
  * @param  buffer and character
  * @retval None
  */
unsigned int  Esp8266_IPDBufIn (WifiRecvBuf *buf, WifiRecvStr *c) 
{
	unsigned int next;

	next = (buf->rear + 1) % WIFI_RECVDATABUF_LEN;   /* check if space is available */
	if (next == buf->front)  /* buffer full */
	{               
		//return 0;
		buf->front = ((buf->front + 1) % WIFI_RECVDATABUF_LEN);
	}

	buf->buffer[buf->rear] = *c;
	buf->rear = next;

	return 1;
}

/**
  * @brief   get a character out of  the buffer
  * @param  buffer and character
  * @retval None
  */
unsigned int  Esp8266_IPDBufOut (WifiRecvBuf *buf, WifiRecvStr *c) 
{
	unsigned int next;

	if (buf->front == buf->rear) /* check if data is available */
	{                   
		return 0;
	}

	next = (buf->front + 1) % WIFI_RECVDATABUF_LEN;

	*c = buf->buffer[buf->front];
	buf->front = next;

	return 1;
}

/**
  * @brief   get the size of the buffer
  * @param  buffer and character
  * @retval None
  */
unsigned int  Esp8266_IPDBufSize (WifiRecvBuf *buf) 
{
	unsigned int used;

	used = (WIFI_RECVDATABUF_LEN + buf->rear - buf->front) % WIFI_RECVDATABUF_LEN;

	return (used);
}

/**
  * @brief  解析IPD报文
  * @param  buffer and character
  * @retval None
  */
void Esp8266_IpdPro(uint8_t readbyte)
{
	uint32_t i;
	WifiRecvStr recvStr;
		
	switch(esp8266IpdPktState)
	{
		case IPD_H1:
			if(readbyte == 'I')
			{
				esp8266IpdPktState = IPD_H2;
			}
			break;
		case IPD_H2:
			if(readbyte == 'P')
			{
				esp8266IpdPktState = IPD_H3;
			}
			else
				esp8266IpdPktState = IPD_H1;
			break;
		case IPD_H3:
			if(readbyte == 'D')
			{
				esp8266IpdPktState = IPD_ID;
			}
			else
				esp8266IpdPktState = IPD_H1;
			break;
		case IPD_ID:
			if(readbyte == ',')
			{
				esp8266IpdPktState = IPD_ID_IN;
				
				for(i=0;i<8;i++)
					esp8266IpdPkt.ipdIdStr[i] = 0;
				
				esp8266IpdPkt.ipdIdIdx = 0;
			}
			else
				esp8266IpdPktState = IPD_H1;
			break;
		case IPD_ID_IN:
			if(readbyte != ',')
			{
				if((readbyte >= 0x30) && (readbyte <=0x39))
				{
					esp8266IpdPkt.ipdIdStr[(esp8266IpdPkt.ipdIdIdx)] = readbyte;
					esp8266IpdPkt.ipdIdIdx++;
				}
				else
					esp8266IpdPktState = IPD_H1;
			}
			else
			{
				esp8266IpdPkt.ipdId = atoi(esp8266IpdPkt.ipdIdStr);
				
				for(i=0;i<8;i++)
					esp8266IpdPkt.ipdLenStr[i] = 0;
				
				esp8266IpdPkt.ipdLenStrIdx = 0;

				esp8266IpdPktState = IPD_LEN_IN;
			}
			break;
		case IPD_LEN_IN:
			if(readbyte != ',')
			{
				if((readbyte >= 0x30) && (readbyte <=0x39))
				{
					esp8266IpdPkt.ipdLenStr[(esp8266IpdPkt.ipdLenStrIdx)] = readbyte;
					esp8266IpdPkt.ipdLenStrIdx++;
				}
				else
					esp8266IpdPktState = IPD_H1;
			}
			else
			{
				esp8266IpdPkt.ipdLen = atoi(esp8266IpdPkt.ipdLenStr);
				esp8266IpdPkt.ipdIdx = 0;
				
				if(esp8266IpdPkt.ipdLen >= ESP8266_IPD_DATA_LEN)
					esp8266IpdPktState = IPD_H1;
				else
				{
					for(i=0;i<32;i++)
						esp8266IpdPkt.ipdIp[i] = 0;
				
					esp8266IpdPkt.ipdIpIdx = 0;

					esp8266IpdPktState = IPD_REMOTEIP;
				}
			}
			break;
		case IPD_REMOTEIP:
			if(readbyte != ',')
			{
				esp8266IpdPkt.ipdIp[(esp8266IpdPkt.ipdIpIdx)] = readbyte;
				esp8266IpdPkt.ipdIpIdx++;
			}
			else
			{
				esp8266IpdPktState = IPD_REMOTEID;
			}
			break;
		case IPD_REMOTEID:
			if(readbyte != ':')
			{
			}
			else
			{
				esp8266IpdPktState = IPD_GETPKT;
			}
			break;
		case IPD_GETPKT:
			esp8266IpdPkt.ipdDate[(esp8266IpdPkt.ipdIdx)] = readbyte;
			esp8266IpdPkt.ipdIdx++;
			if(esp8266IpdPkt.ipdIdx >= (esp8266IpdPkt.ipdLen))
			{
				esp8266IpdPkt.ipdDate[(esp8266IpdPkt.ipdLen)] = 0x0;
				
				esp8266IpdPktState = IPD_H1;

				memcpy((char *)recvStr.data,(char *)esp8266IpdPkt.ipdDate,esp8266IpdPkt.ipdLen);

				recvStr.ip = inet_addr_ty((char *)esp8266IpdPkt.ipdIp);
				recvStr.len = esp8266IpdPkt.ipdLen;
				recvStr.socket = esp8266IpdPkt.ipdId;

				Esp8266_IPDBufIn(&ipdDatatBuf,&recvStr);
			}
			break;
	}	
}

/**
  * @brief  解析IPD报文
  * @param  buffer and character
  * @retval None
  */
uint32_t Esp8266_IpdProState(void)
{
	return esp8266IpdPktState;

}

/**
  * @brief  u7500 发送命令后等待回复
  * @param  buffer and character
  * @retval 0:OK;1:In;2:timeout Fail;3:response error fail
  */
uint32_t Esp8266_CheckWithCmd(EspATcmdStr *cmdinfo, char * recvdata,uint32_t len)
{
	uint8_t data;
	uint32_t xReturn = 1;

	switch(esp8266SendState)
	{
		case ESP8266_SEND_CMD:
			
			memset(esp8266RespBuf,0,ESP8266_RXBUF_SIZE);
			
			//BSP_USART_RxBufInit(&uartRxBuf[WIFI_UART]);
			
			esp8266SendTimer = Get_Gtime();
			
			if(cmdinfo->cmd != NULL)
				Esp8266_SendCmd(cmdinfo->cmd,cmdinfo->cmd_len);

			if(cmdinfo->resp != NULL)
				esp8266RespStrlen = strlen(cmdinfo->resp);

			if(recvdata != NULL)
				memset(recvdata,0,len);

			esp8266RespRecvNum = 0;
			esp8266RespBufOff = 0;
			esp8266RespStrNum = 0;
			esp8266RespErrStrNum = 0;
			esp8266RespErr2StrNum = 0;
			
			esp8266SendState = ESP8266_WAIT_RESP;
			break;
		case ESP8266_WAIT_RESP:
			if(IsTimeExpired(esp8266SendTimer + (cmdinfo->timerout)))
			{
				xReturn = 2;

				if(cmdinfo->resp != NULL)
				{
					if(strstr(esp8266RespBuf,cmdinfo->resp) != NULL)
					{
						xReturn = 0;
					}
				}
				
				esp8266SendState = ESP8266_SEND_CMD;
			}
			else
			{
				if(Esp8266_GetChar(&data) != 0)
				{
					Esp8266_IpdPro(data);
					
					if(recvdata != NULL)
					{
						if(esp8266RespRecvNum < len)
							recvdata[esp8266RespRecvNum] = data;
						esp8266RespRecvNum++;
					}

					if(esp8266RespBufOff < ESP8266_RXBUF_SIZE)
					{
						esp8266RespBuf[esp8266RespBufOff] = data;
					}
					esp8266RespBufOff++;

					if(cmdinfo->resp != NULL)
					{
						if(data == cmdinfo->resp[esp8266RespStrNum])
						{
							esp8266RespStrNum++;
						}
						else
						{
							if(esp8266RespStrNum != 0)
							{
								esp8266RespStrNum = 0;
							}
						}
						
						if(esp8266RespStrNum >= esp8266RespStrlen)
						{
							xReturn = 0;
							esp8266SendState = ESP8266_SEND_CMD;
							break;
						}

						if(data == esp8266ErrResp[esp8266RespErrStrNum])
							esp8266RespErrStrNum++;
						else if(esp8266RespErrStrNum != 0)
							esp8266RespErrStrNum = 0;
						if(esp8266RespErrStrNum >= 5)
						{
							xReturn = 3;
							esp8266SendState = ESP8266_SEND_CMD;
							break;
						}

						if(data == esp8266ErrResp2[esp8266RespErr2StrNum])
							esp8266RespErr2StrNum++;
						else if(esp8266RespErr2StrNum != 0)
							esp8266RespErr2StrNum = 0;
						if(esp8266RespErr2StrNum >= 4)
						{
							xReturn = 3;
							esp8266SendState = ESP8266_SEND_CMD;
							break;
						}
					}
				}
				else
				{
					
				}
			}	
			break;
	}

	return xReturn;
}

/**
  * @brief  Wifi 读取缓冲区所有数据
  * @param  buffer and character
  * @retval 收到的报文字节个数
  */
uint32_t Esp8266_RecvRxBuf(char * recvdata, uint32_t len)
{
	uint32_t i = 0;
	
	for(i=0;i<len;i++)
	{
		
		if(BSP_USART_RxBufOut(&uartRxBuf[WIFI_UART],(uint8_t *)recvdata) == 0)
		{
			break;
		}
		recvdata++;
	}

	return i;

}



