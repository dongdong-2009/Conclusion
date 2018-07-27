#ifndef _STM32F10X_CONFIG_H
#define _STM32F10X_CONFIG_H
	
#include "stm32f10_usart.h" 
#include "stm32f10_dac.h"
#include "stm32f10_gpio.h" 
#include "stm32f10_timer.h"
#include "analogin.h"
#include "dataprocess.h" 
#include "logic.h"
#include "heatpump_ctrl.h"
#include <stdio.h>
#include <string.h>	  

//液位报警信息  正常启动---再生液位过高---再生液位过低----weak solution 液位过高---strong solution 液位过高---启动失败
enum _alarm{start_normal,REhighlevel,RElowlevel,WShighlevel,SShighlevel,Startfail}re_alarm;

u8 panelControl=0;
u8 panelCStatus=0;
u8 remoteControl=0;
u8 localControl=0;
u8 deviceRun=0;
u8 runStatus=0;
u8 alarmFlag=0;
u8 DE_Level=0;
u8 SS_Level=0;
u8 De_On=0;
u8 System_On=0;
u8 tf_flag=0;
u8 Concentration=0;        //除湿系统发送过来的浓度信息
u8 Tran_Flag=0;            //换液标志位

u8 algorithmstart=0;
u8 digitalIn[8];//digital input data storge
u8 digitalOut[8];//digital output data storge
u8 flowratecntH=0;
u8 flowratecntL=0;
float  aimed_solultiontemp;

float rangeIn[12]={10,10,10,10,10,10,10,10,10,10,10,10};//	
float analogIn[16];// 
float TempanalogIn[16];

float rangeOut[8]={10,10,10,10,10,10,10,10}; //
float analogOut[8];//
u8    localDeviceRun=0;
static float  outlethumN [12] = {60,60,60,60,60,60,60,60,60,60,60,60};
static float  outlethumO [12] = {60,60,60,60,60,60,60,60,60,60,60,60};

static float  outletTemN  [12] = {16,16,16,16,16,16,16,16,16,16,16,16};
static float  outletTemO  [12] = {16,16,16,16,16,16,16,16,16,16,16,16};
static float  SetpointValueR[3]= {0,7.4,16}; 
static float  SetpointValueL[2]= {0,7.4};  
static u8    Datamarker;

float concentration=0.0;
float DE_Levelsingal;
float RHout=0.0;
u8 StatusFlag=0;
u8 ConFlag=0;

//****************************************************
u8 dataCbuff[53];
u8 dataDbuff[53];
u8 dataEbuff[5] = {0,0,0,0,0};
u8 dataUbuff[24];
float SetpointValue[3]={0,7.4,16};
float AbOutHum=0.0;
float AbInHum=0.0;
float AbDelta=0.0;

sc8 address1[6]={0x02,0x00,0x01,0x00,0x00,0x03};	 
sc8 address2[6]={0x02,0x00,0x01,0x00,0x00,0x04};

u8 TX1[53]={0x55,0x66,0x02,0x00,0x01,0x00,0x00,0x03,0x00,0x41,0x26,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x55};
u8 TX2[53]={0x55,0x66,0x02,0x00,0x01,0x00,0x00,0x04,0x00,0x41,0x26,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x55};
u8 TX9[53]={0x55,0x66,0x02,0x00,0x01,0x00,0x00,0x01,0x00,0x57,0x26,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x33,0x66,0x55};

u8 tx1[24]={0x55,0x66,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x55};
u8 tx2[24]={0x55,0x66,0x02,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x10,0x66,0x55};
u8 tx3[24]={0x55,0x66,0x03,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x10,0x66,0x55};
u8 tx4[24]={0x55,0x66,0x04,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x10,0x66,0x55};
/***********************************************************/ 

void RCC_Configuration(void);
void dataProcess(void);
void dataResponseLocal(void);

#endif
