#include "Globle.h"

uint16_t ADC_ConvertedValue[10][6];

uint8_t Uart1_SCnt=0;
uint8_t Uart1_Send_buffer[150]={0};
uint8_t Uart1_receive_buffer[150]={0};
uint8_t Uart1_RCnt=0;
uint8_t Uart1_SendBuffSize=0;

//AI¶Ë¿ÚÊý¾Ý
float advalue[7]={0};

float temperature=0.0;

//modbus
uint16_t ReadReg[100]={0};
uint16_t WriteReg[100]={0};
uint8_t TimerOverFlag=0;
uint8_t BegainRxFlag=0;
uint8_t BusyFlag=0;
