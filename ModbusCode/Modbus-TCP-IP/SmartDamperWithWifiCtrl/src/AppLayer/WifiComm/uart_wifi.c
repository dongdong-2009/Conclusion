/* Standard includes. */
#include <stm32f10x.h>

#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "bsp_hwConfig.h"
#include "bsp_systimer.h"
#include "bsp_usart.h"
#include "esp8266.h"
#include "encode.h"
#include "uart_wifi.h"

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
WifiProStr wifiPro;


/**
  * @brief  init wifi module 
  * @param  buffer and character
  * @retval None
  */
void Wifi_Init( void)
{
	wifiPro.send_state = WIFI_SEND_IPSEND;
	wifiPro.cfg_state = WIFI_CFG_RST;
	wifiPro.client_state = WIFI_CLIENT_SET_MODE;
	wifiPro.server_state = WIFI_START_STATION;
	wifiPro.conntoap_state = WIFI_CONNTOAP_CJWAP;

	Esp8266_Init( 115200 );
}

/**
  * @brief  复位模块
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_Rst(void)
{
	uint32_t atCmdRet;
	EspATcmdStr atCmdInfo;

	atCmdInfo.cmd = "AT+RST\r\n";	
	atCmdInfo.resp = "OK";
	atCmdInfo.cmd_len = strlen(atCmdInfo.cmd);
	atCmdInfo.timerout = 100;

	atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,NULL,0);
	if(atCmdRet == WIFI_RET_OK)
	{
		return WIFI_RET_OK;
	}		
	else if(atCmdRet > WIFI_RET_IN)
		return WIFI_RET_FAIL_RESET;
	
	return WIFI_RET_IN;
}

/**
  * @brief  回显状态设置
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_ATE0(uint32_t mode)
{
	uint32_t atCmdRet;
	EspATcmdStr atCmdInfo;

	if(mode == 0)
		atCmdInfo.cmd = "ATE0\r\n";	
	else
		atCmdInfo.cmd = "ATE1\r\n";	
	
	atCmdInfo.resp = "OK";
	atCmdInfo.timerout = 100;
	atCmdInfo.cmd_len = strlen(atCmdInfo.cmd);

	atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,NULL,0);
	if(atCmdRet == WIFI_RET_OK)
	{
		return WIFI_RET_OK;
	}		
	else if(atCmdRet > WIFI_RET_IN)
		return WIFI_RET_FAIL_ATE;
	
	return WIFI_RET_IN;
}

/**
  * @brief  获取版本号
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_GetVer(uint8_t *version,uint32_t len)
{
	uint32_t atCmdRet;
	EspATcmdStr atCmdInfo;

	atCmdInfo.cmd = "AT+GMR\r\n";	
	atCmdInfo.resp = "OK";
	atCmdInfo.timerout = 100;
	atCmdInfo.cmd_len = strlen(atCmdInfo.cmd);

	atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,wifiPro.wifiTmpBuf,128);
	if(atCmdRet > WIFI_RET_IN)
	{
		return WIFI_RET_FAIL_GETVER;
	}		
	else if(atCmdRet == WIFI_RET_OK)
	{
		if(version != NULL)
		{
			len = ((len > strlen(wifiPro.wifiTmpBuf)) ? len : strlen(wifiPro.wifiTmpBuf));
			memcpy((char *)version,wifiPro.wifiTmpBuf,len);	
		}
		return WIFI_RET_OK;
	}

	return WIFI_RET_IN;
}

/**
  * @brief  设置Wifi的工作模式
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_SetMode(uint32_t mode)
{
	uint32_t atCmdRet;
	EspATcmdStr atCmdInfo;

	switch(mode)
	{
		case ESP8266_STATION:
			atCmdInfo.cmd = "AT+CWMODE_CUR=1\r\n";
			break;
		case ESP8266_AP:
			atCmdInfo.cmd = "AT+CWMODE_CUR=2\r\n";
			break;
		default:
			atCmdInfo.cmd = "AT+CWMODE_CUR=3\r\n";
			break;
			
	}
	atCmdInfo.resp = "OK";
	atCmdInfo.timerout = 100;
	atCmdInfo.cmd_len = strlen(atCmdInfo.cmd);

	atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,NULL,0);
	
	if(atCmdRet == WIFI_RET_OK)
	{
		return WIFI_RET_OK;
	}		
	else if(atCmdRet > WIFI_RET_IN)
		return WIFI_RET_FAIL_SET_WMODE;
	
	return WIFI_RET_IN;
}

/**
  * @brief  设置IP的单、多连接
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_SetIPMux(uint32_t mode)
{
	uint32_t atCmdRet;
	EspATcmdStr atCmdInfo;

	if(mode == 0)
		atCmdInfo.cmd = "AT+CIPMUX=0\r\n";
	else
		atCmdInfo.cmd = "AT+CIPMUX=1\r\n";
	
	atCmdInfo.resp = "OK";
	atCmdInfo.timerout = 100;
	atCmdInfo.cmd_len = strlen(atCmdInfo.cmd);

	atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,NULL,0);
	
	if(atCmdRet == WIFI_RET_OK)
	{
		return WIFI_RET_OK;
	}		
	else if(atCmdRet > WIFI_RET_IN)
		return WIFI_RET_FAIL_SET_IPMUX;
	
	return WIFI_RET_IN;
}

/**
  * @brief  查询设备的IP地址
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_GetIPAddr(uint32_t *local_ip)
{
	char *pos = NULL;
	char *p = NULL;
	uint32_t atCmdRet;
	EspATcmdStr atCmdInfo;

	atCmdInfo.cmd = "AT+CIFSR\r\n";
	atCmdInfo.resp = "OK";
	atCmdInfo.timerout = 100;
	atCmdInfo.cmd_len = strlen(atCmdInfo.cmd);

	atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,wifiPro.wifiTmpBuf,256);

	if(atCmdRet == WIFI_RET_OK)
	{
		if(local_ip != NULL)
		{
			pos = strstr(wifiPro.wifiTmpBuf,"STAIP");
			if(pos != NULL)
			{
				strtok(pos,",");
				
				p = strtok(NULL,",");
				p++;
				
				*local_ip = inet_addr_ty(p);
			}
		}
		return WIFI_RET_OK;
	}		
	else if(atCmdRet > WIFI_RET_IN)
		return WIFI_RET_FAIL_SET_IPMODE;
	
	return WIFI_RET_IN;
}

/**
  * @brief  设置IP的透传模式
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_SetIPMode(uint32_t mode)
{
	uint32_t atCmdRet;
	EspATcmdStr atCmdInfo;

	if(mode == 0)
		atCmdInfo.cmd = "AT+CIPMODE=0\r\n";
	else
		atCmdInfo.cmd = "AT+CIPMODE=1\r\n";
	
	atCmdInfo.resp = "OK";
	atCmdInfo.timerout = 100;
	atCmdInfo.cmd_len = strlen(atCmdInfo.cmd);

	atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,NULL,0);

	if(atCmdRet == WIFI_RET_OK)
	{
		return WIFI_RET_OK;
	}		
	else if(atCmdRet > WIFI_RET_IN)
		return WIFI_RET_FAIL_SET_IPMODE;
	
	return WIFI_RET_IN;
}

/**
  * @brief  建立服务器
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_SetIpServer(uint32_t mode,uint32_t port)
{
	uint32_t atCmdRet;
	EspATcmdStr atCmdInfo;

	if(mode == 0)
		atCmdInfo.cmd = "AT+CIPSERVER=0\r\n";
	else
	{
		sprintf(wifiPro.wifiTmpBuf,"AT+CIPSERVER=1,%d\r\n",port);
		atCmdInfo.cmd = wifiPro.wifiTmpBuf;
	}
	
	atCmdInfo.resp = "OK";
	atCmdInfo.timerout = 100;
	atCmdInfo.cmd_len = strlen(atCmdInfo.cmd);

	atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,NULL,0);
	if(atCmdRet == WIFI_RET_OK)
	{
		return WIFI_RET_OK;
	}		
	else if(atCmdRet > WIFI_RET_IN)
		return WIFI_RET_FAIL_IPSERVER;
	
	return WIFI_RET_IN;
}

/**
  * @brief  建立AP的SSID
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_SetSSID(char *ssid,char *pwd,uint32_t mode)
{
	uint32_t atCmdRet;
	EspATcmdStr atCmdInfo;

	sprintf(wifiPro.wifiTmpBuf,"AT+CWSAP_CUR=\"%s\",\"%s\",6,%d\r\n",ssid,pwd,mode);
	atCmdInfo.cmd = wifiPro.wifiTmpBuf;
	atCmdInfo.resp = "OK";
	atCmdInfo.timerout = 100;
	atCmdInfo.cmd_len = strlen(atCmdInfo.cmd);

	atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,NULL,0);
	if(atCmdRet == WIFI_RET_OK)
	{
		return WIFI_RET_OK;
	}		
	else if(atCmdRet > WIFI_RET_IN)
		return WIFI_RET_FAIL_CWSAP;
	
	return WIFI_RET_IN;
}

/**
  * @brief  设置Ap路由器的SSID和密码
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_Set_Cwjap(char *ssid,char *pwd)
{
	uint32_t atCmdRet;
	EspATcmdStr atCmdInfo;

	sprintf(wifiPro.wifiTmpBuf,"AT+CWJAP_CUR=\"%s\",\"%s\"\r\n",ssid,pwd);
	atCmdInfo.cmd = wifiPro.wifiTmpBuf;
	atCmdInfo.resp = "OK";
	atCmdInfo.timerout = 1500;
	atCmdInfo.cmd_len = strlen(atCmdInfo.cmd);

	atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,NULL,0);
	if(atCmdRet == WIFI_RET_OK)
	{
		return WIFI_RET_OK;
	}		
	else if(atCmdRet > WIFI_RET_IN)
		return WIFI_RET_FAIL_CWJAP;
	
	return WIFI_RET_IN;
}

/**
  * @brief  设置模块AP热点的IP地址
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_SetApIP(char *ipAddr,char *gateway,char * netmask)
{
	uint32_t atCmdRet;
	EspATcmdStr atCmdInfo;
	
	sprintf(wifiPro.wifiTmpBuf,"AT+CIPAP_CUR=\"%d.%d.%d.%d\",\"%d.%d.%d.%d\",\"%d.%d.%d.%d\"\r\n",
			ipAddr[0],ipAddr[1],ipAddr[2],ipAddr[3],
			gateway[0],gateway[1],gateway[2],gateway[3],
			netmask[0],netmask[1],netmask[2],netmask[3]);
	
	atCmdInfo.cmd = wifiPro.wifiTmpBuf;
	atCmdInfo.resp = "OK";
	atCmdInfo.timerout = 100;
	atCmdInfo.cmd_len = strlen(atCmdInfo.cmd);

	atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,NULL,0);
	if(atCmdRet == WIFI_RET_OK)
	{
		return WIFI_RET_OK;
	}		
	else if(atCmdRet > WIFI_RET_IN)
		return WIFI_RET_FAIL_CIPAP;
	
	return WIFI_RET_IN;
}

/**
  * @brief  设置ip数据提示类型
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_SetIpDinfo(uint32_t mode)
{
	uint32_t atCmdRet;
	EspATcmdStr atCmdInfo;

	if(mode == 0)
		atCmdInfo.cmd = "AT+CIPDINFO=0\r\n";
	else
	{
		atCmdInfo.cmd = "AT+CIPDINFO=1\r\n";
	}
	
	atCmdInfo.resp = "OK";
	atCmdInfo.timerout = 100;
	atCmdInfo.cmd_len = strlen(atCmdInfo.cmd);

	atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,NULL,0);
	if(atCmdRet == WIFI_RET_OK)
	{
		return WIFI_RET_OK;
	}		
	else if(atCmdRet > WIFI_RET_IN)
		return WIFI_RET_FAIL_CIPDINFO;
	
	return WIFI_RET_IN;
}

/**
  * @brief  设置tcp超时时间
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_SetIpSto(uint32_t sec)
{
	uint32_t atCmdRet;
	EspATcmdStr atCmdInfo;

	sprintf(wifiPro.wifiTmpBuf,"AT+CIPSTO=%d\r\n",sec);
	
	atCmdInfo.cmd = wifiPro.wifiTmpBuf;
	atCmdInfo.resp = "OK";
	atCmdInfo.timerout = 500;
	atCmdInfo.cmd_len = strlen(atCmdInfo.cmd);

	atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,NULL,0);
	if(atCmdRet == WIFI_RET_OK)
	{
		return WIFI_RET_OK;
	}		
	else if(atCmdRet > WIFI_RET_IN)
		return WIFI_RET_FAIL_CIPSTO;
	
	return WIFI_RET_IN;
}

/**
  * @brief  Wifi模块基本配置
  * @param  buffer and character
  * @retval 0:ok;1:in;>2:fail
  */
