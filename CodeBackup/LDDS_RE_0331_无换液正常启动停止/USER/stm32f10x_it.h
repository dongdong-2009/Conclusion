/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.h 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

#include "stm32f10_usart.h"
/* Exported types ------------------------------------------------------------*/
#define CLENGTH  53
#define CSTART 0
#define CSTOP  50

#define ULENGTH 22
#define USTART 3
#define USTOP 21

static u8 timercnt=0  ;

typedef struct Frame
{
	u8 num;
  u8 format;
	u8 address; 
	u8 pattern;
	u8 autom;
}frame;

typedef struct _Frame
{
	u8 num;
  u8 format;
	u8 pattern;
}disframe;

extern u8 TX1[53];
extern u8 TX2[53];
extern u8 TX9[53];

extern u8 tx1[24];
extern u8 tx2[24];
extern u8 tx3[24];
extern u8 tx4[24];

extern u8 panelControl;
extern u8 panelCStatus;
extern u8 remoteControl;
extern u8 localControl;
extern u8 deviceRun;
extern u8 runStatus;

extern u8 digitalIn[8];//digital input data storge
extern u8 digitalOut[8];//digital output data storge


extern float rangeIn[12];//	
extern float analogIn[16];// 

extern float rangeOut[8]; //
extern float analogOut[8];//

extern sc8 address1[6];
extern sc8 address2[6];
u8 nCount;
u8 mCount;
u8 indata_type = 0;
u8 usart1_buff[53];
extern u8 dataCbuff[53];
extern u8 dataDbuff[53];
extern u8 dataEbuff[5];

u8 usart2_buff[24];
extern u8 dataUbuff[24];

	
extern void dataProcess(void);
extern void dataResponseLocal(void);
extern u8 CRC_check(u8 arr[],u8 start, u8 stop);


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void TIM1_UP_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void usart_senddata(u8 arr[]);
void usart2_senddata(u8 arr[]);
void usart2_senddata2(u8 arr[]);

//void SendInformation(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_IT_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
