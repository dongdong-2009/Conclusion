#ifndef BSP_SYSTIMER_H
#define BSP_SYSTIMER_H

#include "stm32f10x.h"
#include "core_cm3.h"

/** @addtogroup  exported  macros
  * @{
  */
#define SYS_TICK_FREQUENCY          100			//100hz

/** @addtogroup exported variables
  * @{
  */
typedef struct _HDTimer
{
	__IO uint32_t nX10ms;
	__IO uint32_t nSysTick;
} HDTimer;

/** @addtogroup exported functions
  * @{
  */
void BSP_SysTickCfg(void);
void SysTick_Handler(void);
uint32_t Get_Gtime(void);
uint32_t IsTimeExpired(uint32_t ms);
uint32_t lg(uint32_t a, uint32_t b);
int _diff_uint32(uint32_t a, uint32_t b);

void delay_us(__IO uint32_t nTime_us);
void delay_ms(__IO uint32_t nTime_ms);
void delay_s(__IO uint32_t nTime_s);	

uint32_t IsTimeExpiredHD(HDTimer T);
HDTimer HDTimer_add_us(HDTimer T0, __IO uint32_t nTime_us);
HDTimer HDTimer_add_ms(HDTimer T0, __IO uint32_t nTime_ms);
HDTimer HDTimer_add_s(HDTimer T0, __IO uint32_t nTime_s);
int HDTimer_diff_us(HDTimer T1, HDTimer T2);
int HDTimer_diff_ms(HDTimer T1, HDTimer T2);
float HDTimer_diff(HDTimer T1, HDTimer T2);

HDTimer GetTimeHD(void);
float GetTime_s(void);
#endif
/*----------------------end of file----------------------*/

