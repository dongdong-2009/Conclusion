#include "mb_core.h"
#include "mb_config.h"
#include "mb_crc.h"
#include "mb_port.h"
#include "mb_app.h"
#include "stm32f10x.h"
#include "usart.h"
#include "timer.h"
#include "stdio.h"
#include "stdlib.h"

static MB_EventType_t eQueuedEvent;
static BOOL     MB_EventMutex;		         //�¼�����������һ���źŷ��ͺ������û�еõ�������ô�������ٴη����ź�

unsigned char  MB_ADD=0x01;					       //�ӻ���ַ  Slave-ID
unsigned short REG_HOLDING_START=0;			   //���ּĴ�����ʼ��ַ
unsigned short REG_HOLDING_NREGS=8;			   //���ּĴ�������
unsigned short REG_INPUT_START=0;          //����Ĵ�����ʼ��ַ
unsigned short REG_INPUT_NREGS=8;				   //�Ĵ������ö�̬����

unsigned char  M_SendBuff[M_SendBuffLen];  //�������ͻ�����
unsigned short M_SendCnt=0;                //�������ͼ���
unsigned short M_SendLen=0;                //���������ֽڳ���

unsigned char  M_ReceiveBuff[M_ReceiveBuffLen];    //�������ջ�����
unsigned short M_ReceiveCnt=0;                     //���������ֽڳ���

unsigned char  S_SendBuff[S_SendBuffLen];          //�ӻ����ͻ�����
unsigned short S_SendCnt=0;                        //�ӻ����ͼ���
unsigned short S_SendLen=0;                        //�ӻ������ֽڳ���

unsigned char  S_ReceiveBuff[S_ReceiveBuffLen];    //�ӻ����ջ���
unsigned short S_ReceiveCnt=0;                     //�ӻ������ֽڳ���

unsigned short *usRegHoldingBuf;                   //���ּĴ���������
unsigned short *usRegInputBuf;                     //����Ĵ���������

mb_pro_t mb_pro_m;                                //������Ϣ�ṹ��
mb_pro_t mb_pro_s;                                //�ӻ���Ϣ�ṹ��
unsigned long usTimerT35_50us;                    //���ͼ����

unsigned char MB_EventInit( void )
{
	MB_EventMutex = FALSE;		//�¼���
  return TRUE;
}

//״̬�л�
unsigned char MB_EventPost( MB_EventType_t eEvent )
{
	MB_EventMutex = TRUE;
  eQueuedEvent = eEvent;
  return TRUE;
}

//��ȡ�¼�״̬
unsigned char MB_EventGet( MB_EventType_t * eEvent )
{
	BOOL  xEventHappened = FALSE;
	if( MB_EventMutex )              //���ͻ�����
  {
		*eEvent = eQueuedEvent;
    MB_EventMutex = FALSE;
    xEventHappened = TRUE;
  }
  return xEventHappened;
}

MB_EventType_t MB_EventState()
{
	return eQueuedEvent;
}

//��������Ĵ����ͱ��ּĴ����洢�ռ�
void MB_RegInit()
{
	usRegHoldingBuf=malloc(REG_HOLDING_NREGS*sizeof(unsigned short));  //����REG_HOLDING_NREGS��unsigned short�ʹ洢���ͣ������׵�ַ�洢��ָ�����usRegHoldingBuf
	usRegInputBuf=malloc(REG_INPUT_NREGS*sizeof(unsigned short));
}

//���ݲ�������ȷ��Modbus���ʱ��
void MB_Init(unsigned long ulBaudRate)
{
	/* Modbus RTU uses 8 Databits. */
  USART_Configuration(USART2, ulBaudRate);

	/* If baudrate > 19200 then we should use the fixed timer values
	 * t35 = 1750us. Otherwise t35 must be 3.5 times the character time.
	 */
	if( ulBaudRate > 19200 )
	{
		usTimerT35_50us = 35;       /* 1800us. */
	}
	else
	{
		/* The timer reload value for a character is given by:
		 *
		 * ChTimeValue = Ticks_per_1s / ( Baudrate / 11 )
		 *             = 11 * Ticks_per_1s / Baudrate
		 *             = 220000 / Baudrate
		 * The reload for t3.5 is 1.5 times this value and similary
		 * for t3.5.
		 */
		usTimerT35_50us = ( 7UL * 220000UL ) / ( 2UL * ulBaudRate );
	}
	TIM3_Int_Init(usTimerT35_50us,3600);
}

