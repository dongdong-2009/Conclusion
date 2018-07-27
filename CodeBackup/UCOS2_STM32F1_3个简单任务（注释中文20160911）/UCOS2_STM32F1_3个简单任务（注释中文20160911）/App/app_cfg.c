/**
  ********************************  STM32F10x  *********************************
  *********************************  uC/OS-II  *********************************
  * @文件名     ： app_cfg.c
  * @作者       ： strongerHuang
  * @库版本     ： V3.5.0
  * @系统版本   ： V2.92
  * @文件版本   ： V1.0.0
  * @日期       ： 2016年06月28日
  * @摘要       ： 应用配置源文件
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2016-06-28 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include "app_cfg.h"
#include "app_task.h"
#include "bsp.h"


/* 全局变量 ------------------------------------------------------------------*/
OS_STK TaskStartStk[TASK_START_STK_SIZE];
OS_STK Task1_Stk[TASK1_STK_SIZE];
OS_STK Task2_Stk[TASK2_STK_SIZE];
OS_STK Task3_Stk[TASK3_STK_SIZE];

/************************************************
函数名称 ： OSTick_Init
功    能 ： 操作系统滴答时钟初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void OSTick_Init(void)
{
  RCC_ClocksTypeDef RCC_ClocksStructure;
  RCC_GetClocksFreq(&RCC_ClocksStructure);       //获取系统时钟频率
                                                 //初始化并启动SysTick和它的中断
  SysTick_Config(RCC_ClocksStructure.HCLK_Frequency / OS_TICKS_PER_SEC);
}

/************************************************
函数名称 ： AppTaskStart
功    能 ： 启动任务
参    数 ： p_arg --- 可选参数
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void AppTaskStart(void *p_arg)
{
  BSP_Initializes();                             //板子底层初始化

  OSTick_Init();                                 //初始化滴答时钟

  /* 创建任务1 */
  OSTaskCreateExt((void (*)(void *)) AppTask1,
                  (void           *) 0,
                  (OS_STK         *)&Task1_Stk[TASK1_STK_SIZE-1],
                  (INT8U           ) TASK1_PRIO,
                  (INT16U          ) TASK1_PRIO,
                  (OS_STK         *)&Task1_Stk[0],
                  (INT32U          ) TASK1_STK_SIZE,
                  (void           *) 0,
                  (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

  /* 创建任务2 */
  OSTaskCreateExt((void (*)(void *)) AppTask2,
                  (void           *) 0,
                  (OS_STK         *)&Task2_Stk[TASK2_STK_SIZE-1],
                  (INT8U           ) TASK2_PRIO,
                  (INT16U          ) TASK2_PRIO,
                  (OS_STK         *)&Task2_Stk[0],
                  (INT32U          ) TASK2_STK_SIZE,
                  (void           *) 0,
                  (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

  /* 创建任务3 */
  OSTaskCreateExt((void (*)(void *)) AppTask3,
                  (void           *) 0,
                  (OS_STK         *)&Task3_Stk[TASK3_STK_SIZE-1],
                  (INT8U           ) TASK3_PRIO,
                  (INT16U          ) TASK3_PRIO,
                  (OS_STK         *)&Task3_Stk[0],
                  (INT32U          ) TASK3_STK_SIZE,
                  (void           *) 0,
                  (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

  while(1)
  {
    LED0_TOGGLE;
    OSTimeDly(20);
  }

}

/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
