/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*
*                                (c) Copyright 2006, Micrium, Weston, FL
*                                          All Rights Reserved
*
*                                           ARM Cortex-M3 Port
*
* File      : OS_CPU_C.C
* Version   : V2.89
* By        : Jean J. Labrosse
*             Brian Nagel
*
* For       : ARMv7M Cortex-M3
* Mode      : Thumb2
* Toolchain : RealView Development Suite
*             RealView Microcontroller Development Kit (MDK)
*             ARM Developer Suite (ADS)
*             Keil uVision
*********************************************************************************************************
*/

#define  OS_CPU_GLOBALS
#include <ucos_ii.h>

/*
*********************************************************************************************************
*                                      LOCAL VARIABLES（局部变量）
*********************************************************************************************************
*/

#if OS_TMR_EN > 0u
static  INT16U  OSTmrCtr;                                  /* 定时器计数器                             */
#endif

/*
*********************************************************************************************************
*                                          SYS TICK DEFINES
*********************************************************************************************************
*/
#if 0                                                      /* app_cfg.c配置"系统滴答"                  */
#define  OS_CPU_CM3_NVIC_ST_CTRL    (*((volatile INT32U *)0xE000E010uL)) /* SysTick Ctrl & Status Reg. */
#define  OS_CPU_CM3_NVIC_ST_RELOAD  (*((volatile INT32U *)0xE000E014uL)) /* SysTick Reload  Value Reg. */
#define  OS_CPU_CM3_NVIC_ST_CURRENT (*((volatile INT32U *)0xE000E018uL)) /* SysTick Current Value Reg. */
#define  OS_CPU_CM3_NVIC_ST_CAL     (*((volatile INT32U *)0xE000E01CuL)) /* SysTick Cal     Value Reg. */
#define  OS_CPU_CM3_NVIC_PRIO_ST    (*((volatile INT8U  *)0xE000ED23uL)) /* SysTick Handler Prio  Reg. */

#define  OS_CPU_CM3_NVIC_ST_CTRL_COUNT                    0x00010000uL   /* Count flag.                */
#define  OS_CPU_CM3_NVIC_ST_CTRL_CLK_SRC                  0x00000004uL   /* Clock Source.              */
#define  OS_CPU_CM3_NVIC_ST_CTRL_INTEN                    0x00000002uL   /* Interrupt enable.          */
#define  OS_CPU_CM3_NVIC_ST_CTRL_ENABLE                   0x00000001uL   /* Counter mode.              */
#define  OS_CPU_CM3_NVIC_PRIO_MIN                               0xFFu    /* Min handler prio.          */
#endif
/*
*********************************************************************************************************
*                                           启动钩子函数
*                                            (BEGINNING)
*
* Description: 这个函数被OSInit()开头调用。
*
* Arguments  : none
*
* Note(s)    : 1) 在调用这个函数期间需要禁止中断。
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0u
void  OSInitHookBegin (void)
{
    INT32U   size;
    OS_STK  *pstk;

                                                           /* Clear exception stack for stack checking.*/
    pstk = &OS_CPU_ExceptStk[0];
    size = OS_CPU_EXCEPT_STK_SIZE;
    while (size > 0u) {
        size--;
       *pstk++ = (OS_STK)0;
    }

    OS_CPU_ExceptStkBase = &OS_CPU_ExceptStk[OS_CPU_EXCEPT_STK_SIZE - 1u];

#if OS_TMR_EN > 0u
    OSTmrCtr = 0u;
#endif
}
#endif

/*
*********************************************************************************************************
*                                           结束钩子函数
*                                               (END)
*
* Description: 这个函数被OSInit()结束调用。
*
* Arguments  : none
*
* Note(s)    : 1) 在调用这个函数期间需要禁止中断。
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0u
void  OSInitHookEnd (void)
{
}
#endif

/*
*********************************************************************************************************
*                                      TASK CREATION HOOK(创建HOOK任务函数)
*
* Description: 这个函数在任务创建时被调用(来初始化一些信息)。
*
* Arguments  : ptcb   指向TCB的指针。
*
* Note(s)    : 1) 在调用该函数时禁止中断。
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0u
void  OSTaskCreateHook (OS_TCB *ptcb)
{
#if OS_APP_HOOKS_EN > 0u
    App_TaskCreateHook(ptcb);
#else
    (void)ptcb;                                  /* Prevent compiler warning                           */
#endif
}
#endif


