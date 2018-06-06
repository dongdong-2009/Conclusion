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
void sendBufferFill (u8 *readPortsBuffer);
void writeBufferFill (u8 *writePortsBuffer)	;
/*********************************************************************************************************
* Functoin name:       void ReadPortsData(void)
* Descriptions:        �������ȡ���ж˿����ݣ�����䷢�ͻ�������send_buffer
*                      ��ȡ˳��AI,RI,AO,DI,DO,RGE  ��������Ч����86+12λ��36+8+16+1+1+24��
* input paraments:     ��
* output paraments:    ��    
* Returned values:     ��
*********************************************************************************************************/
void readPorts(void )
{
   u8 i=0;
   ADC_allchannels(ADC_data,CurrentflagAI);
   getAIPhysicalValue(ADC_value, AIParams);
   GetDiMap(DI_data);
   
	 for(i=0;i<6;i++)
	 {
	 	 ADC_value[i]=i+0.5;

	 }
	 	 for(i=0;i<4;i++)
	 {
	 	 DI_data[i]=1;

	 }

}




/*********************************************************************************************************
* Functoin name:       void WritePortsData(void)
* Descriptions:        �������ö˿����� ��������Ч����38λ��12+26��
*                      ����˳��AO,DO,Reg
* input paraments:     ��
* output paraments:    ��    
* Returned values:     ��
*********************************************************************************************************/
void writePorts(void)
{
   int j= 0;
   float data,value;
   u8 flag;

   for(j=0;j<4;j++)	              //AO
   {
		 value = DAC_value[j];
		 flag  = CurrentflagAO[j];
		 data = (value - AOParams[j].b)/AOParams[j].a;
    	 SetAoOut(data,j,flag);

    }

   for(j=0;j<4;j++)	  //DO
   {
		 DO_onechannel(j,DO_data[j]);
		  
   } 

 
}

/////////////////////////////////////////////////////////
///<��������> �ѵ��ź�ֵת���ɶ�Ӧ������ֵ
///<����1> ���ź�ֵ
///<����2> ת������	y = a*x + b
///<����ֵ> ��������ֵ
//////////////////////////////////////////////////////////
void getAIPhysicalValue(float *aarr, PARAMS *range )
{   
   char i=0;
    for(i=0;i<12;i++)
    {          
        aarr[i]= getAIonechanelPhyVal(i,CurrentflagAI,aarr, range );

    }

}

float getAIonechanelPhyVal(char channel,char* flag,float *aarr, PARAMS *range )
{
    
	 float ADC_voltage = 0.0;
	 float adc_value =0.0;
	 adc_value= ReadAdOfChannel(channel,flag[channel]);
	 ADC_voltage =range[channel].a*adc_value-range[channel].b;

  	 return   ADC_voltage;

}

/////////////////////////////////////////////////////////////////
///<��������>AOall����,һ���Գ�ʼ������AO�˿�
///<����1> port  δ��
///<����2> par1  ��ʼ������  AO1toAO8 = 1�� AO8toAO1 = 2
///<����3> par2  ʱ����(s) 0,1,2...n
///<����3> par3	 ��ʼ��ֵ (v)
///<����ֵ> δ��
////////////////////////////////////////////////////////////////
float deAOReset(int port,float par1,float par2,float par3)     
{
   	float res = par3; 
	int i;
	u8 flag;
	if(par1 == 1)
	{
	    for(i=0;i<4;i++)
	   {
	      AOAM[i] = AUTO; 	
	      DAC_value[i] = par3;	//����ֵ
	      DAC_data[i] = par3;	 //��ѹֵ
		 flag  = CurrentflagAO[i];
    	 SetAoOut(DAC_data[i],i,flag);
		 delay_ms(2);
	   } 
	}
	else
	{
	   for(i=3;i>=0;i--)
	   {
	      AOAM[i] = AUTO; 	
	      DAC_value[i] = par3;	//����ֵ
	      DAC_data[i] = par3;	 //��ѹֵ
		 flag  = CurrentflagAO[i];
    	 SetAoOut(DAC_data[i],i,flag);
		 	 delay_ms(2); 
	   } 
	}
	return res;
}

