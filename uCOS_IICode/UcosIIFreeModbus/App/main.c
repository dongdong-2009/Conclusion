#include "ucos_ii.h"
#include "mb.h"
#include "mbutils.h"
#include "mbReg.h"

u16 temp=0;
void RegMap(void);

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
	//��ʼ�� RTUģʽ �ӻ���ַΪ1 USART1 ������9600 ��У��
	eMBInit(MB_RTU, 0x01, 0x01, 9600, MB_PAR_NONE);
	//����FreeModbus 
	eMBEnable(); 
	RegMap();
	/* 1��OS��ʼ�� */
  OSInit();
	  /* 2���������� */
  OSTaskCreateExt((void (*)(void *)) AppTaskStart,
                  (void           *) 0,
                  (OS_STK         *)&TaskStartStk[TASK_START_STK_SIZE - 1],
                  (INT8U           ) TASK_START_PRIO,
                  (INT16U          ) TASK_START_PRIO,
                  (OS_STK         *)&TaskStartStk[0],
                  (INT32U          ) TASK_START_STK_SIZE,
                  (void           *) 0,
                  (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

  /* 3���������� */
  OSStart();
									
	return 0;	
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


void RegMap(void)
{
	usRegHoldingBuf[0] = &temp;
}
