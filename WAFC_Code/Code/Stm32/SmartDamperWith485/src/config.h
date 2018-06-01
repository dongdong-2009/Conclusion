#ifndef __CONFIG_H
#define __CONFIG_H

#include "timer.h"
extern void TimConfigure(void);

//choose with screen or no screen
#undef _DISPLAY_
//#define _DISPLAY_

#include <stm32f10x.h>

#include "bsp_hwConfig.h"
#include "sysISRPriConf.h"
#include "bsp_systimer.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "param.h"

#include "uart_wifi.h"
#include "wifi_server.h"
#include "modbus_tcp.h"
#include "modbus_app.h"

#include "usart.h"

#include "bsp_pwm.h"
#include "bsp_adc.h"
#include "servo.h"
#include "damper.h"

#include "CO2.h"

#ifdef _DISPLAY_
#include "oled.h"
#include "stdio.h"
#include "display.h"
#endif

#include "io.h"
#include "iic.h"
#include "D6F_PH.h"
#include "diff_pressure.h"


/*global variable defines*/
//´®¿Ú1±äÁ¿
uint8_t Uart1_SCnt=0;
uint8_t Uart1_Send_buffer[150]={0};
uint8_t Uart1_receive_buffer[150]={0};
uint8_t Uart1_RCnt=0;
uint8_t Uart1_SendBuffSize=0;

u16 ReadReg[50]={0};
u16 WriteReg[50]={0};

uint8_t TimerOverFlag=0;
uint8_t BegainRxFlag=0;
uint8_t BusyFlag=0;


/* for CO2 sensor */
u8 CO2BufIdx;
u16 CO2_IC1_Buf[50];
u16 CO2_IC2_Buf[50];

int i;
#endif
