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

uint32_t IsTimeExpiredHD(uint32_t ms, uint32_t SysTickVAL)
{
    return lg(ms,globalTime) || (globalTime==ms && (SysTick->VAL > SysTickVAL));
}

/*微秒级精确延时函数*/
void delay_us(__IO uint32_t nTime)
{
    uint32_t tempSysTickVAL;
	uint32_t tempGTime;

	tempSysTickVAL = SysTick->VAL;
	tempGTime = globalTime + nTime/(1000000/SYS_TICK_FREQUENCY);
	nTime = nTime%(1000000/SYS_TICK_FREQUENCY);
	if (nTime>tempSysTickVAL/72)
	{
	    tempSysTickVAL += SystemCoreClock/SYS_TICK_FREQUENCY - nTime*72;
	    tempGTime++;
	}
	else
	    tempSysTickVAL -= nTime*72;
	
	while(lg(tempGTime,globalTime) || (globalTime==tempGTime && (SysTick->VAL > tempSysTickVAL)));
}

/*毫秒级精确延时函数*/
void delay_ms(__IO uint32_t nTime)
{
    uint32_t tempSysTickVAL;
	uint32_t tempGTime;

	tempSysTickVAL = SysTick->VAL;
	tempGTime = globalTime + nTime/(1000/SYS_TICK_FREQUENCY);
	nTime = nTime%(1000/SYS_TICK_FREQUENCY);
	if (nTime>tempSysTickVAL/72000)
	{
	    tempSysTickVAL += SystemCoreClock/SYS_TICK_FREQUENCY - nTime*72000;
	    tempGTime++;
	}
	else
	    tempSysTickVAL -= nTime*72000;
	
	while(lg(tempGTime,globalTime) || (globalTime==tempGTime && (SysTick->VAL > tempSysTickVAL)));
}

/*秒级精确延时函数*/
void delay_s(__IO uint32_t nTime)	     
{
  uint32_t tempSysTickVAL;
	uint32_t tempGTime;

	tempSysTickVAL = SysTick->VAL;
	tempGTime = globalTime + nTime*SYS_TICK_FREQUENCY;
	while(lg(tempGTime,globalTime) || (globalTime==tempGTime && (SysTick->VAL > tempSysTickVAL)));
}
