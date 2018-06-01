/* Standard includes. */
#include "wifi_server.h"

#define DEFAULT_SSID "SD_0002"
#define DEFAULT_PASSWORD "67906z538"

WifiServer wifiServer;
WifiRecvStr wifiRecvStr;
WifiCfg wifiCfg;

//used for getip json data
char data_getIp_json[200] = {
/* "HTTP/1.1 200 OK
" (17 bytes) */
0x48,0x54,0x54,0x50,0x2f,0x31,0x2e,0x31,0x20,0x32,0x30,0x30,0x20,0x4f,0x4b,0x0d,
0x0a,

/* "Server: ty-httpd"
" (18 bytes) */
0x53,0x65,0x72,0x76,0x65,0x72,0x3a,0x20,0x74,0x79,0x2d,0x68,0x74,0x74,0x70,0x64,
0x0d,0x0a,

/* "Content-type: text/html
" (25 bytes) */
0x43,0x6f,0x6e,0x74,0x65,0x6e,0x74,0x2d,0x74,0x79,0x70,0x65,0x3a,0x20,0x74,0x65,
0x78,0x74,0x2f,0x68,0x74,0x6d,0x6c,0x0d,0x0a,

/* "Connection: keep-alive" (24 bytes) */
0x43,0x6f,0x6e,0x6e,0x65,0x63,0x74,0x69,0x6f,0x6e,0x3a,0x20,0x6b,0x65,0x65,0x70,
0x2D,0x61,0x6c,0x69,0x76,0x65,0x0d,0x0a,

/* "Content-length: 597" (23 bytes) */
0x43,0x6f,0x6e,0x74,0x65,0x6e,0x74,0x2d,0x4c,0x65,0x6e,0x67,0x74,0x68,0x3a,0x20,
0x31,0x36,0x36,0x0d,0x0a,0x0d,0x0a,0
};

/**
  * @brief  获取公网路由器的SSID和密码
  * @param  pData:输入字符串;ssid:解析得到的ssid;pswd:解析得到的字符串
  * @retval 0:ok;1:fail
  */
int GetSsidPswd(uint32_t mode,char *pPost,char *ssid,char *pswd)
{
	char *pData;
	char *pSSID;
	char *pPswd;
	int ret = 0;

	//获取SSID和Password的字符串
	if(mode == 0)
	{
		pData = strstr(pPost, "\r\n\r\n");
		if(pData == NULL)
			return 1;

		pData = (pData + 4);
	}
	else
		pData = pPost;
	pSSID = strtok(pData, ",");
	strtok(NULL, ",");
	pPswd = strtok(NULL, ",");

	if (strstr(pSSID, "SSID") != NULL)
	{
		strtok(pSSID, ":");
		pSSID = strtok(NULL, ":");

		ret = ParaseString(pSSID, ssid);
		if(ret != 0)
			return ret;
	}
	else
		return 1;

	if (strstr(pPswd, "Password") != NULL)
	{
		strtok(pPswd, ":");
		pPswd = strtok(NULL, ":");

		ret = ParaseString(pPswd, pswd);
	}
	else
		return 1;

	return ret;
}

void GenGetipJson(WifiServer *server, WifiCfg *cfg)
{
	char buf[64];
	char ip[4];
	uint32_t len;
	
	strcpy(server->tmpBuf,"{\"IsConnected\":");

	if(server->connToAp >= 3)
	{
		strcat(server->tmpBuf,"\"true\",");
		
		strcat(server->tmpBuf,"\"IP\":\"");
		
		ip[0] = ((cfg->localStationIpAddr>>24) & 0xFF);
		ip[1] = ((cfg->localStationIpAddr>>16) & 0xFF);
		ip[2] = ((cfg->localStationIpAddr>>8) & 0xFF);
		ip[3] = ((cfg->localStationIpAddr>>0) & 0xFF);
		sprintf(buf,"%d.%d.%d.%d",ip[0],ip[1],ip[2],ip[3]);
		strcat(server->tmpBuf,buf);
		
		strcat(server->tmpBuf,"\",");
		strcat(server->tmpBuf,"\"Status\":\"1,");

		
	}
	else if(server->connToAp == 1)
	{
		strcat(server->tmpBuf,"\"false\",");
		strcat(server->tmpBuf,"\"IP\":\"\",");
		strcat(server->tmpBuf,"\"Status\":\"0,");
	}
	else
	{
		strcat(server->tmpBuf,"\"false\",");
		strcat(server->tmpBuf,"\"IP\":\"\",");
		strcat(server->tmpBuf,"\"Status\":\"-1,");
	}

	strcat(server->tmpBuf,"\"SSID\":\"");
	//for(i=0;i<32;i++)
	len = strlen(param.wifi_rap_ssid);
	if(len >= 32)
	{
		sprintf(buf,"%s","NULL");
	}
	else
	{
		sprintf(buf,"%s",param.wifi_rap_ssid);
	}
	
	strcat(server->tmpBuf,buf);
	
	strcat(server->tmpBuf,"\"}");

	len = strlen(server->tmpBuf);

	/* change the pkt header*/
	data_getIp_json[100] = ((len/100) + 0x30);
	data_getIp_json[101] = (((len/10) % 10) + 0x30);
	data_getIp_json[102] = ((len%10) + 0x30);

	//merge the header and data
	strcpy(server->send.dataBuf,data_getIp_json);
	strcat(server->send.dataBuf,server->tmpBuf);
	
	server->send.len = strlen(server->send.dataBuf);
}

