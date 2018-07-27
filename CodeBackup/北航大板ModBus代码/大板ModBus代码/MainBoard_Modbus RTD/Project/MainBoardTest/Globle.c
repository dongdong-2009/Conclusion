#include "Globle.h"


uint8_t Uart1_SCnt=0;
uint8_t Uart1_Send_buffer[150]={0};
uint8_t Uart1_receive_buffer[150]={0};
uint8_t Uart1_RCnt=0;
uint8_t Uart1_SendBuffSize=0;

uint8_t Uart2_SCnt=0;
uint8_t Uart2_Send_buffer[150]={0};
uint8_t Uart2_receive_buffer[150]={0};
uint8_t Uart2_RCnt=0;
uint8_t Uart2_SendBuffSize=0;

uint8_t Uart3_SCnt=0;
uint8_t Uart3_Send_buffer[150]={0};
uint8_t Uart3_receive_buffer[150]={0};
uint8_t Uart3_RCnt=0;
uint8_t Uart3_SendBuffSize=0;

uint8_t Uart4851_TestFlag=0;
uint8_t Uart4852_TestFlag=0;
uint8_t Wifi_TestFlag=0;

uint16_t AdREG[12]={0};                  //modbus Ó³Éä¼Ä´æÆ÷ Ad ch1-ch12
uint16_t DiREG[8]={0};                   //modbus Ó³Éä¼Ä´æÆ÷ Di ch1-ch8
uint16_t DoREG[8]={0};               //modbus Ó³Éä¼Ä´æÆ÷ D0 ch1-ch8
uint16_t DAREG[8]={0};               //modbus Ó³Éä¼Ä´æÆ÷ Da ch1-ch8
int16_t  RTDREG[4]={0};                  //modbus Ó³Éä¼Ä´æÆ÷ RTD ch1-ch4

uint8_t TimerOverFlag=0;
uint8_t BegainRxFlag=0;
uint8_t BusyFlag=0;
