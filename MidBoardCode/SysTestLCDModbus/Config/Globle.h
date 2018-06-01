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
//IO口地址映射
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

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入


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
  CONFIG    = 0x01,	    //配置期-- 即MCU逻辑配置期 -- 配置数据存于FLASH
  RUNTIME   = 0x02,     //运行时-- 即MCU逻辑运行期 -- 端口数据存于DATABASE
  LUT       = 0x03		  //查表数据下发 -- Look up Table	-- 配置期之前执行
}STAGESEL;

typedef enum _taskselection
{
  NON        = 0x00,             //无任务
  READPORTS  = 0x55,	           //读端口任务 -- read ports 
  WRITEPORTS = 0x66,	           //写端口任务  -- write ports
  READPID    = 0x77,		         //读PID任务   -- read pid group
  WRITEPID   = 0x88            	 //写PID任务   -- write pid group               
}TASKSEL;

typedef enum _autoselection
{
  MANUAL = 0x10,	  //模式选择-- 上位机手动控制AO/DO/Registers输出
  AUTO   = 0x20       //模式选择-- 程序根据运行自动控制AO/DO/Registers输出
}AUTOSEL;

typedef enum _modeselection
{
  LOAD  = 0x11,	  //模式选择-- download
  DEBUG = 0x22,	  //模式选择-- debug model
  RUN   = 0x33,	  //模式选择-- run model
  STOP  = 0x44    //模式选择-- stop model
}MODESEL;

typedef enum _loopstateselection
{
  OPENLOOP = 0x00,	        //PID环路状态选择-- 开环
  CLOSELOOP   = 0x01        //PID环路状态选择-- 闭环
}LOOPSEL;

typedef enum _onoffline
{
  ONLINE = 0x00,
  OFFLINE = 0x01
}LINESEL;

typedef enum _tstaskselection
{
  TSNON      = 0x00,             //无任务
  READDATA   = 0x01,	           //读数据
  SETDATA    = 0x02,	           //设置数据
  START      = 0x03,		         //启动
  TSSTOP     = 0x04              //停止
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

extern unsigned int MCUaddress;                  //此MCU的地址，用于唯一标定该MCU，在Config期确定
extern volatile STAGESEL StageSel;               //通信串口USART1分时复用，阶段选择
extern volatile MODESEL ModeSel;			           //Config期模式选择
extern volatile TASKSEL	TaskSel;			           //Runtime期任务选择 
extern volatile LINESEL LineSel;			           //Online Offlien 选择
extern volatile char  ReceivedState;					   //数据串接收完成标志位
extern unsigned int   ReceivedNum;					     //接收到的字符的个数
extern char  ReceivedBuffer[4000];			         //接收缓存区
extern char  SentBuffer[200];				             //发送缓存区
 
//data---电信号值，value---物理意义值
extern float  TSRegister[12];
extern float  Registers[16];                 //寄存器值,存储非端口类数据
extern float  ADC_value[12];                 //ADC物理意义值
extern float  ADC_data[12];                  //ADC电信号值
extern float  RTD_value[4];
extern float  DAC_value[8];
extern float  DAC_data[8];
extern u8   	 DI_data[8];
extern u8     DO_data[8];
extern float  Setpoint[3];

extern PARAMS AIParams[12];

//全局变量
extern float CO2;
extern float CO2Sv;
extern float RoomTemp;
extern float RoomTempSv;
extern float RoomHum;

//小板通信定义相关量
extern char TSReadPortsBuffer[18];
extern char TSSendBuffer[22];
extern char TSwriteRegister[12];
extern char TSSentCheckCode;         //待发送数据的效验码
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

