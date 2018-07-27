#include "stm32_config.h"

//printf��ӡ��������
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

int main(void)
{
	RCC_Configuration();            //ϵͳʱ��������Ϣ
	IO_Configuration();             //DI and DO ��ʼ��
	ADC_init();                     //AI��ʼ��
	DAC_init();                     //AO��ʼ��
	RTD_init();                     //���³�ʼ��
	Usart_Total_Initi();            //���ڳ�ʼ��
	InitializeTimer(0,2);           //��ʼ����ʱ��1����ʱ5s	
	TurnOnTim(0);
	TurnOnUsart1();
	
	InitializeTimer(1,1);           //��ʼ����ʱ��2����ʱ1s	
	TurnOnTim(1);
	TurnOnUsart2();
	
	InitializeTimer(2,2);          //��ʼ����ʱ��3����ʱ1s
	while(1)
		{
						
			//�����Ʋ�����PannelControl:1---Local/Remote  0---Stop    �������״̬ PannelStatus:  0---����޲�����1---���Local/Remote
			while((!PannelControl)&&(!PannelStatus))
				{
					PannelControl=DPortIn(LOCALORREMOTE); //��ȡ�����Ϣ
					if(PannelControl)
						PannelStatus=1;
				}
			//�������в����󣬳��ֹ�����Ϣ
			if(!PannelControl)
				{
					DPortOut(NSLHAlarm,1);      //���������Ϣ
					 
					NSLH_Clear(DAC_data,DO_data);  //AO DO�˿�ȫ������
					PannelStatus=0;
				}
			//BMSControl---BMS Control system under Unoccupined mode	
			//TSControl---Touch Screen Control   Device Run---Host Computer Control  
			//RunStatus---the status of the system 0---not ok  1---ok
			if((TSControl|DeviceRun|(!UnOccupined))&&(!RunStatus)&&PannelControl)
				{
					AlarmFlag=NSLH_Start(ADC_data,DAC_data,DI_data,DO_data);
					if(AlarmFlag!=0)
						{
							DPortOut(NSLHAlarm,1);								
							NSLH_Clear(DAC_data,DO_data);
						}
					RunStatus=1;
				}
			else if(UnOccupined&&(!RunStatus)&&PannelControl)
				{
						NSLH_OccMode(ADC_data,DAC_data,DI_data,DO_data);
						RunStatus=1;
				}
			else if(BMSControl&&(!RunStatus)&&PannelControl)
				{
					AlarmFlag=NSLH_BMSStart(ADC_data,DAC_data,DI_data,DO_data);
					if(AlarmFlag!=0)
						{
							DPortOut(NSLHAlarm,1);								
							NSLH_Clear(DAC_data,DO_data);
						}
					NSLH_OccMode(ADC_data,DAC_data,DI_data,DO_data);
					RunStatus=1;
				}
							
			if(((!DeviceRun)|(!BMSControl))&&RunStatus&&PannelControl&&(!AlarmFlag))
				{
					AlarmFlag=NSLH_Stop(ADC_data,DAC_data,DI_data,DO_data);
					if(AlarmFlag!=0)
						{
							DPortOut(NSLHAlarm,1);
							NSLH_Clear(DAC_data,DO_data);
						}
						RunStatus=0;
				}
			while(RunStatus&&PannelControl&&(TSControl|DeviceRun|BMSControl))
			
			if(RunStatus)
			{
				RTContrHybird(off_coilTempSv,off_coilTemp,RoomTempSv,RoomTemp);
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