uint32_t Wifi_CfgModule(void)
{
	uint32_t atCmdRet;

	switch(wifiPro.cfg_state)
	{
		case WIFI_CFG_RST:
			atCmdRet = Wifi_Rst();
			if(atCmdRet == WIFI_RET_OK)
			{
				wifiPro.timer = Get_Gtime();
				wifiPro.cfg_state = WIFI_CFG_RST_WAIT;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				return atCmdRet;
			}
			break;
		case WIFI_CFG_RST_WAIT:
			if(IsTimeExpired(wifiPro.timer + 300))
			{
				wifiPro.cfg_state = WIFI_CFG_ATE0;
			}
			break;
		case WIFI_CFG_ATE0:
			atCmdRet = Wifi_ATE0(0);
			if(atCmdRet == WIFI_RET_OK)
			{
				wifiPro.cfg_state = WIFI_CFG_RST;
				return WIFI_RET_OK;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				return atCmdRet;
			}
			break;
	}

	return WIFI_RET_IN;
}

/**
  * @brief  关闭IP连接
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_CloseIp(uint32_t socketId)
{

	return WIFI_RET_OK;
}

/**
  * @brief  查询网络连接状态
  * @param  *linkstatus:0xFF,未收到响应
  * @retval 0:ok;1:WIFI_RET_IN;
  */
