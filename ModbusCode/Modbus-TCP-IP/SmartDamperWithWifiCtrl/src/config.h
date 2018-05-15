#ifndef __CONFIG_H
#define __CONFIG_H

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

#include "servo.h"
#include "CO2.h"
#include "oled.h"
#include "stdio.h"
#include "io.h"
#include "iic.h"

/*global variable defines*/

/* for CO2 sensor */
u8 CO2BufIdx;
u16 CO2_IC1_Buf[50];
u16 CO2_IC2_Buf[50];


char str[50];

int i;

float Pressure=0.0;
float Temperature=0.0;

u16 ADCdata=0;
u16 ADCBuff=0;

u16 PWMvalue=0;



#endif
