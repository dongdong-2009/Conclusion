#include <stm32f10x.h>
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#include "modbus_tcp.h"
#include "modbus_app.h"

/*--------------global variables------------------*/
MbTcpAppData gModuleData;


//寄存器映射表格
RegTable MbTcpDataTbl[]=
{
	{OFFSET(MbTcpAppData,Sys.Version),					0,	2},
	{OFFSET(MbTcpAppData,Sys.SubVersion) ,			1,	2},
	
	{OFFSET(MbTcpAppData,Flow.Measure),					16,	4},
	{OFFSET(MbTcpAppData,Flow.MeasureSrc),			18,	2},
	{OFFSET(MbTcpAppData,Flow.SetPoint),				19,	4},
	{OFFSET(MbTcpAppData,Flow.SetPointSrc),			21,	2},
	
	{OFFSET(MbTcpAppData,Damper.Position),				32,	4},
	{OFFSET(MbTcpAppData,Damper.SetPoint),				34,	4},
	{OFFSET(MbTcpAppData,Damper.SetPointSrc),			36,	2},
	
	{OFFSET(MbTcpAppData,Servo.PWM),							48,	2},
	{OFFSET(MbTcpAppData,Servo.Current),					49,	4},
	{OFFSET(MbTcpAppData,Servo.PWM_Angle_0),			51,	2},
	{OFFSET(MbTcpAppData,Servo.PWM_Angle_90),			52,	2},
	{OFFSET(MbTcpAppData,Servo.Mode),							63,	2},
	
	{OFFSET(MbTcpAppData,Pitot.DiffPressure),			64,	4},
	{OFFSET(MbTcpAppData,Pitot.AmpCoeff),					66,	4},
	{OFFSET(MbTcpAppData,Pitot.SizeCoeff),				68,	4},
	{OFFSET(MbTcpAppData,Pitot.TempCoeff),				70,	4},
	{OFFSET(MbTcpAppData,Pitot.PressureBias),			72,	4},
	{OFFSET(MbTcpAppData,Pitot.Temperature),			74,	4},
	{OFFSET(MbTcpAppData,Pitot.Var_DiffPressure),			76,	4},
	
	{OFFSET(MbTcpAppData,CO2.Measure),				80,	2},
	{OFFSET(MbTcpAppData,CO2.MeasureSrc),			81,	2},
	{OFFSET(MbTcpAppData,CO2.Kp_FlowSP),			82,	4},
	
	{OFFSET(MbTcpAppData,FBCtrl.Kp),					96,	4},
	
	{OFFSET(MbTcpAppData,Terminal[0].Flow),			112+16*0,	4},
	{OFFSET(MbTcpAppData,Terminal[0].Damper),		114+16*0,	4},
	{OFFSET(MbTcpAppData,Terminal[0].CO2),			116+16*0,	2},

	{OFFSET(MbTcpAppData,Terminal[1].Flow),			112+16*1,	4},
	{OFFSET(MbTcpAppData,Terminal[1].Damper),		114+16*1,	4},
	{OFFSET(MbTcpAppData,Terminal[1].CO2),			116+16*1,	2},

	{OFFSET(MbTcpAppData,Terminal[2].Flow),			112+16*2,	4},
	{OFFSET(MbTcpAppData,Terminal[2].Damper),		114+16*2,	4},
	{OFFSET(MbTcpAppData,Terminal[2].CO2),			116+16*2,	2},
	
	{OFFSET(MbTcpAppData,Terminal[3].Flow),			112+16*3,	4},
	{OFFSET(MbTcpAppData,Terminal[3].Damper),		114+16*3,	4},
	{OFFSET(MbTcpAppData,Terminal[3].CO2),			116+16*3,	2},

	{OFFSET(MbTcpAppData,Terminal[4].Flow),			112+16*4,	4},
	{OFFSET(MbTcpAppData,Terminal[4].Damper),		114+16*4,	4},
	{OFFSET(MbTcpAppData,Terminal[4].CO2),			116+16*4,	2},

	{OFFSET(MbTcpAppData,Terminal[5].Flow),			112+16*5,	4},
	{OFFSET(MbTcpAppData,Terminal[5].Damper),		114+16*5,	4},
	{OFFSET(MbTcpAppData,Terminal[5].CO2),			116+16*5,	2},
	
	{OFFSET(MbTcpAppData,Terminal[6].Flow),			112+16*6,	4},
	{OFFSET(MbTcpAppData,Terminal[6].Damper),		114+16*6,	4},
	{OFFSET(MbTcpAppData,Terminal[6].CO2),			116+16*6,	2},

	{OFFSET(MbTcpAppData,Terminal[7].Flow),			112+16*7,	4},
	{OFFSET(MbTcpAppData,Terminal[7].Damper),		114+16*7,	4},
	{OFFSET(MbTcpAppData,Terminal[7].CO2),			116+16*7,	2},

	{OFFSET(MbTcpAppData,Terminal[8].Flow),			112+16*8,	4},
	{OFFSET(MbTcpAppData,Terminal[8].Damper),		114+16*8,	4},
	{OFFSET(MbTcpAppData,Terminal[8].CO2),			116+16*8,	2},

	{OFFSET(MbTcpAppData,Terminal[9].Flow),			112+16*9,	4},
	{OFFSET(MbTcpAppData,Terminal[9].Damper),		114+16*9,	4},
	{OFFSET(MbTcpAppData,Terminal[9].CO2),			116+16*9,	2},

	{OFFSET(MbTcpAppData,Fan.Speed),				240,	4},
	{OFFSET(MbTcpAppData,Fan.Pressure),			242,	4},
};