/////////////////////////////////////////////////////////////////
///<��������>DOall����,һ���Գ�ʼ������DO�˿�
///<����1> port  δ��
///<����2> par1  ��ʼ������  DO1toDO8 = 1�� DO8toDO1 = 2
///<����3> par2  ʱ����(s) 0,1,2...n
///<����3> par3	 ��ʼ��ֵ (v) 0,1
///<����ֵ> δ��
////////////////////////////////////////////////////////////////
float deDOReset(int port,float par1,float par2,float par3)     
{
   	float res = par3; 
	int i;
	if(par1 == 1)
	{
	    for(i=0;i<4;i++)
	   {	
	      DO_onechannel(i,(int)par3);
	      DO_data[i] = (int)par3;
		  delay_ms(2);
	   } 
	}
	else
	{
	  for(i=3;i>=0;i--)
	   {
	      DO_onechannel(i,(int)par3);
	      DO_data[i] = (int)par3;
		  delay_ms(2);
	   } 
	}
	return res;
}



/////////////////////////////////////////////////////////////////
///<��������> AO ������� 
///<����1> port ѡ����ʱ�ĵ�λ 1--ms  2--s 
///<����2> par1  �趨��ʱ������  1-1000
///<����3> par2,par3  δ��
///<����ֵ>δ�� 
////////////////////////////////////////////////////////////////


void setAOonechanelPhyVal(char port,float dacvl,float range)
{ 
     float DAC_voltage = 0.0;

	 DAC_voltage = dacvl/range*10.0;
	 SetAoOut(DAC_voltage,port,CurrentflagAO[port]);

}

void setAOallchanelPhyVal(float *dacvl,PARAMS *range)
{
   char i;
   for(i=0;i<8;i++)
   {
       setAOonechanelPhyVal(i,dacvl[i],range[i].a);
   }

}
 /*********************************************************************************************************
* Functoin name:       void sendbuffer(void)
* Descriptions:        ��ȡUI������Ϣ������䷢�ͻ�������send_buffer
*                      ��ȡ˳��AI,AO,DI,DO,RGE  ��������Ч����86+12λ��36+8+16+1+1+24��
* input paraments:     ��
* output paraments:    ��    
* Returned values:     ��
*********************************************************************************************************/
 void sendBufferFill (u8 *SentBuffer)
{


   SentBuffer[8]= getIntLowByte(ADC_data[DELEVEL])	;			   //de solution level 
   SentBuffer[9] =getDecHighByte(ADC_data[DELEVEL]);

   SentBuffer[12] =	(DI_data[TSF_PUMP]<<4)|DI_data[TSF_VAV];
   SentBuffer[13] =	DI_data[TSF_PUMP_FALT]<<4|0;

   SentBuffer[20] =	 panelControl;


}
 /*********************************************************************************************************
* Functoin name:       void writeBufferFill(void)
* Descriptions:        ��ȡUI������Ϣ������䷢�ͻ�������send_buffer
*                      ��ȡ˳��AI,RI,AO,DI,DO,RGE  ��������Ч����86+12λ��36+8+16+1+1+24��
* input paraments:     ��
* output paraments:    ��    
* Returned values:     ��
*********************************************************************************************************/
 void writeBufferFill (u8 *writePortsBuffer)
{
 
   int j,i = 0;
   char temp,temp1;
//   char intHighByte,decLowByte,sign;
   char decHighByte,intLowByte;
   float value;

   temp = writePortsBuffer[i++];  //AOAM
   for(j=0;j<8;j++)
   {
     if((temp>>j)&0x01)	AOAM[j] = MANUAL;
	 else AOAM[j] = AUTO;
   }

   temp = writePortsBuffer[i++];  //AO_HANDLER
   for(j=0;j<8;j++)	              //AO
   {
    //  intHighByte = writePortsBuffer[i++];
	  intLowByte  = writePortsBuffer[i++];
	  decHighByte = writePortsBuffer[i++];
	// decLowByte  = writePortsBuffer[i++];  

      if((temp>>j)&0x01)	
      {	     
	  //	 sign = (intHighByte & 0x80)>>7;
	  //   value = (intHighByte&0x7f)*100 + intLowByte + decHighByte/100.0 + decLowByte/10000.0;	

		 value =  intLowByte + decHighByte/100.0 ;	

	//	 if(sign) value = value * -1;
		 DAC_value[j] = value;
//		 data = (value - AOParams[j].b)/AOParams[j].a;
//     	 DAC_onechannel(j,data);
      }
    }

   temp  = writePortsBuffer[i++];  //DO_HANDLER
   temp1 = writePortsBuffer[i++];  //DO
   for(j=0;j<8;j++)	  //DO
   {
      if((temp>>j) & 0x01)
	  {	     
	    if((temp1>>j) & 0x01)
		{
//		   DO_onechannel(j,1);
		   DO_data[j] = 1;
		}
		else 
		{
//		   DO_onechannel(j,0);
		   DO_data[j] = 0;
		}
	  }
   } 

     temp = writePortsBuffer[i++];  //REGAM9--16
   for(j=0;j<8;j++)
   {
    if((temp>>j)&0x01)	AOAM[j] = MANUAL;
	 else AOAM[j] = AUTO;
   }
   temp = writePortsBuffer[i++];  //REGAM1--8
   for(j=0;j<8;j++)
   {
    if((temp>>j)&0x01)	AOAM[j] = MANUAL;
	 else AOAM[j] = AUTO;
   }
   

   temp1 = writePortsBuffer[i++];  	//REG_HANDLER9--16
   temp = writePortsBuffer[i++];  	//REG_HANDLER1--8
   for(j=0;j<8;j++)	              //REG1--8
   {
   //   intHighByte = writePortsBuffer[i++];
	  intLowByte  = writePortsBuffer[i++];
	  decHighByte = writePortsBuffer[i++];
  //	  decLowByte  = writePortsBuffer[i++];  
   //   if((temp>>j)&0x01)	
   //   {
        // sign = (intHighByte & 0x80)>>7;
	    // value = (intHighByte&0x7f)*100 + intLowByte + decHighByte/100.0 + decLowByte/10000.0;	
		 value =  intLowByte + decHighByte/100.0 ;	
		 //if(sign) value = value * -1;	
		 wRegisters[j] = value;
   //   }
    }
	for(j=0;j<8;j++)	              //REG9--16
   {
  //  intHighByte = writePortsBuffer[i++];
	  intLowByte  = writePortsBuffer[i++];
	  decHighByte = writePortsBuffer[i++];
//	  decLowByte  = writePortsBuffer[i++];  
     // if((temp1>>j)&0x01)	
     // {
     //    sign = (intHighByte & 0x80)>>7;
	 //    value = (intHighByte&0x7f)*100 + intLowByte + decHighByte/100.0 + decLowByte/10000.0;	
		value =  intLowByte + decHighByte/100.0 ;	

	//	 if(sign) value = value * -1;	
		 wRegisters[j+8] = value;
     // }
    }

  
}

