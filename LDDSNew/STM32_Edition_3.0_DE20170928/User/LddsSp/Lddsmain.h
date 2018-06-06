#ifndef _LDDSMAIN_H
#define _LDDSMAIN_H
#include "LddsSp.h"
#include "extvart.h"


  float  UIregister[12]={0}	;
  float  Registers[16]  = {0};
  float  wRegisters[16]	={0};
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
 char autoControl=0;
 char alarmFlag=0;	
 char algorithmstart=0;
 char System_On=0;

//#define DSLEVELSTART		 31 //³ýÊª»»Òº¿ªÊ¼	33
// #define DSLEVELSTOP		 13  //³ýÊª»»ÒºÍ£Ö¹
//#define DSLEVELMAXALARM    40 //³ýÊªÈÜÒºÉÏÏÞ±¨¾¯
//#define DSLEVELMINALARM    5  //³ýÊªÈÜÒºÏÂÏÞ±¨¾¯
//#define SSLEVELMAXALARM    115 //strongÈÜÒºÉÏÏÞ±¨¾¯
//#define SSLEVELMINALARM	 5 //STRONG SOLUTION LOW LIMITED WARNING
//#define SSLEVELMAX		 100 //strongÈÜÒºÉÏ



 char StrSLevelHigh	=  115   ;
 char StrSLevelLow	=	5    ;

 char DeSLevelHigh  =  40	 ;
 char DeSLevelTrasf =  31	 ;	
 char DeSLevelOpt  	=  23    ;
 char DeSLevelLow	=	5    ;	

 float CtrlParaP	=	0	 ;	
 float CtrlParaI 	=	0    ;
 float CtrlParaD 	=	0	;


float  deAOReset(int port,float par1,float par2,float par3);    
float  deDOReset(int port,float par1,float par2,float par3)   ;  

float   delay_fun(int port,float par1,float par2,float par3);

PARAMS AOParams[8] = {{50.0,0.0},{50.0,0.0},{100.0,0.0},{1,0.0},{1,0},{1,0},{1,0},{1,0}};
PARAMS AIParams[12] = {{5.0,0},{10.0,0},{10.0,0},{10.0,0},{6,0},{10,0},{6,0},{10,0},{0.125,25},{0.125,25},{25,0},{25,0}};
AUTOSEL AOAM[8] = {AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO};
AUTOSEL REGAM[16] = {AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO};

float  Setpoint[3]={7.5,16.0,0};
float  SetpointPC[3]={0.0,0.0,0.0};


#endif 
