#ifndef _GLOBLE_H
#define _GLOBLE_H

#include "stm32f10x_it.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "stm32f10x.h"
#include "delay.h"
#include "DAC8554.h"
#include "MuxCfg.h"
#include "Dio.h"
#include "Pwm.h"
#include "W25Q16.h"

#define MODE_CURRENT 1
#define MODE_VOLTAGE 0
//IO�ڵ�ַӳ��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����


#define USART1_GPIO              GPIOA
#define USART1_CLK               RCC_APB2Periph_USART1
#define USART1_GPIO_CLK          RCC_APB2Periph_GPIOA
#define USART1_RxPin             GPIO_Pin_10
#define USART1_TxPin             GPIO_Pin_9
#define USART1_IRQn              USART1_IRQn
#define USART1_IRQHandler        USART1_IRQHandler

#define USART2_GPIO              GPIOD
#define USART2_CLK               RCC_APB1Periph_USART2
#define USART2_GPIO_CLK          RCC_APB2Periph_GPIOD
#define USART2_RxPin             GPIO_Pin_6
#define USART2_TxPin             GPIO_Pin_5
#define USART2_IRQn              USART2_IRQn
#define USART2_IRQHandler        USART2_IRQHandler

#define USART3_GPIO              GPIOB
#define USART3_CLK               RCC_APB1Periph_USART3
#define USART3_GPIO_CLK          RCC_APB2Periph_GPIOB
#define USART3_RxPin             GPIO_Pin_11
#define USART3_TxPin             GPIO_Pin_10
#define USART3_IRQn              USART3_IRQn
#define USART3_IRQHandler        USART3_IRQHandler

typedef struct _params		//y = a*x +b
{
  float a;
  float b;
}PARAMS;

typedef enum _stageselection
{
  CONFIG    = 0x01,	    //������-- ��MCU�߼������� -- �������ݴ���FLASH
  RUNTIME   = 0x02,     //����ʱ-- ��MCU�߼������� -- �˿����ݴ���DATABASE
  LUT       = 0x03		  //��������·� -- Look up Table	-- ������֮ǰִ��
}STAGESEL;

typedef enum _taskselection
{
  NON        = 0x00,             //������
  READPORTS  = 0x55,	           //���˿����� -- read ports 
  WRITEPORTS = 0x66,	           //д�˿�����  -- write ports
  READPID    = 0x77,		         //��PID����   -- read pid group
  WRITEPID   = 0x88            	 //дPID����   -- write pid group               
}TASKSEL;

typedef enum _autoselection
{
  MANUAL = 0x10,	  //ģʽѡ��-- ��λ���ֶ�����AO/DO/Registers���
  AUTO   = 0x20       //ģʽѡ��-- ������������Զ�����AO/DO/Registers���
}AUTOSEL;

typedef enum _modeselection
{
  LOAD  = 0x11,	  //ģʽѡ��-- download
  DEBUG = 0x22,	  //ģʽѡ��-- debug model
  RUN   = 0x33,	  //ģʽѡ��-- run model
  STOP  = 0x44    //ģʽѡ��-- stop model
}MODESEL;

typedef enum _loopstateselection
{
  OPENLOOP = 0x00,	        //PID��·״̬ѡ��-- ����
  CLOSELOOP   = 0x01        //PID��·״̬ѡ��-- �ջ�
}LOOPSEL;

typedef enum _onoffline
{
  ONLINE = 0x00,
  OFFLINE = 0x01
}LINESEL;

typedef enum _tstaskselection
{
  TSNON      = 0x00,             //������
  READDATA   = 0x01,	           //������
  SETDATA    = 0x02,	           //��������
  START      = 0x03,		         //����
  TSSTOP     = 0x04              //ֹͣ
}TSTASKSEL;

extern volatile TSTASKSEL TSTaskSel;

extern uint16_t ADC_ConvertedValue[10][6];

extern uint8_t Uart1_SCnt;
extern uint8_t Uart1_Send_buffer[150];
extern uint8_t Uart1_receive_buffer[150];
extern uint8_t Uart1_RCnt;
extern uint8_t Uart1_SendBuffSize;

extern uint8_t Uart2_SCnt;
extern uint8_t Uart2_Send_buffer[150];
extern uint8_t Uart2_receive_buffer[150];
extern uint8_t Uart2_RCnt;
extern uint8_t Uart2_SendBuffSize;

extern float advalue[7];
extern float temperature;

extern uint16_t ReadReg[100];
extern uint16_t WriteReg[100];
extern uint8_t TimerOverFlag;
extern uint8_t BegainRxFlag;
extern uint8_t BusyFlag;

extern unsigned int MCUaddress;                  //��MCU�ĵ�ַ������Ψһ�궨��MCU����Config��ȷ��
extern volatile STAGESEL StageSel;               //ͨ�Ŵ���USART1��ʱ���ã��׶�ѡ��
extern volatile MODESEL ModeSel;			           //Config��ģʽѡ��
extern volatile TASKSEL	TaskSel;			           //Runtime������ѡ�� 
extern volatile LINESEL LineSel;			           //Online Offlien ѡ��
extern volatile char  ReceivedState;					   //���ݴ�������ɱ�־λ
extern unsigned int   ReceivedNum;					     //���յ����ַ��ĸ���
extern char  ReceivedBuffer[4000];			         //���ջ�����
extern char  SentBuffer[200];				             //���ͻ�����
 
//data---���ź�ֵ��value---��������ֵ
extern float  TSRegister[12];
extern float  Registers[16];                 //�Ĵ���ֵ,�洢�Ƕ˿�������
extern float  ADC_value[12];                 //ADC��������ֵ
extern float  ADC_data[12];                  //ADC���ź�ֵ
extern float  RTD_value[4];
extern float  DAC_value[8];
extern float  DAC_data[8];
extern u8   	 DI_data[8];
extern u8     DO_data[8];
extern float  Setpoint[3];

extern PARAMS AIParams[12];

//ȫ�ֱ���
extern float CO2;
extern float CO2Sv;
extern float RoomTemp;
extern float RoomTempSv;
extern float RoomHum;

//С��ͨ�Ŷ��������
extern char TSReadPortsBuffer[18];
extern char TSSendBuffer[22];
extern char TSwriteRegister[12];
extern char TSSentCheckCode;         //���������ݵ�Ч����
extern char  TSReceivedBuffer[24];

extern u8 localControl;

extern char tx1[24]; 
extern char tx2[24]; 
extern char tx3[24]; 
extern char tx4[24]; 


#define DE1 PAout(11)
#define DE2 PDout(7)
#define LED PBout(9)

#endif

