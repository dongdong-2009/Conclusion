#ifndef _EXTVARI_H
#define _EXTVARI_H
#include <stdint.h>

#define LENGTH  10      //���ݰ�����ͷ+���ݶ�+��β���İ�ͷ����Ϊ 10
#define UILENGTH 3      //UI���ݰ�����ͷ+���ݶ�+��β���İ�ͷ����Ϊ 3

typedef enum _taskselection
{
  NON        = 0x00,             //������
  READPORTS  = 0x55,	        //���˿����� -- read ports 
  WRITEPORTS = 0x66,	       //д�˿�����  -- write ports
  READPID    = 0x77,		   //��PID����   -- read pid group
  WRITEPID   = 0x88            //дPID����   -- write pid group               
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
  MANUAL = 0x10,	  //ģʽѡ��-- ��λ���ֶ�����AO/DO/Registers���
  AUTO   = 0x20       //ģʽѡ��-- ������������Զ�����AO/DO/Registers���
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

extern unsigned int MCUaddress ;                //��MCU�ĵ�ַ������Ψһ�궨��MCU����Config��ȷ��
extern volatile TASKSEL TaskSel ;			   //Runtime������ѡ�� 
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
extern char ReceivedCheckCode;              //�ѽ������ݵ�Ч����
extern char SentCheckCode; 
extern char UISentCheckCode;         //���������ݵ�Ч����
extern unsigned int ReceivedDataLength;     //�ѽ������ݵ����ݳ���
extern unsigned int SentDataLength;         //���������ݵ����ݳ���
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
