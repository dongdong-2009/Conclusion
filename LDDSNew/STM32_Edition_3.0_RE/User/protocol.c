#include "protocol.h"

unsigned int MCUaddress =8 ;                //��MCU�ĵ�ַ������Ψһ�궨��MCU����Config��ȷ��
char ReceivedCheckCode=0;              //�ѽ������ݵ�Ч����
char SentCheckCode=0; 
char UISentCheckCode=0;         //���������ݵ�Ч����

unsigned int UIReceivedDataLength=0; 
unsigned int ReceivedDataLength=0;     //�ѽ������ݵ����ݳ���
unsigned int SentDataLength=0;         //���������ݵ����ݳ���
unsigned int UISentDataLength=0;


////////////////////////////////////////////////////
///<��������>�������յ������ݵİ�ͷ
///<����> ָ�룬ָ����ջ���Ĵ����׵�ַ
///<˵��> ��ͷ��10���ֽڹ���
///<����ֵ>	���ݷ�����ȷ 1�����ݷ������� 0
///////////////////////////////////////////////////
int PacketHeaderAnalysis(char * receivedData)
{
   int i;
   int isTrue = 0; 	//У���Ƿ���ȷ 1--true
   unsigned int address;
   char data[LENGTH];
   for(i=0;i<LENGTH;i++)
        data[i] = receivedData[i];
   ReceivedCheckCode = data[6];
   ReceivedDataLength = data[7]*100 + data[8];
   isTrue = CheckReceivedData(receivedData+LENGTH); 

   if(isTrue)
   {   
     address = data[0]*100 + data[1];

	  if(MCUaddress==address)
	   { 
	     if(data[4] == 0x02)
         {	    
	       TaskSel  =  (TASKSEL)data[5];
         }
		 return 1;
	    }
 
 	  return 0;   
   }
   return 0;   
}

////////////////////////////////////////////////////
///<��������>�������յ������ݵİ�ͷ
///<����> ָ�룬ָ����ջ���Ĵ����׵�ַ
///<˵��> ��ͷ��10���ֽڹ���
///<����ֵ>	���ݷ�����ȷ 1�����ݷ������� 0
///////////////////////////////////////////////////

int UIPacketAnalysis(char * receivedData)
{
   int i;
   int isTrue = 0; 	//У���Ƿ���ȷ 1--true
//   unsigned int address;
   char UIdata[UILENGTH];

   for(i=0;i<UILENGTH;i++)
   UIdata[i] = receivedData[i];
   isTrue    = CheckUIReceivedData(receivedData+UILENGTH); 
   
   if(isTrue)
   {   
	    if((UIdata[0]==0x55)||(UIdata[1]==0x66))
		{
		   UITaskSel  =  (UITASKSEL)UIdata[2];
		}

	  return 1;
   }
   return 0;   
}




////////////////////////////////////////////////////////////////////////////////////////
///<Functoin Desriptions>: Form a 10-byte data packet as the header of a data stream, 
///                        flowing to upper machine       
///<Input parament1>:       
///<Input parament2>:                          
///<Return value>:  Null
///////////////////////////////////////////////////////////////////////////////////////
void PacketHeaderGeneration(char* sentData)
{
   sentData[0] = MCUaddress/100;	  
   sentData[1] = MCUaddress%100;       //Address
   sentData[2] = 0x00;
   sentData[3] = 0x00;

 //  sentData[4] = (int)StageSel;	      //StageSel
//   if(StageSel == CONFIG)
//	  sentData[5] = (int)ModeSel;
//   else								  
	  sentData[5] = (int)TaskSel;		 //FuncSel
   
   sentData[6] = SentCheckCode;		  //CheckCode
   sentData[7] = SentDataLength/100;  //Length
   sentData[8] = SentDataLength%100; 
   sentData[9] = 0;	                 //Reserved 
}


////////////////////////////////////////////////////////////////////////////////////////
///<Functoin Desriptions>: Form a 5-byte data packet as the header of a data stream, 
///                        flowing to upper machine       
///<Input parament1>:       
///<Input parament2>:                          
///<Return value>:  Null
///////////////////////////////////////////////////////////////////////////////////////
void UIPacketHeaderGeneration(char* UIsentData)
{
   UIsentData[0] = 0x55;	  
   UIsentData[1] = 0x66;       //Address
   UIsentData[2] = (int)UITaskSel;;
}


