#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include"runtimedata.h"
#include "AD.h"
#include "rtd.h"
#include "DAC8554.h"	   			 
#include "dio.h"	
#include "Globle.h"
#include "LddsPorts.h"	
#include "delay.h"

u8  selectedBuffer;
void sendBufferFill (u8 *readPortsBuffer);
void writeBufferFill (u8 *writePortsBuffer)	;
u8 statusVerify(void);
/*********************************************************************************************************
* Functoin name:       void ReadPortsData(void)
* Descriptions:        按次序读取所有端口数据，并填充发送缓存数组send_buffer
*                      读取顺序：AI,RI,AO,DI,DO,RGE  共发送有效数据86+12位（36+8+16+1+1+24）
* input paraments:     无
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/
void readPorts(void )
{
   u8 i=0;

   GetDiMap(DI_data);
   
	for(i=0;i<4;i++)
	 {
	 	 DI_data[i]=1;

	 }

}


 /*********************************************************************************************************
* Functoin name:       void sendbuffer(void)
* Descriptions:        读取UI所需信息，并填充发送缓存数组send_buffer
*                      读取顺序：AI,AO,DI,DO,RGE  共发送有效数据86+12位（36+8+16+1+1+24）
* input paraments:     无
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/
 void DEsendBufferFill (u8 *SentBuffer)
{
    SentBuffer[10] = getIntLowByte(tempRegisters[WSTLEVEL]); 
    SentBuffer[11] = getDecHighByte(tempRegisters[WSTLEVEL]); 

	SentBuffer[12] = getIntLowByte(tempRegisters[SSTLEVEL]); 
    SentBuffer[13] = getDecHighByte(tempRegisters[SSTLEVEL]); 

	SentBuffer[14] = getIntLowByte(tempRegisters[RELEVEL]); 
    SentBuffer[15] = getDecHighByte(tempRegisters[RELEVEL]);

    SentBuffer[17] = selectedBuffer;

    SentBuffer[18] = tempRegisters[CASETRANSFER]; 
    SentBuffer[19] = tempRegisters[CASEEMERGENCY]; 
}

 /*********************************************************************************************************
* Functoin name:       void sendbuffer(void)
* Descriptions:        读取UI所需信息，并填充发送缓存数组send_buffer
*                      读取顺序：AI,AO,DI,DO,RGE  共发送有效数据86+12位（36+8+16+1+1+24）
* input paraments:     无
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/
 void REsendBufferFill (u8 *SentBuffer)
{
//	SentBuffer[12] = getIntLowByte(tempRegisters[BUFLEVEL]); 
//  SentBuffer[13] = getDecHighByte(tempRegisters[BUFLEVEL]); 

//	SentBuffer[14] = getIntLowByte(tempRegisters[DELEVEL]); 
//  SentBuffer[15] = getDecHighByte(tempRegisters[DELEVEL]);

    SentBuffer[18] = tempRegisters[CASETRANSFER]; 
    SentBuffer[19] = tempRegisters[CASEEMERGENCY]; 

}

void DE1receBufferFill(u8 *ReceivedBuffer)
{
   setPoint[SPHUM]	 =  ReceivedBuffer[3] ;
   setPoint[SPTEMP]	 =  ReceivedBuffer[4]*100 + ReceivedBuffer[5] ;

   tempRegisters[BUFLEVEL1] = ReceivedBuffer[8]*100+ReceivedBuffer[9] ;
   tempRegisters[DELEVEL1]  = ReceivedBuffer[10]*100+ReceivedBuffer[11] ;

//   alarmFlag   = ReqSysBuffer[20];
}
//please modifiy based on protocol
void REreceBufferFill(u8 *ReceivedBuffer)
{
   setPoint[SETRECON]	 =  ReceivedBuffer[6]/100 ;

   tempRegisters[WSTLEVEL] = ReceivedBuffer[8]*100+ReceivedBuffer[9] ;
   tempRegisters[SSTLEVEL]  = ReceivedBuffer[10]*100+ReceivedBuffer[11] ;
   tempRegisters[RELEVEL]  = ReceivedBuffer[12]*100+ReceivedBuffer[13] ;

//   alarmFlag   = ReqSysBuffer[20];


}


void statusCheck(void)
{
//  u8 type=0;
//  type = statusVerify();
//
//  if(type)
     emergencyCheck();
//  else
	 transferCheck();

} 

u8 statusVerify(void)
{
  u8 flag=0;
  u8 i=0;

   for(i=0;i<DENUM;i++)
  {
	if((tempRegisters[DELEVEL1+i]>DHA1)&&(tempRegisters[DELEVEL1+i]<DHA2))
	   flag=0;
     else
       flag=1;

    if((tempRegisters[BUFLEVEL1+i]>BMA1)&&(tempRegisters[BUFLEVEL1+i]<BMA2))
	   flag=0;
     else
       flag=1;
  
  }

   if((tempRegisters[RELEVEL]>RLA)&&(tempRegisters[RELEVEL]<RHA1))
    flag=0;
   else
    flag=1;

   if((tempRegisters[WSTLEVEL]>WLA)&&(tempRegisters[WSTLEVEL]<WHA1))
    flag=0;
   else
    flag=1;

   if((tempRegisters[SSTLEVEL]>SLA)&&(tempRegisters[SSTLEVEL]<SHA1))
    flag=0;
   else
    flag=1;

	return flag;
}

void  emergencyCheck(void)
{
  u8 i=0,flag=0;

  for(i=0;i<DENUM;i++)
  {
	if(tempRegisters[DELEVEL1+i]>DHA3)
	   flag=0x01;
    if(tempRegisters[DELEVEL1+i]<=DLA)
	   flag=0x02;
	if(tempRegisters[BUFLEVEL1+i]>=BHA2)
	   flag=0x03;

	 if(tempRegisters[DELEVEL1+i]>DHA2)
	 {
	 	if(tempRegisters[WSTLEVEL+i]>=WHA1)
		 flag=0x08;
		else
		 flag=0x09;
	 }
	  
    if(tempRegisters[BUFLEVEL1+i]<=BLA)
	   flag=0x0A;
  }

   if(tempRegisters[RELEVEL]>=RHA2)
    	flag=4;
   if(tempRegisters[WSTLEVEL]>=WHA2)
    	flag=5;  
   if(tempRegisters[SSTLEVEL]>=SHA2)
    	flag=6;
   if(tempRegisters[SSTLEVEL]>=SLA)
    	flag=7;  
			
   	tempRegisters[CASEEMERGENCY]=flag; 
}


void transferCheck(void)
{
   u8 i=0,flag=0;

  for(i=0;i<DENUM;i++)
  {
	if(tempRegisters[DELEVEL1+i]>DHA1)
	   flag=4;
    if(tempRegisters[BUFLEVEL1+i]<=BMA1)
	   flag=3;
  }

   if(tempRegisters[SSTLEVEL]>=WHA1)
    flag=2;
   if(tempRegisters[RELEVEL]>=SHA1)
    flag=1;

    tempRegisters[CASETRANSFER] =  flag;
}


void  lowbufCheck(void)
{
 u8 i=0,j=0,temppos=0;
 float temp=0;
 u8 pos[16]={0};

  if(DENUM==1)
	selectedBuffer=0x66;
  else
  {
   for(i=0;i<DENUM;i++)
   {
	 bufRegisters[i] = tempRegisters[BUFLEVEL1+i];
	 pos[i]			 = i;
   }
	    
   for(i=0;i<DENUM;i++)
   {
	 for(j=i+1;j<DENUM;j++)
     {
      if(bufRegisters[j]<bufRegisters[i])
	   {    
	       temp=bufRegisters[i];
		   temppos= i;
		   pos[i] = j;
		   pos[j] =temppos;
	       bufRegisters[i]= bufRegisters[j];
		   bufRegisters[j]=temp;
       } 
     }
    }

   }
   selectedBuffer=boardRegisters[pos[0]];
}
