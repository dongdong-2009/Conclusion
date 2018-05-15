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

/** @addtogroup exported functions
  * @{
  */
void BSP_SysTickCfg(void);
void SysTick_Handler(void);
uint32_t Get_Gtime(void);
uint32_t IsTimeExpired(uint32_t ms);
uint32_t lg(uint32_t a, uint32_t b);
uint32_t IsTimeExpiredHD(uint32_t ms, uint32_t SysTickVAL);

void delay_us(__IO uint32_t nTime);
void delay_ms(__IO uint32_t nTime);
void delay_s(__IO uint32_t nTime);	

#endif
/*----------------------end of file----------------------*/

