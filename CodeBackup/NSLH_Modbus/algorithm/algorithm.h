#ifndef __ALGORITHM_H
#define __ALGORITHM_H

extern float Kp;               //����ϵ��
extern float Ki;               //����ϵ��
extern float Kd;               //΢��ϵ��

float PID_Control(float sv,float pv);  //����ʽPID

#endif
