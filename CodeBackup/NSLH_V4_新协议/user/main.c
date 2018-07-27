#include "stm32_config.h"

//printf打印到串口中
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

int main(void)
{
	RCC_Configuration();            //系统时钟配置信息
	IO_Configuration();             //DI and DO 初始化
	ADC_init();                     //AI初始化
	DAC_init();                     //AO初始化
	RTD_init();                     //测温初始化
	Usart_Total_Initi();            //串口初始化
	InitializeTimer(0,2);           //初始化定时器1，定时5s	
	TurnOnTim(0);
	TurnOnUsart1();
	
	InitializeTimer(1,1);           //初始化定时器2，定时1s	
	TurnOnTim(1);
	TurnOnUsart2();
	
	InitializeTimer(2,2);          //初始化定时器3，定时1s
	while(1)
		{
						
			//面板控制操作，PannelControl:1---Local/Remote  0---Stop    面板运行状态 PannelStatus:  0---面板无操作，1---面板Local/Remote
			while((!PannelControl)&&(!PannelStatus))
				{
					PannelControl=DPortIn(LOCALORREMOTE); //读取面板信息
					if(PannelControl)
						PannelStatus=1;
				}
			//对面板进行操作后，出现故障信息
			if(!PannelControl)
				{
					DPortOut(NSLHAlarm,1);      //输出报警信息
					 
					NSLH_Clear(DAC_data,DO_data);  //AO DO端口全部清零
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
