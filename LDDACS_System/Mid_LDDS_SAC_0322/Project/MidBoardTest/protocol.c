#include "Globle.h"
#include "delay.h"
#include "stm32f10x_usart.h"

unsigned int MCUaddress =0 ;           //此MCU的地址，用于唯一标定该MCU，在Config期确定
char ReceivedCheckCode=0;              //已接收数据的效验码
char SentCheckCode=0; 
unsigned int ReceivedDataLength=0;     //已接收数据的数据长度
unsigned int SentDataLength=0;         //待发送数据的数据长度

void DataProcess(void);
void SendProcess(void);

////////////////////////////////////////////////////
///<功能描述>解析接收到的数据的包头
///<参数> 指针，指向接收缓存寄存器首地址
///<说明> 包头由10个字节构成
///<返回值>	数据分析正确 1，数据分析有误 0
///////////////////////////////////////////////////
int PacketHeaderAnalysis(u8 * receivedData)
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
		 return 1;
	    }
 
 	  return 0;   
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
void PacketHeaderGeneration(u8* sentData,u8 selectedBoard)
{
   sentData[0] = 0x55;
   sentData[1] = selectedBoard;
  
   sentData[2] = 0x08;	  

   sentData[21] = CheckSentData(sentData);		  //CheckCode
   sentData[22] = selectedBoard;                   //Length
   sentData[23] = 0x55; 
}

////////////////////////////////////////////////////
///<功能描述>校验接收到的数据
///<参数1> 指针，指向接收缓存寄存器的数据段首地址
///<返回值> 0 -- 数据传输失真，1--数据传输正确
///////////////////////////////////////////////////
int CheckReceivedData(u8* dataBuffer)
{
   int i; 
   long result = 0;
   int checkCode = 0;
    if(dataBuffer[2]!=8)
	return 0;

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
char CheckSentData(u8* dataBuffer)
{
   int i; 
   long result = 0;
   char checkCode;

   for(i=3;i<21;i++)
   {
      result += dataBuffer[i];
   }
   checkCode = result % 100;

   return checkCode;
}


/*********************************************************************************************************
* Functoin name:       void DataProcess(void)

* Descriptions:        data refresh
* input paraments:     void
* output paraments:    无    
* Returned values:     void
*********************************************************************************************************/

void DataProcess(void)
{
	 readPorts();

}

/*********************************************************************************************************
* Functoin name:       void SendProcess(void)

* Descriptions:        usart1 send 24byte data to give response to dehumidifier main controller
* input paraments:     void
* output paraments:    无    
* Returned values:     void
*********************************************************************************************************/

void SendProcess(void)
{
  
   unsigned int i=0;
   //USART_ITConfig(USART1, USART_IT_RXNE, DISABLE); 
   USART_ITConfig(USART1,USART_IT_TXE,ENABLE);	  
   PacketHeaderGeneration(SentBuffer,ReceivedBuffer[1]);
   delay_ms(2) ;

   switch(ReceivedBuffer[1])
   {
     case 0x66: 

	 DE1receBufferFill(ReceivedBuffer);
	 DEsendBufferFill(SentBuffer);
	 DE1=0;
	 for(i=0;i<24;i++)
	 {
	    Usart_SendChar(SentBuffer[i]); 
	 
	 }
	 delay_ms(2);
	 DE1=1;
	 break;	          

	 case 0x77: 
	 
	 REreceBufferFill(ReceivedBuffer);
	 REsendBufferFill(SentBuffer);
     DE1=0;
	 for(i=0;i<24;i++)
	 {
	    Usart_SendChar(SentBuffer[i]); 
	 
	 }
	 delay_ms(2);
	 DE1=1;

	 break;	
	 default:break;
   }
   USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 
}




/*********************************************************************************************************
* Functoin name:       void getIntHighByte(void)
						char getIntLowByte(float data)
					   char getDecHighByte(float data)
					   char getDecLowByte(float data)

* Descriptions:        get the high/low bytes of integer and decimal parts of a float data
* input paraments:     float data
* output paraments:    无    
* Returned values:     char value
*********************************************************************************************************/

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

