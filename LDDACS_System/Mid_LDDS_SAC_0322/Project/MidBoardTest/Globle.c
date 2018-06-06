#include "Globle.h"

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

uint8_t Uart3_SCnt=0;
uint8_t Uart3_Send_buffer[150]={0};
uint8_t Uart3_receive_buffer[150]={0};
uint8_t Uart3_RCnt=0;
uint8_t Uart3_SendBuffSize=0;

uint8_t Uart4_SCnt=0;
uint8_t Uart4_Send_buffer[150]={0};
uint8_t Uart4_receive_buffer[150]={0};
uint8_t Uart4_RCnt=0;
uint8_t Uart4_SendBuffSize=0;

uint8_t Uart4851_TestFlag=0;
uint8_t Uart4852_TestFlag=0;
uint8_t Wifi_TestFlag=0;


const float MeasuredGainCodeValue_Pt100_150R = 6100805.09090909; // for 150 Ohm resistor
//const float MeasuredGainCodeValue_Pt1000_1K5 = 6710886.0;      // for 1500 Ohm resistor
const float MeasuredGainCodeValue_Pt1000_1K5 = 7381974.6;      // for 1650 Ohm resistor
                                                               //new value = 1k5 value * (newref/1k5)
const float Rref_Pt100  = 3300.0;                          // reference resistor value on the board is 3.24k Ohm
const float Rref_Pt1000 = 15000.0;

float ADS1220GainCorrection_1;
float ADS1220GainCorrection_2;
unsigned char RcvData[16];

long OffsetCalibrateData_1 = 0;
unsigned char OffsetCalibrateCount_1 = 0;
long OffsetCalibrateValue_1 = 0;
float PgaGainLevel_1;
long rawData_1;

long OffsetCalibrateData_2 = 0;
unsigned char OffsetCalibrateCount_2 = 0;
long OffsetCalibrateValue_2 = 0;
float PgaGainLevel_2;
long rawData_2;

unsigned char ReadConversionData_1 = 0;
unsigned char ReadConversionData_2 = 0;

unsigned char OffsetCalFlag = 0;

long temperature_1;
long temperature_2;
long code_1;
long code_2;
float avgTemp_1;
float avgTemp_2;
float avgRaw_1;
float avgRaw_2;
unsigned char avgCount_1 = 0;
unsigned char avgCount_2 = 0;

unsigned char GainCal_1 = 0;
unsigned char GainCal_2 = 0;

unsigned char tempData_1[3];
unsigned char tempData_2[3];