uint32_t Wifi_CheckIpstatus(uint32_t *linkID, uint32_t *linkstatus)
{
	uint32_t atCmdRet;
	EspATcmdStr atCmdInfo;
	char *pos = NULL;
//	char *p = NULL;
	
	atCmdInfo.cmd = "AT+CIPSTATUS\r\n";
	atCmdInfo.resp = "OK";
	atCmdInfo.timerout = 50;
	atCmdInfo.cmd_len = strlen(atCmdInfo.cmd);

	atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,wifiPro.wifiTmpBuf,WIFI_BUF_SIZE);
	if(atCmdRet > 1)
	{
		return WIFI_RET_FAIL_CIPSTATUS;
	}		
	else if(atCmdRet == 0)
	{
		pos = strstr(wifiPro.wifiTmpBuf,"STATUS");
		if(pos != NULL)
		{
			*linkstatus = (pos[7]-0x30);
		}
		else
			*linkstatus = 0xFF;
		
		return WIFI_RET_OK;
	}
	
	return WIFI_RET_IN;
}

/**
  * @brief  连接远方的TCP服务器
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_ConnToTcpServer(char *hostip,uint32_t port)
{
	uint32_t atCmdRet;
	EspATcmdStr atCmdInfo;
	
	sprintf(wifiPro.wifiTmpBuf,"AT+CIPSTART=\"TCP\",\"%s\",%d\r\n",hostip,port);
	
	atCmdInfo.cmd = wifiPro.wifiTmpBuf;
	atCmdInfo.resp = "OK";
	atCmdInfo.timerout = 200;
	atCmdInfo.cmd_len = strlen(atCmdInfo.cmd);

	atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,NULL,0);
	if(atCmdRet == WIFI_RET_OK)
	{
		return WIFI_RET_OK;
	}		
	else if(atCmdRet > WIFI_RET_IN)
		return WIFI_RET_FAIL_CIPAP;
	
	return WIFI_RET_IN;	
}


/**
  * @brief  建立本地服务器
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_CfgLocalTcpServer(WifiCfg *cfg)
{
	uint32_t atCmdRet;
	
	switch(wifiPro.server_state)
	{

		case WIFI_START_STATION:
			atCmdRet = Wifi_SetMode(cfg->wifi_mode);
			if(atCmdRet == WIFI_RET_OK)
			{
				if(cfg->wifi_mode != ESP8266_STATION)
					wifiPro.server_state = WIFI_START_SERVER_IP;
				else
					wifiPro.server_state = WIFI_START_SERVER_IPMOD;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				wifiPro.server_state = WIFI_START_STATION;
				return atCmdRet;
			}
			break;
		case WIFI_START_SERVER_IP:
			atCmdRet = Wifi_SetApIP((char *)cfg->localApIpAddr,(char *)cfg->localApGateway,(char *)cfg->localApNetmask);
			if(atCmdRet == WIFI_RET_OK)
			{
				wifiPro.server_state = WIFI_START_SERVER_SSID;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				wifiPro.server_state = WIFI_START_STATION;
				return atCmdRet;
			}
			break;
		case WIFI_START_SERVER_SSID:
			atCmdRet = Wifi_SetSSID((char *)cfg->localSsid,(char *)cfg->localPswd,cfg->ecn);
			if(atCmdRet == WIFI_RET_OK)
			{
				wifiPro.server_state = WIFI_START_SERVER_IPMOD;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				wifiPro.server_state = WIFI_START_STATION;
				return atCmdRet;
			}
			break;
		case WIFI_START_SERVER_IPMOD:
			//设置普通传输模式
			atCmdRet = Wifi_SetIPMode(0);
			if(atCmdRet == WIFI_RET_OK)
			{
				wifiPro.server_state = WIFI_START_SERVER_IPMUX;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				wifiPro.server_state = WIFI_START_STATION;
				return atCmdRet;
			}
			break;
		case WIFI_START_SERVER_IPMUX:
			//设置多链接模式
			atCmdRet = Wifi_SetIPMux(1);
			if(atCmdRet == WIFI_RET_OK)
			{
				wifiPro.server_state = WIFI_START_SERVER_IPD;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				wifiPro.server_state = WIFI_START_STATION;
				return atCmdRet;
			}
			break;
		case WIFI_START_SERVER_IPD:
			//设置多链接模式
			atCmdRet = Wifi_SetIpDinfo(1);
			if(atCmdRet == WIFI_RET_OK)
			{
				//wifiPro.server_state = WIFI_START_CWJAP;
				if(cfg->wifi_mode != ESP8266_STATION)
					wifiPro.server_state = WIFI_START_SERVER_TCPSERVER;
				else
					wifiPro.server_state = WIFI_START_CWJAP;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				wifiPro.server_state = WIFI_START_STATION;
				return atCmdRet;
			}
			break;
		case WIFI_START_CWJAP:
			atCmdRet = Wifi_Set_Cwjap((char *)cfg->remoteSsid,(char *)cfg->remotePswd);
			if(atCmdRet == WIFI_RET_OK)
			{
				wifiPro.server_state = WIFI_START_SERVER_TCPSERVER;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				wifiPro.server_state = WIFI_START_STATION;
				return atCmdRet;
			}
			break;	
		case WIFI_START_SERVER_TCPSERVER:
			//建立tcp服务器
			atCmdRet = Wifi_SetIpServer(1,cfg->localPort);
			if(atCmdRet == WIFI_RET_OK)
			{
				//wifiPro.server_state = WIFI_START_IFSR;
				if(cfg->wifi_mode != ESP8266_STATION)
				{
					wifiPro.server_state = WIFI_START_STATION;
					return WIFI_RET_OK;
				}
				else
					wifiPro.server_state = WIFI_START_IFSR;
				
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				wifiPro.server_state = WIFI_START_STATION;
				return atCmdRet;
			}
			break;
		case WIFI_START_SERVER_TCPTIMER:
			//建立tcp服务器
			atCmdRet = Wifi_SetIpSto(cfg->tcptimer);
			if(atCmdRet == WIFI_RET_OK)
			{
				wifiPro.server_state = WIFI_START_SERVER_IP;
				return WIFI_RET_OK;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				wifiPro.server_state = WIFI_START_STATION;
				return atCmdRet;
			}
			break;
		case WIFI_START_IFSR:
			atCmdRet = Wifi_GetIPAddr(&(cfg->localStationIpAddr));
			if(atCmdRet == WIFI_RET_OK)
			{
				wifiPro.server_state = WIFI_START_STATION;
				return WIFI_RET_OK;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				wifiPro.server_state = WIFI_START_STATION;
				return atCmdRet;
			}
			break;
	}
	
	return WIFI_RET_IN;
}

/**
  * @brief  连接到路由器，并获取ip地址
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_ConntoAp(WifiCfg *wifcfg)
{
	uint32_t atCmdRet;
	switch(wifiPro.conntoap_state)
	{
		case WIFI_CONNTOAP_CJWAP:
			atCmdRet = Wifi_Set_Cwjap(wifcfg->remoteSsid,wifcfg->remotePswd);
			if(atCmdRet == WIFI_RET_OK)
			{
				wifiPro.conntoap_state = WIFI_CONNTOAP_TCPSERVER;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				return atCmdRet;
			}
			break;	
		case WIFI_CONNTOAP_TCPSERVER:
			//建立tcp服务器
			atCmdRet = Wifi_SetIpServer(1,502);
			if(atCmdRet == WIFI_RET_OK)
			{
				wifiPro.conntoap_state = WIFI_CONNTOAP_GETIP;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				wifiPro.conntoap_state = WIFI_CONNTOAP_CJWAP;
				return atCmdRet;
			}
			break;
		case WIFI_CONNTOAP_GETIP:
			atCmdRet = Wifi_GetIPAddr(&(wifcfg->localStationIpAddr));
			if(atCmdRet == WIFI_RET_OK)
			{
				wifiPro.conntoap_state = WIFI_CONNTOAP_CJWAP;
				return WIFI_RET_OK;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				wifiPro.conntoap_state = WIFI_CONNTOAP_CJWAP;
				return atCmdRet;
			}
			break;	
		case WIFI_CONNTOAP_GETSOCKET:
			atCmdRet = Wifi_CheckIpstatus(&(wifcfg->localStationSocketId), NULL);
			if(atCmdRet == WIFI_RET_OK)
			{
				wifiPro.conntoap_state = WIFI_CONNTOAP_CJWAP;
				return WIFI_RET_OK;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				wifiPro.conntoap_state = WIFI_CONNTOAP_CJWAP;
				return atCmdRet;
			}
			break;
	}
	return WIFI_RET_IN;
}

/**
  * @brief  发送数据
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_Send(uint32_t socketID,unsigned char *data,uint32_t len)
{
	uint32_t atCmdRet;
	EspATcmdStr atCmdInfo;

	switch(wifiPro.send_state)
	{
		case WIFI_SEND_IPSEND:
			//memset(wifiPro.wifiTmpBuf,0,WIFI_BUF_SIZE);
			sprintf((char *)wifiPro.wifiTmpBuf,"AT+CIPSEND=%d,%d\r\n",socketID,(len));
			wifiPro.send_state = WIFI_SEND_IPSEND_WAIT;
			break;
		case WIFI_SEND_IPSEND_WAIT:	
			atCmdInfo.cmd = wifiPro.wifiTmpBuf;
			atCmdInfo.resp = ">";
			atCmdInfo.timerout = 50;
			atCmdInfo.cmd_len = strlen(atCmdInfo.cmd);
			
			atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,NULL,0);
				
			if(atCmdRet == WIFI_RET_OK)
			{
				wifiPro.send_state = WIFI_SEND_DATA;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				wifiPro.send_state = WIFI_SEND_IPSEND;
				return WIFI_RET_FAIL_CIPSEND;
			}
			break;
		case WIFI_SEND_DATA:				
			memcpy((char *)wifiPro.wifiTmpBuf,data,len);
			wifiPro.send_state = WIFI_SEND_DATA_RESP;
			break;
		case WIFI_SEND_DATA_RESP:
			atCmdInfo.cmd = wifiPro.wifiTmpBuf;
			atCmdInfo.resp = "OK";
			atCmdInfo.timerout = 50;
			atCmdInfo.cmd_len = len;

			atCmdRet = Esp8266_CheckWithCmd(&atCmdInfo,NULL,0);
			
			if(atCmdRet == WIFI_RET_OK)
			{
				wifiPro.send_state = WIFI_SEND_IPSEND;
				return WIFI_RET_OK;
			}	
			else if(atCmdRet > WIFI_RET_IN)
			{
				wifiPro.send_state = WIFI_SEND_IPSEND;
				return WIFI_RET_FAIL_CIPSEND;
			}
			break;
	}

	return WIFI_RET_IN;
}

/**
  * @brief  接受数据
  * @param  size:接收的数据长度
  * @retval 0:ok;1:recv in
  */
uint32_t Wifi_IpdRecv(void)
{
	uint32_t ret = WIFI_RET_IN;
	uint8_t readbyte;
	
	while(1)
	{
		if(Esp8266_GetChar(&readbyte) == 0)
		{
			break;
		}
		else
		{
			Esp8266_IpdPro(readbyte);
		}
	}
	
	return ret;
}

/**
  * @brief  获取接受数据的状态
  * @param  buffer and character
  * @retval 0:ok;1:fail
  */
uint32_t Wifi_GetIpdRecvState(void)
{
	return (Esp8266_IpdProState());
}
/*-----------------------end of file ----------------------*/

