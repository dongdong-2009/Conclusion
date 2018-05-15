#include <stm32f10x.h>
#include "bsp_hwConfig.h"
#include "bsp_led.h"

/**
  * @brief  io init
  * @param none
  * @retval None
*/
void BSP_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(LED1_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(LED2_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED2_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED2_PORT, &GPIO_InitStructure);

	BSP_GPIO_SetOut(GPIO_ALL,GPIO_ALL);
}

/**
  * @brief  io set,可以调用该函数，一次置位多个引脚的输出状态
  * @param none
  * @retval None
*/

void BSP_GPIO_SetOut(uint32_t pins,uint32_t val)
{	
	if(pins & GPIO_LED1)
	{	
		if(val & GPIO_LED1)
			GPIO_WriteBit(LED1_PORT, LED1_PIN, Bit_RESET);
		else
			GPIO_WriteBit(LED1_PORT, LED1_PIN, Bit_SET);
	}
	
	if(pins & GPIO_LED2)
	{	
		if(val & GPIO_LED2)
			GPIO_WriteBit(LED2_PORT, LED2_PIN, Bit_RESET);
		else
			GPIO_WriteBit(LED2_PORT, LED2_PIN, Bit_SET);
	}
}
/*---------------------end of file----------------------*/

