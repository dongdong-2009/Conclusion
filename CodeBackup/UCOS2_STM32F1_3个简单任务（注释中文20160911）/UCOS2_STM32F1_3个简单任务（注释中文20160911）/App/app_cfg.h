/**
  ********************************  STM32F10x  *********************************
  *********************************  uC/OS-II  *********************************
  * @文件名     ： app_cfg.h
  * @作者       ： strongerHuang
  * @库版本     ： V3.5.0
  * @系统版本   ： V2.92
  * @文件版本   ： V1.0.0
  * @日期       ： 2016年06月28日
  * @摘要       ： 应用配置头文件
  ******************************************************************************/

/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _APP_CFG_H
#define _APP_CFG_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "stm32f10x.h"
#include "os_cpu.h"


/* 宏定义 --------------------------------------------------------------------*/
/* 任务优先级 */
#define TASK_START_PRIO                        3
#define TASK1_PRIO                             8
#define TASK2_PRIO                             9
#define TASK3_PRIO                             10

/* 任务堆栈大小 */
#define TASK_START_STK_SIZE                    64
#define TASK1_STK_SIZE                         64
#define TASK2_STK_SIZE                         64
#define TASK3_STK_SIZE                         64

/* 任务堆栈变量 */
extern OS_STK TaskStartStk[TASK_START_STK_SIZE];
extern OS_STK Task1_Stk[TASK1_STK_SIZE];
extern OS_STK Task2_Stk[TASK2_STK_SIZE];
extern OS_STK Task3_Stk[TASK3_STK_SIZE];

/* 函数申明 ------------------------------------------------------------------*/
void OSTick_Init(void);
void AppTaskStart(void *p_arg);


#endif /* _APP_CFG_H */

/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/





