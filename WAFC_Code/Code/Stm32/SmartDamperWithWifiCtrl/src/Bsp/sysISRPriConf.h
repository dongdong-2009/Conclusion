/**
  ******************************************************************************
  * @file    MCLibraryISRPriorityConf.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.2.0
  * @date    08-May-2012 16:22
  * @brief   This file contains the priority configuration for each interrupt 
  *			 service routine used by the MC library      
  ******************************************************************************
  * <br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BB5000_ISRPRIORITYCONF_H
#define _BB5000_ISRPRIORITYCONF_H

/* Includes ------------------------------------------------------------------*/

/** @addtogroup STM32_PMSM_MC_Library
  * @{
  */
  
/** @defgroup MCLibraryISRPriorityConf_definitions MCLibraryISRPriorityConf definitions
* @{
*/

/* Systick ISR priority */
#define SYSTICK_PRE_EMPTION_PRIORITY 4u
#define SYSTICK_SUB_PRIORITY 0u

/* Do not modify (NVIC_PriorityGroup_3 is assumed to be set) */
#define SYSTICK_PRIORITY (((SYSTICK_PRE_EMPTION_PRIORITY & 0x07) << 1) | (SYSTICK_SUB_PRIORITY & 0x01))

/**
  * @}
  */

/**
  * @}
  */

#endif /* __MCLIBRARYISRPRIORITYCONF_H */

/******************* (C) COPYRIGHT 2012 STMicroelectronics *****END OF FILE****/
