#include "stm32f10x_config.h"
#include "UI.h"
#include "touch.h"
#include "stm32f10_timer.h"
#include "LCD.h"
#include "stm32f10_gpio.h"
#include "stm32f10_usart.h" 
#include "math.h"	  
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
/*******************************************************************************
  * @brief  Main program.
  * @param  None
  * @retval None
  ******************************************************************************/
u8  trahdatabuffer[60][4];
long int  trahdatasum[4];
u8  trahdataave[4];

u8 codeMatrix[4]={0};
u8 codeCnt=0;
u8 pwFlag=0;
void 	pwCheck(u8 inCode);

u16 PvRH=600,PvTe=255,SvTe=0,PvCO2=0,SvCO2=0,PSvTe=255, PSVCO2value=500;
u8  Tflag=0,Oflag=0,touchcase=0;
volatile  u8 PAGEflag=1;
char ss[6];

unsigned char getdataflag=0,lcdBG=1,lcdBG_timecount=0,onoff_flag=0,clearflag=0,send_flag=0;
unsigned char timcount=0;
GPIO_InitTypeDef GPIO_InitStruct;

int   PCO2value=0;
float PCO2valueO=0;
float IC1value=0; 
float IC2value=0; 

int IC1sumvaluesum;
int IC2sumvaluesum;
int IC1sum[20]={0};
int IC2sum[20]={0};
u8 cnti=0;
u8 i=0;
u8 pageFinish=0;
extern u8 co2flag;

int main(void)
{
	u8 tempi=0;
    RCC_Configuration(); //系统时钟配置
    NVIC_Configuration();
	//SPI_Flash_Init();//初始化Flash;
    Usart_Configuration(); //串口配置
    Time_Configuration();  //定时器配置
	  Usart2ST(); //开启串口2中断
    Tim3ST(); //开启时钟3
    Tim1ST();
	  Tim2ST();
    Tim4ST() ;
	  Tim5ST() ;

	LCD_Init();
  TP_Init();
	LCD_Clear(WHITE);
	PAGE0();
	PAGE1(PvRH,PvTe,PvCO2);


	while(1)
	{
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

				default:break;
			}

			 for(cnti=0;cnti<20;cnti++)
			{
			  
			   IC1sumvaluesum+=IC1sum[cnti]	;
			   IC2sumvaluesum+=IC2sum[cnti]	;
	
			 }

			 IC1value =	 IC1sumvaluesum/20;
			 IC2value =	 IC2sumvaluesum/20;

			 PCO2valueO = 2000.0*(IC1value-20)/(IC2value-40)  ;   
			 PCO2value  = rint(2.21*(PCO2valueO-384)+744)   ;

			 if((IC1sum[0]==0)|(IC2value==40))
			 PCO2value =400;

			 IC1sumvaluesum =0;
			 IC2sumvaluesum =0;
		}
			  	 
    	if(	PCin(10)==0)
		{
			lcdBG_timecount=0;
			clearflag=1;
			if (lcdBG==0)
			{
			    PCout(6)=1; 	
				lcdBG=1;
			}
			if(Oflag==2)
			{
				touchcase=function();
				Oflag=10;
			}
			
			else if(Oflag==0)
			{
				Oflag=2;
              //  timer 
			}
			
			else if(Oflag==1)
			{
		  		pageFinish=0;	
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
					  Tim4SP();
					 // pageFinish = PAGE2(PSvTe,PSVCO2value);
						pageFinish = PAGEpw();
					  PAGEflag=4;
					  Tim4ST();
					} 			
					else if(PAGEflag==2)
					{
					  Tim4SP();
					  pageFinish =PAGE1(PvRH,PvTe,PCO2value);
					  PAGEflag=1;
					   Tim4ST();
					}

					break;
					
					case 3:

				    if  (PAGEflag==2)
					{	Tim4SP();
						pageFinish = PAGE1(PvRH,PvTe,PCO2value);PAGEflag=1;
						packagedata(PvRH,PvTe,PSvTe,PCO2value,PSVCO2value);
						send_flag=1;
						 Tim4ST();
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
                     	showzifustr(10,120,ss,0,BLUEBG,2);
					}
					break;
					case 11:if (PAGEflag==2)
					{
						PSvTe++;
						inttostrA(PSvTe,ss);
						showzifustr(10,120,ss,0,BLUEBG,2);

					}break;
					case 12:if ((PAGEflag==2)&&(PCO2value>0))
					{
						PSVCO2value--;
						inttostr(PSVCO2value,ss);
						showzifustr(252,120,ss,0,BLUEBG,2);
					}break;
					case 13:if (PAGEflag==2)
					{
						PSVCO2value++;
						inttostr(PSVCO2value,ss);
						showzifustr(252,120,ss,0,BLUEBG,2);
					}break;

				  case 20:
					{
					  
						pwCheck(1);	
            codeCnt++;						

					}break;
					
					case 21:
					{
						
						pwCheck(2);
						codeCnt++;

					}break;
					
					case 22:
					{
						
						pwCheck(3);
						codeCnt++;

					}break;
					
					case 23:
					{
						pwCheck(4);
						codeCnt++;

					}break;
					
					 case 24:
					{
						
						pwCheck(5);
						codeCnt++;

					}break;
					
					 case 25:
					{
						
						pwCheck(6);
						codeCnt++;

					}break;
					
					 case 26:
					{
						
						pwCheck(7);
						codeCnt++;

					}break;
					
					 case 27:
					{
						
						pwCheck(8);
						codeCnt++;

					}break;
					
					 case 28:
					{
						
						pwCheck(9);
						codeCnt++;

					}break;
					
					 case 29:
					{
						
						pwCheck('*');
						codeCnt++;

					}break;
					
					 case 30:
					{
						
						pwCheck(0);
						codeCnt++;

					}break;
					 case 31:
					{
						
						pwCheck('#');
						codeCnt++;

					}break;
					 case 32:
					{
						if(pwFlag==1)
							pageFinish = PAGE2(PSvTe,PSVCO2value);
						else
						{
							 for(tempi=0;tempi<4;tempi++)
								 codeMatrix[tempi]=0;
						}
              pwFlag=0;
					}break;
					
					 case 33:
					{
						for(tempi=0;tempi<4;tempi++)
								 codeMatrix[tempi]=0;
						pwFlag=0;

					}break;
					
					default:break;
				}
				touchcase=0;
			}
		}
		else if((PCin(10)!=0)&&(clearflag==1))
		{
			touchcase=0;
			touch_clear();
		}
	}
}
 
