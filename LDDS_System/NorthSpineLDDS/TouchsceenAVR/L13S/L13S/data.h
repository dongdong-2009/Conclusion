#ifndef PID_H
#define PID_H

#include "math.h"
#include "LCD.h"
#include "touch.h"
#include "usart0.h"
#include "usart1.h"
#include "Sensor.h"
#include "UI.h"

#define SCALING_FACTOR  128
typedef struct PID_DATA{  double SetPoint; // 设定目标 Desired Value
 double Proportion; // 比例常数 Proportional Const
 double Integral; // 积分常数 Integral Const
 double Derivative; // 微分常数 Derivative Const
 double LastError; // Error[-1]
 double PrevError; // Error[-2]
 double SumError; // Sums of Errors 
 } pidData_t;
 
void usarS(void);
void usarP(unsigned int data1,unsigned int data2,unsigned int data3,unsigned int data4,unsigned int data5,unsigned int data6,unsigned int data7,unsigned int data8,unsigned int data9,unsigned int data10,unsigned int data11,unsigned int data12);
void usarH(unsigned int data1,unsigned int data2,unsigned int data3,unsigned int data4,unsigned int data5,unsigned int data6,unsigned int data7,unsigned int data8,unsigned int data9,unsigned int data10,unsigned int data11,unsigned int data12);
void usarT(unsigned int data1);
void usarSD(void);
void usarHD(void);
void usarTD(void);
void getTandH(unsigned int T,unsigned int H);
void Mainfunction(void);
void getflag(void);
void Getdataflag(void);
void ACBinit(void);
unsigned int returnT(void);
unsigned int returnH(void);
void pid_Init(int P, int I, int D, struct PID_DATA *pid);
double pid_Calc(struct PID_DATA *pid,double NextPoint);
#define Chillwatertem	10
#define MAX_INT         int_MAX
#define MAX_LONG        INT32_MAX
#define MAX_I_TERM      (MAX_LONG / 2)
#define RELAY1_ON		PORTE|= 1<<6
#define RELAY1_OFF		PORTE&= ~(1<<6)
#define RELAY2_ON		PORTE|= 1<<7
#define RELAY2_OFF		PORTE&= ~(1<<7)

#endif