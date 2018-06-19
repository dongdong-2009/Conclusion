#ifndef __CONFIG_H
#define __CONFIG_H


#include "stm32f10x.h"
#include "master.h"
#include "stm32_it.h"
#include "Modbus_m.h"



//����Modbus Master����ͨ����ر�����ȫ�ֱ���
u8 SlaveID;                       //slave ID
u8 FunCode;                       //Function Code
u16 ReadAddr;                     //Read Address
u16 RegReadNum;                   //Read Register Number
u16 WriteAddr;                    //Write Address
u16 RegWriteNum;                  //Write Register Number
u16 SendBuffer[BufferSize];       //Send Buffer 
u8  ReceBuffer[BufferSize];       //Receive Buffer

//���ݴ��
u8 ModbusADU[256];
u8 MBStatus=ku8MBSuccess;         //modbus�ӻ�״̬��

//��������
uint8_t Uart1_SCnt=0;
uint8_t Uart1_Send_buffer[150]={0};
uint8_t Uart1_RCnt=0;
uint8_t Uart1_SendBuffSize=0;

void RCC_Configuration(void);
void NVIC_Configuration(void);

#endif
