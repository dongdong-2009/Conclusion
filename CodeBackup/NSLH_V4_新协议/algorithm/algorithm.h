#ifndef __ALGORITHM_H
#define __ALGORITHM_H

extern float Kp;               //比例系数
extern float Ki;               //积分系数
extern float Kd;               //微分系数

float PID_Control(float sv,float pv);  //增量式PID

#endif
