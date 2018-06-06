#ifndef _EXTVARI_H
#define _EXTVARI_H
#include <stdint.h>

#define LENGTH  10      //数据包（包头+数据段+包尾）的包头长度为 10
#define UILENGTH 3      //UI数据包（包头+数据段+包尾）的包头长度为 3

typedef enum _taskselection
{
  NON        = 0x00,             //无任务
  READPORTS  = 0x55,	        //读端口任务 -- read ports 
  WRITEPORTS = 0x66,	       //写端口任务  -- write ports
  READPID    = 0x77,		   //读PID任务   -- read pid group
  WRITEPID   = 0x88            //写PID任务   -- write pid group               
}TASKSEL;

typedef enum _uitaskselection
{
  UINON        = 0x00,            //
  READDATA   = 0x01,	        //
  SETDATA    = 0x02,	        //
  START      = 0x03,		    //
  STOP       = 0x04             //   

}UITASKSEL;

typedef enum _autoselection
{
  MANUAL = 0x10,	  //模式选择-- 上位机手动控制AO/DO/Registers输出
  AUTO   = 0x20       //模式选择-- 程序根据运行自动控制AO/DO/Registers输出
}AUTOSEL;

typedef struct _params		//y = a*x +b
{
  float a;
  float b;
}PARAMS;

/**************** Buffer ****************/
extern  float  UIregister[12] ;
extern  float  Registers[16];
 extern  float  wRegisters[16];
extern  float  ADC_value[12]; 
extern  float  ADC_data[12];
extern  float  RTD_value[4];
extern  float  DAC_value[8];
extern  float  DAC_data[8];
extern  char   DI_data[8];
extern  char   DO_data[8];
/**************** Buffer ****************/

/*************** Protocol **************/

extern PARAMS AOParams[8] ;
extern PARAMS AIParams[12] ;
extern AUTOSEL AOAM[8] ;
extern AUTOSEL REGAM[16];

extern unsigned int MCUaddress ;                //此MCU的地址，用于唯一标定该MCU，在Config期确定
extern volatile TASKSEL TaskSel ;			   //Runtime期任务选择 
extern volatile UITASKSEL UITaskSel;

extern unsigned int  ReceivedNum ;
extern unsigned int  UIReceivedNum ;
extern char  ReceivedBuffer[200];
extern char  SentBuffer[175];
extern char* ReceivedData ;
extern char* SentData ;
extern char  UISendBuffer[22] ;
extern char  UIReceivedBuffer[24];
extern char* UIReceivedData ;
extern char* UISendData    ;

extern unsigned int UIReceivedDataLength ; //data+verified	 19
extern char ReceivedCheckCode;              //已接收数据的效验码
extern char SentCheckCode; 
extern char UISentCheckCode;         //待发送数据的效验码
extern unsigned int ReceivedDataLength;     //已接收数据的数据长度
extern unsigned int SentDataLength;         //待发送数据的数据长度
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
extern void UIsendBufferFill (char *UIsendbuffer) ;
extern void UIMiddleDataGeneration(int length,char* UIsentBuffer);
extern void UIPacketHeaderGeneration(char* UIsentData);
extern int  UIPacketAnalysis(char * receivedData);
extern int CheckUIReceivedData(char* dataBuffer);

extern void  getAIPhysicalValue(float *aarr, PARAMS *range );
extern float getAIonechanelPhyVal(char channel,float *ADC_value, PARAMS *range );
extern void  setAOonechanelPhyVal(char port,float dacvl,float range);
extern void  setAOallchanelPhyVal(float *dacvl,PARAMS *range);
extern float getRTDonechanelPhyVal(char channel,float *temperature );
extern void  DO_onechannel(uint8_t port,char level);

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
extern char autoControl			;
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


/*************** Control Signal **************/





#endif 
