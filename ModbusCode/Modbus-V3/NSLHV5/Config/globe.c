#include "globe.h"

extern float dataTemp[12];
extern float Para[3];
extern float AI_Input[12];

uint8_t Uart2_SCnt=0;
uint8_t Uart2_Send_buffer[150]={0};
uint8_t Uart2_receive_buffer[150]={0};
uint8_t Uart2_RCnt=0;
uint8_t Uart2_SendBuffSize=0;

float ValveControl(float SetValue)
{
	float out=10.0;
	VavleFeedback=AI_Input[11];
	if(VavleFeedback>10.0)
		VavleFeedback=10.0;
	error=SetValue-RoomTemp;                                  //温度数据都乘以10进行处理
	out=VavleFeedback-(Para[0]*error+Para[1]*error*Para[2]);  //PID parameters should be adjusted
	
	//限幅
	if(out<0.0)
		out=0.0;
	else if(out>=10.0)
		out=10.0;
	
	return out;
}
