/**
  ********************************  STM32F10x  *********************************
  *********************************  uC/OS-II  *********************************
  * @�ļ���     �� app_cfg.h
  * @����       �� strongerHuang
  * @��汾     �� V3.5.0
  * @ϵͳ�汾   �� V2.92
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��06��28��
  * @ժҪ       �� Ӧ������ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _APP_CFG_H
#define _APP_CFG_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm32f10x.h"
#include "os_cpu.h"


/* �궨�� --------------------------------------------------------------------*/
/* �������ȼ� */
#define TASK_START_PRIO                        3
#define Com_PRIO                               4
#define Led_PRIO                               5

/* �����ջ��С */
#define TASK_START_STK_SIZE                    64
#define Com_STK_SIZE                           250
#define Led_STK_SIZE                           64

/* �����ջ���� */
extern OS_STK TaskStartStk[TASK_START_STK_SIZE];
extern OS_STK Com_Stk[Com_STK_SIZE];
extern OS_STK Led_Stk[Led_STK_SIZE];

/* �������� ------------------------------------------------------------------*/
void OSTick_Init(void);
void AppTaskStart(void *p_arg);

#endif /* _APP_CFG_H */

/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/