/** @addtogroup private global variables
  * @{
  */

/**
* @brief:  初始化
* @param:  None
* @retval:	 None
*/
void MbTcpApp_Init(void)
{
	gModuleData.Sys.Version = 0;
	gModuleData.Sys.SubVersion = 1;
	
	gModuleData.Flow.MeasureSrc = 1;
	gModuleData.Flow.SetPointSrc = 1;
	
	gModuleData.Damper.SetPoint = 45.0;
	gModuleData.Damper.SetPointSrc = 2;
	
	gModuleData.Servo.Mode = 1;
	gModuleData.Servo.PWM_Angle_0 = 1000;
	gModuleData.Servo.PWM_Angle_90 = 2000;
	
	
	gModuleData.CO2.MeasureSrc = 2;
}

void MbTcpApp_Pro(char *recvData,uint32_t len,char *txData,uint32_t *txLen)
{
	int ret = 0;
	uint32_t i;
	uint32_t idx = 0;
	uint32_t flag = 0;
	uint32_t temp = 0;
	uint32_t regData;
	uint32_t regLen;
	uint8_t *pData;
	int32_t errFlag = 0;
	
	ret = MbTcp_RecvFrame(recvData,len);

	errFlag = ret;

	if(ret == 0)
	{	
		switch(modbusMsg.funCode)
		{
			case MODBUS_FUNC_RD:
				if(modbusMsg.regNum == 0)
				{
					errFlag = COM_RECV_REGNUM_ERR;
					break;
				}					
				for(i=0;i<sizeof(MbTcpDataTbl)/sizeof(RegTable);i++)
				{
					if(modbusMsg.regAddr == MbTcpDataTbl[i].regAddr)
					{
						flag = 1;
						regLen = (modbusMsg.regNum << 1);		//记下寄存器个数
					}
					if(flag == 1)
					{	
						if(modbusMsg.regNum > 0)
						{
							pData = (uint8_t *)&(gModuleData);
						
							if(MbTcpDataTbl[i].dataSize == 2)
							{
								temp = *(uint16_t *)(pData + MbTcpDataTbl[i].offset);
								regData = ((temp >> 8) & 0xFF);
								regData |= ((temp << 8) & 0xFF00);
								
								memcpy((char *)((txData+9)+idx),&(regData),2);
								idx += 2;

								modbusMsg.regNum--;
							}
							else if(MbTcpDataTbl[i].dataSize == 4)
							{
								temp = *(uint32_t *)(pData + MbTcpDataTbl[i].offset);

								regData = ((temp >> 24) & 0x000000FF);
								regData |= ((temp >> 8) & 0x0000FF00);
								regData |= ((temp << 8) & 0x00FF0000);
								regData |= ((temp << 24) & 0xFF000000);
								
								memcpy((char *)((txData+9)+idx),(char *)(&regData),4);

								idx += 4;

								modbusMsg.regNum -= 2;
							}	
						}
						else
						{
							//errFlag = COM_RECV_REGNUM_ERR;
							break;
						}
					}
				}
				
				if(flag == 0)
				{
					errFlag = COM_RECV_REGADDR_ERR;
					break;
				}
				if(modbusMsg.regNum > 0)
				{
					errFlag = COM_RECV_REGNUM_ERR;
					break;
				}
				
				if(idx)
				{
					ret = 1;
					//regLen = idx;

					idx = 0;
					txData[idx] = ((modbusMsg.tid >> 8) & 0xFF);
					idx++;
					txData[idx] = ((modbusMsg.tid >> 0) & 0xFF);
					idx++;
					txData[idx] = ((modbusMsg.pid >> 8) & 0xFF);
					idx++;
					txData[idx] = ((modbusMsg.pid >> 0) & 0xFF);
					idx++;
					txData[idx] = (0x00);
					idx++;
					txData[idx] = (regLen + 0x3);
					idx++;
					txData[idx] = (modbusMsg.uid);
					idx++;
					txData[idx] = (modbusMsg.funCode);
					idx++;
					txData[idx] = (regLen);
					idx++;
					
					*txLen = (regLen + 9);
				}	
				break;
			default: 
				if(modbusMsg.funCode == MODBUS_FUNC_WR_SINGLE)
				{
					if(modbusMsg.regNum != 1)
					{
						errFlag = COM_RECV_REGNUM_ERR;
						break;
					}
				}
				if(modbusMsg.regNum == 0)
				{
					errFlag = COM_RECV_REGNUM_ERR;
					break;
				}
				
				for(i=0;i<sizeof(MbTcpDataTbl)/sizeof(RegTable);i++)
				{
					if(modbusMsg.regAddr == MbTcpDataTbl[i].regAddr)
					{
						flag = 1;
						regLen = modbusMsg.regNum;		//记下寄存器个数
					}
					
					if(flag == 1)
					{
						if(modbusMsg.regNum > 0)
						{
							pData = (uint8_t *)&(gModuleData);
							if(MbTcpDataTbl[i].dataSize == 2)
							{
								temp = modbusMsg.regData[idx];
								regData = (temp << 8);
								
								temp = modbusMsg.regData[(idx+1)];
								regData |= (temp);
								
								memcpy((char *)(pData + MbTcpDataTbl[i].offset), (char *)(&regData), 2);

								idx += 2;

								modbusMsg.regNum--;
							}
							else if(MbTcpDataTbl[i].dataSize == 4)
							{
								temp = modbusMsg.regData[idx];
								regData = (temp << 24);
								
								temp = modbusMsg.regData[(idx+1)];
								regData |= (temp << 16);

								temp = modbusMsg.regData[(idx+2)];
								regData |= (temp << 8);

								temp = modbusMsg.regData[(idx+3)];
								regData |= (temp << 0);
								
								memcpy((char *)(pData + MbTcpDataTbl[i].offset),(char *)(&regData),4);								

								idx += 4;

								modbusMsg.regNum -= 2;
							}	
						}
						else
						{
							//errFlag = COM_RECV_REGNUM_ERR;
							break;
						}
					}
				}
				
				if(flag == 0)
				{
					errFlag = COM_RECV_REGADDR_ERR;
					break;	
				}
				
				if(modbusMsg.regNum > 0)
				{
					errFlag = COM_RECV_REGNUM_ERR;
					break;
				}

				//准备发送应答数据
				if(idx)
				{
					idx = 0;
					txData[idx] = ((modbusMsg.tid >> 8) & 0xFF);
					idx++;
					txData[idx] = ((modbusMsg.tid >> 0) & 0xFF);
					idx++;
					txData[idx] = ((modbusMsg.pid >> 8) & 0xFF);
					idx++;
					txData[idx] = ((modbusMsg.pid >> 0) & 0xFF);
					idx++;
					txData[idx] = (0x00);
					idx++;
					txData[idx] = (0x06);
					idx++;
					txData[idx] = (modbusMsg.uid);
					idx++;
					txData[idx] = (modbusMsg.funCode);
					idx++;
					txData[idx] = ((modbusMsg.regAddr >> 8) & 0xFF);
					idx++;
					txData[idx] = ((modbusMsg.regAddr >> 0) & 0xFF);
					idx++;
					
					if(modbusMsg.funCode == MODBUS_FUNC_WR_SINGLE)
					{
						txData[idx] = (modbusMsg.regData[0]);
						idx++;
						txData[idx] = (modbusMsg.regData[1]);
						idx++;
					}
					else
					{
						txData[idx] = ((regLen >> 8) & 0xFF);
						idx++;
						txData[idx] = ((regLen >> 0) & 0xFF);
						idx++;
					}

					*txLen = idx;
				}	
				break;
		}
	}

	if(errFlag != 0)
	{
		idx = 0;
		txData[idx] = ((modbusMsg.tid >> 8) & 0xFF);
		idx++;
		txData[idx] = ((modbusMsg.tid >> 0) & 0xFF);
		idx++;
		txData[idx] = ((modbusMsg.pid >> 8) & 0xFF);
		idx++;
		txData[idx] = ((modbusMsg.pid >> 0) & 0xFF);
		idx++;
		txData[idx] = (0x00);
		idx++;
		txData[idx] = (0x03);
		idx++;
		txData[idx] = (modbusMsg.uid);
		idx++;
		txData[idx] = (modbusMsg.funCode + 0x80);
		idx++;
		
		switch(errFlag)
		{
			case COM_RECV_FUNC_ERR:
				txData[idx] = (1);
				break;
			case COM_RECV_REGNUM_ERR:
			case COM_RECV_DATALEN_ERR:
				txData[idx] = (3);
				break;
			case COM_RECV_REGADDR_ERR:
				txData[idx] = (2);
				break;
			default:
				txData[idx] = (4);
				break;
		}

		idx++;

		*txLen = idx;
	}
}


/*----------------------------end of file---------------------------*/