void writeCtrlSignal(void)
{

   tempRegisters[BUFLEVEL]		=	  ReceivedBuffer[8] + ReceivedBuffer[9]/100	;
   tempRegisters[WSTLEVEL]	 	=	  ReceivedBuffer[10] + ReceivedBuffer[11]/100	;
   tempRegisters[SSTLEVEL]	 	=	  ReceivedBuffer[12] + ReceivedBuffer[13]/100;
   tempRegisters[RELEVEL]	   	=     ReceivedBuffer[14] + ReceivedBuffer[15]/100;

   tempRegisters[LOWBUF]	    =     ReceivedBuffer[17] ;
   tempRegisters[CASETRANSFER] 	=     ReceivedBuffer[18] ;
   tempRegisters[CASEEMERGENCY] =     ReceivedBuffer[19] ;


}

void readCtrlSignal(void)
{
   int i=0;
//  Registers[i++]	= 	 Setpoint[SPHUM]    ;
//  Registers[i++]    = 	 Setpoint[SPTEMP]   ;
//  Registers[i++]    = 	 alarmFlag          ;
  Registers[i++]    =	 deviceRun          ;
  Registers[i++]	= 	 localControl       ;
  Registers[i++]	= 	 panelControl       ;
  Registers[i++]	= 	 runStatus          ;
//  	
//  Registers[i++]    =	 StrSLevelHigh      ;
//  Registers[i++]	= 	 StrSLevelLow       ;
//
//  Registers[i++]	= 	 DeSLevelHigh  		;
//  Registers[i++]	= 	 DeSLevelTrasf 		;	
//  Registers[i++]	= 	 DeSLevelOpt  		;
//  Registers[i++]	= 	 DeSLevelLow		;	
//
//  Registers[i++]	= 	 CtrlParaP			;	
//  Registers[i++]	= 	 CtrlParaI 			;
//  Registers[i++]	= 	 CtrlParaD 			;


}

