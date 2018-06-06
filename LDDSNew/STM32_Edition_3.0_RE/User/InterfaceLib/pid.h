
#ifndef _PID_
#define _PID_

#include<stdio.h>
#include<stdlib.h>
//����PID�ṹ��--PID_PAR �������� *PPָ��ṹ���ָ��
typedef struct _PID
{
  int Ti;
  int Td;
  int T;
  float Kp;
  float Ki;
  float Kd;
  float last_err;
  float prev_err;
  float sp;
  float last_out;
}PID,*PP;
extern PID PidPar[4];


float PID_Calcu(int ith,float pv);
void PID_SetValue(int ith,float Kp,float Ki, float Kd,float sp);
#endif /*_PID_*/



