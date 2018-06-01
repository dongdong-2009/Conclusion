#include "stm32f10x.h"
#include "bsp_hwConfig.h"
#include "sysISRPriConf.h"
#include "bsp_systimer.h"

/*------------------------ global variables---------------------------*/
volatile uint32_t globalTime;

/**
  * @brief  Configures the SysTick.
  * @param  None
  * @retval None
 */
void BSP_SysTickCfg(void)
{	
	/* Setup SysTick Timer for 10 msec interrupts  */
	if (SysTick_Config((SystemCoreClock) / SYS_TICK_FREQUENCY))
	{ 
		/* Capture error */ 
		while (1);
	}

	NVIC_SetPriority(SysTick_IRQn, SYSTICK_PRIORITY);
	
	globalTime = 0;
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	globalTime++;
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
uint32_t Get_Gtime(void)
{
	return globalTime;
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
uint32_t IsTimeExpired(uint32_t ms)
{
	uint32_t time_now;
	time_now = globalTime;
	if (time_now > ms)
	{
		if ((time_now - ms) < 0x80000000)
			return 1;
		else
		  	return 0;
	}
	else
	{
		if ((ms - time_now) > 0x80000000)
		  	return 1;
		else
		 	return 0;
	}
}

uint32_t lg(uint32_t a, uint32_t b)
{
    if (a>b)
    {
        if ((a-b) < 0x80000000)
            return 1;
        else
            return 0;
    }
    else
    {
        if ((b-a) > 0x80000000)
            return 1;
        else
            return 0;
    }
}

int _diff_uint32(uint32_t a, uint32_t b)
{
    if (a>b)
    {
        if ((a-b) < 0x80000000)
            return (int)a-(int)b;
        else
            return (int)b-(int)a;
    }
    else
    {
        if ((b-a) > 0x80000000)
            return (int)a-(int)b;
        else
            return (int)b-(int)a;
    }
}

/*微秒级精确延时函数*/
void delay_us(__IO uint32_t nTime_us)
{
  uint32_t tempSysTickVAL;
	uint32_t tempGTime;

	tempSysTickVAL = SysTick->VAL;
	tempGTime = globalTime + nTime_us/(1000000/SYS_TICK_FREQUENCY);
	nTime_us = nTime_us%(1000000/SYS_TICK_FREQUENCY);
	if (nTime_us>tempSysTickVAL/72)
	{
	    tempSysTickVAL += SystemCoreClock/SYS_TICK_FREQUENCY - nTime_us*72;
	    tempGTime++;
	}
	else
	    tempSysTickVAL -= nTime_us*72;
	
	while(lg(tempGTime,globalTime) || (globalTime==tempGTime && (SysTick->VAL > tempSysTickVAL)));
}

/*毫秒级精确延时函数*/
void delay_ms(__IO uint32_t nTime_ms)
{
  uint32_t tempSysTickVAL;
	uint32_t tempGTime;

	tempSysTickVAL = SysTick->VAL;
	tempGTime = globalTime + nTime_ms/(1000/SYS_TICK_FREQUENCY);
	nTime_ms = nTime_ms%(1000/SYS_TICK_FREQUENCY);
	if (nTime_ms>tempSysTickVAL/72000)
	{
	    tempSysTickVAL += SystemCoreClock/SYS_TICK_FREQUENCY - nTime_ms*72000;
	    tempGTime++;
	}
	else
	    tempSysTickVAL -= nTime_ms*72000;
	
	while(lg(tempGTime,globalTime) || (globalTime==tempGTime && (SysTick->VAL > tempSysTickVAL)));
}

/*秒级精确延时函数*/
void delay_s(__IO uint32_t nTime_s)	     
{
  uint32_t tempSysTickVAL;
	uint32_t tempGTime;

	tempSysTickVAL = SysTick->VAL;
	tempGTime = globalTime + nTime_s*SYS_TICK_FREQUENCY;
	while(lg(tempGTime,globalTime) || (globalTime==tempGTime && (SysTick->VAL > tempSysTickVAL)));
}

uint32_t IsTimeExpiredHD(HDTimer T)
{
    return lg(globalTime,T.nX10ms) || (globalTime==T.nX10ms && (SysTick->VAL <= T.nSysTick));
}

HDTimer HDTimer_add_us(HDTimer T0, __IO uint32_t nTime_us)
{
	T0.nX10ms += + nTime_us/(1000000/SYS_TICK_FREQUENCY);
	nTime_us = nTime_us%(1000000/SYS_TICK_FREQUENCY);
	if (nTime_us>T0.nSysTick/72)
	{
	    T0.nSysTick += SystemCoreClock/SYS_TICK_FREQUENCY - nTime_us*72;
	    (T0.nX10ms)++;
	}
	else
	    T0.nSysTick -= nTime_us*72;
	return T0;
}

HDTimer HDTimer_add_ms(HDTimer T0, __IO uint32_t nTime_ms)
{
	T0.nX10ms += nTime_ms/(1000/SYS_TICK_FREQUENCY);
	nTime_ms = nTime_ms%(1000/SYS_TICK_FREQUENCY);
	if (nTime_ms>T0.nSysTick/72000)
	{
	    T0.nSysTick += SystemCoreClock/SYS_TICK_FREQUENCY - nTime_ms*72000;
	    (T0.nX10ms)++;
	}
	else
	    T0.nSysTick -= nTime_ms*72000;
	return T0;
}

HDTimer HDTimer_add_s(HDTimer T0, __IO uint32_t nTime_s)
{
	T0.nX10ms += nTime_s*SYS_TICK_FREQUENCY;
	return T0;
}

HDTimer GetTimeHD(void)
{
	HDTimer T;
	T.nX10ms = globalTime;
	T.nSysTick = SysTick->VAL;
	return T;
}

float GetTime_s(void)
{
	return ((float)globalTime/SYS_TICK_FREQUENCY + (float)((SysTick->VAL))/SystemCoreClock);
}

int HDTimer_diff_us(HDTimer T1, HDTimer T2)
{
	int td;
	td = _diff_uint32(T1.nX10ms, T2.nX10ms)*1000000/SYS_TICK_FREQUENCY;
	if (td < 0)//T1 earlier than T2
		td += ((int)T1.nSysTick - (int)T2.nSysTick)/72;
	else // T1 later than T2 or in same globalTime
		td += ((int)T2.nSysTick - (int)T1.nSysTick)/72;	
	return td;
}

int HDTimer_diff_ms(HDTimer T1, HDTimer T2)
{
	int td;
	td = _diff_uint32(T1.nX10ms, T2.nX10ms)*1000/SYS_TICK_FREQUENCY;
	if (td < 0)//T1 earlier than T2
		td += ((int)T1.nSysTick - (int)T2.nSysTick)/72000;
	else // T1 later than T2 or in same globalTime
		td += ((int)T2.nSysTick - (int)T1.nSysTick)/72000;	
	return td;
}
	
float HDTimer_diff(HDTimer T1, HDTimer T2)
{
	float td;
	td = (float)_diff_uint32(T1.nX10ms, T2.nX10ms)/SYS_TICK_FREQUENCY;
	if (td < 0)//T1 earlier than T2
		td += (float)((int)T1.nSysTick - (int)T2.nSysTick)/SystemCoreClock;
	else // T1 later than T2 or in same globalTime
		td += (float)((int)T2.nSysTick - (int)T1.nSysTick)/SystemCoreClock;
	return td;
}

