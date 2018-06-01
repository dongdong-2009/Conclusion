#ifndef ESP8266_H
#define ESP8266_H

#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include <stm32f10x.h>
#include "bsp_hwConfig.h"
#include "bsp_usart.h"
#include "bsp_systimer.h"
#include "encode.h"

//for ipd_state
#define IPD_H1		0
#define IPD_H2		1
#define IPD_H3		2
#define IPD_LEN		3
#define IPD_LEN_IN	4
#define IPD_ID		5
#define IPD_ID_IN	6
#define IPD_GETPKT	7
#define IPD_REMOTEIP	8
#define IPD_REMOTEID	9

#define ESP8266_IPD_DATA_LEN		COMM_BUF_SIZE
#define ESP8266_RXBUF_SIZE			COMM_BUF_SIZE

#define ESP8266_SEND_CMD		0
#define ESP8266_WAIT_RESP		1

typedef struct _ESPATcmdStr
{
	char *cmd;
	char *resp;
	uint32_t cmd_len;
	uint32_t timerout;
}EspATcmdStr;


//用于存储收到的IPD报文
typedef struct _WifiRecvStr
{
	uint32_t socket;
	uint32_t len;
	uint32_t ip;
	uint8_t data[ESP8266_IPD_DATA_LEN];
}WifiRecvStr;

#define WIFI_RECVDATABUF_LEN					4
typedef struct _WifiRecvBuf
{
	unsigned int  front;          //对列头指针,输出元素
	unsigned int  rear;			  //队列尾指针，输入元素
	WifiRecvStr buffer[WIFI_RECVDATABUF_LEN];
}WifiRecvBuf;

extern WifiRecvBuf ipdDatatBuf;

uint32_t Esp8266_Init(uint32_t ulWantedBaud);
uint32_t Esp8266_GetChar( uint8_t *pcRxedChar);
uint32_t Esp8266_SendCmd(char * cmd,uint32_t len);
void Esp8266_IpdPro(uint8_t readbyte);
uint32_t Esp8266_IpdProState(void);
uint32_t Esp8266_CheckWithCmd(EspATcmdStr *,char *,uint32_t);
uint32_t Esp8266_RecvRxBuf(char * recvdata, uint32_t len);

void Esp8266_IPDBufInit (WifiRecvBuf *buf);
unsigned int Esp8266_IPDBufIn (WifiRecvBuf *buf, WifiRecvStr *c) ;
unsigned int Esp8266_IPDBufOut (WifiRecvBuf *buf, WifiRecvStr *c) ;
unsigned int  Esp8266_IPDBufSize (WifiRecvBuf *buf) ;

#endif
/*----------------------end of file------------------------*/

