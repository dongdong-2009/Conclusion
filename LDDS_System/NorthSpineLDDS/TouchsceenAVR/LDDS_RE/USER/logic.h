#ifndef __LOGIC_H
#define __LOGIC_H

#include "stm32f10x.h"
#include "stm32f10_timer.h"
#include "analogin.h"
#include "stm32f10_dac.h"
#include "stm32f10_gpio.h"	
#include <math.h>   

#define DESTVALUE             1	//     继电器启动
#define DESPVALUE			  0	//     继电器停止

// preset value
#define RSLEVELSTART         30  //再生溶液上限
#define RSLEVELMAXALARM      35  //再生溶液上限
#define RSLEVELSTOP          18  //再生溶液下限
#define RSLEVELMINALARM      10  //再生溶液下限
#define WSLEVELMAX           90  //weak溶液上限
#define WSLEVELMAXALARM      95  //weak溶液上限
#define SSLEVELMAX           90  //weak溶液上限
#define SSLEVELMAXALARM      95  //weak溶液上限
#define HOTVALVEO            10  //热水阀初始值
#define DESTEMPSP            16  //溶液工作区适合温度
#define DEPUMPSP             40  //泵的初始化默认频率
#define DEFANSP              40  //风机的初始化默认频率
#define DESDENSITY           30  //盐溶液浓度  


//AI
#define   TOUT                0   //Inlet温度
#define   RHOUT               1   //Inlet湿度
#define   TIN               2   //Outlet温度
#define   RHIN			         3   //Outlet湿度
#define   RSLEVEL				     4   //再生液位
#define   WSLEVEL		         5   //weak solution液位
#define   TSIN		           12  //除湿Inlet温度
#define   TSOUT		           13  //除湿Outlet温度
#define   TWIN		           14  //热水Inlet温度
#define   TWOUT		           15  //热水Outlet温度

//DO
#define   TFVALVE 		      3  //transfer valve
#define   WSVALVE             2  //weak solution valve
#define   REFAN				  1  //regeneration fan
#define	  CPUMP				  0  //circulation pump
#define   HEATPUMP            4//heat pump

//DI
#define   LOCALORREMOTE      0  //Inlet 温度
#define   FAUT_PUMP          1  //Inlet 温度
#define   FAUT_FAN           2  //Inlet 温度

//AO
#define   HWVALVE 			     0  //Inlet 温度
   
extern u8 De_On;
extern u8 DE_Level;
extern u8 SS_Level;
extern float analogOut[8];
extern u8 digitalOut[8];
u8 reg_algorithm(float analogIn[], float arout[]);
u8 reg_transfer(u8 vflag);
u8 reg_level_alarm(void);
u8 regStart(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8],u8 dehflag);
u8 regStop(float arin[12],float arout[8],u8 dout[8]);
void reInit(float arr[8]);
void reClever(float aout[8],u8 dout[8]);
void reDefault(void);
void getlevel(float relevel,float wslevel,float hottemp,float hwvfb);
extern u8 DE_Level;
extern u8 SS_Level;
extern u8 De_On;
extern u8 System_On;
#endif
