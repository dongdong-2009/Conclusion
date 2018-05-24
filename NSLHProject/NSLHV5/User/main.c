#include "mb.h"
#include "mbutils.h"
#include "mbReg.h"
#include "sysconfig.h"

//输入寄存器内容
uint16_t usRegInputBuf[REG_INPUT_NREGS] = {0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007};
//输入寄存器起始地址
uint16_t usRegInputStart = REG_INPUT_START;

//保持寄存器内容
uint16_t *usRegHoldingBuf[REG_HOLDING_NREGS]={0};
//保持寄存器起始地址
uint16_t usRegHoldingStart = REG_HOLDING_START;

//线圈状态，上位机可以修改
uint8_t ucRegCoilsBuf[REG_COILS_SIZE / 8] = {0x00,0x02};  
//开关输入状态，供上位机读取
uint8_t ucRegDiscreteBuf[REG_DISCRETE_SIZE / 8] = {0x01,0x02};


//定义相关变量
float dataTemp[12];
float RTDtemperature[4];
float AI_Input[12]={0};
u8   	DI_data[8]={0};
u8 DataFlag=0;

int main(void)
{
 	RCC_Configuration();            //系统时钟配置信息
	IO_Configuration();             //DI and DO 初始化
	ADC_init();                     //AI初始化
	DAC_init();                     //AO初始化
	RTD_init();                     //测温初始化
	Usart_Total_Initi();            //串口初始化
	Tim2Configure();               	//定时处理与小板通信数据
	Tim4Configure();               	//定时器4定时15s，定时处理PID control algorithm,时间间隔是15s
	InitialSys();
	IWDG_Configuration();
	RegMap();
	//初始化 RTU模式 从机地址为1 USART1 波特率9600 无校验
	eMBInit(MB_RTU, 0x67, 0x01, 19200, MB_PAR_NONE);
	//启动FreeModbus 
	eMBEnable(); 
	while (1)
	{
		IWDG_ReloadCounter();         //喂狗  10s
		//FreeMODBUS不断查询
		eMBPoll(); 
		CO2Control();                 //co2浓度控制
		
		//RunStatus为系统运行状态标志位，RunStatus--0:系统未运行，RunStatus--1：系统正常运行
		if(!RunStatus&&(IBSCommand||ScheduleComm))      //收到Booking或者Schedule命令启动系统
		{
			AlarmFlag=NSLH_Start();              					//系统启动，水阀开40%
			if(AlarmFlag!=0)                              //如果系统启动异常，关闭所有端口输出信号
				NSLH_Clear();
			RunStatus=1;
		}
		
		//系统运行时，收到E-booking或者Schedule关系统指令时，关闭系统
		if(RunStatus&&((!IBSCommand)&&(!ScheduleComm)))
		{
			AlarmFlag=NSLH_Stop();                      //关闭系统
			if(AlarmFlag!=0)
			{
				NSLH_Clear();                             //如果系统异常，关闭所有端口
			}
			RunStatus=0;
		}
		
				//在系统正常运行状态下，Motion Sensor检测到有人进入房间
		if(RunStatus&&OccSta)
		{
			if(RoomTemp==0&&RoomHum==0&&CO2==0)
			{
				APortOut(CHWV,10.0);
				DataFlag=1;
			}
			else
			{
				DataFlag=0;
			}
			
			if(RoomTempSv==270)
			{
				RoomTempSv=245;
			}
			
			if(!DataFlag)
			{
				AlarmFlag=OccupanyMode();     //执行有人情况下控制操作
				if(AlarmFlag!=0)              //如果系统异常，则关闭全部端口信息
				{
					NSLH_Clear();
				}
			}
		}
		
				//在系统正常运行状态下，Motion Sensor检测到房间无人状态下
		if(RunStatus&&(!OccSta))
		{
			RoomTempSv=270;              //无人状况下，房间温度设定值为27度，保持不变
			if(RoomTemp==0&&RoomHum==0&&CO2==0)
			{
				APortOut(CHWV,10.0);
				DataFlag=1;
			}
			else
			{
				DataFlag=0;
			}
			if(!DataFlag)
			{
				AlarmFlag=Unoccupanied();    //执行无人模式下，温度控制操作，温度设定值为27度，PID调节水阀
				if(AlarmFlag!=0)
				{
					NSLH_Clear();
				}
			}
		}
	}
}

