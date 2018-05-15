#include "stm32f10x.h"
#include <stdio.h>
#include "mb.h"
#include "mbutils.h"
#include "mbReg.h"
#include "sysconfig.h"

//输入寄存器内容
uint16_t usRegInputBuf[REG_INPUT_NREGS] = {0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007};
//输入寄存器起始地址
uint16_t usRegInputStart = REG_INPUT_START;

//保持寄存器内容
uint16_t usRegHoldingBuf[REG_HOLDING_NREGS] = {0x0001,0x0002,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007};
//保持寄存器起始地址
uint16_t usRegHoldingStart = REG_HOLDING_START;

//线圈状态，上位机可以修改
uint8_t ucRegCoilsBuf[REG_COILS_SIZE / 8] = {0x00,0x02};  
//开关输入状态，供上位机读取
uint8_t ucRegDiscreteBuf[REG_DISCRETE_SIZE / 8] = {0x01,0x02};


int main(void)
{
	RCC_Configuration();
	IWDG_Configuration();
	//初始化 RTU模式 从机地址为1 USART1 波特率9600 无校验
	eMBInit(MB_RTU, 0x01, 0x01, 9600, MB_PAR_NONE);
	//启动FreeModbus 
	eMBEnable(); 
	while (1)
	{
		IWDG_ReloadCounter();         //喂狗  10s
		//FreeMODBUS不断查询
		eMBPoll(); 
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
					*pucRegBuffer++ = ( uint8_t )( usRegHoldingBuf[iRegIndex] >> 8 );
					*pucRegBuffer++ = ( uint8_t )( usRegHoldingBuf[iRegIndex] & 0xFF );
					iRegIndex++;
					usNRegs--;
				}
				break;

			//写处理函数 
			case MB_REG_WRITE:
				while( usNRegs > 0 )
				{
					usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
					usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
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
