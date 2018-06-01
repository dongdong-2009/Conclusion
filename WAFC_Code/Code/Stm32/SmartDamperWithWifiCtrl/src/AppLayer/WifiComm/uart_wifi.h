#ifndef __UART_WIFI_H
#define __UART_WIFI_H

#include <stm32f10x.h>

#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "bsp_hwConfig.h"
#include "bsp_systimer.h"
#include "bsp_usart.h"
#include "esp8266.h"
#include "encode.h"

#define ESP8266_STATION		1
#define ESP8266_AP			2
#define ESP8266_AP_STA		3

#define WIFI_RET_OK					0x00
#define WIFI_RET_IN					0x01
#define WIFI_RET_FAIL_RESET			0x02
#define WIFI_RET_FAIL_SET_WMODE		0x03
#define WIFI_RET_FAIL_ATE			0x04
#define WIFI_RET_FAIL_GETVER		0x05
#define WIFI_RET_FAIL_SET_IPMUX		0x06
#define WIFI_RET_FAIL_IPCLOSE		0x07
#define WIFI_RET_FAIL_SET_IPMODE	0x08
#define WIFI_RET_FAIL_IPSERVER		0x09
#define WIFI_RET_FAIL_CWSAP			0x0A
#define WIFI_RET_FAIL_CIPAP			0x0B
#define WIFI_RET_FAIL_CIPDINFO		0x0C
#define WIFI_RET_FAIL_CIPSTATUS		0x0D
#define WIFI_RET_FAIL_CIPSEND		0x0E
#define WIFI_RET_FAIL_CIPSTO		0x0F
#define WIFI_RET_FAIL_CWJAP			16

#define WIFI_BUF_SIZE	COMM_BUF_SIZE

//for cfg state
#define WIFI_CFG_RST				0
#define WIFI_CFG_RST_WAIT			1
#define WIFI_CFG_ATE0				2

//for client_state
#define WIFI_CLIENT_SET_MODE	0
#define WIFI_CLIENT_CWJAP		1
#define WIFI_CLIENT_IPMUX		2
#define WIFI_CLIENT_CONNECT		3
#define WIFI_CLIENT_IPMODE		4
#define WIFI_CLIENT_RST			5
#define WIFI_CLIENT_RST_WAIT	6
#define WIFI_CLIENT_IPDINFO		7
#define WIFI_CLIENT_IFSR		8
#define WIFI_CLIENT_STO			9

//for send_state
#define WIFI_SEND_IPSEND		0
#define WIFI_SEND_IPSEND_WAIT	1
#define WIFI_SEND_DATA			2
#define WIFI_SEND_DATA_RESP		3


//server_state
#define WIFI_START_STATION				0
#define WIFI_START_SERVER_IP			1
#define WIFI_START_SERVER_SSID			2
#define	WIFI_START_SERVER_IPMOD			3
#define	WIFI_START_SERVER_IPMUX			4
#define WIFI_START_SERVER_IPD			5
#define WIFI_START_SERVER_TCPSERVER		6
#define WIFI_START_SERVER_TCPTIMER		7
#define WIFI_START_CWJAP				8
#define WIFI_START_IFSR					9

#define WIFI_CONNTOAP_CJWAP				0
#define WIFI_CONNTOAP_GETIP				1
#define WIFI_CONNTOAP_TCPSERVER			2
#define WIFI_CONNTOAP_GETSOCKET			3

typedef struct _WifiSocket
{
	uint32_t protocal;
	char *hostip;
	uint32_t localport;
	uint32_t hostport;
	uint32_t socket;
}WifiSocket;

typedef struct _WifiCfg
{
	uint32_t wifi_mode;
	uint8_t localApIpAddr[4];
	uint8_t localApGateway[4];
	uint8_t localApNetmask[4];
	uint32_t localStationIpAddr;
	uint32_t localStationGateway;
	uint32_t localStationNetmask;
	
	uint32_t localPort;

	uint8_t localSsid[16];
	uint8_t localPswd[16];
	char remoteSsid[16];
	char remotePswd[16];
	uint32_t ecn;				//wifi模块加密方式
	uint32_t tcptimer;

	uint32_t localStationSocketId;		//作为站点连接到公网时使用的socket
}WifiCfg;

typedef struct _WifiLinkstatus
{
	uint32_t status;
	uint32_t link_id;
	uint32_t protocal_type;
	uint32_t remoteip;
	uint32_t remoteport;
	uint32_t localport;
	uint32_t client_server;
}WifiLinkstatus;

typedef struct _WifiProStr
{	
	char wifiTmpBuf[WIFI_BUF_SIZE];
	uint32_t timer;
	uint32_t cfg_state;
	uint32_t client_state;
	uint32_t send_state;
	uint32_t server_state;
	uint32_t conntoap_state;
}WifiProStr;


void Wifi_Init( void);
uint32_t Wifi_CfgModule(void);
uint32_t Wifi_GetVer(uint8_t *version,uint32_t len);
uint32_t Wifi_CheckIpstatus(uint32_t *linkID, uint32_t *linkstatus);
uint32_t Wifi_CfgLocalTcpServer(WifiCfg *cfg);
uint32_t Wifi_ConntoAp(WifiCfg *wifcfg);
uint32_t Wifi_Send(uint32_t socketID,unsigned char *data,uint32_t len);
uint32_t Wifi_IpdRecv(void);
uint32_t Wifi_GetIpdRecvState(void);
uint32_t Wifi_SetMode(uint32_t mode);
#endif

