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

//�Ƿ�����ģ���������Ϲ���wifi�ȵ���г�APģʽ
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
	uint32_t postNext;		//����ָʾ�Ƿ�post���ֳ���2��IPD����
	uint32_t bootConnToAp;	//�ϵ���flash��ȡ������ֱ�������ⲿ�ȵ�
	uint32_t connToAp;		//0:�ȴ�����AP;1:�ѻ��ssid�����룬��������Ap;2:����APʧ��; 3:����AP�ɹ�
	uint32_t recvRequest;		//Զ������������������  0:δ�����κ�����; 1:GetIp; 2:APState;
	uint32_t recvGetIp;		//Զ��������������getip����
	uint32_t modbusData;	//�յ�����λ�����͵�Modbus����
	uint32_t checkApStateTimer;		//��ѯ�����ȵ�״̬�Ķ�ʱ��
	uint32_t apState;				//���ӹ����ȵ�ap��״̬
	uint32_t remoteSocketId;		//�빫��ͨ��ʹ�õ�socket ID
	uint32_t ipdPktSocketId;		//���յ�IPD����ʱʹ�õ�socket ID
	char ipdIp[32];					//���յ�����ʱ�յ���IP��ַ
	WifiServerSend send;
	char tmpBuf[256];
}WifiServer;

void WifiServer_Task( void );
void WifiServer_TaskStart(void);

#endif
/*---------------------------end of file------------------------------*/

