#include "config.h"

int main(void)
{
	RCC_Configuration();   //ϵͳʱ������
	LCD_Init();
	LCD_Clear(WHITE);
	while(1)
	{
		xianshi();
		showqq();
	}
}

void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus; //�����ⲿ���پ�������״̬ö�ٱ�����
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_DeInit();//��λRCC�Ĵ�����Ĭ��ֵ��
	RCC_HSEConfig(RCC_HSE_ON);//���ⲿ�ĸ��پ��� 
	HSEStartUpStatus = RCC_WaitForHSEStartUp();//�ȴ��ⲿ����ʱ��׼����

	if(HSEStartUpStatus == SUCCESS)
	{
		RCC_HCLKConfig(RCC_SYSCLK_Div1);//����AHB
		RCC_PCLK2Config(RCC_HCLK_Div1);//����APB2 
		RCC_PCLK1Config(RCC_HCLK_Div2);//����APB1 
		//RCC_ADCCLKConfig(RCC_PCLK2_Div4);	      
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);//PLL=8M*9=72M
		RCC_PLLCmd(ENABLE);//ʱ��PLL
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);//�ȴ�PLL����	      
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);// ����ϵͳʱ��=PLL	  
		while(RCC_GetSYSCLKSource() != 0x08);//���PLLʱ���Ƿ���Ϊϵͳʱ��	       
	}
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6; //PC6
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	//�����������
  GPIO_Init(GPIOC, &GPIO_InitStruct); 
  PCout(6)=1;           
}
