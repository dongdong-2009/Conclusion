#ifndef __LOGIC_H
#define __LOGIC_H

#include "stm32f10x.h"
#include "stm32f10_timer.h"
#include "analogin.h"
#include "stm32f10_dac.h"
#include "stm32f10_gpio.h"	
#include <math.h>   

#define DESTVALUE             1	//     �̵�������
#define DESPVALUE			  0	//     �̵���ֹͣ

// preset value
#define RSLEVELSTART         30  //������Һ����
#define RSLEVELMAXALARM      35  //������Һ����
#define RSLEVELSTOP          18  //������Һ����
#define RSLEVELMINALARM      10  //������Һ����
#define WSLEVELMAX           90  //weak��Һ����
#define WSLEVELMAXALARM      95  //weak��Һ����
#define SSLEVELMAX           90  //weak��Һ����
#define SSLEVELMAXALARM      95  //weak��Һ����
#define HOTVALVEO            10  //��ˮ����ʼֵ
#define DESTEMPSP            16  //��Һ�������ʺ��¶�
#define DEPUMPSP             40  //�õĳ�ʼ��Ĭ��Ƶ��
#define DEFANSP              40  //����ĳ�ʼ��Ĭ��Ƶ��
#define DESDENSITY           30  //����ҺŨ��  


//AI
#define   TOUT                0   //Inlet�¶�
#define   RHOUT               1   //Inletʪ��
#define   TIN               2   //Outlet�¶�
#define   RHIN			         3   //Outletʪ��
#define   RSLEVEL				     4   //����Һλ
#define   WSLEVEL		         5   //weak solutionҺλ
#define   TSIN		           12  //��ʪInlet�¶�
#define   TSOUT		           13  //��ʪOutlet�¶�
#define   TWIN		           14  //��ˮInlet�¶�
#define   TWOUT		           15  //��ˮOutlet�¶�

//DO
#define   TFVALVE 		      3  //transfer valve
#define   WSVALVE             2  //weak solution valve
#define   REFAN				  1  //regeneration fan
#define	  CPUMP				  0  //circulation pump
#define   HEATPUMP            4//heat pump

//DI
#define   LOCALORREMOTE      0  //Inlet �¶�
#define   FAUT_PUMP          1  //Inlet �¶�
#define   FAUT_FAN           2  //Inlet �¶�

//AO
#define   HWVALVE 			     0  //Inlet �¶�
   
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