/*
*********************************************************************************************************
*                                           TASK DELETION HOOK
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0u
void  OSTaskDelHook (OS_TCB *ptcb)
{
#if OS_APP_HOOKS_EN > 0u
    App_TaskDelHook(ptcb);
#else
    (void)ptcb;                                  /* Prevent compiler warning                           */
#endif
}
#endif

/*
*********************************************************************************************************
*                                             IDLE TASK HOOK
*
* Description: This function is called by the idle task.  This hook has been added to allow you to do
*              such things as STOP the CPU to conserve power.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are enabled during this call.
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0u
void  OSTaskIdleHook (void)
{
#if OS_APP_HOOKS_EN > 0u
    App_TaskIdleHook();
#endif
}
#endif

/*
*********************************************************************************************************
*                                            TASK RETURN HOOK
*
* Description: This function is called if a task accidentally returns.  In other words, a task should
*              either be an infinite loop or delete itself when done.
*
* Arguments  : ptcb      is a pointer to the task control block of the task that is returning.
*
* Note(s)    : none
*********************************************************************************************************
*/

#if OS_CPU_HOOKS_EN > 0u
void  OSTaskReturnHook (OS_TCB  *ptcb)
{
#if OS_APP_HOOKS_EN > 0u
    App_TaskReturnHook(ptcb);
#else
    (void)ptcb;
#endif
}
#endif

/*
*********************************************************************************************************
*                                           STATISTIC TASK HOOK
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your
*              application to add functionality to the statistics task.
*
* Arguments  : none
*********************************************************************************************************
*/

#if OS_CPU_HOOKS_EN > 0u
void  OSTaskStatHook (void)
{
#if OS_APP_HOOKS_EN > 0u
    App_TaskStatHook();
#endif
}
#endif

/*
*********************************************************************************************************
*                                 INITIALIZE A TASK'S STACK（初始化一个任务堆栈）
*
* Description: 这个函数被OSTaskCreate() 或 OSTaskCreateExt()调用来初始化被创建任务的堆栈。
*              这个函数特定于处理器。
*
* Arguments  : task          指向任务的指针。
*
*              p_arg         传递给任务的参数。
*
*
*              ptos          指向栈顶的指针。
*                            It is assumed that 'ptos' points to a 'free' entry on the task stack.
*                            If OS_STK_GROWTH is set to 1 then 'ptos' will contain the HIGHEST valid address of the stack.
*                            Similarly, if OS_STK_GROWTH is set to 0, the 'ptos' will contains the LOWEST valid address
*                            of the stack.
*
*              opt           特殊选项， 可以用来改变OSTaskStkInit()。
*                            (查看 uCOS_II.H for OS_TASK_OPT_xxx).
*
* Returns    : 返回新栈顶（入栈顺序是从高到低）。
*
*
* Note(s)    : 1) 当你的任务开始执行时，使能中断。
*              2) 所有的任务运行在线程模式，使用进程堆栈。
*********************************************************************************************************
*/

OS_STK *OSTaskStkInit (void (*task)(void *p_arg), void *p_arg, OS_STK *ptos, INT16U opt)
{
    OS_STK *stk;


    (void)opt;                                   /* 'opt' 未使用, 防止编译警告                         */
    stk       = ptos;                            /* 指向分配出來的栈顶指针                             */

                                                 /* 中断后xPSR，PC，LR，R12，R3-R0被自动保存到栈中     */
    *(stk)    = (INT32U)0x01000000uL;            /* xPSR                                               */
    *(--stk)  = (INT32U)task;                    /* 任务入口（PC）                                     */
    *(--stk)  = (INT32U)OS_TaskReturn;           /* R14 (LR)                                           */
    *(--stk)  = (INT32U)0x12121212uL;            /* R12                                                */
    *(--stk)  = (INT32U)0x03030303uL;            /* R3                                                 */
    *(--stk)  = (INT32U)0x02020202uL;            /* R2                                                 */
    *(--stk)  = (INT32U)0x01010101uL;            /* R1                                                 */
    *(--stk)  = (INT32U)p_arg;                   /* R0 : argument                                      */

                                                 /* 剩下的寄存器保存在进程堆栈                         */
    *(--stk)  = (INT32U)0x11111111uL;            /* R11                                                */
    *(--stk)  = (INT32U)0x10101010uL;            /* R10                                                */
    *(--stk)  = (INT32U)0x09090909uL;            /* R9                                                 */
    *(--stk)  = (INT32U)0x08080808uL;            /* R8                                                 */
    *(--stk)  = (INT32U)0x07070707uL;            /* R7                                                 */
    *(--stk)  = (INT32U)0x06060606uL;            /* R6                                                 */
    *(--stk)  = (INT32U)0x05050505uL;            /* R5                                                 */
    *(--stk)  = (INT32U)0x04040404uL;            /* R4                                                 */

    return (stk);                                /* 返回（TCB）栈顶（用于任务控制块的初始化）          */
}

