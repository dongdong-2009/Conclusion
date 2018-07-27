#include "algorithm.h"

float PID_Control(float sv,float pv)
{
	float Output=0.0;            //PID��ǰ���
	float last_Output=0.0;       //��һ�����
	float ek=0.0;                //�������
	float ek1=0.0;               //�ϴ����
	float ek2=0.0;               //���������
	float pError=0.0;            //�������
	float iError=0.0;            //�������
	float dError=0.0;            //΢�����
	
	ek=sv-pv;
	pError=ek-ek1;
	iError=ek;
	dError=ek-2*ek1+ek2;
	
	ek2=ek1;                 //����ǰ�������
	ek1=ek;                  //����ǰһ�����
	
	Output=Kp*pError+Ki*iError+Kd*dError+last_Output;      //��ȡPID���ڵ����ֵ
	last_Output=Output;      //�洢ǰһ�����ֵ
	
	return Output;
}
