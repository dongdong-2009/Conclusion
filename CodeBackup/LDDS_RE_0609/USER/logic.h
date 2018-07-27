#ifndef __LOGIC_H
#define __LOGIC_H

#include "stm32f10x.h"
#include "stm32f10_timer.h"
#include "analogin.h"
#include "stm32f10_dac.h"
#include "stm32f10_gpio.h"	
#include <math.h>   

#define Number               8

#define DESTVALUE            1	        //�̵�������
#define DESPVALUE			       0	        //�̵���ֹͣ

// preset value
#define RSLEVELSTART         30         //������Һ����
#define RSLEVELMAXALARM      35         //������Һ����
#define RSLEVELSTOP          18         //������Һ����
#define RSLEVELMINALARM      7          //������Һ����
#define WSLEVELMAX           90         //weak��Һ����
#define WSLEVELMAXALARM      95         //weak��Һ����
#define SSLEVELMAX           90         //strong solution ��Һ����
#define SSLEVELMAXALARM      115         //strong solution ��Һ����
#define HOTVALVEO            10         //��ˮ����ʼֵ
#define DESTEMPSP            16         //��Һ�������ʺ��¶�
#define DEPUMPSP             40         //�õĳ�ʼ��Ĭ��Ƶ��
#define DEFANSP              40         //����ĳ�ʼ��Ĭ��Ƶ��
#define DESDENSITY           30         //����ҺŨ��  
#define DELTAHumidity        43         //�����ھ���ʪ�Ȳ�

//AI
#define   TOUT               0          //outlet�¶�
#define   RHOUT              1          //outletʪ��
#define   TIN                2          //inlet�¶�
#define   RHIN			         3          //inletʪ��
#define   RSLEVEL				     4          //����Һλ  RE LEVEL
#define   WSLEVEL		         5          //weak solutionҺλ   WS LEVEL
#define   DE_LEVEL           7          //DE ϵͳ�ź�
#define   TSIN		           12         //solution Inlet�¶�
#define   TSOUT		           13         //solution Outlet�¶�
#define   TWIN		           14         //hot water Inlet�¶�
#define   TWOUT		           15         //hot water Outlet�¶�

//DO
#define	  CPUMP				       0          //circulation pump
#define   REFAN				       1          //regeneration fan
#define   WSVALVE            2          //weak solution valve
#define   TFVALVE 		       3          //transfer valve
#define   HEATPUMP           4          //heat pump
#define 	RE_ALARM           5          //������Ϣ

//DI
#define   LOCALORREMOTE      0          //Local or remote mode selection 
#define   FAUT_PUMP          1          //pump 
#define   FAUT_FAN           2          //fan
#define 	REMOTEONFF         4          //Remote on/off
#define   DETransFlag        7          //de ��Һ��־λ

//AO
#define   HWVALVE 			     0          //hot water valve

extern u8 System_On;
extern u8 DE_Level;                     //��ʪҺλ
extern u8 SS_Level;                     //ǿ��ҺҺλ
extern u8 System_On;                    //ϵͳ������Ϣ
extern u8 De_On;                        //��ʪϵͳ����״̬
extern u8 DE_Level;                     //��ʪҺλ
extern u8 SS_Level;                     //ǿ��ҺҺλ
extern float analogOut[8];              //ģ�������Ϣ
extern u8 digitalOut[8];                //���������Ϣ
extern float analogIn[16];              //���ݿ�����

u8 reg_algorithm(float analogIn[], float arout[]);                                       //�����㷨��Ϣ
u8 regStart(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8],u8 dehflag);           //����ϵͳ����
u8 regStop(float arin[12],float arout[8],u8 dout[8]);                                    //����ϵͳ�ر�
void reInit(float arr[8]);                                                               //����ϵͳ��ʼ��
void reClever(float aout[8],u8 dout[8]);                                                 //�豸�������
void reDefault(void);                                                                    //�豸Ĭ��ģʽ��������
void getlevel(float relevel,float wslevel,float hottemp,float hwvfb,float tempout);                    //��ȡҺλ��Ϣ

float ConCalculate(void);                                                                //Ũ�ȼ���  Concentration Calculate  
float RH2HR(float temp, float relativehum);                                              //���ʪ�Ⱥ;���ʪ��ת��
u8 JudgeFlag(void);
extern float concentration;
extern u8 Tran_Flag;
//u8 De_TranFlag=0;

u8 RE_Level_Alarm(void);                                                                 //����ϵͳҺλ����
u8 SS_Re_Transfer(u8 TFlag);									                                               //��Һ����
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