/**
  * @brief  对接收到的IPD数据进行处理
  * @param  None
  * @retval None
  */
void WifiServer_IpdPro(WifiServer *server, WifiCfg *wifiCfg, WifiRecvStr *wifiRecv)
{
	int ret;
	char *str1;
	char *str2;
	char *pdata = (char *)(wifiRecv->data);
	uint32_t len = wifiRecv->len;
	uint32_t flag = 0;		//ipd报文处理标志
	uint32_t localServerIp = 0;

	//报文隔离处理
	localServerIp = wifiCfg->localApIpAddr[0];
	localServerIp <<= 24;
	localServerIp |= (wifiCfg->localApIpAddr[1] << 16);
	localServerIp |= (wifiCfg->localApIpAddr[2] << 8);
	
	if ((localServerIp & 0xFFFFFF00) != (wifiRecv->ip & 0xFFFFFF00))
		flag = 1;
	else
		flag = 0;

	/* parse method */
	if (!strncmp(pdata, "GET ", 4)) 
	{
		if(flag == 0)
		{
			str1 = (pdata + 4);
			str2 = strstr(str1, " ");
			len = (str2 - str1);
			str1[len] = '\0';

			if(strcmp(str1,"/getIp") == 0)
			{
				server->recvGetIp = 1;
			}
		}
	} 
	else if (!strncmp(pdata, "POST ", 5)) 
	{
		if(flag == 0)
		{
			ret = GetSsidPswd(0,pdata, wifiCfg->remoteSsid, wifiCfg->remotePswd);
			if(ret == 0)
			{
				server->postNext = 0;

				//保存ssid和密码
				if((strcmp(wifiCfg->remoteSsid,param.wifi_rap_ssid) != 0) || \
					(strcmp(wifiCfg->remotePswd,param.wifi_rap_pwd) != 0))
				{
					strcpy(param.wifi_rap_ssid,wifiCfg->remoteSsid);
					strcpy(param.wifi_rap_pwd,wifiCfg->remotePswd);
					Save_Param();

					server->connToAp = 1;
				}
				else
				{
					if(server->connToAp < 3)
					{
						server->connToAp = 1;
					}
					else
						server->recvGetIp = 1;
				}

			}
			else
			{
				//post报文被分成了两封报文
				server->postNext = 1;
			}
		}
	} 
	else 
	{
		if(server->postNext == 1)
		{
			if(flag == 0)
			{
				server->postNext = 0;
				
				ret = GetSsidPswd(1,pdata, wifiCfg->remoteSsid, wifiCfg->remotePswd);
				if(ret == 0)
				{	
					//保存ssid和密码
					if((strcmp(wifiCfg->remoteSsid,param.wifi_rap_ssid) != 0) || \
						(strcmp(wifiCfg->remotePswd,param.wifi_rap_pwd) != 0))
					{
						strcpy(param.wifi_rap_ssid,wifiCfg->remoteSsid);
						strcpy(param.wifi_rap_pwd,wifiCfg->remotePswd);
						Save_Param();

						server->connToAp = 1;
					}
					else
					{
						if(server->connToAp < 3)
							server->connToAp = 1;
						else
							server->recvGetIp = 1;
					}
				}
			}
		}
		else
		{
			if(flag)
			{
				server->send.len = 0;
				MbTcpApp_Pro(pdata,len,server->send.dataBuf,&(server->send.len));
				if(server->send.len != 0)
				{
					server->modbusData = 1;
				}
			}
		}
	}
}

/**
  * @brief  Wifi server task
  * @param  None
  * @retval None
  */
