#include "config.h"

u8 mode=MODE_VOLTAGE;
unsigned char DiMap;
int i=0;

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
	
	//开启定时器2，定时周期为2ms
	Tim2Configure();
		
	while(1)
	{
		LED=0;
		
		//AI Test
		for(i=0;i<=6;i++)
		{
			advalue[i]=ReadAdOfChannel(i,mode);
		}
		temperature = advalue[1]*20;
		//DI Test
		DiMap=GetDiMap(); 

		PWM1_Init(WriteReg[18]);                     //设置PWM1输出周期100*100us           
		PWM1_SetHighTime(WriteReg[19]);               //设置PWM1输出高电平时间为70*100us 
	
		PWM2_Init(WriteReg[20]);                     //设置PWM2输出周期100*100us  
		PWM2_SetHighTime(WriteReg[21]);               //设置PWM2输出高电平时间为30*100us 
		
		//AO Test
		//SetAoOut(9,1,mode);  
		SetAoOut(WriteReg[0],1,mode);
		SetAoOut(WriteReg[1],2,mode);
		SetAoOut(WriteReg[2],3,mode);
		SetAoOut(WriteReg[3],4,mode);
		
		//DO Test
		SetSpdtState(1,WriteReg[14]);SetSpdtState(3,WriteReg[15]);
		SetSpdtState(2,WriteReg[16]); SetSpdtState(4,WriteReg[17]); 
		
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel =TIM2_IRQn;          	 //TIM2中断   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//
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
