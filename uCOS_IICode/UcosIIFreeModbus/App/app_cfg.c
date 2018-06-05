/**
  ********************************  STM32F10x  *********************************
  *********************************  uC/OS-II  *********************************
  * @�ļ���     �� app_cfg.c
  * @����       �� strongerHuang
  * @��汾     �� V3.5.0
  * @ϵͳ�汾   �� V2.92
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��06��28��
  * @ժҪ       �� Ӧ������Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2016-06-28 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "app_cfg.h"
#include "app_task.h"
#include "bsp.h"


/* ȫ�ֱ��� ------------------------------------------------------------------*/
OS_STK TaskStartStk[TASK_START_STK_SIZE];
OS_STK Com_Stk[Com_STK_SIZE];
OS_STK Led_Stk[Led_STK_SIZE];

/************************************************
�������� �� OSTick_Init
��    �� �� ����ϵͳ�δ�ʱ�ӳ�ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void OSTick_Init(void)
{
  RCC_ClocksTypeDef RCC_ClocksStructure;
  RCC_GetClocksFreq(&RCC_ClocksStructure);       //��ȡϵͳʱ��Ƶ��
  //��ʼ��������SysTick�������ж�
  SysTick_Config(RCC_ClocksStructure.HCLK_Frequency / OS_TICKS_PER_SEC);
}

/************************************************
�������� �� AppTaskStart
��    �� �� ��������
��    �� �� p_arg --- ��ѡ����
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void AppTaskStart(void *p_arg)
{
  BSP_Initializes();                             //���ӵײ��ʼ��

  OSTick_Init();                                 //��ʼ���δ�ʱ��

  /* ��������1 */
  OSTaskCreateExt((void (*)(void *)) ComTask,
                  (void           *) 0,
                  (OS_STK         *)&Com_Stk[Com_STK_SIZE-1],
                  (INT8U           ) Com_PRIO,
                  (INT16U          ) Com_PRIO,
                  (OS_STK         *)&Com_Stk[0],
                  (INT32U          ) Com_STK_SIZE,
                  (void           *) 0,
                  (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

  /* ��������2 */
  OSTaskCreateExt((void (*)(void *)) LedTask,
                  (void           *) 0,
                  (OS_STK         *)&Led_Stk[Led_STK_SIZE-1],
                  (INT8U           ) Led_PRIO,
                  (INT16U          ) Led_PRIO,
                  (OS_STK         *)&Led_Stk[0],
                  (INT32U          ) Led_STK_SIZE,
                  (void           *) 0,
                  (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

  while(1)
  {
    OSTimeDly(20);
  }

}

/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
