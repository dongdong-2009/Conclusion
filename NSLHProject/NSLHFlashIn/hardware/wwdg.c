#include "wwdg.h"
#include "flash.h"

//WWDG������ֵ,Ĭ��Ϊ���0x7F
extern u8 WWDG_CNT;

/*
WWDG���ú���
tr:�ݼ���������ֵ��ȡֵ��ΧΪ0x40-0x7f,������Χֱ�Ӹ�λ
wr:����ֵ��ȡֵ��ΧΪ0x40-0x7f
prv��Ԥ��Ƶֵ��ȡֵ�����ǣ�
	WWDG_Prescaler_1:WWDG counter clock =(PCLK1(45Mhz)/4096)/1 Լ10968hz 91us
	WWDG_Prescaler_2:WWDG counter clock =(PCLK1(45Mhz)/4096)/2 Լ5484hz 182us
	WWDG_Prescaler_4:WWDG counter clock =(PCLK1(45Mhz)/4096)/4 Լ2742hz 364us
	WWDG_Prescaler_8:WWDG counter clock =(PCLK1(45Mhz)/4096)/8 Լ1371hz 728us

tr=0x7f,wr=0x50,prv=WWDG_Prescaler_8  728*(0x7f-0x50)=34.2ms<ˢ�´���ʱ��<728*(0x7f-0x40)=46.6ms
Ҳ����˵�� ����WWDG_Config�����������ã���֮����34.2msǰι����ϵͳ�Ḵλ����46.6ms֮��ι����ϵͳ��λ
ֻ����ˢ�´��ڵ�ʱ����ι����ϵͳ�Ų��Ḵλ
*/
void WWDG_Init(u8 tr,u8 wr,u32 prv)
{
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);  // WWDGʱ��ʹ��

    WWDG_CNT=tr&WWDG_CNT;             // ��ʼ��WWDG_CNT (ֻȡ��7λ,��ֹ���)

    WWDG_SetPrescaler(prv);         // ����IWDGԤ��Ƶֵ

    WWDG_SetWindowValue(wr);          // ���ô���ֵ

    WWDG_Enable(WWDG_CNT);            // ���ÿ��Ź�ʹ��λ,����һ��ι��               

    WWDG_ClearFlag();                 // �����ǰ�����жϱ�־λ

    WWDG_NVIC_Init();                 // ���ڿ��Ź��ж����ȼ�����

    WWDG_EnableIT();                  // �������Ź��ж�
}


// ι��-����WWDG������ֵ
void WWDG_Set_Counter(u8 cnt)
{
    WWDG_Enable(cnt);        // ʹ�ܴ��ڿ��Ź������ó�ֵ(�״�ι��)   
}

// ���Ź��жϷ������
void WWDG_NVIC_Init()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;            // WWDG�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;  // ��ռ���ȼ� 
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;              // ʹ��
    NVIC_Init(&NVIC_InitStructure);                            // NVIC��ʼ��
}

//����������0x40ʱ����
void WWDG_IRQHandler(void)
{
    //WWDG_SetCounter(WWDG_CNT);      // ע�ʹ˾�,���ڿ��Ź���������λ

    WWDG_ClearFlag();               // �����ǰ�����жϱ�־λ
		FLASH_WriteNWord((uint16_t *)&WWDG_CNT, FLASH_ADDR_DATA, 1);
//		FlashDataPack();               //״̬���ݱ���
//		FLASH_WriteNWord((uint16_t*)&WriteBuf, FLASH_ADDR_DATA, 20);  //��Flash��д����
}

//�������״̬��
void FlashDataPack(void)
{
	WriteBuf[0]=RoomTempSv/256;
	WriteBuf[1]=RoomTempSv%256;
	
	WriteBuf[2]=TempSPSet_Unocc/256;
	WriteBuf[3]=TempSPSet_Unocc%256;
	
	WriteBuf[4]=ERVCmd/256;
	WriteBuf[5]=ERVCmd%256;
	
	WriteBuf[6]=IBSCommand&0xff;

	WriteBuf[7]=ScheduleComm&0xff;
	
	WriteBuf[8]=PurgeCmd&0xff;
	
	WriteBuf[9]=ValveCmd/256;
	WriteBuf[10]=ValveCmd%256;
		
	WriteBuf[11]=PDVComm&0xff;

	WriteBuf[12]=RunStatus;
	
	WriteBuf[13]=OccSta&0xff;
	
	WriteBuf[14]=0x01;	
}

void FlashDataRead(void)
{
	RoomTempSv = ReadBuf[0]<<8|ReadBuf[1];
	TempSPSet_Unocc = ReadBuf[2]<<8|ReadBuf[3];
	ERVCmd = ReadBuf[4]<<8|ReadBuf[5];
	
	IBSCommand = ReadBuf[6];
	ScheduleComm = ReadBuf[7];
	PurgeCmd = ReadBuf[8];
	ValveCmd = ReadBuf[9]<<8|ReadBuf[10];
	PDVComm = ReadBuf[11];
	RunStatus = ReadBuf[12];
	OccSta = ReadBuf[13];
}

