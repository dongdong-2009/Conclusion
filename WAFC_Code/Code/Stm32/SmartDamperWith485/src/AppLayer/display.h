#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "oled.h"
#include "stdio.h"
#include "math.h"
#include "bsp_systimer.h"
#include "modbus_app.h"
#include "wifi_server.h"
#include "uart_wifi.h"

#define DISP_REFRESH_MS 50
#define STR_BUF_SIZE 10


void Display_Init(void);
void Display_Task(void);

#endif
