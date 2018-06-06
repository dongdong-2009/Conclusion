#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include"runtimedata.h"
#include "ads1115.h"
#include "rtd.h"
#include "dac8554.h" 	   			 
#include "dio.h"	
#include "Globle.h"
#include "LddsPorts.h"	
#include "pid.h"
#include "delay.h"

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
//      u8 i=0;
//   ADC_allchannels(ADC_data,CurrentflagAI);
//   getAIPhysicalValue(ADC_value, AIParams);
//   GetDiMap(DI_data);
//
//   RTD_allchannels(RTD_value);
//
//   System_On    = DI_data[REMONOFF];
//   panelControl = DI_data[LOCALORREMOTE]  ;

	   ADC_value[TOUT]=	17.5;
	   ADC_value[RHOUT]=40.2;
	   ADC_value[TIN]= 20.2;
	   ADC_value[RHIN]=71.4 ;
}




/*********************************************************************************************************
* Functoin name:       void WritePortsData(void)
* Descriptions:        依次设置端口数据 共接收有效数据38位（12+26）
*                      设置顺序：AO,DO,Reg
* input paraments:     无
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/
void writePorts(void)
{
   int j= 0;
   float data,value;
   u8 flag;

   for(j=0;j<8;j++)	              //AO
   {
		 value = DAC_value[j];
		 flag  = CurrentflagAO[j];
		 data = (value - AOParams[j].b)/AOParams[j].a;
    	 SetAoOut(data,j,flag);

    }

   for(j=0;j<8;j++)	  //DO
   {
		 DO_onechannel(j,DO_data[j]);
		  
   } 

 
}
/*********************************************************************************************************
* Functoin name:       void PIDTunning(void)
* Descriptions:        PID参数调制，共接收有效数据24位（12+12）
* input paraments:     无
* output paraments:    无    
* Returned values:     无
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
///<功能描述> 把电信号值转换成对应的物理值
///<参数1> 电信号值
///<参数2> 转换参数	y = a*x + b
///<返回值> 返回物理值
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

float getRTDonechanelPhyVal(char channel,float *temperature )

  {	 	float Tempvalue =0.0;

		RTD_allchannels(temperature) ;
		Tempvalue	 = temperature[channel] ;

		return Tempvalue;
  }


/////////////////////////////////////////////////////////////////
///<功能描述>AOall函数,一次性初始化所有AO端口
///<参数1> port  未用
///<参数2> par1  初始化方向  AO1toAO8 = 1， AO8toAO1 = 2
///<参数3> par2  时间间隔(s) 0,1,2...n
///<参数3> par3	 初始化值 (v)
///<返回值> 未用
////////////////////////////////////////////////////////////////
float deAOReset(int port,float par1,float par2,float par3)     
{
   	float res = par3; 
	int i;
	u8 flag;
	if(par1 == 1)
	{
	    for(i=0;i<8;i++)
	   {
	      AOAM[i] = AUTO; 	
	      DAC_value[i] = par3;	//物理值
	      DAC_data[i] = par3;	 //电压值
		 flag  = CurrentflagAO[i];
    	 SetAoOut(DAC_data[i],i,flag);
		 delay_ms(2);
	   } 
	}
	else
	{
	   for(i=7;i>=0;i--)
	   {
	      AOAM[i] = AUTO; 	
	      DAC_value[i] = par3;	//物理值
	      DAC_data[i] = par3;	 //电压值
		 flag  = CurrentflagAO[i];
    	 SetAoOut(DAC_data[i],i,flag);
		 	 delay_ms(2); 
	   } 
	}
	return res;
}

/////////////////////////////////////////////////////////////////
///<功能描述>DOall函数,一次性初始化所有DO端口
///<参数1> port  未用
///<参数2> par1  初始化方向  DO1toDO8 = 1， DO8toDO1 = 2
///<参数3> par2  时间间隔(s) 0,1,2...n
///<参数3> par3	 初始化值 (v) 0,1
///<返回值> 未用
////////////////////////////////////////////////////////////////
float deDOReset(int port,float par1,float par2,float par3)     
{
   	float res = par3; 
	int i;
	if(par1 == 1)
	{
	    for(i=0;i<8;i++)
	   {	
	      DO_onechannel(i,(int)par3);
	      DO_data[i] = (int)par3;
		  delay_ms(2);
	   } 
	}
	else
	{
	  for(i=7;i>=0;i--)
	   {
	      DO_onechannel(i,(int)par3);
	      DO_data[i] = (int)par3;
		  delay_ms(2);
	   } 
	}
	return res;
}



/////////////////////////////////////////////////////////////////
///<功能描述> AO 物理输出 
///<参数1> port 选择延时的单位 1--ms  2--s 
///<参数2> par1  设定延时的数字  1-1000
///<参数3> par2,par3  未用
///<返回值>未用 
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
* Functoin name:       void UIXXbuffer(void)
* Descriptions:        读取UI所需信息，并填充发送缓存数组send_buffer                      
* input paraments:     无
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/
 void UIsendBufferFill (char *UIsendbuffer)		//touch screen
{
     int SpHRValue = (int)	10*Setpoint[0] ;
	 int SpTValue = (int)	Setpoint[1] ;

	 int  humRatioOut = 0;
	 int  humRatioIn  = 0;
//	 static int i=0;

	 	 humRatioOut =(int)	10*RH2HR( ADC_value[TOUT], ADC_value[RHOUT])  ;
		 humRatioIn	 =(int)	10*RH2HR( ADC_value[TIN],  ADC_value[RHIN])  ;
	   
	    UIsendbuffer[0] = 0x55;	  
        UIsendbuffer[1] = 0x66;       //Address
        UIsendbuffer[2] = 0X01;


        UIsendbuffer[3]  = SpHRValue; 

		UIsendbuffer[4]  =((int)SpTValue/100);	
        UIsendbuffer[5]  =((int)SpTValue%100);

		UIsendbuffer[6]  = humRatioIn; 
        UIsendbuffer[7]  = humRatioOut;

		UIsendbuffer[8]  = getIntLowByte(ADC_value[TIN]);	
        UIsendbuffer[9] = getDecHighByte(ADC_value[TIN]); 

	   	UIsendbuffer[10] = getIntLowByte(ADC_value[TOUT]); 
        UIsendbuffer[11] = getDecHighByte(ADC_value[TOUT]); 

		UIsendbuffer[12] = deviceRun|localControl;	

		UIsendbuffer[19] =  1;
        UIsendbuffer[20] =alarmFlag;
					
        UIsendbuffer[21]= UICheckSentData(UIsendbuffer+UILENGTH); //
		UIsendbuffer[22] = 0x66;	  
        UIsendbuffer[23] = 0x55;       //Address

}

 void UIsubBufferFill (char *ReqSubBuffer)	   //ACC->SLC
{
     int SpHRValue = (int)	10*Setpoint[0] ;
	 int SpTValue = (int)	Setpoint[1] ;

	    ReqSubBuffer[0] = 0x55;	  
        ReqSubBuffer[1] = 0x66;       //Address
        ReqSubBuffer[2] = 0X07;


        ReqSubBuffer[3]  = SpHRValue; 

		ReqSubBuffer[4]  =((int)SpTValue/100);	
        ReqSubBuffer[5]  =((int)SpTValue%100);

		ReqSubBuffer[6]  = 0; 

        ReqSubBuffer[7]  = 0;

		ReqSubBuffer[8]  = getIntLowByte(ADC_value[BUFLEVEL]);	
        ReqSubBuffer[9]  = getDecHighByte(ADC_value[BUFLEVEL]); 

	   	ReqSubBuffer[10] = getIntLowByte(tempRegisters[WSTLEVEL]); 
        ReqSubBuffer[11] = getDecHighByte(tempRegisters[WSTLEVEL]); 

	    ReqSubBuffer[12] = getIntLowByte(tempRegisters[SSTLEVEL]); 
        ReqSubBuffer[13] = getDecHighByte(tempRegisters[SSTLEVEL]); 

	   	ReqSubBuffer[14] = getIntLowByte(tempRegisters[RELEVEL]); 
        ReqSubBuffer[15] = getDecHighByte(tempRegisters[RELEVEL]); 

	    ReqSubBuffer[17] = tempRegisters[LOWBUF];

		ReqSubBuffer[18] = tempRegisters[CASETRANSFER]; 
		ReqSubBuffer[19] = tempRegisters[CASEEMERGENCY]; 

        ReqSubBuffer[20] =alarmFlag;
					
        ReqSubBuffer[21]= UICheckSentData(ReqSubBuffer+UILENGTH); //
		ReqSubBuffer[22] = 0x66;	  
        ReqSubBuffer[23] = 0x55;       //Address

}
 void UIsysBufferFill (char *ReqSysBuffer)				  //ACC->SAC
{
     int SpHRValue = (int)	10*Setpoint[0] ;
	 int SpTValue = (int)	Setpoint[1] ;


	    ReqSysBuffer[0] = 0x55;	  
        ReqSysBuffer[1] = 0x66;       //Address
        ReqSysBuffer[2] = 0X08;


        ReqSysBuffer[3]  = SpHRValue; 

		ReqSysBuffer[4]  =((int)SpTValue/100);	
        ReqSysBuffer[5]  =((int)SpTValue%100);

		ReqSysBuffer[6]  = 0; 
        ReqSysBuffer[7]  = 0;

	    ReqSysBuffer[8]  = getIntLowByte(ADC_value[BUFLEVEL]);	
        ReqSysBuffer[9]  = getDecHighByte(ADC_value[BUFLEVEL]); 

	   	ReqSysBuffer[10] = getIntLowByte(tempRegisters[DELEVEL]); 
        ReqSysBuffer[11] = getDecHighByte(tempRegisters[DELEVEL]); 

		ReqSysBuffer[13] = 0;	

		ReqSysBuffer[19] = 1;
        ReqSysBuffer[20] =alarmFlag;
					
        ReqSysBuffer[21]= UICheckSentData(ReqSysBuffer+UILENGTH); //
		ReqSysBuffer[22] = 0x66;	  
        ReqSysBuffer[23] = 0x55;       //Address

}
 /*********************************************************************************************************
* Functoin name:       void sendbuffer(void)
* Descriptions:        读取UI所需信息，并填充发送缓存数组send_buffer
*                      读取顺序：AI,RI,AO,DI,DO,RGE  共发送有效数据86+12位（36+8+16+1+1+24）
* input paraments:     无
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/
 void sendBufferFill (char *readPortsBuffer)
{

   int i = 0;
   int j;
//   int count=0 ;
   char temp = 0;  

   for(j=0;j<12;j++)		
   {
//    readPortsBuffer[i++] = getIntHighByte(ADC_value[j]);	    //intH
	  readPortsBuffer[i++] = getIntLowByte(ADC_value[j]);	   //intL
	  readPortsBuffer[i++] = getDecHighByte(ADC_value[j]);     //decH
//	  readPortsBuffer[i++] = getDecLowByte(ADC_value[j]);	   //decL
   }
   
   for(j=0;j<4;j++)	       
   {
//    readPortsBuffer[i++] = getIntHighByte(RTD_value[j]);	    //intH
	  readPortsBuffer[i++] = getIntLowByte(RTD_value[j]);	   //intL
	  readPortsBuffer[i++] = getDecHighByte(RTD_value[j]);     //decH
//	  readPortsBuffer[i++] = getDecLowByte(RTD_value[j]);	   //decL
   }
   //读取AOAM位
   for(j=0;j<8;j++)	      
   {
      if(AOAM[j] == MANUAL)
	    temp |= (0x01<<j);
   } 
   readPortsBuffer[i++] = temp;
   temp = 0;
   //读取AO端口值 AO1-AO8
   for(j=0;j<8;j++)		
   {
//    readPortsBuffer[i++] = getIntHighByte(DAC_value[j]);	    //intH
	  readPortsBuffer[i++] = getIntLowByte(DAC_value[j]);	   //intL
	  readPortsBuffer[i++] = getDecHighByte(DAC_value[j]);     //decH
//	  readPortsBuffer[i++] = getDecLowByte(DAC_value[j]);	   //decL
   }
   //读取DI端口值 

   for(j=0;j<8;j++)	  
   {
      if(DI_data[j]) temp |=(0x01<<j);
   }
   readPortsBuffer[i++] = temp;
   temp = 0;
   //读取DO端口值
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

   //读取REG REG1-REG8
   for(j=0;j<16;j++)		
   {
      readPortsBuffer[i++] = getIntHighByte(Registers[j]);	    //intH
	  readPortsBuffer[i++] = getIntLowByte (Registers[j]);	   //intL
   // readPortsBuffer[i++] = getDecHighByte(Registers[j]);     //decH
   // readPortsBuffer[i++] = getDecLowByte (Registers[j]);	   //decL
   }
   
 // System_On				 =   DI_data[REMONOFF];
}
 /*********************************************************************************************************
* Functoin name:       void writeBufferFill(void)
* Descriptions:        读取UI所需信息，并填充发送缓存数组send_buffer
*                      读取顺序：AI,RI,AO,DI,DO,RGE  共发送有效数据86+12位（36+8+16+1+1+24）
* input paraments:     无
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/
 void writeBufferFill (char *writePortsBuffer)
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
	  //   sign = (intHighByte & 0x80)>>7;
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
  int i=0;

	 SetpointPC[SPHUM]       =   wRegisters[i++];
	 SetpointPC[SPTEMP]      =   wRegisters[i++];
//	 alarmFlag			     =  Registers[i++];
	 i++  ;
	 deviceRun				 =  wRegisters[i++];
//	 localControl			 =  Registers[i++];
//	 panelControl			 =  Registers[i++];
//	 runStatus				 =  Registers[i++];
	 i++  ;
	 i++  ;
	 i++  ;

//	 if(wRegisters[i]!=0)
//	 StrSLevelHigh			 =  wRegisters[i++];
//	  if(wRegisters[i]!=0)
//	 StrSLevelLow			 =  wRegisters[i++];
//	  if(wRegisters[i]!=0)
//	 DeSLevelHigh			 =  wRegisters[i++];
//	  if(wRegisters[i]!=0)
//	 DeSLevelTrasf			 =  wRegisters[i++];
//	  if(wRegisters[i]!=0)
//	 DeSLevelOpt			 =  wRegisters[i++];
//	  if(wRegisters[i]!=0)
//	 DeSLevelLow			 =  wRegisters[i++];

//	 CtrlParaP				 =  wRegisters[i++];
//	 CtrlParaI				 =  wRegisters[i++];
//	 CtrlParaD				 =  wRegisters[i++];

}

void readCtrlSignal(void)
{
   int i=0;


  Registers[i++]	= 	 Setpoint[SPHUM]    ;
  Registers[i++]    = 	 Setpoint[SPTEMP]   ;
  Registers[i++]    = 	 alarmFlag          ;
  Registers[i++]    =	 deviceRun          ;
  Registers[i++]	= 	 localControl       ;
  Registers[i++]	= 	 panelControl       ;
  Registers[i++]	= 	 runStatus          ;
  	
  Registers[i++]    =	 StrSLevelHigh      ;
  Registers[i++]	= 	 StrSLevelLow       ;

  Registers[i++]	= 	 DeSLevelHigh  		;
  Registers[i++]	= 	 DeSLevelTrasf 		;	
  Registers[i++]	= 	 DeSLevelOpt  		;
  Registers[i++]	= 	 DeSLevelLow		;	

  Registers[i++]	= 	 CtrlParaP			;	
  Registers[i++]	= 	 CtrlParaI 			;
  Registers[i++]	= 	 CtrlParaD 			;


}

void  UIregisterFill(char * UIwriteRegister)
{
		UIregister[0]=((float)UIwriteRegister[3]*100+(float)UIwriteRegister[4])/10;
	    UIregister[1]=((float)UIwriteRegister[5]*100+(float)UIwriteRegister[6])/10;      
	    UIregister[2]=((float)UIwriteRegister[7]*100+(float)UIwriteRegister[8])/10; //HumSP
	   	Setpoint[0]  =   UIregister[2];
}


void  UIsubregisterFill(char * UIwriteRegister)		 //	slc to acc
{
  		tempRegisters[DELEVEL] 		= (float) (UIwriteRegister[8]+ UIwriteRegister[9]/100);
		tempRegisters[TSF_PUMP]		=  UIwriteRegister[12]>>4 ;
		tempRegisters[TSF_VAVL]		=  UIwriteRegister[12] ;
		tempRegisters[TSF_PUMP_FALT]=  UIwriteRegister[13]>>4 ;



}

void  UIsysregisterFill(char * UIwriteRegister)		   //  sacc to acc
{
		tempRegisters[WSTLEVEL]	=(float) (UIwriteRegister[10]+ UIwriteRegister[11]/100);
		tempRegisters[SSTLEVEL]	=(float) (UIwriteRegister[12]+ UIwriteRegister[13]/100);
	    tempRegisters[RELEVEL]	=(float) (UIwriteRegister[14]+ UIwriteRegister[15]/100);
		tempRegisters[LOWBUF]	= UIwriteRegister[17];
	    tempRegisters[CASETRANSFER]  = UIwriteRegister[18]; 
        tempRegisters[CASEEMERGENCY] = UIwriteRegister[19];


}