/*******************************************************************************
  * @brief  System clock setting.
  * @param  None
  * @retval None
  ******************************************************************************/
void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus; //定义外部高速晶体启动状态枚举变量；
	GPIO_InitTypeDef GPIO_InitStruct;

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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6; //PA.9
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	//复用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStruct); 
    PCout(6)=1;

}

void 	pwCheck(u8 inCode)
{

	 codeMatrix[codeCnt]= inCode;
	 
   if ((codeMatrix[0]==1)|| (codeMatrix[1]==1)||(codeMatrix[2]==2)||(codeMatrix[3]==2))
     pwFlag=1;
	 
	 if (codeCnt==3)
		 codeCnt=0;
	 
}
void dataProcess()
{
    int Mtemp =0 ;
    int Mhum  =0 ;
	
	ReadDHT11();

	Mtemp  = (tdata[2]*256+tdata[3]);
	Mhum   = (tdata[0]*256+tdata[1]);

	if((Mtemp>320)|(Mtemp<180))
	 Mtemp = 255 ;

	if (PAGEflag==1)	   ///有PAGEFLAG变了2但是还那个啥
	{
		inttostrA(Mtemp,ss);
		showzifustr(10,120,ss,0,BLUEBG,2);
		inttostr(PCO2value,ss);
		showzifustr(302,188,ss,0,BLUEBG,1);
		inttostrA(Mhum,ss);
		showzifustr(302,90,ss,0,BLUEBG,1);
	
	} 

	 PvRH = Mhum   ;
	 PvTe =	Mtemp  ;
 	packagedata(PvRH,PvTe,PSvTe,PCO2value,PSVCO2value);
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
//			PAGE1(PvRH,PvTe,PCO2value);
//			PAGEflag=1;
		break;
		
		default:break;
	}
}

void showonoff(int onoff)
{
	if(onoff==1)
	{
		onoff_flag=1;
		showzifustr(10,247,"ON",0x5ACB,0X01CF,1);
		showzifustr(410,247,"OFF",0xFFFF,0X01CF,1);

	}
	else if(onoff==0)
	{
		onoff_flag=0;
		showzifustr(10,247,"ON",0xFFFF,0X01CF,1);
		showzifustr(410,247,"OFF",0x5ACB,0X01CF,1);
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
