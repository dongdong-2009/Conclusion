#include "config.h"
#include "modbusNew.h"
#include "stm32f10x_iwdg.h"

u8 mode_vol=MODE_VOLTAGE;
u8 mode_curr=MODE_CURRENT;
float Position=0.0;

int main(void)
{	
	RCC_Configuration();
	NVIC_Configuration();
	delay_init();
	ADC1_GPIO_Config();
  ADC1_Mode_Config();
	DioCfg();
	LedInit();
	SPI_Flash_Init();
	DAC7554_GPIO_Config();
	UsartConfigure();
	IWDG_Configuration();
	Timer1Config();        //定时器处理Modbus协议
	Tim2Configure();       //定时器处理与小板通信协议
	
	PWM1_Init(100);                     //设置PWM1输出周期100*100us           
	PWM2_Init(100);                     //设置PWM2输出周期100*100us  

	while(1)
	{
		IWDG_ReloadCounter(); 
		Modbus_RegMap();
		RS485_Service();                              //modbus通信
		
		LED=0;
		Position=CO2Sv/10.0;
		SetAoOut(Position,4,mode_vol);      //水阀全开
		advalue[1]=ReadAdOfChannel(6,mode_vol);       //电压输入
		//advalue[2]=ReadAdOfChannel(2,mode_curr);  //电流输入
		//advalue[3]=ReadAdOfChannel(3,mode);       //电压输入
		temperature = advalue[1]*10.0-50;              //读取水温  Offcoill_temp = advalue[3]*10.0-50.0;温度计算公式
		Temp=(u16)(temperature*10);
		if(RoomTempSv<=5.1)
			RoomTempSv=0.0;
		PWM1_SetHighTime(RoomTempSv*10);
		PWM2_SetHighTime(RoomTempSv*10);
		
		delay_ms(100);
		LED=1;
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

void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//设置中断向量表位置和偏移量  
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);    //向量表位于FLASH，向量表基地址的偏移量为0 
	
	//设置优先级分组：先占优先级和从优先级。
	//输入参数：优先级分组位长度
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  //先占优先级4位，从优先级0位
  
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;          //USART1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel =TIM1_UP_IRQn;          //TIM1中断   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级3	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;          //USART1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;          //USART1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
}

void LedInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE  , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void IWDG_Configuration(void)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);      
    IWDG_SetPrescaler(IWDG_Prescaler_256);      //40K/256=156HZ(6.4ms)
    IWDG_SetReload(1562);       
    IWDG_ReloadCounter();
    IWDG_Enable();
}
