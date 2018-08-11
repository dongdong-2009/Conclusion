#include "wwdg.h"
#include "flash.h"

//WWDG计数器值,默认为最大0x7F
extern u8 WWDG_CNT;

/*
WWDG配置函数
tr:递减计数器的值，取值范围为0x40-0x7f,超出范围直接复位
wr:窗口值，取值范围为0x40-0x7f
prv：预分频值，取值可以是：
	WWDG_Prescaler_1:WWDG counter clock =(PCLK1(45Mhz)/4096)/1 约10968hz 91us
	WWDG_Prescaler_2:WWDG counter clock =(PCLK1(45Mhz)/4096)/2 约5484hz 182us
	WWDG_Prescaler_4:WWDG counter clock =(PCLK1(45Mhz)/4096)/4 约2742hz 364us
	WWDG_Prescaler_8:WWDG counter clock =(PCLK1(45Mhz)/4096)/8 约1371hz 728us

tr=0x7f,wr=0x50,prv=WWDG_Prescaler_8  728*(0x7f-0x50)=34.2ms<刷新窗口时间<728*(0x7f-0x40)=46.6ms
也就是说在 调用WWDG_Config进行这样配置，若之后在34.2ms前喂狗，系统会复位，在46.6ms之后喂狗，系统复位
只有在刷新窗口的时间内喂狗，系统才不会复位
*/
void WWDG_Init(u8 tr,u8 wr,u32 prv)
{
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);  // WWDG时钟使能

    WWDG_CNT=tr&WWDG_CNT;             // 初始化WWDG_CNT (只取低7位,防止溢出)

    WWDG_SetPrescaler(prv);         // 设置IWDG预分频值

    WWDG_SetWindowValue(wr);          // 设置窗口值

    WWDG_Enable(WWDG_CNT);            // 设置看门狗使能位,并第一次喂狗               

    WWDG_ClearFlag();                 // 清除提前唤醒中断标志位

    WWDG_NVIC_Init();                 // 窗口看门狗中断优先级配置

    WWDG_EnableIT();                  // 开启看门狗中断
}


// 喂狗-重置WWDG计数器值
void WWDG_Set_Counter(u8 cnt)
{
    WWDG_Enable(cnt);        // 使能窗口看门狗并设置初值(首次喂狗)   
}

// 看门狗中断服务程序
void WWDG_NVIC_Init()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;            // WWDG中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;  // 抢占优先级 
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;              // 使能
    NVIC_Init(&NVIC_InitStructure);                            // NVIC初始化
}

//计数器到达0x40时进入
void WWDG_IRQHandler(void)
{
    //WWDG_SetCounter(WWDG_CNT);      // 注释此句,窗口看门狗将产生复位

    WWDG_ClearFlag();               // 清除提前唤醒中断标志位
		FLASH_WriteNWord((uint16_t *)&WWDG_CNT, FLASH_ADDR_DATA, 1);
//		FlashDataPack();               //状态数据保存
//		FLASH_WriteNWord((uint16_t*)&WriteBuf, FLASH_ADDR_DATA, 20);  //往Flash中写数据
}

//保存相关状态量
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

