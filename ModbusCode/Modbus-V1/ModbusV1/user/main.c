#include "stm32_config.h"

//printf��ӡ��������
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

float dataTemp[12];
float RTDtemperature[4];
float datavalue[8]={0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0};
int main(void)
{
 	RCC_Configuration();            //ϵͳʱ��������Ϣ
	IO_Configuration();             //DI and DO ��ʼ��
	ADC_init();                     //AI��ʼ��
	DAC_init();                     //AO��ʼ��
	RTD_init();                     //���³�ʼ��
	Usart_Total_Initi();            //���ڳ�ʼ��
	Timer1Config();
	Tim2Configure();
	
	InitializeTimer(2,2);          //��ʼ����ʱ��3����ʱ2s����ʱ����˿�����
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
