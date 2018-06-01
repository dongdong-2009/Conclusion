#ifndef __WIFI_SERVER_H
#define __WIFI_SERVER_H

#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include <stm32f10x.h>
#include "bsp_hwConfig.h"
#include "bsp_systimer.h"
#include "bsp_usart.h"
#include "param.h"
#include "esp8266.h"
#include "encode.h"
#include "modbus_tcp.h"
#include "modbus_app.h"
#include "uart_wifi.h"

//是否允许模块在连接上公网wifi热点后，切除AP模式
#undef WIFI_CH_WKMODE				

#define WIFI_SEND_BUF_LEN			COMM_BUF_SIZE

#define WIFISERVER_CFG_WIFI			0
#define WIFISERVER_GETVER			1
#define WIFISERVER_STARTSERVER		2
#define WIFISERVER_LISTEN			3
#define WIFISERVER_RECV				4
#define WIFISERVER_STARTSERVER_PRE	5
#define WIFISERVER_SEND				6
#define WIFISERVER_CONNTOAP			7
#define WIFISERVER_GETAPIP			8
#define WIFISERVER_CHGMODE			10
#define WIFISERVER_CONNTOAP_IN		11
#define WIFISERVER_CHKAP			12

typedef struct _WifiServerSend
{
	uint32_t socket;
	uint32_t len;
	char dataBuf[WIFI_SEND_BUF_LEN];
}WifiServerSend;

typedef struct _WifiServer
{
	uint32_t state;
	uint32_t failCnt;
	uint32_t timer;
	uint32_t sendFail;
	uint32_t sendIpStateCnt;
	uint32_t postNext;		//用于指示是否post被分成了2封IPD报文
	uint32_t bootConnToAp;	//上电后从flash读取参数，直接连接外部热点
	uint32_t connToAp;		//0:等待连接AP;1:已获得ssid和密码，可以连接Ap;2:连接AP失败; 3:连接AP成功
	uint32_t recvRequest;		//远方服务器发送了请求  0:未发送任何请求; 1:GetIp; 2:APState;
	uint32_t recvGetIp;		//远方服务器发送了getip请求
	uint32_t modbusData;	//收到了上位机发送的Modbus报文
	uint32_t checkApStateTimer;		//查询公网热点状态的定时器
	uint32_t apState;				//连接公网热点ap的状态
	uint32_t remoteSocketId;		//与公网通信使用的socket ID
	uint32_t ipdPktSocketId;		//接收到IPD报文时使用的socket ID
	char ipdIp[32];					//接收到报文时收到的IP地址
	WifiServerSend send;
	char tmpBuf[256];
}WifiServer;

void WifiServer_Task( void );
void WifiServer_TaskStart(void);

#endif
/*---------------------------end of file------------------------------*/

