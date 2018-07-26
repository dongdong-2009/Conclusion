#include "mb.h"
#include "mbutils.h"
#include "mbReg.h"
#include "sysconfig.h"

//����Ĵ�������
uint16_t usRegInputBuf[REG_INPUT_NREGS] = {0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007};
//����Ĵ�����ʼ��ַ
uint16_t usRegInputStart = REG_INPUT_START;

//���ּĴ�������
uint16_t *usRegHoldingBuf[REG_HOLDING_NREGS]={0};
//���ּĴ�����ʼ��ַ
uint16_t usRegHoldingStart = REG_HOLDING_START;

//��Ȧ״̬����λ�������޸�
uint8_t ucRegCoilsBuf[REG_COILS_SIZE / 8] = {0x00,0x02};  
//��������״̬������λ����ȡ
uint8_t ucRegDiscreteBuf[REG_DISCRETE_SIZE / 8] = {0x01,0x02};


//������ر���
float dataTemp[12];
float RTDtemperature[4];
float AI_Input[12]={0};
u8   	DI_data[8]={0};
u8 DataFlag=0;

int main(void)
{
 	RCC_Configuration();            //ϵͳʱ��������Ϣ
	IO_Configuration();             //DI and DO ��ʼ��
	ADC_init();                     //AI��ʼ��
	DAC_init();                     //AO��ʼ��
	RTD_init();                     //���³�ʼ��
	Usart_Total_Initi();            //���ڳ�ʼ��
	Tim2Configure();               	//��ʱ������С��ͨ������
	Tim4Configure();               	//��ʱ��4��ʱ15s����ʱ����PID control algorithm,ʱ������15s
	InitialSys();
	IWDG_Configuration();
	RegMap();
	
	//��ʼ�� RTUģʽ �ӻ���ַΪ1 USART1 ������19200 ��У��
	eMBInit(MB_RTU, 0x65, 0x01, 19200, MB_PAR_NONE);
	//����FreeModbus 
	eMBEnable(); 
	while (1)
	{
		IWDG_ReloadCounter();         //ι��  10s
		//FreeMODBUS���ϲ�ѯ
		eMBPoll(); 
		
		//14��������ȫ�������ִ�������¶ȿ����߼�
		if(ValveCmd!=0&&ForceValveFlag==0)
		{
			if(ValveCmd>100)
				ValveCmd=100;
			if(ValveCmd<1)
				ValveCmd=0;
			APortOut(CHWV,ValveCmd/10.0);
			APortOut(PTBFan1,8.0);		//��ptb����
			APortOut(PTBFan2,8.0);		//��ptb����
			ForceValveFlag=1;
		}
		else if(ValveCmd==0&&ForceValveFlag==1)
		{
			APortOut(CHWV,0.0);
			APortOut(PTBFan1,0.0);		//��ptb����
			APortOut(PTBFan2,0.0);		//��ptb����
			ForceValveFlag=0;
		}
		else if(ValveCmd!=0&&ForceValveFlag==1)
		{
			if(ValveCmd>100)
				ValveCmd=100;
			if(ValveCmd<1)
				ValveCmd=0;
			APortOut(CHWV,ValveCmd/10.0);
			APortOut(PTBFan1,8.0);		//��ptb����
			APortOut(PTBFan2,8.0);		//��ptb����
			ForceValveFlag=1;
		}
		
				//����ERVǿ������������ܵ�ǰERV����ʲô״̬������Ҫ����ERV
		if(ERVCmd!=0)
		{
			DPortOut(ERVFan,1);
			ERVState=1;
			ERVFlag=1;
		}
		if(ERVCmd==0&&ERVFlag==1)   //��ERVǿ��������ERVCmd����Ϊ0�����ر�ERVͨ��
		{
			DPortOut(ERVFan,0);
			ERVState=0;
			ERVFlag=0;
		}
		
		//û��ERVǿ�����ͬʱ���ڷ�ǿ��ģʽ������CO2Ũ�Ƚ��п���
		if(ERVCmd==0&&ERVFlag==0)
		{
			CO2Control();//�ǽ������������У�CO2�����߼
		}
		
		normal();
	}
}

