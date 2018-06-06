#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include"runtimedata.h"
#include "adc.h"
#include "rtd.h"
#include "dac.h" 	   			 
#include "pid.h"
#include "digital_io.h"	
#include "LddsSp.h"	

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

   ADC_allchannels(ADC_data);  
   getAIPhysicalValue(ADC_value, AIParams);
   RTD_allchannels(RTD_value);
   DI_allchannels(DI_data);
   System_On =	 DI_data[REMOTEONFF];
}

/*********************************************************************************************************
* Functoin name:       void WritePortsData(void)
* Descriptions:        �������ö˿����� ��������Ч����38λ��12+26��
*                      ����˳��AO,DO,Reg
* input paraments:     ��
* output paraments:    ��    
* Returned values:     ��
*********************************************************************************************************/
void writePorts( void)
{
   int j= 0;
   float data,value;

   
   for(j=0;j<8;j++)	              //AO
   {
		 value = DAC_value[j];
		 data = (value - AOParams[j].b)/AOParams[j].a;
     	 DAC_onechannel(j,data);

    }

   for(j=0;j<8;j++)	  //DO
   {
		DO_onechannel(j,DO_data[j]);
		  
   } 

 
}
/*********************************************************************************************************
* Functoin name:       void PIDTunning(void)
* Descriptions:        PID�������ƣ���������Ч����24λ��12+12��
* input paraments:     ��
* output paraments:    ��    
* Returned values:     ��
*********************************************************************************************************/
void writePID(char* writePIDBuffer)
{
  int j,cnt,i = 0;
  char intHighByte[6],intLowByte[6],decHighByte[6],decLowByte[6],flag[6];
  float Kp,Ki,Kd,sp;
  char handle; //handle bit

  handle = writePIDBuffer[i++] & 0x0f;
  for(cnt=0;cnt<4;cnt++)
  {
     for(j=0;j<6;j++)
     {
	    intHighByte[j]  = writePIDBuffer[i++];
		intLowByte[j]  = writePIDBuffer[i++];
		decHighByte[j] = writePIDBuffer[i++];
		decLowByte[j]  = writePIDBuffer[i++];
        flag[j] = (intHighByte[j] & 0x80)>>7;
     }
     Kp = (intHighByte[0]&0x7f)*100 + intLowByte[0] + decHighByte[0]/100.0 + decLowByte[0]/10000.0;
     Ki = (intHighByte[1]&0x7f)*100 + intLowByte[1] + decHighByte[1]/100.0 + decLowByte[1]/10000.0;
     Kd = (intHighByte[2]&0x7f)*100 + intLowByte[2] + decHighByte[2]/100.0 + decLowByte[2]/10000.0;
     sp = (intHighByte[3]&0x7f)*100 + intLowByte[3] + decHighByte[3]/100.0 + decLowByte[3]/10000.0;
     if(flag[0]) Kp = Kp * -1;
     if(flag[1]) Ki = Ki * -1;
     if(flag[2]) Kd = Kd * -1;
     if(flag[3]) sp = sp * -1;

	 if((handle>>cnt) & 0x01)
	    PID_SetValue(cnt,Kp,Ki,Kd,sp);
  }
}

void readPID(char* readPIDBuffer)
{
   int i = 0;
   int j,c; 

   for(j=0;j<4;j++)		//AI1-AI12
   {
      readPIDBuffer[i++] = getIntHighByte(PidPar[j].Kp);	    //intH
	  readPIDBuffer[i++] = getIntLowByte(PidPar[j].Kp);	   //intL
	  readPIDBuffer[i++] = getDecHighByte(PidPar[j].Kp);     //decH
	  readPIDBuffer[i++] = getDecLowByte(PidPar[j].Kp);	   //decL

	  readPIDBuffer[i++] = getIntHighByte(PidPar[j].Ki);	    //intH
	  readPIDBuffer[i++] = getIntLowByte(PidPar[j].Ki);	   //intL
	  readPIDBuffer[i++] = getDecHighByte(PidPar[j].Ki);     //decH
	  readPIDBuffer[i++] = getDecLowByte(PidPar[j].Ki);	   //decL

	  readPIDBuffer[i++] = getIntHighByte(PidPar[j].Kd);	    //intH
	  readPIDBuffer[i++] = getIntLowByte(PidPar[j].Kd);	   //intL
	  readPIDBuffer[i++] = getDecHighByte(PidPar[j].Kd);     //decH
	  readPIDBuffer[i++] = getDecLowByte(PidPar[j].Kd);	   //decL

	  readPIDBuffer[i++] = getIntHighByte(PidPar[j].sp);	    //intH
	  readPIDBuffer[i++] = getIntLowByte(PidPar[j].sp);	   //intL
	  readPIDBuffer[i++] = getDecHighByte(PidPar[j].sp);     //decH
	  readPIDBuffer[i++] = getDecLowByte(PidPar[j].sp);	   //decL

	  for(c=0;c<8;c++)
	   readPIDBuffer[i++] = 0;
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
        aarr[i]=getAIonechanelPhyVal(i,aarr,range);
    }

}

