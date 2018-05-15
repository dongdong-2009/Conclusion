#include "stm32_config.h"

//printf打印到串口中
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

float dataTemp[12];
float RTDtemperature[4];
float datavalue[8]={0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0};
int main(void)
{
 	RCC_Configuration();            //系统时钟配置信息
	IO_Configuration();             //DI and DO 初始化
	ADC_init();                     //AI初始化
	DAC_init();                     //AO初始化
	RTD_init();                     //测温初始化
	Usart_Total_Initi();            //串口初始化
	Timer1Config();
	Tim2Configure();
	
	InitializeTimer(2,2);          //初始化定时器3，定时2s，定时处理端口数据
	while(1)
	{
		PTBOn(0.0);					//PTB Fan 7.0
		APortOut(1,0.0);    //ERV 2.0  Range 0.0-5.0V
		ValvePosition = ValveControl();
		APortOut(2,10.0);   //Vavle Full Open  10.0
		DPortCIn(DI_data);  //Read the Status motion sensor(DI0) and 2 Damper(DI7 and DI6) 
		RTD_allchannels(RTDtemperature);  //Read the return water temperature (RTD 0)
		APortCIn(dataTemp);	//Read the DP sensor value(AI3) and chilled water valve feedback(AI11)
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

void PTBOn(float value)
{
	APortOut(0,value);
	APortOut(3,value);
}

void PTBOff(float value)
{
	APortOut(0,value);
	APortOut(3,value);
}

void systemTesting(void)
{
	if(CO2>CO2Sv)
		APortOut(1,3.0);
	else
		APortOut(1,2.0);
	
	if(RoomTemp>RoomTempSv)
		PTBOn(8.0);
	else
		PTBOn(7.0);
}

float ValveControl(void)
{
	float out=0.0;
	error=28.0-RoomTemp;
	ierror+=error;
	derror=error-last_error;
	out=1.5*error+0.2*ierror+0.01*derror;  //PID parameters should adjust
	last_error=error;
	
	if(out<0.0)
		out=0.0;
	else if(out>10.0)
		out=10.0;
	Delay_ms(25);
	return out;
}
