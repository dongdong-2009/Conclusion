#include "stm32f10x_config.h"
#include "UI.h"
#include "touch.h"
#include "stm32f10_timer.h"
#include "LCD.h"
#include "stm32f10_gpio.h"
#include "stm32f10_usart.h" 
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
/*******************************************************************************
  * @brief  Main program.
  * @param  None
  * @retval None
  ******************************************************************************/
 u8  trahdatabuffer[60][4];
long int  trahdatasum[4];
u8  trahdataave[4];
int Mtemp =0 ;
int Mhum  =0 ;
float  humval=0.0;
float  tempval=0.0;
u16 PvRH=0,PvTe=0,SvTe=0,PvCO2=0,SvCO2=0,PSvTe=0,PSvCO2=0,uoSvTe=0,uoSvCO2=0;
u8  Tflag=0,Oflag=0,touchcase=0,PAGEflag=1;
char ss[6];
u16 RHO=0;
unsigned char getdataflag=0,lcdBG=1,lcdBG_timecount=0,onoff_flag=0,clearflag=0,send_flag=0;
unsigned char timcount=0;
GPIO_InitTypeDef GPIO_InitStruct;
// _lcd_dev lcddev={1,480, 272, 0x1943,0x2c, 0x2A, 0x2B};
u8 Uart2_SCnt=0;
u8 Uart2_Send_buffer[80]={0};
u8 Uart2_receive_buffer[80]={0};
u8 Uart2_RCnt=0;

u8 value=0;
u8 tempvalue=0;
u8 cnt=0;
u8 unoccup=0;
u8 co2cnt=0;

int CO2value=0;
u8 cnti=0;
int CO2valuesum =0;
extern u8 co2flag;

int main(void)
{
	
    RCC_Configuration(); //系统时钟配置
	some_Configuration();
    NVIC_Configuration();
	//SPI_Flash_Init();//初始化Flash;
    Usart_Configuration(); //串口配置
    Time_Configuration();  //定时器配置
//	Usart1ST();//开启串口1中断
	Usart2ST(); //开启串口2中断
    Tim3ST(); //开启时钟3
    Tim4ST() ;
 //   Tim2ST(); //开启时钟3
   // Tim5ST() ;

	LCD_Init();
    TP_Init();
	LCD_Clear(WHITE);
	PAGE0();
	PAGE1(PvRH,PvTe,SvTe,PvCO2,SvCO2);


	while(1)
	{
///////////pWm//////////////////////
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(GPIOA, &GPIO_InitStruct);
//
// value=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);   
//
//   if (!tempvalue& value )
//       cnt++		;
//
//   tempvalue= value;
//   if (cnt==10)
//    cnt=0;
///////////pWm//////////////////////
		if (getdataflag!=0)
		{
			getdataflag=0;
			timcount++;
			switch(send_flag)
			{
				case 0:if (timcount>=5){usart2_senddata(0);timcount=0;}break; //??5??
				case 1: usart2_senddata(1);send_flag=0;break;
                case 2: usart2_senddata(2);send_flag=0;break;
                case 3: usart2_senddata(3);send_flag=0;break;	//start
                case 4: usart2_senddata(4);send_flag=0;break; //stop

				default:break;
			}
			 Tim2ST();
			 for(cnti=0;cnti<100;cnti++)
			{
			 CO2valuesum+=CO2sum[cnti]	;
			 }
			 CO2value =	 CO2valuesum/100;
			 CO2valuesum =0;
		}

			  	 


//    	if((PIND&0x02)==0)
//		{
//			lcdBG_timecount=0;
//			clearflag=1;
//			if (lcdBG==0)
//			{
//		//		LCD_BG_H;
//				lcdBG=1;
//			}
//			if(Oflag==2)
//			{
//				touchcase=function();
//				Oflag=10;
//			}
//			
//			else if(Oflag==0)
//			{
//				Oflag=2;
////			TCNT2 = 0x64;TCCR2 = 0x05;
//			}
//			
//			else if(Oflag==1)
//			{
                touchcase=function();		
		  			
				switch(touchcase)
				{
					case 1:if (onoff_flag==0)
					{
						send_flag=2;
					}
					break;
					case 2:
					if (PAGEflag==1)
					{
		     		  delay_us(500);
					  PAGE2(SvTe,SvCO2);PAGEflag=2;PSvTe=SvTe;PSvCO2=SvCO2;
					  delay_us(500);
					  
					} 
					else if(PAGEflag==2)
					{
			    	    delay_us(500);
						PAGE1(PvRH,PvTe,SvTe,PvCO2,SvCO2);PAGEflag=1;
					    delay_us(500);
					}

					break;
					
					case 3:

				    if  (PAGEflag==2)
					{
					 //  if(PSvTe!=RHO)PSvCO2|=0x01;else PSvCO2&=0xfe;	budong shayisi
						PAGE1(PvRH,PvTe,SvTe,PvCO2,SvCO2);PAGEflag=1;
						packagedata(PvRH,PvTe,PSvTe,PvCO2,PSvCO2);
						send_flag=1;
					}
				
					break;
			
					case 4:if (onoff_flag==1)
					{
						send_flag=3;
					}
					break;

					case 10:if ((PAGEflag==2)&&(PSvTe>0))
					{
						PSvTe--;
						inttostrA(PSvTe,ss);
                     	showzifustr(80,140,ss,0,0xffff);
					}
					break;
					case 11:if (PAGEflag==2)
					{
						PSvTe++;
						inttostrA(PSvTe,ss);
						showzifustr(80,140,ss,0,0xffff);

					}break;
					case 12:if ((PAGEflag==2)&&(PSvCO2>0))
					{
						PSvCO2--;
						inttostr(PSvCO2,ss);
						showzifustr(320,140,ss,0,0xffff);
					}break;
					case 13:if (PAGEflag==2)
					{
						PSvCO2++;
						inttostr(PSvCO2,ss);
						showzifustr(320,140,ss,0,0xffff);
					}break;

					default:break;
				}
				touchcase=0;
			}
		}
