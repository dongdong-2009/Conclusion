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

//AI�˿�����
float advalue[7]={0};

float temperature=0.0;

//modbus
uint16_t ReadReg[100]={0};
uint16_t WriteReg[100]={0};
uint8_t TimerOverFlag=0;
uint8_t BegainRxFlag=0;
uint8_t BusyFlag=0;

//data---���ź�ֵ��value---��������ֵ
float  TSRegister[12]={0};
float  Registers[16]={0};                 //�Ĵ���ֵ,�洢�Ƕ˿�������
float  ADC_value[12]={0};                 //ADC��������ֵ
float  ADC_data[12]={0};                  //ADC���ź�ֵ
float  RTD_value[4]={0};
float  DAC_value[8]={0};
float  DAC_data[8]={0};
u8   	 DI_data[8]={0};
u8     DO_data[8]={0};
float  Setpoint[3]={0};


//ȫ�ֱ���
float CO2=0.0;
float CO2Sv=0.0;
float RoomTemp=0.0;
float RoomTempSv=0.0;
float RoomHum=0.0;

//С��ͨ�Ŷ��������
char TSReadPortsBuffer[18];
char TSSendBuffer[22]={0};
char TSwriteRegister[12]={0};
char TSSentCheckCode=0;         //���������ݵ�Ч����


//����λ��ͨ�ţ�����λ��ʼ������
//volatile�������α���ͬ�̷߳��ʺ��޸ĵı�����ȷ��ָ�����Ϊ���������Ż���ʡ�ԣ���Ҫ��ÿ��ֱ�Ӷ�ֵ
unsigned int MCUaddress = 0;                //��MCU�ĵ�ַ������Ψһ�궨��MCU����Config��ȷ��
volatile STAGESEL StageSel = CONFIG;        //ͨ�Ŵ���USART1��ʱ���ã��׶�ѡ��
volatile TASKSEL TaskSel = NON;			        //Runtime������ѡ�� 
volatile MODESEL ModeSel = LOAD;		        //Config��ģʽѡ��
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

