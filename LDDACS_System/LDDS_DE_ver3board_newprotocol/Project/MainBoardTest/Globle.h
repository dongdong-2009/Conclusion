#ifndef _GLOBLE_H
#define _GLOBLE_H
#include "stm32f10x_it.h"
//#include "stm32f10x_gpio.h"
//#include "stm32f10x.h"
//#include "rtd.h"

//#include "Dio.h"
//#include "Pwm.h"

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

#define LENGTH  10      //
#define UILENGTH 3      //



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

#define USART3_GPIO              GPIOD
#define USART3_CLK               RCC_APB1Periph_USART3
#define USART3_GPIO_CLK          RCC_APB2Periph_GPIOD
#define USART3_RxPin             GPIO_Pin_9
#define USART3_TxPin             GPIO_Pin_8
#define USART3_IRQn              USART3_IRQn
#define USART3_IRQHandler        USART3_IRQHandler


typedef enum _taskselection
{
  NON        = 0x00,             //???
  READPORTS  = 0x55,	        //????? -- read ports 
  WRITEPORTS = 0x66,	       //?????  -- write ports
  READPID    = 0x77,		   //?PID??   -- read pid group
  WRITEPID   = 0x88            //?PID??   -- write pid group               
}TASKSEL;

//typedef enum _uitaskselection
//{
//  UINON      = 0x00,            //
//  SENDDATA   = 0x01,	        // senddata to touch screen
//  SPDATA     = 0x02,	        // 	receive data from touchscreen
//  START      = 0x03,		    //	touch screen start
//  STOP       = 0x04,             //  touch screen stop
//  EMERGENON	 = 0x05 ,			// will be used when you choose a three pages touchscreen
//  EMERGENOFF = 0x06 ,			// will be used when you choose a three pages touchscreen
//  DESUBREAD	 = 0x07 ,			// 
//  SYSREAD	 = 0x08 			// 
//}UITASKSEL;

extern u8 UITaskSel;
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





/**************** Buffer ****************/
extern  float  UIregister[12] ;
extern  float  Registers[16];
 extern  float wRegisters[16];
extern  float  ADC_value[12]; 
extern  float  ADC_data[12];
extern  float  RTD_value[4];
extern  float  DAC_value[8];
extern  float  DAC_data[8];
extern  char   DI_data[8];
extern  char   DO_data[8];
extern  char   CurrentflagAI[12];
extern  char   CurrentflagAO[8];
extern  float   tempRegisters[16];
/**************** Buffer ****************/

/*************** Protocol **************/

extern PARAMS AOParams[8] ;
extern PARAMS AIParams[12] ;
extern AUTOSEL AOAM[8] ;
extern AUTOSEL REGAM[16];

extern unsigned int MCUaddress ;                //?MCU???,???????MCU,?Config???
extern volatile TASKSEL TaskSel ;			   //Runtime????? 
extern u8 UITaskSel;

extern unsigned int  ReceivedNum ;
extern unsigned int  UIReceivedNum ;
extern char  ReceivedBuffer[68];
extern char  SentBuffer[97];
extern char* ReceivedData ;
extern char* SentData ;
extern char  UISendBuffer[24] ;

extern char  ReqSubBuffer[24];
extern char  ReqSysBuffer[24];

extern char  UIReceivedBuffer[24];
extern char* UIReceivedData ;
extern char* UISendData    ;

extern unsigned int UIReceivedDataLength ; //data+verified	 19
extern char ReceivedCheckCode;              //?????????
extern char SentCheckCode; 
extern char UISentCheckCode;         //?????????
extern unsigned int ReceivedDataLength;     //??????????
extern unsigned int SentDataLength;         //??????????
extern unsigned int UISentDataLength;

extern char UIwriteRegister[12];
extern char ReadPortsBuffer[132];
extern char UIReadPortsBuffer[];
extern char WritePortsBuffer[104];
extern char ReadPIDBuffer[96];
extern char WritePIDBuffer[97]; //HandleBit(1),PID1---PID4(24/each);
extern void sendBufferFill (char *readPortsBuffer);
extern  void writeBufferFill (char *writePortsBuffer)	;

