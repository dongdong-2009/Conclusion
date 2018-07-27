#include "stm32_config.h"

//printf打印到串口中
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
int i;
float datavalue[8]={0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0};
int main(void)
{
	RCC_Configuration();            //系统时钟配置信息
	IO_Configuration();             //DI and DO 初始化
	ADC_init();                     //AI初始化
	DAC_init();                     //AO初始化
	RTD_init();                     //测温初始化
	Usart_Total_Initi();            //串口初始化
	InitializeTimer(0,0.005);           //初始化定时器1，定时5ms	
	TurnOnTim(0);
	TurnOnUsart1();
	
	InitializeTimer(1,1);           //初始化定时器2，定时1s	
	TurnOnTim(1);
	TurnOnUsart2();
	
	InitializeTimer(2,2);          //初始化定时器3，定时2s
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
	ErrorStatus HSEStartUpStatus;                              //定义外部高速晶体启动状态枚举变量；
	RCC_DeInit();                                              //复位RCC寄存器到默认值；
	RCC_HSEConfig(RCC_HSE_ON);                                 //打开外部的高速晶振； 
	HSEStartUpStatus = RCC_WaitForHSEStartUp();                //等待外部高速时钟准备好
	if(HSEStartUpStatus == SUCCESS)
		{
			RCC_HCLKConfig(RCC_SYSCLK_Div1);                         //配置AHB
			RCC_PCLK2Config(RCC_HCLK_Div1);                          //配置APB2 
			RCC_PCLK1Config(RCC_HCLK_Div2);                          //配置APB1 
			//RCC_ADCCLKConfig(RCC_PCLK2_Div4);	      
			RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);     //PLL=8M*9=72M
			RCC_PLLCmd(ENABLE);                                      //时能PLL
			while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);      //等待PLL就绪	      
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);               //配置系统时钟=PLL	  
			while(RCC_GetSYSCLKSource() != 0x08);                    //检查PLL时钟是否作为系统时钟	       
		}
}

PUTCHAR_PROTOTYPE    //使用printf函数时，可以将数据通过串口打印出来
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1,(u8)ch);
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	return ch;
}