void MB_Poll()
{
	MB_EventType_t eEvent;

	if( MB_EventGet( &eEvent ) == TRUE )
	{
		switch(eEvent)
		{
			case EV_IDLE:
				break;
			
			case EV_M_SEND:						  //����״̬����
				//			mb_ms_SendData(&gb_mb_pro);
				//			MB_EventPost(EV_M_WAIT);
				USART_IRQSet(1,0);
				break;
			
			case EV_M_WAIT:						  //�ȴ����գ�ͬʱУ��ȴ���ʱ
				break;
			
			case EV_M_RECEIVEING:				//���ڽ��գ�ͬʱУ����ɳ�ʱ
				break;
			
			case EV_M_RECEIVED:					//�������
				//�˴��Խ��յ����ݽ��д���
				M_ReceiveCnt=0;					  //��ֵ��ʾ�������ݵĳ��ȣ������ݴ�����ɺ�ǵ����㣬��Ϊ��û�жԽ�������������ֱ������
				MB_EventPost(EV_IDLE);		//���մ�����ɣ�һ��Э��ͨѶ�������л���idle״̬
				break;
			
			case EV_S_RECEIVEING:				//�ӻ����ڽ��գ�ͬʱУ����ɳ�ʱ
				break;
			
			case EV_S_RECEIVED:					//�ӻ����ݽ������
				//�����ݽ��д���
				MB_S_Execute(S_ReceiveBuff,S_ReceiveCnt);
				S_ReceiveCnt=0;
				MB_EventPost(EV_S_SEND);	//������ɣ��л�������״̬������Ӧ
				break;
			
			case EV_S_SEND:
				USART_IRQSet(1,0);				//��ʼ���ͣ�������ɺ���Զ��л�������״̬
				break;
			
			default:
				break;
		}
	}
}

