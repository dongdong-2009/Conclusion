#include "algorithm.h"

float PID_Control(float sv,float pv)
{
	float Output=0.0;            //PID当前输出
	float last_Output=0.0;       //上一次输出
	float ek=0.0;                //当次误差
	float ek1=0.0;               //上次误差
	float ek2=0.0;               //上两次误差
	float pError=0.0;            //比例误差
	float iError=0.0;            //积分误差
	float dError=0.0;            //微分误差
	
	ek=sv-pv;
	pError=ek-ek1;
	iError=ek;
	dError=ek-2*ek1+ek2;
	
	ek2=ek1;                 //储存前两次误差
	ek1=ek;                  //储存前一次误差
	
	Output=Kp*pError+Ki*iError+Kd*dError+last_Output;      //获取PID调节的输出值
	last_Output=Output;      //存储前一次输出值
	
	return Output;
}