//		else if(((PIND&0x02)!=0)&&(clearflag==1))
//		{
//			touchcase=0;
//			touch_clear();
//		}
//	}
//}
 
/*******************************************************************************
  * @brief  System clock setting.
  * @param  None
  * @retval None
  ******************************************************************************/
void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus; //定义外部高速晶体启动状态枚举变量；
	RCC_DeInit();//复位RCC寄存器到默认值；
	RCC_HSEConfig(RCC_HSE_ON);//打开外部的高速晶振； 
	HSEStartUpStatus = RCC_WaitForHSEStartUp();//等待外部高速时钟准备好
	if(HSEStartUpStatus == SUCCESS)
	{
		RCC_HCLKConfig(RCC_SYSCLK_Div1);//配置AHB
		RCC_PCLK2Config(RCC_HCLK_Div1);//配置APB2 
		RCC_PCLK1Config(RCC_HCLK_Div2);//配置APB1 
		//RCC_ADCCLKConfig(RCC_PCLK2_Div4);	      
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);//PLL=8M*9=72M
		RCC_PLLCmd(ENABLE);//时能PLL
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);//等待PLL就绪	      
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);// 配置系统时钟=PLL	  
		while(RCC_GetSYSCLKSource() != 0x08);//检查PLL时钟是否作为系统时钟	       
	}

}

void some_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

//	lcddev.bus16=1; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	



	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6; //PA.9
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	//复用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStruct); 
    PCout(6)=1;

}




void dataProcess()
{
//    u8 i,j;
    ReadDHT11();

//    for (j=0;j<20;j++)
//	 {
//	    
//	 for(i=0;i<4;i++)
//      {
//	    trahdatabuffer[j][i]= trahdatabuffer[j+1][i] ;
//	    if(j==19)
//	    trahdatabuffer[19][i] = tdata[i];
//	  }
//	 }
//
//	 for(i=0;i<4;i++)
//	 { 
//	    for(j=0;j<20;j++)
//       {
//	  	 trahdatasum[i] += trahdatabuffer[j][i];
//	   }
//	 }
//	 for(i=0;i<4;i++)
//	 {
// 	     trahdataave[i] = trahdatasum[i] /20;
//	 }

	 Mtemp = (tdata[2]*256+tdata[3]);
	 Mhum = (tdata[0]*256+tdata[1]);
	 
	 humval =  Mhum/10;
	 tempval=  Mtemp/10;


	if (PAGEflag==1)
	{
		inttostrA(Mtemp,ss);
		showzifustr(160,90,ss,0,0xffff);
		inttostr(CO2value,ss);
		showzifustr(160,150,ss,0,0xffff);
		inttostrA(Mhum,ss);
		showzifustr(160,210,ss,0,0xffff);
	
	} 
	packagedata(Mhum,Mtemp,PSvTe,1000,PSvCO2);
}

void Send_finish(unsigned char a)
{
	switch(a)
	{
		case 1:
			showonoff(1);
		break;
		
		case 2:
			showonoff(0);
		break;
		
		case 3:
			SvTe=PSvTe;
			SvCO2=PSvCO2;
			PAGE1(PvRH,PvTe,SvTe,PvCO2,SvCO2);
			PAGEflag=1;
		//	RHO=SvHO;
		break;
		
		default:break;
	}
}

void showonoff(int onoff)
{
	if(onoff==1)
	{
		onoff_flag=1;
		showzifustr(10,247,"ON",0x5ACB,0x8430);
		showzifustr(400,247,"OFF",0xb723,0x8430);
	}
	else if(onoff==0)
	{
		onoff_flag=0;
		showzifustr(10,247,"ON",0xb723,0x8430);
		showzifustr(400,247,"OFF",0x5ACB,0x8430);
	}	
}
PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1,(u8)ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

	return ch;
}
