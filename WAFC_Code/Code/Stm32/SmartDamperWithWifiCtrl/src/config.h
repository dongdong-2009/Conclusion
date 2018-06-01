#ifndef __CONFIG_H
#define __CONFIG_H

//choose with screen or no screen
//#undef _DISPLAY_
#define _DISPLAY_

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

#include "bsp_pwm.h"
#include "bsp_adc.h"
#include "servo.h"
#include "damper.h"
#include "feedback.h"

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
#include "pitot.h"

#include "spi.h"
#include "flash.h"
#include "backup.h"


/*global variable defines*/

#endif
