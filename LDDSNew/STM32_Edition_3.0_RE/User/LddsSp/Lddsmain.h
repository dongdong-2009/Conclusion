#ifndef _LDDSMAIN_H
#define _LDDSMAIN_H
#include "LddsSp.h"
#include "extvart.h"


  float  UIregister[12]={0}	;
  float  Registers[16]  = {0};
  float  wRegisters[16]  = {0};
  float  ADC_value[12] = {0}; 
  float  ADC_data[12]  = {0};
  float  RTD_value[4]  = {0};
  float  DAC_value[8]  = {0};
  float  DAC_data[8]   = {0};
  char   DI_data[8]    = {0};
  char   DO_data[8]    = {0};

 char panelControl=0;
 char panelCStatus=0;  
 char remoteControl=0;
 char localControl=0;
 char localDeviceRun=0;
 char deviceRun=0;
 char runStatus=0;
 char alarmFlag=0;	
 char algorithmstart=0;
 char autoControl=0;

float DeltaCon=43;
float DeltaConPC=0;

char DE_Level=0;
char SS_Level=0;
char De_On=0;
char System_On=0;
char tf_flag=0;
char	Concentration=0;        //除湿系统发送过来的浓度信息
char	Tran_Flag=0;            //换液标志位

float  reAOReset(int port,float par1,float par2,float par3);    
float  reDOReset(int port,float par1,float par2,float par3)   ;  
char   RE_Level_Alarm(void); 

float  delay_fun(int port,float par1,float par2,float par3);
int    count=0;

float AbOutHum=0.0;
float AbInHum=0.0;
float AbDelta=0.0;

float concentration=0.0;
float DE_Levelsingal;
float RHout=0.0;
char  StatusFlag=0;
char  ConFlag=0;

char WkSLevelAlarm  =  95    ;
char WkSLevelHigh   =  90    ;

char RsLevelMaxAlarm =	35	;
char RsLevelStart	  =	30	;	
char RsLevelStop	  = 18	;
char RsLevelMinAlarm =	7	;


char SSLevelAlarm  =  115  ;
char SSLevelHigh   =  90   ;

PARAMS AOParams[8] = {{50.0,0.0},{50.0,0.0},{1.0,0.0},{100.0,0.0},{1,0},{1,0},{1,0},{1,0}};
PARAMS AIParams[12] = {{6.0,0},{10.0,0},{6.0,0},{10.0,0},{0.125,25},{0.125,25},{12.0,0},{60,0},{100,0},{0.06,12},{25,0},{25,0}};
AUTOSEL AOAM[8] = {AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO};
AUTOSEL REGAM[8] = {AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO};


#endif 
