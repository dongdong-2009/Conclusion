#include "mb_app.h"
#include "mb_config.h"
#include "mb_core.h"
#include "mb_type.h"



void MB_M_app_demo(unsigned char *flag)
{
	MB_EventType_t sta=MB_EventState();

	switch(*flag)
	{
	case 0:
		break;
	case 1:								//�����ּĴ���
		if(sta!=EV_IDLE) break;

		mb_pro_m.funcid=FUNCID_READHDREG;
		mb_pro_m.startadd=REG_HOLDING_START;
		mb_pro_m.regN=2;
		MB_M_FormatData();
		MB_EventPost(EV_M_SEND);	//��ʼ����
		*flag=0;
		break;
	case 2:								//������Ĵ���
		if(sta!=EV_IDLE) break;

		mb_pro_m.funcid=FUNCID_READIPREG;
		mb_pro_m.startadd=REG_INPUT_START;
		mb_pro_m.regN=2;
		MB_M_FormatData();
		MB_EventPost(EV_M_SEND);	//��ʼ����
		*flag=0;
		break;
	case 3:								//д�����Ĵ���
	{
		unsigned short regn=2;						//д�����Ĵ��������ĸ��ֽ�
		unsigned short datas[2]={0x0101,0x0102};

		if(sta!=EV_IDLE) break;

		mb_pro_m.funcid=FUNCID_WROHDREG;
		mb_pro_m.startadd=REG_HOLDING_START;
		mb_pro_m.regN=1;
		mb_pro_m.databuff=(unsigned char *)datas;

		MB_M_FormatData();
		MB_EventPost(EV_M_SEND);	//��ʼ����
		*flag=0;
		break;
	}
	case 4:								//д����Ĵ���
	{
		unsigned short regn=2;						//д�����Ĵ��������ĸ��ֽ�
		unsigned short datas[2]={0x0102,0x0304};

		mb_pro_m.funcid=FUNCID_WRNHDREG;
		mb_pro_m.startadd=REG_HOLDING_START;
		mb_pro_m.regN=regn;
		mb_pro_m.databuff=(unsigned char *)datas;
		MB_M_FormatData();
		MB_EventPost(EV_M_SEND);	//��ʼ����
		*flag=0;
		break;
	}
	default:
		*flag=0;
		break;
	}
}

//����Ĵ���
void eMBRegInputCB(mb_pro_t *p_prot)
{
    int             iRegIndex;

    iRegIndex = ( int )( p_prot->startadd - REG_INPUT_START );
	while( p_prot->regN > 0 )
	{
		*p_prot->databuff++ =
			( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
		*p_prot->databuff++ =
			( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
		iRegIndex++;
		p_prot->regN--;
	}
}

//���ּĴ���
void eMBRegHoldingCB(mb_pro_t *p_prot)
{
	int iRegIndex;
	iRegIndex = ( int )( p_prot->startadd - REG_HOLDING_START );

	while(p_prot->regN > 0)
	{
		if(p_prot->mode==1)
		{
			*p_prot->databuff++ =
				( unsigned char )( usRegHoldingBuf[iRegIndex] >> 8 );
			*p_prot->databuff++ =
				( unsigned char )( usRegHoldingBuf[iRegIndex] & 0xFF );
		}
		else if(p_prot->mode==2)		//�߰�λ��ǰ���Ͱ�λ�ں�
		{
			usRegHoldingBuf[iRegIndex]=*p_prot->databuff;
			usRegHoldingBuf[iRegIndex]<<=8;
			p_prot->databuff++;
			usRegHoldingBuf[iRegIndex]|=*p_prot->databuff;
			p_prot->databuff++;
		}

		iRegIndex++;
		p_prot->regN--;
	}
}