/*
*********************************************************************************************************
*                                      TASK SWITCH HOOK（任务切换HOOK函数）
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/
#if (OS_CPU_HOOKS_EN > 0u) && (OS_TASK_SW_HOOK_EN > 0u)
void  OSTaskSwHook (void)
{
#if OS_APP_HOOKS_EN > 0u
    App_TaskSwHook();
#endif
}
#endif

/*
*********************************************************************************************************
*                                           OS_TCBInit() HOOK
*
* Description: 这个函数被OS_TCBInit()调用， 设置TCB.
*
* Arguments  : ptcb 是一个指向在任务创建时的TCB的指针。
*
* Note(s)    : 1) 在调用期间，中断可以被使能。
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0u
void  OSTCBInitHook (OS_TCB *ptcb)
{
#if OS_APP_HOOKS_EN > 0u
    App_TCBInitHook(ptcb);
#else
    (void)ptcb;                                  /* 防止编译警告                                       */
#endif
}
#endif

/*
*********************************************************************************************************
*                                               TICK HOOK
*
* Description: 这个函数被调用于滴答。
*
* Arguments  : none
*
* Note(s)    : 1) 在调用期间，中断可以被使能。
*********************************************************************************************************
*/
#if (OS_CPU_HOOKS_EN > 0u) && (OS_TIME_TICK_HOOK_EN > 0u)
void  OSTimeTickHook (void)
{
#if OS_APP_HOOKS_EN > 0u
    App_TimeTickHook();
#endif

#if OS_TMR_EN > 0u
    OSTmrCtr++;
    if (OSTmrCtr >= (OS_TICKS_PER_SEC / OS_TMR_CFG_TICKS_PER_SEC)) {
        OSTmrCtr = 0;
        OSTmrSignal();
    }
#endif
}
#endif
#if 0 //注释下面两函数 OS_CPU_SysTickHandler() 和 OS_CPU_SysTickInit() ，此处我们将引用ST库提供的相应函数
/*
*********************************************************************************************************
*                                          SYS TICK HANDLER
*
* Description: Handle the system tick (SysTick) interrupt, which is used to generate the uC/OS-II tick
*              interrupt.
*
* Arguments  : none.
*
* Note(s)    : 1) This function MUST be placed on entry 15 of the Cortex-M3 vector table.
*********************************************************************************************************
*/

void  OS_CPU_SysTickHandler (void)
{
    OS_CPU_SR  cpu_sr;


    OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
    OSIntNesting++;
    OS_EXIT_CRITICAL();

    OSTimeTick();                                /* Call uC/OS-II's OSTimeTick()                       */

    OSIntExit();                                 /* Tell uC/OS-II that we are leaving the ISR          */
}

/*
*********************************************************************************************************
*                                          INITIALIZE SYS TICK
*
* Description: Initialize the SysTick.
*
* Arguments  : cnts          is the number of SysTick counts between two OS tick interrupts.
*
* Note(s)    : 1) This function MUST be called after OSStart() & after processor initialization.
*********************************************************************************************************
*/

void  OS_CPU_SysTickInit (INT32U  cnts)
{
    OS_CPU_CM3_NVIC_ST_RELOAD = cnts - 1u;
                                                 /* Set prio of SysTick handler to min prio.           */
    OS_CPU_CM3_NVIC_PRIO_ST   = OS_CPU_CM3_NVIC_PRIO_MIN;
                                                 /* Enable timer.                                      */
    OS_CPU_CM3_NVIC_ST_CTRL  |= OS_CPU_CM3_NVIC_ST_CTRL_CLK_SRC | OS_CPU_CM3_NVIC_ST_CTRL_ENABLE;
                                                 /* Enable timer interrupt.                            */
    OS_CPU_CM3_NVIC_ST_CTRL  |= OS_CPU_CM3_NVIC_ST_CTRL_INTEN;
}
#endif
