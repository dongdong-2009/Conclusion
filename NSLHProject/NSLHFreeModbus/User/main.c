#include "mb.h"
#include "mbutils.h"
#include "mbReg.h"
#include "sysconfig.h"

//ÊäÈë¼Ä´æÆ÷ÄÚÈÝ
uint16_t usRegInputBuf[REG_INPUT_NREGS] = {0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007};
//ÊäÈë¼Ä´æÆ÷ÆðÊ¼µØÖ·
uint16_t usRegInputStart = REG_INPUT_START;

//±£³Ö¼Ä´æÆ÷ÄÚÈÝ
uint16_t *usRegHoldingBuf[REG_HOLDING_NREGS]={0};
//±£³Ö¼Ä´æÆ÷ÆðÊ¼µØÖ·
uint16_t usRegHoldingStart = REG_HOLDING_START;

//ÏßÈ¦×´Ì¬£¬ÉÏÎ»»ú¿ÉÒÔÐÞ¸Ä
uint8_t ucRegCoilsBuf[REG_COILS_SIZE / 8] = {0x00,0x02};  
//¿ª¹ØÊäÈë×´Ì¬£¬¹©ÉÏÎ»»ú¶ÁÈ¡
uint8_t ucRegDiscreteBuf[REG_DISCRETE_SIZE / 8] = {0x01,0x02};


//¶¨ÒåÏà¹Ø±äÁ¿
float dataTemp[12];
float RTDtemperature[4];
float AI_Input[12]={0};
u8   	DI_data[8]={0};
u8 DataFlag=0;

int main(void)
{
 	RCC_Configuration();            //ÏµÍ³Ê±ÖÓÅäÖÃÐÅÏ¢
	IO_Configuration();             //DI and DO ³õÊ¼»¯
	ADC_init();                     //AI³õÊ¼»¯
	DAC_init();                     //AO³õÊ¼»¯
	RTD_init();                     //²âÎÂ³õÊ¼»¯
	Usart_Total_Initi();            //´®¿Ú³õÊ¼»¯
	Tim2Configure();               	//¶¨Ê±´¦ÀíÓëÐ¡°åÍ¨ÐÅÊý¾Ý
	Tim4Configure();               	//¶¨Ê±Æ÷4¶¨Ê±15s£¬¶¨Ê±´¦ÀíPID control algorithm,Ê±¼ä¼ä¸ôÊÇ15s
	InitialSys();
	IWDG_Configuration();
	RegMap();
	
	//³õÊ¼»¯ RTUÄ£Ê½ ´Ó»úµØÖ·Îª1 USART1 ²¨ÌØÂÊ19200 ÎÞÐ£Ñé
	eMBInit(MB_RTU, 0x65, 0x01, 19200, MB_PAR_NONE);
	//Æô¶¯FreeModbus 
	eMBEnable(); 
	while (1)
	{
		IWDG_ReloadCounter();         //Î¹¹·  10s
		//FreeMODBUS²»¶Ï²éÑ¯
		eMBPoll(); 
		
		//14£º·§½ô¼±È«¿ªÃüÁî£¬²»Ö´ÐÐÕý³£ÎÂ¶È¿ØÖÆÂß¼­
		if(ValveCmd!=0&&ForceValveFlag==0)
		{
			if(ValveCmd>100)
				ValveCmd=100;
			if(ValveCmd<1)
				ValveCmd=0;
			APortOut(CHWV,ValveCmd/10.0);
			APortOut(PTBFan1,8.0);		//¿ªptb·çÉÈ
			APortOut(PTBFan2,8.0);		//¿ªptb·çÉÈ
			ForceValveFlag=1;
		}
		else if(ValveCmd==0&&ForceValveFlag==1)
		{
			APortOut(CHWV,0.0);
			APortOut(PTBFan1,0.0);		//¿ªptb·çÉÈ
			APortOut(PTBFan2,0.0);		//¿ªptb·çÉÈ
			ForceValveFlag=0;
		}
		else if(ValveCmd!=0&&ForceValveFlag==1)
		{
			if(ValveCmd>100)
				ValveCmd=100;
			if(ValveCmd<1)
				ValveCmd=0;
			APortOut(CHWV,ValveCmd/10.0);
			APortOut(PTBFan1,8.0);		//¿ªptb·çÉÈ
			APortOut(PTBFan2,8.0);		//¿ªptb·çÉÈ
			ForceValveFlag=1;
		}
		
				//ÓÐÁËERVÇ¿ÖÆÆô¶¯ÃüÁî£¬²»¹Üµ±Ç°ERV´¦ÓÚÊ²Ã´×´Ì¬£¬¶¼ÐèÒª¿ªÆôERV
		if(ERVCmd!=0)
		{
			DPortOut(ERVFan,1);
			ERVState=1;
			ERVFlag=1;
		}
		if(ERVCmd==0&&ERVFlag==1)   //ÔÚERVÇ¿ÖÆÆô¶¯ºó£¬ERVCmdÃüÁîÎª0£¬¼´¹Ø±ÕERVÍ¨·ç
		{
			DPortOut(ERVFan,0);
			ERVState=0;
			ERVFlag=0;
		}
		
		//Ã»ÓÐERVÇ¿ÖÆÃüÁî£¬Í¬Ê±´¦ÓÚ·ÇÇ¿ÖÆÄ£Ê½£¬¸ù¾ÝCO2Å¨¶È½øÐÐ¿ØÖÆ
		if(ERVCmd==0&&ERVFlag==0)
		{
			CO2Control();//·Ç½ô¼±µÄÕý³£ÔËÐÐ£¬CO2¿ØÖÆÂß¼
		}
		
		normal();
	}
}