//�����������ݰ����
void MB_M_FormatData()
{
	unsigned short crcval=0;
	unsigned char *databuff=M_SendBuff+MB_DATA_INDEX;   //databuff����ʼ��ַ����M_SendBuff����ʼ��ַ��ƫ��MB_DATA_INDEXλ   databuff[0]=M_SendBuff[MB_DATA_INDEX];
	
	M_SendBuff[MB_ADDR_INDEX]=MB_ADD;                 //ID
	M_SendBuff[MB_FUNCID_INDEX]=mb_pro_m.funcid;      //Function Code

	switch(mb_pro_m.funcid)
	{
		case FUNCID_READHDREG:                                   //������0x03
		{
			databuff[0]=((unsigned short)mb_pro_m.startadd)>>8;    //��ַ��λ
			databuff[1]=(unsigned short)mb_pro_m.startadd;         //��ַ��λ
			databuff[2]=((unsigned short)mb_pro_m.regN)>>8;        //������λ
			databuff[3]=(unsigned short)mb_pro_m.regN;             //������λ

			crcval=usMBCRC16((unsigned char *)M_SendBuff,6);       //����CRCУ����
			databuff[4]=( unsigned char )( crcval & 0xFF );        //У�����λ
			databuff[5]=( unsigned char )( crcval >> 8 );          //У�����λ
			M_SendLen=8;                                           //�������ݳ���Ϊ8
			M_SendCnt=0;
			break;
		}
		
		case FUNCID_READIPREG:                                     	//������Ĵ���
		{
			databuff[0]=((unsigned short)mb_pro_m.startadd)>>8;       //��ʼ��ַ��λ
			databuff[1]=(unsigned short)mb_pro_m.startadd;            //��ʼ��ַ��λ
			databuff[2]=((unsigned short)mb_pro_m.regN)>>8;           //�Ĵ���������λ
			databuff[3]=(unsigned short)mb_pro_m.regN;                //�Ĵ���������λ

			crcval=usMBCRC16((unsigned char *)M_SendBuff,6);          //����CRCУ����
			databuff[4]=( unsigned char )( crcval & 0xFF );           //CRCУ�����λ
			databuff[5]=( unsigned char )( crcval >> 8 );             //CRCУ�����λ
			M_SendLen=8;                                              //�������ݳ���
			M_SendCnt=0;
			break;
		}
	
		case FUNCID_WROHDREG:                                       //������0x06
		{
			databuff[0]=((unsigned short)mb_pro_m.startadd)>>8;       //��ʼ��ַ��λ
			databuff[1]=(unsigned short)mb_pro_m.startadd;            //��ʼ��ַ��λ
			databuff[2]=mb_pro_m.databuff[0];                         //���ݸ�λ
			databuff[3]=mb_pro_m.databuff[1];                         //���ݵ�λ

			crcval=usMBCRC16((unsigned char *)M_SendBuff,6);          //����CRCУ����
			databuff[4]=( unsigned char )( crcval & 0xFF );           //CRCУ�����λ
			databuff[5]=( unsigned char )( crcval >> 8 );             //CRCУ�����λ
			M_SendLen=8; 																							//�������ݳ���
			M_SendCnt=0;
			break;
		}
		case FUNCID_WRNHDREG:                                       //������0x10
		{
			unsigned char i=0;
			databuff[0]=((unsigned short)mb_pro_m.startadd)>>8;       //��ʼ��ַ��λ
			databuff[1]=(unsigned short)mb_pro_m.startadd;            //��ʼ��ַ��λ

			databuff[2]=((unsigned short)mb_pro_m.regN)>>8;           //�Ĵ���������λ
			databuff[3]=(unsigned short)mb_pro_m.regN;                //�Ĵ���������λ

			databuff[4]=(unsigned short)mb_pro_m.regN*2;              //�����ֽ���Ŀ
			for(i=0;i<mb_pro_m.regN;i++)                              //ע���ֽ�˳��
			{
				databuff[5+i*2]=mb_pro_m.databuff[i*2+1];		            //���ݵ�λ       
				databuff[6+i*2]=mb_pro_m.databuff[i*2];                 //���ݸ�λ
			}

			crcval=usMBCRC16((uint8_t *)M_SendBuff,7+mb_pro_m.regN*2); //����CRCУ����
			databuff[5+mb_pro_m.regN*2]=( uint8_t )( crcval & 0xFF );  //CRCУ�����λ
			databuff[6+mb_pro_m.regN*2]=( uint8_t )( crcval >> 8 );    //CRCУ�����λ
			M_SendLen=9+mb_pro_m.regN*2;                               //���ݷ��ͳ���
			M_SendCnt=0;
			break;
		}
		default:
			break;
	}

}