/**
* @brief 保持寄存器处理函数，保持寄存器可读可写
* @param pucRegBuffer 读操作时--返回数据指针,写操作时--输入数据指针
* usAddress 寄存器起始地址
* usNRegs 寄存器长度
* eMode 操作方式,读或者写
* @retval eStatus 寄存器状态
*/
eMBErrorCode 	eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
	//错误状态
	eMBErrorCode eStatus = MB_ENOERR;
	//偏移量
	int16_t iRegIndex;

	//判断寄存器是不是在范围内
	if( ( (int16_t)usAddress >= REG_HOLDING_START )&&( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
	{
		//计算偏移量
		iRegIndex = ( int16_t )( usAddress - REG_HOLDING_START);
		switch ( eMode )
		{
			//读处理函数 
			case MB_REG_READ:
				while( usNRegs > 0 )
				{
					*pucRegBuffer++ = ( uint8_t )( *usRegHoldingBuf[iRegIndex] >> 8 );
					*pucRegBuffer++ = ( uint8_t )( *usRegHoldingBuf[iRegIndex] & 0xFF );
					iRegIndex++;
					usNRegs--;
				}
				break;

			//写处理函数 
			case MB_REG_WRITE:
				while( usNRegs > 0 )
				{
					*usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
					*usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
					iRegIndex++;
					usNRegs--;
				}
			break;
		}
	}
	else
	{
		//返回错误状态
		eStatus = MB_ENOREG;
	}
	return eStatus;
}

/**
* @brief 输入寄存器处理函数,输入寄存器可读,但不可写
* @param pucRegBuffer 返回数据指针
* usAddress 寄存器起始地址
* usNRegs 寄存器长度
* @retval eStatus 寄存器状态
*/
eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
	eMBErrorCode eStatus = MB_ENOERR;
	int16_t iRegIndex;

	//查询是否在寄存器范围内
	//为了避免警告,修改为有符号整数
	if( ( (int16_t)usAddress >= REG_INPUT_START )&& ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
	{
		//获取操作偏移量,本次操作起始地址-输入寄存器的初始地址
		iRegIndex = ( int16_t )( usAddress - REG_INPUT_START );
		//逐个赋值
		while( usNRegs > 0 )
		{
			//赋值高字节
			*pucRegBuffer++ = ( uint8_t )( usRegInputBuf[iRegIndex] >> 8 );
			//赋值低字节
			*pucRegBuffer++ = ( uint8_t )( usRegInputBuf[iRegIndex] & 0xFF );
			//偏移量增加
			iRegIndex++;
			//被操作寄存器数量减1
			usNRegs--;
		}
	}
	else
	{
		//返回错误状态,无寄存器 
		eStatus = MB_ENOREG;
	}
	return eStatus;
}

/**
* @brief 线圈寄存器处理函数,线圈寄存器可读可写
* @param pucRegBuffer 读操作---返回数据指针,写操作--返回数据指针
* usAddress 寄存器起始地址
* usNRegs 寄存器长度
* eMode 操作方式,读或者写
* @retval eStatus 寄存器状态
*/
eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,eMBRegisterMode eMode )
{
	//错误状态
	eMBErrorCode eStatus = MB_ENOERR;
	//寄存器个数
	int16_t iNCoils = ( int16_t )usNCoils;
	//寄存器偏移量
	int16_t usBitOffset;

	//检查寄存器是否在指定范围内
	if( ( (int16_t)usAddress >= REG_COILS_START ) &&( usAddress + usNCoils <= REG_COILS_START + REG_COILS_SIZE ) )
	{
		//计算寄存器偏移量
		usBitOffset = ( int16_t )( usAddress - REG_COILS_START );
		switch ( eMode )
		{
			//读操作
			case MB_REG_READ:
			while( iNCoils > 0 )	
			{
				*pucRegBuffer++ = xMBUtilGetBits( ucRegCoilsBuf, usBitOffset,( uint8_t )( iNCoils > 8 ? 8 : iNCoils ) );
				iNCoils -= 8;
				usBitOffset += 8;
			}
			break;

			//写操作
			case MB_REG_WRITE:
			while( iNCoils > 0 )
			{
				xMBUtilSetBits( ucRegCoilsBuf, usBitOffset,( uint8_t )( iNCoils > 8 ? 8 : iNCoils ),*pucRegBuffer++ );
				iNCoils -= 8;
			}
			break;
		}

	}
	else
	{
		eStatus = MB_ENOREG;
	}
	return eStatus;
}