extern void writePorts( void);
extern void readPorts(void);
extern void readPID(char* readPIDBuffer);
extern void writePID(char* writePIDBuffer);

extern char getIntHighByte(float data);
extern char getIntLowByte(float data);
extern char getDecHighByte(float data);
extern char getDecLowByte(float data);

extern int PacketHeaderAnalysis(char * receivedData);
extern void PacketHeaderGeneration(char* sentData);
extern void MiddleDataGeneration(int length,char* dataBuffer,char* sentBuffer);

extern void UIregisterFill(char *UIwriteRegister);
extern void UIsubregisterFill(char * UIwriteRegister);		 //	slc to acc
extern void UIsysregisterFill(char * UIwriteRegister);		 //	slc to acc



extern void UIsendBufferFill (char *UIsendbuffer) ;
extern void UIsubBufferFill (char *UIsendbuffer);
extern void UIsysBufferFill (char *UIsendbuffer);


extern void UIMiddleDataGeneration(int length,char* UIsentBuffer);
extern void UIPacketHeaderGeneration(char* UIsentData,char code);
extern int  UIPacketAnalysis(char * receivedData);
extern int CheckUIReceivedData(char* dataBuffer);

extern void  getAIPhysicalValue(float *aarr, PARAMS *range );

extern float RH2HR(float temp, float relativehum);

extern float getAIonechanelPhyVal(char channel,char* flag,float *aarr, PARAMS *range );

extern void  setAOonechanelPhyVal(char port,float dacvl,float range);
extern void  setAOallchanelPhyVal(float *dacvl,PARAMS *range);
extern float getRTDonechanelPhyVal(char channel,float *temperature );
extern void  DO_onechannel(u8 channel,u8 State);

extern void DataProcess(void);
extern void UIDataProcess(void);

extern int CheckReceivedData(char* dataBuffer);
extern char UICheckSentData(char* dataBuffer);
extern char CheckSentData(char* dataBuffer);

/*************** Protocol **************/

/*************** Control Signal **************/
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

extern char StrSLevelHigh		;
extern char StrSLevelLow		;

extern char DeSLevelHigh  		;
extern char DeSLevelTrasf 		;	
extern char DeSLevelOpt  		;
extern char DeSLevelLow		    ;	

extern float CtrlParaP			;	
extern float CtrlParaI 			;
extern float CtrlParaD 			;



//extern float AIrangIn[12];
extern float  Setpoint[3];
extern float  SetpointPC[3];


extern char dehStart(PARAMS *arin,PARAMS *arout);
extern char dehStop(PARAMS *arin,PARAMS *arout,char *dout);
extern char	 deh_algorithm(void);

extern float templocker;
extern short int  deh_transfer(void);
extern short int  highlevel_alarm(void)		   ;
extern short int  lowlevel_sv_alarm(void)	  ;
extern int valveopen(float t);
 

extern float opencnts(float error)	  ;
extern char alarmanaysis(void);

extern float RH2HR(float temp, float relativehum);
extern float softsensing(void);
extern void  concenalgorithm(float Setpoint[],float analogIn[16],float rangeIn[12],float analogOut[8],float rangeOut[8]) ;
extern float density(float temperature, float concen );
extern float SolInletPID(float aimed_solultiontemp);
extern float caimdetermin(float setpoint[], float conNow,float SolInTNow )	  ;
extern float opentimecnt(float tempTa,float concenw,float concens,float caim)	;


extern void  Usart_SendChar(char dat);
extern char  Usart_GetChar(USART_TypeDef* USARTx);
extern void  UsartSendData(int num,char* sendbuffer);
extern void  UartSendData(int num,char* sendbuffer) ;
extern void  Uart_SendChar(char dat);

/*************** Control Signal **************/



//extern void DataProcess(void);


#define DE1 PAout(8)
#define DE2 PDout(7)
#define LED PBout(9)
#endif

