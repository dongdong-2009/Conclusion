/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   串口中断接收测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO-MINI STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart1.h"


float average=0.0;
float weight=0.0;
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	//u32 weigh1 = 0;
	//float weigh2 =0.0;
	u32 weigh2 =0;

	NVIC_Configuration();

	RCC_Configuration();
	GPIO_Configuration();	
	/* USART1 配置模式为 115200 8-N-1，中断接收 */
	USART1_Configuration();
	
	while(1)
	{
		Delay_MS(1000);
		//printf("\r\n 这是一个压力传感器实验 \r\n");
		weigh2 = Read_HX711();
		//average=0.9*average+((float)weigh2-8408890)*0.1;
		weight=((float)weigh2-8408890)/36000;
		average=0.9*average+0.1*weight;
		
		//weigh2 = weigh2/83886.08;
//	  weigh1 = weigh2*2000;
		//printf("%d\n",weigh2);
		printf("%f\n",average);
  }	
	
	//printf("\r\n 这是一个串口中断接收回显实验 \r\n");	
	//printf("\r\n 请在超级终端或者串口调试助手输入字符 \r\n");	


}
/*********************************************END OF FILE**********************/
