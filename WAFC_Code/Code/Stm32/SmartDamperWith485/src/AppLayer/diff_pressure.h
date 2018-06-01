#ifndef __DIFF_PRESSURE_H
#define __DIFF_PRESSURE_H

#include "D6F_PH.h"
#include "bsp_systimer.h"
#include "modbus_app.h"

#define DP_STATUS_READY 0x00
#define DP_STATUS_EXEMCU 0x01
#define DP_STATUS_READING 0x02

#define DP_BUF_SIZE 50
#define DP_SAMPLING_CLK_MS 100
#define DP_OUTPUT_CLK_MS 1000

void DiffPressure_Init(void);
void DiffPressure_Task(void);
float DiffPressure_Filter(float buf[]);
float DiffPressure_Variance(float buf[], float buf_weighted_mean);

#endif