void MiddleDataGeneration(int length,char* dataBuffer,char* sentBuffer)
{
   int i;
   SentDataLength = length;
   SentCheckCode  = CheckSentData(dataBuffer);

   for(i=0;i<length;i++)
   {
       sentBuffer[i] = dataBuffer[i];
   }
}


void UIMiddleDataGeneration(int length,char* UIsentBuffer)
{
   int i;
   UISentDataLength = length;
     for(i=0;i<length-3;i++)
   {
       UIsentBuffer[i] = 0x01;
   }
   UISentCheckCode  = UICheckSentData(UIsentBuffer);

 	UIsentBuffer[length-3] =  0x01;
	UIsentBuffer[length-2] = alarmFlag ;
    UIsentBuffer[length-1] =  UISentCheckCode;

}
////////////////////////////////////////////////////
///<��������>У����յ�������
///<����1> ָ�룬ָ����ջ���Ĵ��������ݶ��׵�ַ
///<����ֵ> 0 -- ���ݴ���ʧ�棬1--���ݴ�����ȷ
///////////////////////////////////////////////////
int CheckReceivedData(char* dataBuffer)
{
   int i; 
   long result = 0;
   int checkCode = 0;

   for(i=0;i<ReceivedDataLength;i++)
   {
      result += dataBuffer[i];
   }
   checkCode = result % 100;

   if(checkCode == ReceivedCheckCode)
   return 1;
   else
   return 0;
}


int CheckUIReceivedData(char* dataBuffer)

{
   int i; 
   long result = 0;
   int checkCode = 0;

   for(i=0;i<18;i++)
   {
      result += dataBuffer[i];
   }
   checkCode = result % 100;

   if(checkCode == dataBuffer[18])

   return 1;
   else
   return 0;
}



////////////////////////////////////////////////////
///<��������>У������͵�����
///<����1> ָ�룬ָ���ͻ���Ĵ��������ݶ��׵�ַ
///<����ֵ> ����У����
///////////////////////////////////////////////////
char CheckSentData(char* dataBuffer)
{
   int i; 
   long result = 0;
   char checkCode;

   for(i=0;i<SentDataLength;i++)
   {
      result += dataBuffer[i];
   }
   checkCode = result % 100;

   return checkCode;
}

char UICheckSentData(char* dataBuffer)
{
   int i; 
   long result = 0;
   char checkCode;

   for(i=0;i<18;i++)
   {
      result += dataBuffer[i];
   }
   checkCode = result % 100;

   return checkCode;
}


void DataProcess(void)
{
   switch(TaskSel)
   {
     case NON:          break;
	 case WRITEPORTS:	
	 { writeBufferFill(WritePortsBuffer); 
	   writeCtrlSignal();
	   writePorts();	 }
	 case READPORTS:   
	  {   readPorts();
		  readCtrlSignal();
		  sendBufferFill (ReadPortsBuffer);
	      break;	 
		 }
	 case WRITEPID:     writePID(WritePIDBuffer);
	 case READPID:      readPID(ReadPIDBuffer);break;
   }
   TaskSel = NON;



}



void UIDataProcess(void)
{
   switch(UITaskSel)
   {
     case UINON:          break;
	 case READDATA:	 
	  { readPorts();
	    UIsendBufferFill(UISendBuffer);  
		break; }
	 case SETDATA:    
	 {	UIregisterFill(UIwriteRegister);
	  }
	 {  break;	 	
	 }
	 case START:     ;
	 case STOP:       
   }
   UITaskSel = UINON;



}



char getIntHighByte(float data)
{
    char highByte = 0;
    int temp = (int)data;
	if(temp<0)
	{
	   temp = temp * -1;
   	   highByte = temp/100;
	   highByte = highByte | 0x80;
	}
	else
	   highByte = temp/100;
	return highByte;
}
char getIntLowByte(float data)
{
   char lowByte = 0;
   int temp = (int)data;
   if(temp<0)
      temp = temp * -1;
	lowByte = temp % 100;
   return lowByte;
}
char getDecHighByte(float data)
{
    char decByte = 0;
	if(data<0)
	   data = data * -1;
	decByte = ((int)(data*10000) % 10000) / 100;
	return decByte;
}
char getDecLowByte(float data)
{
    char decByte = 0;
	if(data<0)
	   data = data * -1;
	decByte = (int)(data*10000) % 100;
	return decByte;
}