float getAIonechanelPhyVal(char channel,float *aarr, PARAMS *range )
{
    
	float ADC_voltage = 0.0;

	 ADC_onechannel (channel,aarr);
	 ADC_voltage =range[channel].a*aarr[channel]-range[channel].b;

  	 return   ADC_voltage;

}

float getRTDonechanelPhyVal(char channel,float *temperature )

  {	 	float Tempvalue =0.0;

		RTD_allchannels(temperature) ;
		Tempvalue	 = temperature[channel] ;

		return Tempvalue;
  }


/////////////////////////////////////////////////////////////////
///<��������>AOall����,һ���Գ�ʼ������AO�˿�
///<����1> port  δ��
///<����2> par1  ��ʼ������  AO1toAO8 = 1�� AO8toAO1 = 2
///<����3> par2  ʱ����(s) 0,1,2...n
///<����3> par3	 ��ʼ��ֵ (v)
///<����ֵ> δ��
////////////////////////////////////////////////////////////////
float reAOReset(int port,float par1,float par2,float par3)     
{
   	float res = par3; 
	int i;
	if(par1 == 1)
	{
	    for(i=0;i<8;i++)
	   {
	      AOAM[i] = AUTO; 	
	      DAC_value[i] = par3;	//����ֵ
	      DAC_data[i] = par3;	 //��ѹֵ
	      DAC_onechannel(i,DAC_data[i]); 
		  delay_fun(2,par2,0,0);
	   } 
	}
	else
	{
	   for(i=7;i>=0;i--)
	   {
	      AOAM[i] = AUTO; 	
	      DAC_value[i] = par3;	//����ֵ
	      DAC_data[i] = par3;	 //��ѹֵ
	      DAC_onechannel(i,DAC_data[i]);
		  delay_fun(2,par2,0,0);   
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
float reDOReset(int port,float par1,float par2,float par3)     
{
   	float res = par3; 
	int i;
	if(par1 == 1)
	{
	    for(i=0;i<8;i++)
	   {	
	      DO_onechannel(i,(int)par3);
	      DO_data[i] = (int)par3;
		  delay_fun(2,par2,0,0);
	   } 
	}
	else
	{
	  for(i=7;i>=0;i--)
	   {
	      DO_onechannel(i,(int)par3);
	      DO_data[i] = (int)par3;
		  delay_fun(2,par2,0,0);
	   } 
	}
	return res;
}









/////////////////////////////////////////////////////////////////
///<��������> �ӳٺ��� 
///<����1> port ѡ����ʱ�ĵ�λ 1--ms  2--s 
///<����2> par1  �趨��ʱ������  1-1000
///<����3> par2,par3  δ��
///<����ֵ>δ�� 
////////////////////////////////////////////////////////////////
float delay_fun(int port,float par1,float par2,float par3)
{ 
    float res;
	unsigned long count = 0;
	if(port == 1)
	{
	  count = (unsigned long)par1*8000;
	  if(count>0)
	    while(count--);
	}
	else if(port == 2)
	{
	  count = (unsigned long)par1*8000*1000;
	  if(count>0)
	     while(count--);
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

//float setAOPhysicalValue(float eletricData,PARAMS par)
//{   
//	return  (eletricData - par.b)/par.a;
//}



void setAOonechanelPhyVal(char port,float dacvl,float range)
{ 
     float DAC_voltage = 0.0;

	 DAC_voltage = dacvl/range*10.0;
	 
	 DAC_onechannel(port, DAC_voltage);

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
* Functoin name:       void UIsendbuffer(void)
* Descriptions:        ��ȡUI������Ϣ������䷢�ͻ�������send_buffer
*                      ��ȡ˳��AI,RI,AO,DI,DO,RGE  ��������Ч����86+12λ��36+8+16+1+1+24��
* input paraments:     ��
* output paraments:    ��    
* Returned values:     ��
*********************************************************************************************************/
 void UIsendBufferFill (char *UIsendbuffer)
{
//     int spValue = (int)	10*Setpoint[0] ;
	 int  humRatioOut = 0;
	 int  humRatioIn  = 0;

			humRatioOut	 =(int)	10*RH2HR( ADC_value[TOUT], ADC_value[RHOUT])  ;
		    humRatioIn	 =(int)	10*RH2HR( ADC_value[TIN],  ADC_value[RHIN])  ;
 
        UIsendbuffer[3]  = getIntLowByte(humRatioOut); 
        UIsendbuffer[4]  = getDecHighByte(humRatioOut); 

//		UIsendbuffer[5]  =((int)spValue/100);	
//        UIsendbuffer[6]  =((int)spValue%100);

		UIsendbuffer[7]  = getIntLowByte(humRatioIn); 
        UIsendbuffer[8]  = getDecHighByte(humRatioIn);

		UIsendbuffer[9]  = deviceRun|localControl;	
        UIsendbuffer[10] = 0;

	   	UIsendbuffer[11] = getIntLowByte(ADC_value[TOUT]); 
        UIsendbuffer[12] = getDecHighByte(ADC_value[TOUT]); 
		UIsendbuffer[19] =  1;
        UIsendbuffer[20] =alarmFlag;
					
        UIsendbuffer[21]= UICheckSentData(UIsendbuffer+UILENGTH); //


}

 /*********************************************************************************************************
* Functoin name:       void sendbuffer(void)
* Descriptions:        ��ȡUI������Ϣ������䷢�ͻ�������send_buffer
*                      ��ȡ˳��AI,RI,AO,DI,DO,RGE  ��������Ч����86+12λ��36+8+16+1+1+24��
* input paraments:     ��
* output paraments:    ��    
* Returned values:     ��
*********************************************************************************************************/
 void sendBufferFill (char *readPortsBuffer)
{

   int i = 0;
   int j;
   char temp = 0;  


   for(j=0;j<12;j++)		
   {

      readPortsBuffer[i++] = getIntHighByte(ADC_value[j]);	    //intH
	  readPortsBuffer[i++] = getIntLowByte(ADC_value[j]);	   //intL
	  readPortsBuffer[i++] = getDecHighByte(ADC_value[j]);     //decH
	  readPortsBuffer[i++] = getDecLowByte(ADC_value[j]);	   //decL
   }
   
   for(j=0;j<4;j++)	       
   {
      readPortsBuffer[i++] = getIntHighByte(RTD_value[j]);	    //intH
	  readPortsBuffer[i++] = getIntLowByte(RTD_value[j]);	   //intL
	  readPortsBuffer[i++] = getDecHighByte(RTD_value[j]);     //decH
	  readPortsBuffer[i++] = getDecLowByte(RTD_value[j]);	   //decL
   }
   //��ȡAOAMλ
   for(j=0;j<8;j++)	      
   {
      if(AOAM[j] == MANUAL)
	    temp |= (0x01<<j);
   } 
   readPortsBuffer[i++] = temp;
   temp = 0;
   //��ȡAO�˿�ֵ AO1-AO8
   for(j=0;j<8;j++)		
   {
      readPortsBuffer[i++] = getIntHighByte(DAC_value[j]);	    //intH
	  readPortsBuffer[i++] = getIntLowByte(DAC_value[j]);	   //intL
	  readPortsBuffer[i++] = getDecHighByte(DAC_value[j]);     //decH
	  readPortsBuffer[i++] = getDecLowByte(DAC_value[j]);	   //decL
   }
   //��ȡDI�˿�ֵ 

   for(j=0;j<8;j++)	  
   {
      if(DI_data[j]) temp |=(0x01<<j);
   }
   readPortsBuffer[i++] = temp;
   temp = 0;
   //��ȡDO�˿�ֵ
   for(j=0;j<8;j++)	 
   {
      if(DO_data[j]) temp |=(1<<j);
   }
   readPortsBuffer[i++] = temp;
   temp = 0;

   for(j=0;j<8;j++)	      //REGAM
   {
      if(REGAM[j] == MANUAL)
	    temp |= (0x01<<j);
   }
   readPortsBuffer[i++] = temp;
   temp = 0;

   for(j=0;j<8;j++)	      //REGAM
   {
      if(REGAM[j] == MANUAL)
	    temp |= (0x01<<j);
   }
   readPortsBuffer[i++] = temp;
   temp = 0;

   //��ȡREG REG1-REG8
   for(j=0;j<16;j++)		
   {
      readPortsBuffer[i++] = getIntHighByte(Registers[j]);	    //intH
	  readPortsBuffer[i++] = getIntLowByte (Registers[j]);	   //intL
	  readPortsBuffer[i++] = getDecHighByte(Registers[j]);     //decH
	  readPortsBuffer[i++] = getDecLowByte (Registers[j]);	   //decL
   }
 // System_On				 =   DI_data[REMONOFF];
}
 /*********************************************************************************************************
* Functoin name:       void writeBufferFill(void)
* Descriptions:        ��ȡUI������Ϣ������䷢�ͻ�������send_buffer
*                      ��ȡ˳��AI,RI,AO,DI,DO,RGE  ��������Ч����86+12λ��36+8+16+1+1+24��
* input paraments:     ��
* output paraments:    ��    
* Returned values:     ��
*********************************************************************************************************/
 void writeBufferFill (char *writePortsBuffer)
{
 
   int j,i = 0;
   char temp,temp1;
   char intHighByte,intLowByte,decHighByte,decLowByte,sign;
   float value;

   temp = writePortsBuffer[i++];  //AOAM
   for(j=0;j<8;j++)
   {
     if((temp>>j)&0x01)	AOAM[j] = MANUAL;
	 else AOAM[j] = AUTO;
   }
 if(autoControl==0)
 {
   temp = writePortsBuffer[i++];  //AO_HANDLER
   for(j=0;j<8;j++)	              //AO
   {
      intHighByte = writePortsBuffer[i++];
	  intLowByte  = writePortsBuffer[i++];
	  decHighByte = writePortsBuffer[i++];
	  decLowByte  = writePortsBuffer[i++];  

      if((temp>>j)&0x01)	
      {	     
		 sign = (intHighByte & 0x80)>>7;
	     value = (intHighByte&0x7f)*100 + intLowByte + decHighByte/100.0 + decLowByte/10000.0;	
		 if(sign) value = value * -1;
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
      intHighByte = writePortsBuffer[i++];
	  intLowByte  = writePortsBuffer[i++];
	  decHighByte = writePortsBuffer[i++];
	  decLowByte  = writePortsBuffer[i++];  
   //   if((temp>>j)&0x01)	
   //   {
         sign = (intHighByte & 0x80)>>7;
	     value = (intHighByte&0x7f)*100 + intLowByte + decHighByte/100.0 + decLowByte/10000.0;	
		 if(sign) value = value * -1;	
		 wRegisters[j] = value;
   //   }
    }
	for(j=0;j<8;j++)	              //REG9--16
   {
      intHighByte = writePortsBuffer[i++];
	  intLowByte  = writePortsBuffer[i++];
	  decHighByte = writePortsBuffer[i++];
	  decLowByte  = writePortsBuffer[i++];  
     // if((temp1>>j)&0x01)	
     // {
         sign = (intHighByte & 0x80)>>7;
	     value = (intHighByte&0x7f)*100 + intLowByte + decHighByte/100.0 + decLowByte/10000.0;	
		 if(sign) value = value * -1;	
		 wRegisters[j+8] = value;
     // }
    }

  
}


void writeCtrlSignal(void)
{
    int i=0;

	 i++;
	 DeltaConPC              =   wRegisters[i++];
//	 alarmFlag			     =  Registers[i++];
	 i++  ;
	 deviceRun				 =  wRegisters[i++];
	 autoControl			 =  wRegisters[i++];
//	 localControl			 =  Registers[i++];
//	 panelControl			 =  Registers[i++];
//	 runStatus				 =  Registers[i++];

	 i++  ;
	 i++  ;

	 if(wRegisters[i]!=0)
	 WkSLevelAlarm			 =  wRegisters[i++];
	  if(wRegisters[i]!=0)
	 WkSLevelHigh			 =  wRegisters[i++];
	  if(wRegisters[i]!=0)
	 RsLevelMaxAlarm			 =  wRegisters[i++];
	  if(wRegisters[i]!=0)
	 RsLevelStart			 =  wRegisters[i++];
	  if(wRegisters[i]!=0)
	 RsLevelStop			 =  wRegisters[i++];
	  if(wRegisters[i]!=0)
	 RsLevelMinAlarm			 =  wRegisters[i++];
	  if(wRegisters[i]!=0)
	 SSLevelAlarm			 =  wRegisters[i++];
	  if(wRegisters[i]!=0)
	 SSLevelHigh			 =  wRegisters[i++];

}

void readCtrlSignal(void)
{
  int i=0;

  i++;

  Registers[i++]    = 	 DeltaCon   			;
  Registers[i++]    = 	 alarmFlag        		;
  Registers[i++]    =	 deviceRun  			;
  Registers[i++]	= 	 autoControl			;
  Registers[i++]	= 	 panelControl       ;
  Registers[i++]	= 	 runStatus          ;
  	
  Registers[i++]    =	 WkSLevelAlarm      ;
  Registers[i++]	= 	 WkSLevelHigh       ;

  Registers[i++]	= 	 RsLevelMaxAlarm 		;
  Registers[i++]	= 	 RsLevelStart	 		;	
  Registers[i++]	= 	 RsLevelStop	  		;
  Registers[i++]	= 	 RsLevelMinAlarm		;	

  Registers[i++]	= 	 SSLevelAlarm	  		;
  Registers[i++]	= 	 SSLevelHigh		;	

}

void  UIregisterFill(char * UIwriteRegister)
{
	    UIregister[0]=((float)UIwriteRegister[3]*100+(float)UIwriteRegister[4])/10;
	    UIregister[1]=((float)UIwriteRegister[5]*100+(float)UIwriteRegister[6])/10;      
	    UIregister[2]=((float)UIwriteRegister[7]*100+(float)UIwriteRegister[8])/10; //HumSP
//	   	Setpoint[0]=   UIregister[2];

}



/*********************************************************************************************************
* Functoin name:       void LUTDataConversion(void)
* Descriptions:        �ѽ��յ��Ĳ�����ݣ�lookuptable����һ������ֱ����
*                  	   RowScale��ColumnScale��TableData����������
* input paraments:     ��
* output paraments:    ��    
* Returned values:     ��
*********************************************************************************************************
void LUTDataConversion(char* receivedData)
{
   int i = 0;
   int j,var;
   float temp;
   char intHighByte,intLowByte,decHighByte,decLowByte,sign;

   RowNum = receivedData[i++];
   ColNum = receivedData[i++];
    
   for(j=0;j<RowNum;j++)	  //RowScale
   { 
       intHighByte = receivedData[i++];
	   intLowByte  = receivedData[i++];
	   decHighByte = receivedData[i++];
	   decLowByte  = receivedData[i++];
	   sign = (intHighByte & 0x80)>>7;
	   temp = (intHighByte&0x7f)*100 + intLowByte + decHighByte/100.0 + decLowByte/10000.0;
	   if(sign)	 temp = temp * -1;
       RowScale[j] = temp;
    }

	for(j=0;j<ColNum;j++)	  //ColumnScale
    {  
	   intHighByte = receivedData[i++];
	   intLowByte  = receivedData[i++];
	   decHighByte = receivedData[i++];
	   decLowByte  = receivedData[i++];
	   sign = (intHighByte & 0x80)>>7;
	   temp = (intHighByte&0x7f)*100 + intLowByte + decHighByte/100.0 + decLowByte/10000.0;
	   if(sign)	 temp = temp * -1;
       ColumnScale[j] = temp;
    }

	for(j=0;j<RowNum;j++)	  //TableDataScale
    {  
       for(var=0;var<ColNum;var++)
	   {
		  intHighByte = receivedData[i++];
	      intLowByte  = receivedData[i++];
	      decHighByte = receivedData[i++];
	      decLowByte  = receivedData[i++];
	      sign = (intHighByte & 0x80)>>7;
	      temp = (intHighByte&0x7f)*100 + intLowByte + decHighByte/100.0 + decLowByte/10000.0;
	      if(sign)	 temp = temp * -1;
          TableData[j][var] = temp;
	   }
    }
}
*/