void WifiServer_Task( void )
{	
	uint32_t result;

	switch(wifiServer.state)
	{	
		case WIFISERVER_CFG_WIFI:
			result = Wifi_CfgModule();
			if(result == WIFI_RET_OK)
			{
				wifiServer.state = WIFISERVER_STARTSERVER_PRE;
			}
			else if(result > WIFI_RET_IN)
			{

			}
			break;
		case WIFISERVER_STARTSERVER_PRE:
			wifiCfg.wifi_mode = ESP8266_AP_STA;
				
			memset(wifiCfg.localSsid, 0, sizeof(wifiCfg.localSsid));
			memcpy(wifiCfg.localSsid, DEFAULT_SSID, strlen(DEFAULT_SSID));

			memset(wifiCfg.localPswd, 0, sizeof(wifiCfg.localPswd));
			//memcpy(wifiCfg.localPswd, "12345678", strlen("12345678"));

			//for default setting
			memset(wifiCfg.remoteSsid, 0, sizeof(wifiCfg.remoteSsid));
			strcpy(wifiCfg.remoteSsid, param.wifi_rap_ssid);

			memset(wifiCfg.remotePswd, 0, sizeof(wifiCfg.remotePswd));
			strcpy(wifiCfg.remotePswd, param.wifi_rap_pwd);

			wifiCfg.ecn = 0;
			wifiCfg.localApIpAddr[0] = 192;
			wifiCfg.localApIpAddr[1] = 168;
			wifiCfg.localApIpAddr[2] = 8;
			wifiCfg.localApIpAddr[3] = 1;

			wifiCfg.localApGateway[0] = 192;
			wifiCfg.localApGateway[1] = 168;
			wifiCfg.localApGateway[2] = 8;
			wifiCfg.localApGateway[3] = 1;

			wifiCfg.localApNetmask[0] = 255;
			wifiCfg.localApNetmask[1] = 255;
			wifiCfg.localApNetmask[2] = 255;
			wifiCfg.localApNetmask[3] = 0;

			wifiCfg.localPort = 2000;
			wifiCfg.tcptimer = 60;
			wifiServer.state = WIFISERVER_STARTSERVER;

			wifiServer.failCnt = 0;
			wifiServer.connToAp = 1;		//使能自动连接AP热点
			wifiServer.bootConnToAp = 1;
			break;
		case WIFISERVER_STARTSERVER:
			result = Wifi_CfgLocalTcpServer(&wifiCfg);
			
			if(result == WIFI_RET_OK)
			{
				wifiServer.state = WIFISERVER_RECV;
			}
			else if(result > WIFI_RET_IN)
			{
				wifiServer.failCnt++;
				
				if(wifiServer.failCnt > 5)
					wifiServer.state = WIFISERVER_CFG_WIFI;
			}
			break;
		case WIFISERVER_RECV:
			Wifi_IpdRecv();
			
			if(Wifi_GetIpdRecvState() == 0)
			{
				if( Esp8266_IPDBufOut(&ipdDatatBuf,&wifiRecvStr) != 0)
				{
					wifiServer.ipdPktSocketId = wifiRecvStr.socket;
					
					WifiServer_IpdPro(&wifiServer, &wifiCfg, &wifiRecvStr);
				}
				
				//已经连接上wifi热点
				if(wifiServer.connToAp == 3)
				{
					//10s查询一次ap状态
					if(IsTimeExpired(wifiServer.checkApStateTimer + 10000))
					{
						wifiServer.checkApStateTimer = Get_Gtime();
						wifiServer.state = WIFISERVER_CHKAP;
						break;
					}
				}
				else
				{
					wifiServer.checkApStateTimer = Get_Gtime();
				}
				
				if(wifiServer.connToAp == 1)
				{
					if(wifiServer.bootConnToAp != 1)
					{
						wifiServer.send.socket = wifiRecvStr.socket;
						wifiServer.state = WIFISERVER_CONNTOAP;
						
					}
					else
					{
						wifiServer.state = WIFISERVER_CONNTOAP_IN;
						wifiServer.bootConnToAp = 0;
					}
					
					wifiServer.failCnt = 0;
				}
				else if(wifiServer.recvGetIp == 1)
				{
					wifiServer.recvGetIp = 0;

					wifiServer.send.socket = wifiRecvStr.socket;
					
					GenGetipJson(&wifiServer, &wifiCfg);

					wifiServer.state = WIFISERVER_SEND;
					
					#ifdef WIFI_CH_WKMODE
						if(wifiServer.connToAp == 3)
						{
							wifiServer.sendIpStateCnt++;
							if(wifiServer.sendIpStateCnt > 1)
							{
							
								wifiServer.state = WIFISERVER_CHGMODE;
								wifiServer.connToAp = 4;
								break;
							}
						}
					#endif
						
				}
				else if(wifiServer.modbusData == 1)
				{
					wifiServer.modbusData = 0;
					
					wifiServer.send.socket = wifiRecvStr.socket;
					wifiServer.state = WIFISERVER_SEND;
				}
			}

			#ifdef WIFI_CH_WKMODE
				if(wifiServer.connToAp == 4)
				{
					wifiServer.connToAp = 5;
					wifiServer.state = WIFISERVER_CHGMODE;
				}
			#endif
			break;
		case WIFISERVER_SEND:
			result = Wifi_Send(wifiServer.send.socket, (uint8_t *)(wifiServer.send.dataBuf), wifiServer.send.len);
				
			if(result == WIFI_RET_OK)
			{
				wifiServer.state = WIFISERVER_RECV;
				wifiServer.sendFail = 0;
			}
			else if(result > WIFI_RET_IN)
			{
				wifiServer.state = WIFISERVER_RECV;
				wifiServer.sendFail++;
				if(wifiServer.sendFail > 3)
				{
					//重新配置模块
					wifiServer.state = WIFISERVER_CFG_WIFI;
				}					
			}
			break;
		case WIFISERVER_CONNTOAP:
			GenGetipJson(&wifiServer, &wifiCfg);

			result = Wifi_Send(wifiServer.send.socket, (uint8_t *)(wifiServer.send.dataBuf), wifiServer.send.len);
				
			if(result == WIFI_RET_OK)
			{
				wifiServer.state = WIFISERVER_CONNTOAP_IN;
				wifiServer.sendFail = 0;
			}
			else if(result > WIFI_RET_IN)
			{
				//wifiServer.state = WIFISERVER_CONNTOAP_IN;
				wifiServer.connToAp = 2;
				wifiServer.state = WIFISERVER_RECV;
				wifiServer.sendFail++;
			}
			break;
		case WIFISERVER_CONNTOAP_IN:
			//result = Wifi_ConntoAp(wifiCfg.remoteSsid, wifiCfg.remotePswd,502,&(wifiCfg.localStationIpAddr));
			result = Wifi_ConntoAp(&wifiCfg);
			if(result == WIFI_RET_OK)
			{
				wifiServer.connToAp = 3;
				wifiServer.sendIpStateCnt = 0;
				wifiServer.failCnt = 0;
				wifiServer.state = WIFISERVER_RECV;
				wifiServer.remoteSocketId = wifiCfg.localStationSocketId;
			}
			else if(result > WIFI_RET_IN)
			{	
				wifiServer.connToAp = 2;
				wifiServer.state = WIFISERVER_RECV;
				
				wifiServer.failCnt++;
			}
			break;
		case WIFISERVER_CHGMODE:
			result = Wifi_SetMode(ESP8266_STATION);
			if(result == WIFI_RET_OK)
			{
				wifiServer.state = WIFISERVER_RECV;
			}
			else if(result > WIFI_RET_IN)
			{	
				
				wifiServer.state = WIFISERVER_RECV;
			}
			break;
		case WIFISERVER_CHKAP:
			result = Wifi_CheckIpstatus(&(wifiCfg.localStationSocketId), &(wifiServer.apState));
			if(result == WIFI_RET_OK)
			{
				if((wifiServer.apState == 4) || (wifiServer.apState == 5))	
				{
					wifiServer.connToAp = 1;		//使能自动连接AP热点
					wifiServer.bootConnToAp = 1;
				}	

				wifiServer.remoteSocketId = wifiCfg.localStationSocketId;
				
				wifiServer.state = WIFISERVER_RECV;
			}
			else if(result > WIFI_RET_IN)
			{	
				wifiServer.state = WIFISERVER_RECV;
			}
			break;
		default:
			break;
	}
}


/**
  * @brief  create WIFIserver task 
  * @param  buffer and character
  * @retval None
  */
void WifiServer_TaskStart(void)
{
	wifiServer.state = WIFISERVER_CFG_WIFI;
	wifiServer.failCnt = 0;
	wifiServer.connToAp = 0;
	wifiServer.sendFail = 0;
	wifiServer.sendIpStateCnt = 0;
	wifiServer.postNext = 0;
	wifiServer.bootConnToAp = 0;
	wifiServer.checkApStateTimer = Get_Gtime();
	wifiServer.ipdPktSocketId = 0xFF;
	wifiServer.remoteSocketId = 0xFF;
}

/*--------------------end of file-------------------*/

