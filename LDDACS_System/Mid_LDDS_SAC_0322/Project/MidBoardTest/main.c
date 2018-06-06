/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Main program body.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "rtd.h"
#include "delay.h"
#include "DAC8554.h"
#include "MuxCfg.h"
#include "Dio.h"
#include "Pwm.h"
#include "AD.h"
#include "Globle.h"
#include "LDDSPorts.h"
#include "LDDS_demid.h"

#include<stdlib.h>
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

int main(void)
{
	NVIC_Configuration();
//	delay_init();
	ADC1_GPIO_Config();
    ADC1_Mode_Config();
//	DioCfg();
	UART_Configuration();
	LedInit();
	SPI_Flash_Init(); 
	DAC7554_GPIO_Config();
	TIM2_Int_Init(20,7199); //定时器初始化为5ms中断一次
	TIM4_Int_Init(5,18000-1);

	while (1)
	{	
	    while(!panelControl&&(!panelCStatus))
      {  
		   panelControl =DI_onechannel(LOCALORREMOTE);
		   panelControl=1;
		   if(panelControl)
			{
			 	panelCStatus=1;	
			}
	  }
	  if(!panelControl)
		{
			panelCStatus=0;
		}

      if(panelCStatus)
        {
		  statusCheck();  
		  lowbufCheck();

        }




	}
}


/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
