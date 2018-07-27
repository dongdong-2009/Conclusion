#include "stm32_config.h"

//printf��ӡ��������
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
int i;
float datavalue[8]={0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0};
int main(void)
{
	RCC_Configuration();            //ϵͳʱ��������Ϣ
	IO_Configuration();             //DI and DO ��ʼ��
	ADC_init();                     //AI��ʼ��
	DAC_init();                     //AO��ʼ��
	RTD_init();                     //���³�ʼ��
	Usart_Total_Initi();            //���ڳ�ʼ��
	InitializeTimer(0,0.005);           //��ʼ����ʱ��1����ʱ5ms	
	TurnOnTim(0);
	TurnOnUsart1();
	
	InitializeTimer(1,1);           //��ʼ����ʱ��2����ʱ1s	
	TurnOnTim(1);
	TurnOnUsart2();
	
	InitializeTimer(2,2);          //��ʼ����ʱ��3����ʱ2s
	while(1)
		{
			//APortCOut(datavalue);
			//APortOut(1,5.0);
			APortCIn(ADC_data);
			for(i=0;i<12;i++)
			{
				AdREG[i]=ADC_data[i];
			}
				
			for(i=0;i<8;i++)
			{
				DiREG[i]=DPortIn(i);
			}
			
			RTD_allchannels(RTD_value);
			RTDREG[0]=RTD_value[0]*100;
			RTDREG[1]=RTD_value[1]*100;
			RTDREG[2]=RTD_value[2]*100;
			RTDREG[3]=RTD_value[3]*100;
			
		for(i=0;i<8;i++)
		{
			DPortOut(i,DoREG[i]);
		}
		
		for(i=0;i<8;i++)
		{
			APortOut(i,(float)DAREG[i]);
		}
		
		
		}
	

}	

void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;                              //�����ⲿ���پ�������״̬ö�ٱ�����
	RCC_DeInit();                                              //��λRCC�Ĵ�����Ĭ��ֵ��
	RCC_HSEConfig(RCC_HSE_ON);                                 //���ⲿ�ĸ��پ��� 
	HSEStartUpStatus = RCC_WaitForHSEStartUp();                //�ȴ��ⲿ����ʱ��׼����
	if(HSEStartUpStatus == SUCCESS)
		{
			RCC_HCLKConfig(RCC_SYSCLK_Div1);                         //����AHB
			RCC_PCLK2Config(RCC_HCLK_Div1);                          //����APB2 
			RCC_PCLK1Config(RCC_HCLK_Div2);                          //����APB1 
			//RCC_ADCCLKConfig(RCC_PCLK2_Div4);	      
			RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);     //PLL=8M*9=72M
			RCC_PLLCmd(ENABLE);                                      //ʱ��PLL
			while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);      //�ȴ�PLL����	      
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);               //����ϵͳʱ��=PLL	  
			while(RCC_GetSYSCLKSource() != 0x08);                    //���PLLʱ���Ƿ���Ϊϵͳʱ��	       
		}
}

PUTCHAR_PROTOTYPE    //ʹ��printf����ʱ�����Խ�����ͨ�����ڴ�ӡ����
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1,(u8)ch);
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	return ch;
}
