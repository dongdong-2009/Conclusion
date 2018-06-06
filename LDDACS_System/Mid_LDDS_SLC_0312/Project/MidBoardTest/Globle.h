#ifndef _GLOBLE_H
#define _GLOBLE_H
#include "stm32f10x_it.h"
#include "W25Q16.h"

#define  ISPC  1



#define MODE_CURRENT 1
#define MODE_VOLTAGE 0
//IO口地址映射
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入


#define USART1_GPIO              GPIOA
#define USART1_CLK               RCC_APB2Periph_USART1
#define USART1_GPIO_CLK          RCC_APB2Periph_GPIOA
#define USART1_RxPin             GPIO_Pin_10
#define USART1_TxPin             GPIO_Pin_9
#define USART1_IRQn              USART1_IRQn
#define USART1_IRQHandler        USART1_IRQHandler

#define USART2_GPIO              GPIOD
#define USART2_CLK               RCC_APB1Periph_USART2
#define USART2_GPIO_CLK          RCC_APB2Periph_GPIOD
#define USART2_RxPin             GPIO_Pin_6
#define USART2_TxPin             GPIO_Pin_5
#define USART2_IRQn              USART2_IRQn
#define USART2_IRQHandler        USART2_IRQHandler

//#define USART3_GPIO              GPIOB
//#define USART3_CLK               RCC_APB1Periph_USART3
//#define USART3_GPIO_CLK          RCC_APB2Periph_GPIOB
//#define USART3_RxPin             GPIO_Pin_11
//#define USART3_TxPin             GPIO_Pin_10
//#define USART3_IRQn              USART3_IRQn
//#define USART3_IRQHandler        USART3_IRQHandler

extern uint8_t Uart1_SCnt;
extern uint8_t Uart1_Send_buffer[150];
extern uint8_t Uart1_receive_buffer[150];
extern uint8_t Uart1_RCnt;
extern uint8_t Uart1_SendBuffSize;

extern uint8_t Uart2_SCnt;
extern uint8_t Uart2_Send_buffer[150];
extern uint8_t Uart2_receive_buffer[150];
extern uint8_t Uart2_RCnt;
extern uint8_t Uart2_SendBuffSize;

extern uint8_t Uart3_SCnt;
extern uint8_t Uart3_Send_buffer[150];
extern uint8_t Uart3_receive_buffer[150];
extern uint8_t Uart3_RCnt;
extern uint8_t Uart3_SendBuffSize;

extern uint8_t Uart4_SCnt;
extern uint8_t Uart4_Send_buffer[150];
extern uint8_t Uart4_receive_buffer[150];
extern uint8_t Uart4_RCnt;
extern uint8_t Uart4_SendBuffSize;

extern uint8_t Uart4851_TestFlag;
extern uint8_t Uart4852_TestFlag;
extern uint8_t Wifi_TestFlag;

#define LENGTH  10      //

#define DE1 PAout(11)
#define DE2 PDout(7)
#define LED PBout(9)
#define SAMPLES       20

/**************** parameter ****************/
  typedef enum _autoselection
{
  MANUAL = 0x10,	  //????-- ???????AO/DO/Registers??
  AUTO   = 0x20       //????-- ??????????AO/DO/Registers??
}AUTOSEL;

typedef struct _params		//y = a*x +b
{
  float a;
  float b;
}PARAMS;

/**************** parameter ****************/

extern float ADS1220GainCorrection_1;
extern float ADS1220GainCorrection_2;

extern unsigned char RcvData[16];
extern long OffsetCalibrateData_1;
extern unsigned char OffsetCalibrateCount_1;
extern long OffsetCalibrateValue_1;
extern float PgaGainLevel_1;
extern long rawData_1;

extern  long OffsetCalibrateData_2;
extern  unsigned char OffsetCalibrateCount_2;
extern long OffsetCalibrateValue_2;
extern float PgaGainLevel_2;
extern long rawData_2;

extern unsigned char ReadConversionData_1 ;
extern unsigned char ReadConversionData_2 ;

extern unsigned char OffsetCalFlag;

extern long temperature_1;
extern long temperature_2;
extern long code_1;
extern long code_2;
extern float avgTemp_1;
extern float avgTemp_2;
extern float avgRaw_1;
extern float avgRaw_2;
extern unsigned char avgCount_1;
extern unsigned char avgCount_2;

extern unsigned char GainCal_1;
extern unsigned char GainCal_2;

extern unsigned char tempData_1[3];
extern unsigned char tempData_2[3];

extern uint16_t ADC_ConvertedValue[10][6];

/**************** Buffer ****************/
extern  float  Registers[16];
extern  float  wRegisters[16];
extern  float  ADC_value[6]; 
extern  float  ADC_data[6];
extern  float  DAC_value[4];
extern  float  DAC_data[4];
extern  char   DI_data[4];
extern  char   DO_data[4];
extern  char   CurrentflagAI[6];
extern  char   CurrentflagAO[4];
extern  float  tempRegisters[16];
 
/**************** Buffer ****************/		

/*************** Protocol **************/

extern PARAMS AOParams[4] ;
extern PARAMS AIParams[6] ;
extern AUTOSEL AOAM[4] ;
extern AUTOSEL REGAM[16];

extern unsigned int MCUaddress ;                //?MCU???,???????MCU,?Config???
extern unsigned int  ReceivedNum ;
extern unsigned int  UIReceivedNum ;
extern u8  ReceivedBuffer[24];
extern u8  SentBuffer[24];
//extern char* ReceivedData ;
//extern char* SentData ;


extern char ReceivedCheckCode;              //?????????
extern char SentCheckCode; 
         //?????????
extern unsigned int ReceivedDataLength;     //??????????
extern unsigned int SentDataLength;         //??????????

extern void sendBufferFill (u8 *readPortsBuffer);
extern  void writeBufferFill (u8 *writePortsBuffer)	;

extern void writePorts( void);
extern void readPorts(void);

extern int PacketHeaderAnalysis(u8 * receivedData);
extern void PacketHeaderGeneration(u8* sentData);

extern void  getAIPhysicalValue(float *aarr, PARAMS *range );

extern float RH2HR(float temp, float relativehum);

extern float getAIonechanelPhyVal(char channel,char* flag,float *aarr, PARAMS *range );

extern void  setAOonechanelPhyVal(char port,float dacvl,float range);
extern void  setAOallchanelPhyVal(float *dacvl,PARAMS *range);
extern float getRTDonechanelPhyVal(char channel,float *temperature );
extern void  DO_onechannel(u8 channel,u8 State);

extern void DataProcess(void);
extern void SendProcess(void);

extern int CheckReceivedData(u8* dataBuffer);
extern char CheckSentData(u8* dataBuffer);

extern void Usart_SendChar(char dat);
extern void alarmCheck(void);

/*************** Protocol **************/

/**************** Control ****************/
extern void readCtrlSignal(void);
extern void writeCtrlSignal(void);

extern char panelControl		;
extern char panelCStatus		;  
extern char remoteControl		;
extern char localControl		;
extern char localDeviceRun		;
extern char deviceRun			;
extern char runStatus			;
extern char alarmFlag			;	
extern char algorithmstart		;
extern char System_On 			;
/**************** Control ****************/
extern char getIntHighByte(float data);
extern char getIntLowByte(float data);
extern char getDecHighByte(float data);
extern char getDecLowByte(float data);

#endif

