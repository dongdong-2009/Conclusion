#include "stm32f10x.h"
#include <stdio.h>
#include "mb.h"
#include "mbutils.h"
#include "mbReg.h"
#include "sysconfig.h"

u8 mode=MODE_VOLTAGE;
unsigned char DiMap;

//AI�˿�����
float advalue[7]={0};

//����Ĵ�������
uint16_t usRegInputBuf[REG_INPUT_NREGS] = {0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007};
//����Ĵ�����ʼ��ַ
uint16_t usRegInputStart = REG_INPUT_START;

//���ּĴ�������
uint16_t *usRegHoldingBuf[REG_HOLDING_NREGS];
//���ּĴ�����ʼ��ַ
uint16_t usRegHoldingStart = REG_HOLDING_START;

//��Ȧ״̬����λ�������޸�
uint8_t ucRegCoilsBuf[REG_COILS_SIZE / 8] = {0x00,0x02};  
//��������״̬������λ����ȡ
uint8_t ucRegDiscreteBuf[REG_DISCRETE_SIZE / 8] = {0x01,0x02};


int main(void)
{
	RCC_Configuration();
	NVIC_Configuration();
	delay_init();
	ADC1_GPIO_Config();
  ADC1_Mode_Config();
	DioCfg();
	LedInit();
	SPI_Flash_Init();
	DAC7554_GPIO_Config();
	UsartConfigure();
	Tim2Configure();
	IWDG_Configuration();
	
	PWM1_Init(100);                     //����PWM1�������100*100us           
	PWM1_SetHighTime(70);               //����PWM1����ߵ�ƽʱ��Ϊ70*100us 
	
	PWM2_Init(100);                     //����PWM2�������100*100us  
	PWM2_SetHighTime(30);               //����PWM2����ߵ�ƽʱ��Ϊ30*100us 
	
	
	//��ʼ�� RTUģʽ �ӻ���ַΪ1 USART1 ������9600 ��У��
	eMBInit(MB_RTU, 0x01, 0x01, 9600, MB_PAR_NONE);
	//����FreeModbus 
	eMBEnable(); 
	RegMap();     //Modbusͨ�Ų���ӳ���
	while (1)
	{
		IWDG_ReloadCounter();         //ι��  10s
		//FreeMODBUS���ϲ�ѯ
		eMBPoll(); 
		
		LED=0;
		
		//AO Test
		SetAoOut(9,1,mode);  
		SetAoOut(8,2,mode);
		SetAoOut(7,3,mode);
		SetAoOut(6,4,mode);
		
		//AI Test
		for(int i=0;i<=6;i++)
		{
			advalue[i]=ReadAdOfChannel(i,mode);
		}
		
		//DO Test
		SetSpdtState(1,SpdtOFF);SetSpdtState(3,SpdtOFF);
		SetSpdtState(2,SpdtON); SetSpdtState(4,SpdtON); 
		
		//DI Test
		DiMap=GetDiMap(); 
		
		delay_ms(500);
		LED=1;
			
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

void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//�����ж�������λ�ú�ƫ����  
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);    //������λ��FLASH�����������ַ��ƫ����Ϊ0 
	
	//�������ȼ����飺��ռ���ȼ��ʹ����ȼ���
	//������������ȼ�����λ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  //��ռ���ȼ�4λ�������ȼ�0λ
  	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;          //USART1�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;          //USART1�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
}

void LedInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE  , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void RegMap(void)
{
	usRegHoldingBuf[0] = &AI1;
	usRegHoldingBuf[1] = &AI2;
	usRegHoldingBuf[2] = &AI3;
	usRegHoldingBuf[3] = &AI4;
	usRegHoldingBuf[4] = &AI5;
	usRegHoldingBuf[5] = &AI6;
	usRegHoldingBuf[6] = &DI1;
	usRegHoldingBuf[7] = &DI2;
	usRegHoldingBuf[8] = &DI3;
	usRegHoldingBuf[9] = &DI4;
	usRegHoldingBuf[10] = &AO1;
	usRegHoldingBuf[11] = &AO2;
	usRegHoldingBuf[12] = &AO3;
	usRegHoldingBuf[13] = &AO4;
	usRegHoldingBuf[14] = &DO1;
	usRegHoldingBuf[15] = &DO2;
	usRegHoldingBuf[16] = &DO3;
	usRegHoldingBuf[17] = &DO4;
	usRegHoldingBuf[18] = &PWM1_cyc;
	usRegHoldingBuf[19] = &PWM1_duty;
	usRegHoldingBuf[20] = &PWM2_cyc;
	usRegHoldingBuf[21] = &PWM2_duty;
	usRegHoldingBuf[22] = &StartCmd;
	usRegHoldingBuf[23] = &StopCmd;
	usRegHoldingBuf[24] = &SetValue;
}
