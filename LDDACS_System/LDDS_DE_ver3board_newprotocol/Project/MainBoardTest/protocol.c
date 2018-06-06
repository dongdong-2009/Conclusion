#include "Globle.h"
#include "delay.h"
#include "stm32f10x_usart.h"

unsigned int MCUaddress =0 ;                //此MCU的地址，用于唯一标定该MCU，在Config期确定
char ReceivedCheckCode=0;              //已接收数据的效验码
char SentCheckCode=0; 
char UISentCheckCode=0;         //待发送数据的效验码

unsigned int UIReceivedDataLength=0; 
unsigned int ReceivedDataLength=0;     //已接收数据的数据长度
unsigned int SentDataLength=0;         //待发送数据的数据长度
unsigned int UISentDataLength=0;
unsigned int testreceive=0;

////////////////////////////////////////////////////
///<功能描述>解析接收到的数据的包头
///<参数> 指针，指向接收缓存寄存器首地址
///<说明> 包头由10个字节构成
///<返回值>	数据分析正确 1，数据分析有误 0
///////////////////////////////////////////////////
int PacketHeaderAnalysis(char * receivedData)
{
   int i;
   int isTrue = 0; 	//校验是否正确 1--true
   unsigned int address;
   char data[LENGTH];
   for(i=0;i<LENGTH;i++)
        data[i] = receivedData[i];
   ReceivedCheckCode = data[6];
   ReceivedDataLength = data[7]*100 + data[8];
   isTrue = CheckReceivedData(receivedData+LENGTH); 

   if(isTrue)
   {   
     address = data[2]*100 + data[3];

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
///<功能描述>解析接收到的数据的包头
///<参数> 指针，指向接收缓存寄存器首地址
///<说明> 包头由10个字节构成
///<返回值>	数据分析正确 1，数据分析有误 0
///////////////////////////////////////////////////

int UIPacketAnalysis(char * receivedData)
{
   int i;
   int isTrue = 0; 	//校验是否正确 1--true
//   unsigned int address;
   char UIdata[UILENGTH];

   for(i=0;i<UILENGTH;i++)
   UIdata[i] = receivedData[i];
   isTrue    = CheckUIReceivedData(receivedData+UILENGTH); 
   
   if(isTrue)
   {   
	    if((UIdata[0]==0x55)||(UIdata[1]==0x66))
		{
//		   UITaskSel  =  (UITASKSEL)UIdata[2];
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
   sentData[0] = 0x55;
   sentData[1] = 0x66;
   
   sentData[2] = MCUaddress/100;	  
   sentData[3] = MCUaddress%100;       //Address
   
   sentData[4] = 0x02;
 //sentData[4] = (int)StageSel;	      //StageSel
// if(StageSel == CONFIG)
//	  sentData[5] = (int)ModeSel;
// else								  
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
void UIPacketHeaderGeneration(char* UIsentData,char code)
{
   UIsentData[0] = 0x55;	  
   UIsentData[1] = 0x66;       //Address
   UIsentData[2] = code;
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
    sentBuffer[i]= 0x66;
	i++;
    sentBuffer[i]= 0x55;
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
///<功能描述>校验接收到的数据
///<参数1> 指针，指向接收缓存寄存器的数据段首地址
///<返回值> 0 -- 数据传输失真，1--数据传输正确
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

   for(i=3;i<21;i++)
   {
      result += dataBuffer[i];
   }
   checkCode = result % 100;

   if(checkCode == dataBuffer[21])

   return 1;
   else
   return 0;
}



////////////////////////////////////////////////////
///<功能描述>校验待发送的数据
///<参数1> 指针，指向发送缓存寄存器的数据段首地址
///<返回值> 返回校验码
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
  
   unsigned int i=0;
   USART_ITConfig(USART1, USART_IT_RXNE, DISABLE); 
//   delay_ms(2);
//   USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
   delay_ms(2);

   switch(TaskSel)
   {
     case NON:          break;
	 case WRITEPORTS:	
	 { 
	    ReceivedBuffer[1]=0x66;
		ReceivedBuffer[66]=0x66;
		DE1=0;
	    UsartSendData(ReceivedNum,ReceivedBuffer);
		delay_ms(2);
		DE1=1;
		for(i=0;i<56;i++)
		  WritePortsBuffer[i] = ReceivedBuffer[i+LENGTH];
	    writeBufferFill(WritePortsBuffer); 
	    writeCtrlSignal();
	    writePorts();	 
	   }
	 case READPORTS:   
	  {   
//	      readPorts();
//		  readCtrlSignal();
		  sendBufferFill(ReadPortsBuffer);
		  MiddleDataGeneration(85,ReadPortsBuffer,SentData);		  
	      PacketHeaderGeneration(SentBuffer);
		  DE1=0;
	      UsartSendData(87+LENGTH,SentBuffer);
		  delay_ms(2);
		  DE1=1;

	      break;	 
		 }
	 case WRITEPID:     
	 {	  
	      DE1=0;
		  UsartSendData(ReceivedNum,ReceivedBuffer);
		  delay_ms(2);
		  DE1=1;
		  for(i=0;i<97;i++)
				   WritePIDBuffer[i] = ReceivedData[i];
		  writePID(WritePIDBuffer);
	 }
	 case READPID:      
	 {
	 		readPID(ReadPIDBuffer);
			MiddleDataGeneration(96,ReadPIDBuffer,SentData);	
			PacketHeaderGeneration(SentBuffer);
			DE1=0;
			UsartSendData(98+LENGTH,SentBuffer);
			delay_ms(2);
			DE1=1;

			break;
	 }
   }
   TaskSel = NON;
 //  USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
   USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 
}



void UIDataProcess(void)
{
   u8 task;
   char code=0x01;
   static char type=1;
   delay_ms(2);
   task =   UIReceivedBuffer[2];
   switch(task)
   {
     
	 case 1:	 

		if(type==1)
		{
	    UIsubBufferFill(ReqSubBuffer) ;
		DE2=0;
		UartSendData(24,ReqSubBuffer);
		delay_ms(2);
		type=2;
		}
		else if(type==2)
		{		 
		 UIsysBufferFill(ReqSysBuffer) ;
		 DE2=0;
		 UartSendData(24,ReqSysBuffer);
		 delay_ms(2);
		 type=0;
		}
		else
		{
	    readPorts();
		UIsendBufferFill(UISendBuffer) ;
		DE2=0;
        UartSendData(24,UISendBuffer); 
		delay_ms(2);
		type=1;
		} 

		DE2=1;
		break;
		
	 case 2:    
	   	code=0x02;
		UIregisterFill(UIReceivedBuffer);  
		UIPacketHeaderGeneration(UISendBuffer,code) ;
		UIMiddleDataGeneration(19,UISendBuffer+UILENGTH);
		DE2=0;
		UartSendData(24,UISendBuffer);					
		delay_ms(2);
	    DE2=1;
		break;
	   	 
	 case 3:     
	    code=0x03;
	 	UIPacketHeaderGeneration(UISendBuffer,code) ;
        UIMiddleDataGeneration(19,UISendBuffer+UILENGTH);
		DE2=0;	
        UartSendData(24,UISendBuffer);					
		//Uart_SendChar(0x66);
        //Uart_SendChar(0x55);
		delay_ms(2);
		DE2=1;
	    localControl =1;
		break;	
	 	
	 case 4:  
		 code=0x04;
	 	 UIPacketHeaderGeneration(UISendBuffer,code) ;
		 UIMiddleDataGeneration(19,UISendBuffer+UILENGTH);
		 DE2=0;
         UartSendData(24,UISendBuffer);
         //Uart_SendChar(0x66);
         //Uart_SendChar(0x55);
		 delay_ms(2);
		 DE2=1;
         localControl =0;
	 	 break;
	  	 
	case 7: 
	 	 
		 {
		 
		  UIsubregisterFill(UIReceivedBuffer); 
		  delay_ms(2);

	 	 break;
		 }
	case 8:  
		
		 UIsysregisterFill(UIReceivedBuffer);
		 delay_ms(2);
//		  DE2=1;
         //  localControl =0;
	 	 break;
  		 
  }
    UITaskSel = 0;
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

