/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO-MINI STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart1.h"


float average=0.0;
float weight=0.0;
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	//u32 weigh1 = 0;
	//float weigh2 =0.0;
	u32 weigh2 =0;

	NVIC_Configuration();

	RCC_Configuration();
	GPIO_Configuration();	
	/* USART1 ����ģʽΪ 115200 8-N-1���жϽ��� */
	USART1_Configuration();
	
	while(1)
	{
		Delay_MS(1000);
		//printf("\r\n ����һ��ѹ��������ʵ�� \r\n");
		weigh2 = Read_HX711();
		//average=0.9*average+((float)weigh2-8408890)*0.1;
		weight=((float)weigh2-8408890)/36000;
		average=0.9*average+0.1*weight;
		
		//weigh2 = weigh2/83886.08;
//	  weigh1 = weigh2*2000;
		//printf("%d\n",weigh2);
		printf("%f\n",average);
  }	
	
	//printf("\r\n ����һ�������жϽ��ջ���ʵ�� \r\n");	
	//printf("\r\n ���ڳ����ն˻��ߴ��ڵ������������ַ� \r\n");	


}
/*********************************************END OF FILE**********************/