/**
* @brief ±£³Ö¼Ä´æÆ÷´¦Àíº¯Êý£¬±£³Ö¼Ä´æÆ÷¿É¶Á¿ÉÐ´
* @param pucRegBuffer ¶Á²Ù×÷Ê±--·µ»ØÊý¾ÝÖ¸Õë,Ð´²Ù×÷Ê±--ÊäÈëÊý¾ÝÖ¸Õë
* usAddress ¼Ä´æÆ÷ÆðÊ¼µØÖ·
* usNRegs ¼Ä´æÆ÷³¤¶È
* eMode ²Ù×÷·½Ê½,¶Á»òÕßÐ´
* @retval eStatus ¼Ä´æÆ÷×´Ì¬
*/
eMBErrorCode 	eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
	//´íÎó×´Ì¬
	eMBErrorCode eStatus = MB_ENOERR;
	//Æ«ÒÆÁ¿
	int16_t iRegIndex;

	//ÅÐ¶Ï¼Ä´æÆ÷ÊÇ²»ÊÇÔÚ·¶Î§ÄÚ
	if( ( (int16_t)usAddress >= REG_HOLDING_START )&&( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
	{
		//¼ÆËãÆ«ÒÆÁ¿
		iRegIndex = ( int16_t )( usAddress - REG_HOLDING_START);
		switch ( eMode )
		{
			//¶Á´¦Àíº¯Êý 
			case MB_REG_READ:
				while( usNRegs > 0 )
				{
					*pucRegBuffer++ = ( uint8_t )( *usRegHoldingBuf[iRegIndex] >> 8 );
					*pucRegBuffer++ = ( uint8_t )( *usRegHoldingBuf[iRegIndex] & 0xFF );
					iRegIndex++;
					usNRegs--;
				}
				break;

			//Ð´´¦Àíº¯Êý 
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
		//·µ»Ø´íÎó×´Ì¬
		eStatus = MB_ENOREG;
	}
	return eStatus;
}

/**
* @brief ÊäÈë¼Ä´æÆ÷´¦Àíº¯Êý,ÊäÈë¼Ä´æÆ÷¿É¶Á,µ«²»¿ÉÐ´
* @param pucRegBuffer ·µ»ØÊý¾ÝÖ¸Õë
* usAddress ¼Ä´æÆ÷ÆðÊ¼µØÖ·
* usNRegs ¼Ä´æÆ÷³¤¶È
* @retval eStatus ¼Ä´æÆ÷×´Ì¬
*/
eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
	eMBErrorCode eStatus = MB_ENOERR;
	int16_t iRegIndex;

	//²éÑ¯ÊÇ·ñÔÚ¼Ä´æÆ÷·¶Î§ÄÚ
	//ÎªÁË±ÜÃâ¾¯¸æ,ÐÞ¸ÄÎªÓÐ·ûºÅÕûÊý
	if( ( (int16_t)usAddress >= REG_INPUT_START )&& ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
	{
		//»ñÈ¡²Ù×÷Æ«ÒÆÁ¿,±¾´Î²Ù×÷ÆðÊ¼µØÖ·-ÊäÈë¼Ä´æÆ÷µÄ³õÊ¼µØÖ·
		iRegIndex = ( int16_t )( usAddress - REG_INPUT_START );
		//Öð¸ö¸³Öµ
		while( usNRegs > 0 )
		{
			//¸³Öµ¸ß×Ö½Ú
			*pucRegBuffer++ = ( uint8_t )( usRegInputBuf[iRegIndex] >> 8 );
			//¸³ÖµµÍ×Ö½Ú
			*pucRegBuffer++ = ( uint8_t )( usRegInputBuf[iRegIndex] & 0xFF );
			//Æ«ÒÆÁ¿Ôö¼Ó
			iRegIndex++;
			//±»²Ù×÷¼Ä´æÆ÷ÊýÁ¿¼õ1
			usNRegs--;
		}
	}
	else
	{
		//·µ»Ø´íÎó×´Ì¬,ÎÞ¼Ä´æÆ÷ 
		eStatus = MB_ENOREG;
	}
	return eStatus;
}

/**
* @brief ÏßÈ¦¼Ä´æÆ÷´¦Àíº¯Êý,ÏßÈ¦¼Ä´æÆ÷¿É¶Á¿ÉÐ´
* @param pucRegBuffer ¶Á²Ù×÷---·µ»ØÊý¾ÝÖ¸Õë,Ð´²Ù×÷--·µ»ØÊý¾ÝÖ¸Õë
* usAddress ¼Ä´æÆ÷ÆðÊ¼µØÖ·
* usNRegs ¼Ä´æÆ÷³¤¶È
* eMode ²Ù×÷·½Ê½,¶Á»òÕßÐ´
* @retval eStatus ¼Ä´æÆ÷×´Ì¬
*/
eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,eMBRegisterMode eMode )
{
	//´íÎó×´Ì¬
	eMBErrorCode eStatus = MB_ENOERR;
	//¼Ä´æÆ÷¸öÊý
	int16_t iNCoils = ( int16_t )usNCoils;
	//¼Ä´æÆ÷Æ«ÒÆÁ¿
	int16_t usBitOffset;

	//¼ì²é¼Ä´æÆ÷ÊÇ·ñÔÚÖ¸¶¨·¶Î§ÄÚ
	if( ( (int16_t)usAddress >= REG_COILS_START ) &&( usAddress + usNCoils <= REG_COILS_START + REG_COILS_SIZE ) )
	{
		//¼ÆËã¼Ä´æÆ÷Æ«ÒÆÁ¿
		usBitOffset = ( int16_t )( usAddress - REG_COILS_START );
		switch ( eMode )
		{
			//¶Á²Ù×÷
			case MB_REG_READ:
			while( iNCoils > 0 )	
			{
				*pucRegBuffer++ = xMBUtilGetBits( ucRegCoilsBuf, usBitOffset,( uint8_t )( iNCoils > 8 ? 8 : iNCoils ) );
				iNCoils -= 8;
				usBitOffset += 8;
			}
			break;

			//Ð´²Ù×÷
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
* @brief ¿ª¹ØÊäÈë¼Ä´æÆ÷´¦Àíº¯Êý,¿ª¹ØÊäÈë¼Ä´æÆ÷,¿É¶Á
* @param pucRegBuffer ¶Á²Ù×÷---·µ»ØÊý¾ÝÖ¸Õë
* usAddress ¼Ä´æÆ÷ÆðÊ¼µØÖ·
* usNRegs ¼Ä´æÆ÷³¤¶È
* @retval eStatus ¼Ä´æÆ÷×´Ì¬
*/
eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
	//´íÎó×´Ì¬
	eMBErrorCode eStatus = MB_ENOERR;
	//²Ù×÷¼Ä´æÆ÷¸öÊý
	int16_t iNDiscrete = ( int16_t )usNDiscrete;
	//Æ«ÒÆÁ¿
	uint16_t usBitOffset;

	//ÅÐ¶Ï¼Ä´æÆ÷ÊÇ·ñÔÚÖ¸¶¨µÄ·¶Î§
	if( ( (int16_t)usAddress >= REG_DISCRETE_START ) &&( usAddress + usNDiscrete <= REG_DISCRETE_START + REG_DISCRETE_SIZE ) )
	{
		//»ñµÃÆ«ÒÆÁ¿
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
	ErrorStatus HSEStartUpStatus;                              //¶¨ÒåÍâ²¿¸ßËÙ¾§ÌåÆô¶¯×´Ì¬Ã¶¾Ù±äÁ¿£»
	RCC_DeInit();                                              //¸´Î»RCC¼Ä´æÆ÷µ½Ä¬ÈÏÖµ£»
	RCC_HSEConfig(RCC_HSE_ON);                                 //´ò¿ªÍâ²¿µÄ¸ßËÙ¾§Õñ£» 
	HSEStartUpStatus = RCC_WaitForHSEStartUp();                //µÈ´ýÍâ²¿¸ßËÙÊ±ÖÓ×¼±¸ºÃ
	if(HSEStartUpStatus == SUCCESS)
		{
			RCC_HCLKConfig(RCC_SYSCLK_Div1);                         //ÅäÖÃAHB
			RCC_PCLK2Config(RCC_HCLK_Div1);                          //ÅäÖÃAPB2 
			RCC_PCLK1Config(RCC_HCLK_Div2);                          //ÅäÖÃAPB1 
			//RCC_ADCCLKConfig(RCC_PCLK2_Div4);	      
			RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);     //PLL=8M*9=72M
			RCC_PLLCmd(ENABLE);                                      //Ê±ÄÜPLL
			while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);      //µÈ´ýPLL¾ÍÐ÷	      
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);               //ÅäÖÃÏµÍ³Ê±ÖÓ=PLL	  
			while(RCC_GetSYSCLKSource() != 0x08);                    //¼ì²éPLLÊ±ÖÓÊÇ·ñ×÷ÎªÏµÍ³Ê±ÖÓ	       
		}
}

void IWDG_Configuration(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //Ð´Èë0x5555£¬ÓÃÓÚÔÊÐí¼Ä´æÆ÷Ð´Èë¹¦ÄÜ£¬½â³ý¼Ä´æÆ÷±£»¤
	IWDG_SetPrescaler(IWDG_Prescaler_256);     //Ê±ÖÓ·ÖÆµ 40K/256=156HZ(6.4ms)
	IWDG_SetReload(1562);    //Î¹¹·Ê±¼ä1562*6.4ms=10s,ÊýÖµ²»ÄÜ´óÓÚ0xfff
	IWDG_ReloadCounter();   //Î¹¹·
	IWDG_Enable();    //Ê¹ÄÜ
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
	//Êý¾Ý´¦Àí
	OccSta=((DI_data[0])|(DI_data[1]))*10;
	ValveFb=(AI_Input[11]*10);
	DPValue=(AI_Input[3]*10);	
	CHWTemp=(u16)(RTDtemperature[2]*10);
	
	//ModbusÍ¨ÐÅµØÖ·Æ¥Åä
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
	
	usRegHoldingBuf[18]=(u16*)&ScheduleComm;     //¶ÁÈ¡ScheduleÃüÁî
	usRegHoldingBuf[19]=(u16*)&PDVComm;					 //StartStopÃüÁî,Ö±½ÓÆôÍ££¬²»¹ÜÓÐÃ»ScheduleºÍE-booking
	
	usRegHoldingBuf[20]=(u16*)&ValveCmd;							// 14, ·§½ô¼±È«¿ªÃüÁî£¬²»Ö´ÐÐ¿ØÖÆÂß¼­
	usRegHoldingBuf[21]=(u16*)&ERVCmd;							  // 15; ERV½ô¼±È«¿ªÃüÁî£¬²»Ö´ÐÐ¿ØÖÆÂß¼­
	usRegHoldingBuf[22]=(u16*)&ERVState;							// 16; ERV×´Ì¬·´À¡£¬0Îª¹Ø£¬1ÎªÈ«¿ª£¬ÆäÓàÊýÖµÎª¿ª¶È2-100

	usRegHoldingBuf[23]=(u16*)&PurgeCmd;							// 17; Purge¿ª¹ØÃüÁî£¬0Îª¹Ø£¬1ÎªÈ«¿ª£»¿ª³ÖÐø10·ÖÖÓ
	usRegHoldingBuf[24]=(u16*)&TempSPSet_Unocc;				// 18; ÎÞÈËÄ£Ê½ÏÂÎÂ¶ÈÉè¶¨Öµ	 
	usRegHoldingBuf[25]=(u16*)&SpareSet1;							// 19; ±¸ÓÃ²ÎÊýÉèÖÃ1£¬0-100
	usRegHoldingBuf[32]=(u16*)&SpareSet2;							// 20; ±¸ÓÃ²ÎÊýÉèÖÃ2£¬0-100
	usRegHoldingBuf[33]=(u16*)&SpareSet3;							// 21; ±¸ÓÃ²ÎÊýÉèÖÃ3£¬0-100
}

void  normal(void)
{
		//RunStatusÎªÏµÍ³ÔËÐÐ×´Ì¬±êÖ¾Î»£¬RunStatus--0:ÏµÍ³Î´ÔËÐÐ£¬RunStatus--1£ºÏµÍ³Õý³£ÔËÐÐ
		if(!RunStatus&&(IBSCommand||ScheduleComm||PDVComm))      //ÊÕµ½Booking»òÕßScheduleÃüÁîÆô¶¯ÏµÍ³
		{
						//ÏµÍ³Æô¶¯¹ý³ÌÖÐ£¬ÅÐ¶ÏÊÇ·ñÇ¿ÖÆ¿ª·§
			if(ValveCmd!=0)
			{
				if(ValveCmd>100)
					ValveCmd=100;
				if(ValveCmd<1)
					ValveCmd=0;
				APortOut(CHWV,ValveCmd/10.0);
				APortOut(PTBFan1,8.0);		//¿ªptb·çÉÈ
				APortOut(PTBFan2,8.0);		//¿ªptb·çÉÈ
				ForceValveFlag=1;
				return;
			}
			else if(ValveCmd==0&&ForceValveFlag==1)
			{
				APortOut(CHWV,0.0);
				APortOut(PTBFan1,0.0);		//¿ªptb·çÉÈ
				APortOut(PTBFan2,0.0);		//¿ªptb·çÉÈ
				ForceValveFlag=0;
			}
			else if(ValveCmd==0&&ForceValveFlag==0)
			{
				AlarmFlag=NSLH_Start();              					//ÏµÍ³Æô¶¯£¬Ë®·§¿ª40%
			}
			
			if(AlarmFlag!=0)                              //Èç¹ûÏµÍ³Æô¶¯Òì³££¬¹Ø±ÕËùÓÐ¶Ë¿ÚÊä³öÐÅºÅ
				NSLH_Clear();
			RunStatus=1;
		}
		
		//ÏµÍ³ÕýÔÚÔËÐÐ¹ý³ÌÖÐ£¬ÊÕµ½Ç¿ÖÆ¿ª·§ÃüÁî
		if(RunStatus&&(ValveCmd!=0))
		{
			if(ValveCmd>100)
				ValveCmd=100;
			if(ValveCmd<1)
				ValveCmd=0;
			APortOut(CHWV,ValveCmd/10.0);
			APortOut(PTBFan1,8.0);		//¿ªptb·çÉÈ
			APortOut(PTBFan2,8.0);		//¿ªptb·çÉÈ
			ForceValveFlag=1;
		}
		
		//ÏµÍ³ÔËÐÐÊ±£¬ÊÕµ½E-booking»òÕßSchedule¹ØÏµÍ³Ö¸ÁîÊ±£¬¹Ø±ÕÏµÍ³
		if(RunStatus&&((!IBSCommand)&&(!ScheduleComm)&&(!PDVComm)))
		{
						if(ForceValveFlag==1&&(ValveCmd!=0))
			{
				if(ValveCmd>100)
					ValveCmd=100;
				if(ValveCmd<1)
					ValveCmd=0;
				APortOut(CHWV,ValveCmd/10.0);
				APortOut(PTBFan1,8.0);		//¿ªptb·çÉÈ
				APortOut(PTBFan2,8.0);		//¿ªptb·çÉÈ
				ForceValveFlag=1;
				return;
			}
			else if(ValveCmd==0&&ForceValveFlag==1)
			{
				APortOut(CHWV,0.0);
				APortOut(PTBFan1,0.0);		//¹Øptb·çÉÈ
				APortOut(PTBFan2,0.0);		//¹Øptb·çÉÈ
				ForceValveFlag=0;
			}
			else if(ValveCmd==0&&ForceValveFlag==0)
			{
				AlarmFlag=NSLH_Stop();                      //¹Ø±ÕÏµÍ³
			}
			
			if(AlarmFlag!=0)
			{
				NSLH_Clear();                             //Èç¹ûÏµÍ³Òì³££¬¹Ø±ÕËùÓÐ¶Ë¿Ú
			}
			RunStatus=0;
		}
		
				//ÔÚÏµÍ³Õý³£ÔËÐÐ×´Ì¬ÏÂ£¬Motion Sensor¼ì²âµ½ÓÐÈË½øÈë·¿¼ä
		if(RunStatus&&OccSta&&(ForceValveFlag==0))
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
			
			if(RoomTempSv==250)
			{
				RoomTempSv=230;
			}
			
			if(!DataFlag)
			{
				AlarmFlag=OccupanyMode();     //Ö´ÐÐÓÐÈËÇé¿öÏÂ¿ØÖÆ²Ù×÷
				if(AlarmFlag!=0)              //Èç¹ûÏµÍ³Òì³££¬Ôò¹Ø±ÕÈ«²¿¶Ë¿ÚÐÅÏ¢
				{
					NSLH_Clear();
				}
			}
		}
		
				//ÔÚÏµÍ³Õý³£ÔËÐÐ×´Ì¬ÏÂ£¬Motion Sensor¼ì²âµ½·¿¼äÎÞÈË×´Ì¬ÏÂ
		if(RunStatus&&(!OccSta)&&(ForceValveFlag==0))
		{
			RoomTempSv=250;              //ÎÞÈË×´¿öÏÂ£¬·¿¼äÎÂ¶ÈÉè¶¨ÖµÎª27¶È£¬±£³Ö²»±ä
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
				AlarmFlag=Unoccupanied();    //Ö´ÐÐÎÞÈËÄ£Ê½ÏÂ£¬ÎÂ¶È¿ØÖÆ²Ù×÷£¬ÎÂ¶ÈÉè¶¨ÖµÎª27¶È£¬PIDµ÷½ÚË®·§
				if(AlarmFlag!=0)
				{
					NSLH_Clear();
				}
			}
		}
}

