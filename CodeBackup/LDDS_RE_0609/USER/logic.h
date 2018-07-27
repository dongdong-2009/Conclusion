#ifndef __LOGIC_H
#define __LOGIC_H

#include "stm32f10x.h"
#include "stm32f10_timer.h"
#include "analogin.h"
#include "stm32f10_dac.h"
#include "stm32f10_gpio.h"	
#include <math.h>   

#define Number               8

#define DESTVALUE            1	        //继电器启动
#define DESPVALUE			       0	        //继电器停止

// preset value
#define RSLEVELSTART         30         //再生溶液上限
#define RSLEVELMAXALARM      35         //再生溶液上限
#define RSLEVELSTOP          18         //再生溶液下限
#define RSLEVELMINALARM      7          //再生溶液下限
#define WSLEVELMAX           90         //weak溶液上限
#define WSLEVELMAXALARM      95         //weak溶液上限
#define SSLEVELMAX           90         //strong solution 溶液上限
#define SSLEVELMAXALARM      115         //strong solution 溶液上限
#define HOTVALVEO            10         //热水阀初始值
#define DESTEMPSP            16         //溶液工作区适合温度
#define DEPUMPSP             40         //泵的初始化默认频率
#define DEFANSP              40         //风机的初始化默认频率
#define DESDENSITY           30         //盐溶液浓度  
#define DELTAHumidity        43         //进出口绝对湿度差

//AI
#define   TOUT               0          //outlet温度
#define   RHOUT              1          //outlet湿度
#define   TIN                2          //inlet温度
#define   RHIN			         3          //inlet湿度
#define   RSLEVEL				     4          //再生液位  RE LEVEL
#define   WSLEVEL		         5          //weak solution液位   WS LEVEL
#define   DE_LEVEL           7          //DE 系统信号
#define   TSIN		           12         //solution Inlet温度
#define   TSOUT		           13         //solution Outlet温度
#define   TWIN		           14         //hot water Inlet温度
#define   TWOUT		           15         //hot water Outlet温度

//DO
#define	  CPUMP				       0          //circulation pump
#define   REFAN				       1          //regeneration fan
#define   WSVALVE            2          //weak solution valve
#define   TFVALVE 		       3          //transfer valve
#define   HEATPUMP           4          //heat pump
#define 	RE_ALARM           5          //报警信息

//DI
#define   LOCALORREMOTE      0          //Local or remote mode selection 
#define   FAUT_PUMP          1          //pump 
#define   FAUT_FAN           2          //fan
#define 	REMOTEONFF         4          //Remote on/off
#define   DETransFlag        7          //de 换液标志位

//AO
#define   HWVALVE 			     0          //hot water valve

extern u8 System_On;
extern u8 DE_Level;                     //除湿液位
extern u8 SS_Level;                     //强溶液液位
extern u8 System_On;                    //系统运行信息
extern u8 De_On;                        //除湿系统运行状态
extern u8 DE_Level;                     //除湿液位
extern u8 SS_Level;                     //强溶液液位
extern float analogOut[8];              //模拟输出信息
extern u8 digitalOut[8];                //数字输出信息
extern float analogIn[16];              //数据库数据

u8 reg_algorithm(float analogIn[], float arout[]);                                       //再生算法信息
u8 regStart(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8],u8 dehflag);           //再生系统启动
u8 regStop(float arin[12],float arout[8],u8 dout[8]);                                    //再生系统关闭
void reInit(float arr[8]);                                                               //再生系统初始化
void reClever(float aout[8],u8 dout[8]);                                                 //设备清零操作
void reDefault(void);                                                                    //设备默认模式参数设置
void getlevel(float relevel,float wslevel,float hottemp,float hwvfb,float tempout);                    //读取液位信息

float ConCalculate(void);                                                                //浓度计算  Concentration Calculate  
float RH2HR(float temp, float relativehum);                                              //相对湿度和绝对湿度转换
u8 JudgeFlag(void);
extern float concentration;
extern u8 Tran_Flag;
//u8 De_TranFlag=0;

u8 RE_Level_Alarm(void);                                                                 //再生系统液位报警
u8 SS_Re_Transfer(u8 TFlag);									                                               //换液函数
float AverageFilter(float data);
float recursive_average_filter(float data);
extern float DE_Levelsingal;
extern u8 StatusFlag;
extern u8 ConFlag;
extern float RHout;
extern float AbDelta;
extern float rangeIn[12];
extern int count;
extern float ValueBuf[Number];
extern float valuebuf[Number+1];
extern float AbdeltaHum;
extern float InletSolutemp;
#endif