//�ӻ����ݴ���
void MB_S_Execute(uint8_t *buff,uint16_t len)
{
	uint16_t crcval=0;
//	uint8_t mbId=buff[0];                //slave ID
	uint8_t func=buff[1];                //function Code

	uint16_t add=((unsigned short)buff[2]<<8)+buff[3]; //������ʼ��ַ

	S_SendBuff[0]=MB_ADD;                //�ӻ��������ݴӻ���ַ
	S_SendBuff[1]=func;                  //�ӻ��������ݹ�����

	switch(func)
	{
		case FUNCID_READHDREG:		//�����ּĴ���
		{
			unsigned short num=((unsigned short)buff[4]<<8)+buff[5];                       //�����ȡ�Ĵ�������
			if(add<REG_HOLDING_START||(add+num)>(REG_HOLDING_START+REG_HOLDING_NREGS))     //��ַ����
			{
				//���ʹ�����
			}
			else
			{
				//������Ӧ����
				mb_pro_s.funcid=func;
				mb_pro_s.startadd=add;
				mb_pro_s.regN=num;
				mb_pro_s.mode=1;
				mb_pro_s.databuff=S_SendBuff+3;                //��д��������
				S_SendBuff[2]=2*num;                           //�ֽ���
				eMBRegHoldingCB(&mb_pro_s);		                 //�˺�����������ݶ�
				crcval=usMBCRC16(S_SendBuff,3+2*num);
				S_SendBuff[3+2*num]=( unsigned char )( crcval & 0xFF );   //CRC��λ
				S_SendBuff[4+2*num]=( unsigned char )( crcval >> 8 );     //CRC��λ
				S_SendLen=5+2*num;                                        //���ͳ���
				S_SendCnt=0;
			 }
				break;
		 }
		
	case FUNCID_READIPREG:		//������Ĵ���
	{
		unsigned short num=((unsigned short)buff[4]<<8)+buff[5];
		if(add<REG_INPUT_START||(add+num)>(REG_INPUT_START+REG_INPUT_NREGS))
		{
			//���ʹ�����
		}
		else
		{
			//������Ӧ����
			mb_pro_s.funcid=func;
			mb_pro_s.startadd=add;
			mb_pro_s.regN=num;
			mb_pro_s.mode=1;
			mb_pro_s.databuff=S_SendBuff+3;
			S_SendBuff[2]=2*num;         //�ֽ���
			eMBRegInputCB(&mb_pro_s);		 //�˺�����������ݶ�
			crcval=usMBCRC16(S_SendBuff,3+2*num);
			S_SendBuff[3+2*num]=( unsigned char )( crcval & 0xFF );
			S_SendBuff[4+2*num]=( unsigned char )( crcval >> 8 );
			S_SendLen=5+2*num;
			S_SendCnt=0;
		 }
		 break;
	 }
	
	case FUNCID_WROHDREG:		//д�������ּĴ���
	{
		if(add<REG_HOLDING_START||add>(REG_HOLDING_START+REG_HOLDING_NREGS-1))
		{
			//���ʹ�����
		}
		else
		{
			//������Ӧ����
			mb_pro_s.funcid=func;
			mb_pro_s.startadd=add;
			mb_pro_s.regN=1;
			mb_pro_s.mode=2;
			mb_pro_s.databuff=buff+4;
			S_SendBuff[2]=buff[2];                      //��ʼ��ַ�ߵ�λ
			S_SendBuff[3]=buff[3];
			S_SendBuff[4]=buff[4];                      //�Ĵ��������ߵ�λ
			S_SendBuff[5]=buff[5];
			eMBRegHoldingCB(&mb_pro_s);
			crcval=usMBCRC16(S_SendBuff,6);
			S_SendBuff[6]=( unsigned char )( crcval & 0xFF );
			S_SendBuff[7]=( unsigned char )( crcval >> 8 );
			S_SendLen=8;
			S_SendCnt=0;
		}
		break;
	}
	
	case FUNCID_WRNHDREG:		//д������ּĴ���
	{
		unsigned short num=((unsigned short)buff[4]<<8)+buff[5];
		if(add<REG_HOLDING_START||add+num>(REG_HOLDING_START+REG_HOLDING_NREGS))
		{
			//���ʹ�����
		}
		else
		{
			//������Ӧ����
			mb_pro_s.funcid=func;
			mb_pro_s.startadd=add;
			mb_pro_s.regN=num;
			mb_pro_s.mode=2;
			S_SendBuff[2]=buff[2];                 //��ʼ��ַ�ߵ�λ
			S_SendBuff[3]=buff[3];
			S_SendBuff[4]=buff[4];                 //�Ĵ��������ߵ�λ
			S_SendBuff[5]=buff[5];
			mb_pro_s.databuff=buff+7;
			eMBRegHoldingCB(&mb_pro_s);
			crcval=usMBCRC16(S_SendBuff,6);
			S_SendBuff[6]=( unsigned char )( crcval & 0xFF );
			S_SendBuff[7]=( unsigned char )( crcval >> 8 );
			S_SendLen=8;
			S_SendCnt=0;
		}
		break;
	}
	
	default: break;
	}
}