/**
* @brief 开关输入寄存器处理函数,开关输入寄存器,可读
* @param pucRegBuffer 读操作---返回数据指针
* usAddress 寄存器起始地址
* usNRegs 寄存器长度
* @retval eStatus 寄存器状态
*/
eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
	//错误状态
	eMBErrorCode eStatus = MB_ENOERR;
	//操作寄存器个数
	int16_t iNDiscrete = ( int16_t )usNDiscrete;
	//偏移量
	uint16_t usBitOffset;

	//判断寄存器是否在指定的范围
	if( ( (int16_t)usAddress >= REG_DISCRETE_START ) &&( usAddress + usNDiscrete <= REG_DISCRETE_START + REG_DISCRETE_SIZE ) )
	{
		//获得偏移量
		usBitOffset = ( uint16_t )( usAddress - REG_DISCRETE_START );

		while( iNDiscrete > 0 )
		{
			*pucRegBuffer++ = xMBUtilGetBits( ucRegDiscreteBuf, usBitOffset,( uint8_t)( iNDiscrete > 8 ? 8 : iNDiscrete ) );
			iNDiscrete -= 8;
			usBitOffset += 8;
		}
	}
	else
	{
		eStatus = MB_ENOREG;
	}
	return eStatus;
}


void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;                              //定义外部高速晶体启动状态枚举变量；
	RCC_DeInit();                                              //复位RCC寄存器到默认值；
	RCC_HSEConfig(RCC_HSE_ON);                                 //打开外部的高速晶振； 
	HSEStartUpStatus = RCC_WaitForHSEStartUp();                //等待外部高速时钟准备好
	if(HSEStartUpStatus == SUCCESS)
		{
			RCC_HCLKConfig(RCC_SYSCLK_Div1);                         //配置AHB
			RCC_PCLK2Config(RCC_HCLK_Div1);                          //配置APB2 
			RCC_PCLK1Config(RCC_HCLK_Div2);                          //配置APB1 
			//RCC_ADCCLKConfig(RCC_PCLK2_Div4);	      
			RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);     //PLL=8M*9=72M
			RCC_PLLCmd(ENABLE);                                      //时能PLL
			while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);      //等待PLL就绪	      
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);               //配置系统时钟=PLL	  
			while(RCC_GetSYSCLKSource() != 0x08);                    //检查PLL时钟是否作为系统时钟	       
		}
}

void IWDG_Configuration(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //写入0x5555，用于允许寄存器写入功能，解除寄存器保护
	IWDG_SetPrescaler(IWDG_Prescaler_256);     //时钟分频 40K/256=156HZ(6.4ms)
	IWDG_SetReload(1562);    //喂狗时间1562*6.4ms=10s,数值不能大于0xfff
	IWDG_ReloadCounter();   //喂狗
	IWDG_Enable();    //使能
}

void InitialSys(void)
{
	DPortCIn(DI_data);  //Read the Status motion sensor(DI0) and 2 Damper(DI7 and DI6) 
	RTD_allchannels(RTDtemperature);  //Read the return water temperature (RTD 0)
	APortCIn(dataTemp);	//Read the DP sensor value(AI3) and chilled water valve feedback(AI11)
	APortIn(11,AI_Input);
	APortIn(3,AI_Input);
}

void RegMap(void)
{
	//数据处理
	OccSta=(DI_data[0])|(DI_data[1]);
	ValveFb=(AI_Input[11]*10);
	DPValue=(AI_Input[3]*10);	
	CHWTemp=(u16)(RTDtemperature[2]*10);
	
	//Modbus通信地址匹配
	usRegHoldingBuf[0] = &RoomTemp;
	usRegHoldingBuf[1] = &RoomTempSv;
	usRegHoldingBuf[2] = &RoomHum;
	usRegHoldingBuf[3] = &RoomHumSv;
	usRegHoldingBuf[4] = &CHWTemp;
	usRegHoldingBuf[5] = &CO2;
	usRegHoldingBuf[6] = &CO2Sv;
	usRegHoldingBuf[7] = &OccSta;
	usRegHoldingBuf[8] = &ECS;
	usRegHoldingBuf[9] = &ValveFb;
	usRegHoldingBuf[10] = &DPValue;
	
	usRegHoldingBuf[11] = &IBSCommand;
	usRegHoldingBuf[12] = &ScheduleComm;
}

