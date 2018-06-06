#ifndef __LOGIC_H
#define __LOGIC_H

#include "stm32f10_timer.h"
#include "analogin.h"
#include "stm32f10_dac.h"
#include "stm32f10_gpio.h"	
#include <math.h>   

#define DESTVALUE             1	//     继电器启动
#define DESPVALUE			  0	//     继电器停止

// preset value
#define DSLEVELSTART		 33 //除湿换液开始
#define DSLEVELSTOP			 31  //除湿换液停止
#define DSLEVELMAXALARM      35 //除湿溶液上限报警
#define DSLEVELMINALARM      5  //除湿溶液下限报警
#define SSLEVELMAXALARM      95 //strong溶液上限报警
#define SSLEVELMAX			 90 //strong溶液上限
#define WSLEVELMAXALARM      95 //strong溶液上限报警
#define WSLEVELMAX			 90 //strong溶液上限
#define CHILLEDVALVEO        100  //chilled water valve init
#define CPUMPO       				 70  //circulation pump init
#define SFANO       				 70  //supply fan init

#define DESTEMPSP            16  //溶液工作区适合温度
#define DEPUMPSP             40  //泵的初始化默认频率
#define DEFANSP              40  //风机的初始化默认频率
#define DESDENSITY           30  //盐溶液浓度  


//AI
#define   FLOWRATE           0   //solution flowrate
#define   CPUMPFB            1   //circulation pump feedback
#define   SFANFB             2   //supply fan feedback
#define   CWVALVEFB			     3   //chilled water feedback
#define   TIN   				     4   //inlet temperature
#define   RHIN  		         5   //inlet RH
#define   TOUT   				     6   //outlet temperature
#define   RHOUT  		         7   //outlet RH
#define   DSLEVEL            8   //dehumidifier level
#define   SSLEVEL            9   //strong solution level
#define   DATASET            10  //RH set value

#define   TSIN		           12  //除湿Inlet温度
#define   TSOUT		           13  //除湿Outlet温度
#define   TWIN		           14  //热水Inlet温度
#define   TWOUT		           15  //热水Outlet温度

//DO
#define   VSD_PUMP 		       0  //VSD pump
#define   VSD_FAN            1  //vsd fan
#define   TRPUMP			       2  //transfer pump
#define	  STVALVE				  	 3  //solution tank valve

//DI
#define   LOCALORREMOTE      0  //本地开关
#define   FAUT_PUMPVSD       1  //pump vsd fault
#define   FAUT_FANVSD        2  //fan vsd fault
#define   FAUT_TFPUMP        3  //transfer pump OL fault
//AO
#define   CPUMP 			     0  //VSD circulation pump
#define   SFAN 			       1  //VSD supply fan
#define   CWVALVE 			   2  //chilled water valve
#define   RHDATA 			     3  //current RH

extern u8 System_On;
extern u8 Re_On;
extern u8 RE_Level;
extern u8 WS_Level;
extern u8 tf_flag;
u8 deh_algorithm(float analogIn[], float arout[]);
u8 deh_transfer(void);
u8 dehStart(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8],u8 dehflag);
u8 dehStop(float arin[12],float arout[8],u8 dout[8]);
void deInit(float arr[8]);
void deClever(float aout[8],u8 dout[8]);
void deDefault(void);
void getlevel(float delevel,float sslevel,float chiltemp,float cwfb);
#endif