/**
* @brief ���ּĴ��������������ּĴ����ɶ���д
* @param pucRegBuffer ������ʱ--��������ָ��,д����ʱ--��������ָ��
* usAddress �Ĵ�����ʼ��ַ
* usNRegs �Ĵ�������
* eMode ������ʽ,������д
* @retval eStatus �Ĵ���״̬
*/
eMBErrorCode 	eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
	//����״̬
	eMBErrorCode eStatus = MB_ENOERR;
	//ƫ����
	int16_t iRegIndex;

	//�жϼĴ����ǲ����ڷ�Χ��
	if( ( (int16_t)usAddress >= REG_HOLDING_START )&&( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
	{
		//����ƫ����
		iRegIndex = ( int16_t )( usAddress - REG_HOLDING_START);
		switch ( eMode )
		{
			//�������� 
			case MB_REG_READ:
				while( usNRegs > 0 )
				{
					*pucRegBuffer++ = ( uint8_t )( *usRegHoldingBuf[iRegIndex] >> 8 );
					*pucRegBuffer++ = ( uint8_t )( *usRegHoldingBuf[iRegIndex] & 0xFF );
					iRegIndex++;
					usNRegs--;
				}
				break;

			//д������ 
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
		//���ش���״̬
		eStatus = MB_ENOREG;
	}
	return eStatus;
}

/**
* @brief ����Ĵ���������,����Ĵ����ɶ�,������д
* @param pucRegBuffer ��������ָ��
* usAddress �Ĵ�����ʼ��ַ
* usNRegs �Ĵ�������
* @retval eStatus �Ĵ���״̬
*/
eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
	eMBErrorCode eStatus = MB_ENOERR;
	int16_t iRegIndex;

	//��ѯ�Ƿ��ڼĴ�����Χ��
	//Ϊ�˱��⾯��,�޸�Ϊ�з�������
	if( ( (int16_t)usAddress >= REG_INPUT_START )&& ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
	{
		//��ȡ����ƫ����,���β�����ʼ��ַ-����Ĵ����ĳ�ʼ��ַ
		iRegIndex = ( int16_t )( usAddress - REG_INPUT_START );
		//�����ֵ
		while( usNRegs > 0 )
		{
			//��ֵ���ֽ�
			*pucRegBuffer++ = ( uint8_t )( usRegInputBuf[iRegIndex] >> 8 );
			//��ֵ���ֽ�
			*pucRegBuffer++ = ( uint8_t )( usRegInputBuf[iRegIndex] & 0xFF );
			//ƫ��������
			iRegIndex++;
			//�������Ĵ���������1
			usNRegs--;
		}
	}
	else
	{
		//���ش���״̬,�޼Ĵ��� 
		eStatus = MB_ENOREG;
	}
	return eStatus;
}

/**
* @brief ��Ȧ�Ĵ���������,��Ȧ�Ĵ����ɶ���д
* @param pucRegBuffer ������---��������ָ��,д����--��������ָ��
* usAddress �Ĵ�����ʼ��ַ
* usNRegs �Ĵ�������
* eMode ������ʽ,������д
* @retval eStatus �Ĵ���״̬
*/
eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,eMBRegisterMode eMode )
{
	//����״̬
	eMBErrorCode eStatus = MB_ENOERR;
	//�Ĵ�������
	int16_t iNCoils = ( int16_t )usNCoils;
	//�Ĵ���ƫ����
	int16_t usBitOffset;

	//���Ĵ����Ƿ���ָ����Χ��
	if( ( (int16_t)usAddress >= REG_COILS_START ) &&( usAddress + usNCoils <= REG_COILS_START + REG_COILS_SIZE ) )
	{
		//����Ĵ���ƫ����
		usBitOffset = ( int16_t )( usAddress - REG_COILS_START );
		switch ( eMode )
		{
			//������
			case MB_REG_READ:
			while( iNCoils > 0 )	
			{
				*pucRegBuffer++ = xMBUtilGetBits( ucRegCoilsBuf, usBitOffset,( uint8_t )( iNCoils > 8 ? 8 : iNCoils ) );
				iNCoils -= 8;
				usBitOffset += 8;
			}
			break;

			//д����
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
* @brief ��������Ĵ���������,��������Ĵ���,�ɶ�
* @param pucRegBuffer ������---��������ָ��
* usAddress �Ĵ�����ʼ��ַ
* usNRegs �Ĵ�������
* @retval eStatus �Ĵ���״̬
*/
eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
	//����״̬
	eMBErrorCode eStatus = MB_ENOERR;
	//�����Ĵ�������
	int16_t iNDiscrete = ( int16_t )usNDiscrete;
	//ƫ����
	uint16_t usBitOffset;

	//�жϼĴ����Ƿ���ָ���ķ�Χ
	if( ( (int16_t)usAddress >= REG_DISCRETE_START ) &&( usAddress + usNDiscrete <= REG_DISCRETE_START + REG_DISCRETE_SIZE ) )
	{
		//���ƫ����
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
	ErrorStatus HSEStartUpStatus;                              //�����ⲿ���پ�������״̬ö�ٱ�����
	RCC_DeInit();                                              //��λRCC�Ĵ�����Ĭ��ֵ��
	RCC_HSEConfig(RCC_HSE_ON);                                 //���ⲿ�ĸ��پ��� 
	HSEStartUpStatus = RCC_WaitForHSEStartUp();                //�ȴ��ⲿ����ʱ��׼����
	if(HSEStartUpStatus == SUCCESS)
		{
			RCC_HCLKConfig(RCC_SYSCLK_Div1);                         //����AHB
			RCC_PCLK2Config(RCC_HCLK_Div1);                          //����APB2 
			RCC_PCLK1Config(RCC_HCLK_Div2);                          //����APB1 
			//RCC_ADCCLKConfig(RCC_PCLK2_Div4);	      
			RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);     //PLL=8M*9=72M
			RCC_PLLCmd(ENABLE);                                      //ʱ��PLL
			while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);      //�ȴ�PLL����	      
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);               //����ϵͳʱ��=PLL	  
			while(RCC_GetSYSCLKSource() != 0x08);                    //���PLLʱ���Ƿ���Ϊϵͳʱ��	       
		}
}

void IWDG_Configuration(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //д��0x5555����������Ĵ���д�빦�ܣ�����Ĵ�������
	IWDG_SetPrescaler(IWDG_Prescaler_256);     //ʱ�ӷ�Ƶ 40K/256=156HZ(6.4ms)
	IWDG_SetReload(1562);    //ι��ʱ��1562*6.4ms=10s,��ֵ���ܴ���0xfff
	IWDG_ReloadCounter();   //ι��
	IWDG_Enable();    //ʹ��
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
	//���ݴ���
	OccSta=((DI_data[0])|(DI_data[1]))*10;
	ValveFb=(AI_Input[11]*10);
	DPValue=(AI_Input[3]*10);	
	CHWTemp=(u16)(RTDtemperature[2]*10);
	
	//Modbusͨ�ŵ�ַƥ��
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
	
	usRegHoldingBuf[18]=(u16*)&ScheduleComm;     //��ȡSchedule����
	usRegHoldingBuf[19]=(u16*)&PDVComm;					 //StartStop����,ֱ����ͣ��������ûSchedule��E-booking
	
	usRegHoldingBuf[20]=(u16*)&ValveCmd;							// 14, ������ȫ�������ִ�п����߼�
	usRegHoldingBuf[21]=(u16*)&ERVCmd;							  // 15; ERV����ȫ�������ִ�п����߼�
	usRegHoldingBuf[22]=(u16*)&ERVState;							// 16; ERV״̬������0Ϊ�أ�1Ϊȫ����������ֵΪ����2-100

	usRegHoldingBuf[23]=(u16*)&PurgeCmd;							// 17; Purge�������0Ϊ�أ�1Ϊȫ����������10����
	usRegHoldingBuf[24]=(u16*)&TempSPSet_Unocc;				// 18; ����ģʽ���¶��趨ֵ	 
	usRegHoldingBuf[25]=(u16*)&SpareSet1;							// 19; ���ò�������1��0-100
	usRegHoldingBuf[32]=(u16*)&SpareSet2;							// 20; ���ò�������2��0-100
	usRegHoldingBuf[33]=(u16*)&SpareSet3;							// 21; ���ò�������3��0-100
}

void  normal(void)
{
		//RunStatusΪϵͳ����״̬��־λ��RunStatus--0:ϵͳδ���У�RunStatus--1��ϵͳ��������
		if(!RunStatus&&(IBSCommand||ScheduleComm||PDVComm))      //�յ�Booking����Schedule��������ϵͳ
		{
						//ϵͳ���������У��ж��Ƿ�ǿ�ƿ���
			if(ValveCmd!=0)
			{
				if(ValveCmd>100)
					ValveCmd=100;
				if(ValveCmd<1)
					ValveCmd=0;
				APortOut(CHWV,ValveCmd/10.0);
				APortOut(PTBFan1,8.0);		//��ptb����
				APortOut(PTBFan2,8.0);		//��ptb����
				ForceValveFlag=1;
				return;
			}
			else if(ValveCmd==0&&ForceValveFlag==1)
			{
				APortOut(CHWV,0.0);
				APortOut(PTBFan1,0.0);		//��ptb����
				APortOut(PTBFan2,0.0);		//��ptb����
				ForceValveFlag=0;
			}
			else if(ValveCmd==0&&ForceValveFlag==0)
			{
				AlarmFlag=NSLH_Start();              					//ϵͳ������ˮ����40%
			}
			
			if(AlarmFlag!=0)                              //���ϵͳ�����쳣���ر����ж˿�����ź�
				NSLH_Clear();
			RunStatus=1;
		}
		
		//ϵͳ�������й����У��յ�ǿ�ƿ�������
		if(RunStatus&&(ValveCmd!=0))
		{
			if(ValveCmd>100)
				ValveCmd=100;
			if(ValveCmd<1)
				ValveCmd=0;
			APortOut(CHWV,ValveCmd/10.0);
			APortOut(PTBFan1,8.0);		//��ptb����
			APortOut(PTBFan2,8.0);		//��ptb����
			ForceValveFlag=1;
		}
		
		//ϵͳ����ʱ���յ�E-booking����Schedule��ϵͳָ��ʱ���ر�ϵͳ
		if(RunStatus&&((!IBSCommand)&&(!ScheduleComm)&&(!PDVComm)))
		{
						if(ForceValveFlag==1&&(ValveCmd!=0))
			{
				if(ValveCmd>100)
					ValveCmd=100;
				if(ValveCmd<1)
					ValveCmd=0;
				APortOut(CHWV,ValveCmd/10.0);
				APortOut(PTBFan1,8.0);		//��ptb����
				APortOut(PTBFan2,8.0);		//��ptb����
				ForceValveFlag=1;
				return;
			}
			else if(ValveCmd==0&&ForceValveFlag==1)
			{
				APortOut(CHWV,0.0);
				APortOut(PTBFan1,0.0);		//��ptb����
				APortOut(PTBFan2,0.0);		//��ptb����
				ForceValveFlag=0;
			}
			else if(ValveCmd==0&&ForceValveFlag==0)
			{
				AlarmFlag=NSLH_Stop();                      //�ر�ϵͳ
			}
			
			if(AlarmFlag!=0)
			{
				NSLH_Clear();                             //���ϵͳ�쳣���ر����ж˿�
			}
			RunStatus=0;
		}
		
				//��ϵͳ��������״̬�£�Motion Sensor��⵽���˽��뷿��
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
				AlarmFlag=OccupanyMode();     //ִ����������¿��Ʋ���
				if(AlarmFlag!=0)              //���ϵͳ�쳣����ر�ȫ���˿���Ϣ
				{
					NSLH_Clear();
				}
			}
		}
		
				//��ϵͳ��������״̬�£�Motion Sensor��⵽��������״̬��
		if(RunStatus&&(!OccSta)&&(ForceValveFlag==0))
		{
			RoomTempSv=250;              //����״���£������¶��趨ֵΪ27�ȣ����ֲ���
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
				AlarmFlag=Unoccupanied();    //ִ������ģʽ�£��¶ȿ��Ʋ������¶��趨ֵΪ27�ȣ�PID����ˮ��
				if(AlarmFlag!=0)
				{
					NSLH_Clear();
				}
			}
		}
}

