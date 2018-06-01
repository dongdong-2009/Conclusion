#include "Globle.h"

PARAMS AIParams[12] = {{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0}};

uint16_t ADC_ConvertedValue[10][6];

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

//AI端口数据
float advalue[7]={0};

float temperature=0.0;

//modbus
uint16_t ReadReg[100]={0};
uint16_t WriteReg[100]={0};
uint8_t TimerOverFlag=0;
uint8_t BegainRxFlag=0;
uint8_t BusyFlag=0;

//data---电信号值，value---物理意义值
float  TSRegister[12]={0};
float  Registers[16]={0};                 //寄存器值,存储非端口类数据
float  ADC_value[12]={0};                 //ADC物理意义值
float  ADC_data[12]={0};                  //ADC电信号值
float  RTD_value[4]={0};
float  DAC_value[8]={0};
float  DAC_data[8]={0};
u8   	 DI_data[8]={0};
u8     DO_data[8]={0};
float  Setpoint[3]={0};


//全局变量
float CO2=0.0;
float CO2Sv=0.0;
float RoomTemp=0.0;
float RoomTempSv=0.0;
float RoomHum=0.0;

//小板通信定义相关量
char TSReadPortsBuffer[18];
char TSSendBuffer[22]={0};
char TSwriteRegister[12]={0};
char TSSentCheckCode=0;         //待发送数据的效验码


//与上位机通信，功能位初始化代码
//volatile用来修饰被不同线程访问和修改的变量，确保指令不会因为编译器的优化而省略，且要求每次直接读值
unsigned int MCUaddress = 0;                //此MCU的地址，用于唯一标定该MCU，在Config期确定
volatile STAGESEL StageSel = CONFIG;        //通信串口USART1分时复用，阶段选择
volatile TASKSEL TaskSel = NON;			        //Runtime期任务选择 
volatile MODESEL ModeSel = LOAD;		        //Config期模式选择
volatile LINESEL LineSel = ONLINE;
volatile char ReceivedState = 0;
unsigned int  ReceivedNum = 0;
char ReceivedBuffer[4000];
char  TSReceivedBuffer[24];
char  SentBuffer[200];


volatile TSTASKSEL TSTaskSel = TSNON;

u8 localControl=0;

char tx1[24]={0x55,0x66,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x55};
char tx2[24]={0x55,0x66,0x02,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x10,0x66,0x55};
char tx3[24]={0x55,0x66,0x03,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x10,0x66,0x55};
char tx4[24]={0x55,0x66,0x04,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x10,0x66,0x55};

