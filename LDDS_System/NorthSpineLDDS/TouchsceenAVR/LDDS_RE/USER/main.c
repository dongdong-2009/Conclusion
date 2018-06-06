
#include "stm32f10x_config.h"


 
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)


/*******************************************************************************
  * @brief  Main program.
  * @param  None
  * @retval None
  ******************************************************************************/
int aset=0,dset=9,dset1=9,abit=0;
int eevcount=0;	
int main(void)
{
	
    RCC_Configuration(); //系统时钟配置
    Usart_Configuration(); //串口配置
    port_Configuration(); //端口配置
    analog_in_init(); //电流电压输入模块初始化
	rtd_init();	//温度模块初始化
    dac_init();	//电流电压输出初始化
    Time_Configuration();  //定时器配置
	UsartST();//开启串口1中断
	UartST(); //开启串口2中断
    Tim3ST(); //开启时钟3（数据处理）中断

    while(1)
    {
		while(!panelControl&&(!panelCStatus))
		{
			panelControl=DPortIn(0);
			if(panelControl)
			{
				panelCStatus=1;
			}
		}
		if(!panelControl)
		{
			reClever(analogOut,digitalOut);
			panelCStatus=0;
		}
		if((deviceRun|localControl)&&(!runStatus)&&panelControl)
		{
		 	alarmFlag=regStart(digitalIn, digitalOut,analogIn,rangeIn,analogOut,rangeOut,panelControl);
			re_alarm=(enum _alarm)alarmFlag;
			runStatus=1;
		}
		if((!deviceRun)&&(!localControl)&&runStatus&&panelControl&&(re_alarm==start_normal))
		{
		 	alarmFlag=regStop(rangeIn, rangeOut,digitalOut);
			re_alarm=(enum _alarm)alarmFlag;
			reClever(analogOut,digitalOut);
			runStatus=0;
		}
		while(runStatus&&panelControl&&((remoteControl&deviceRun)|localControl))
		if(runStatus)
		{
			alarmFlag=reg_transfer(tf_flag);
			re_alarm=(enum _alarm)alarmFlag;
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

void dataResponseLocal(void)
{
     APortCIn(analogIn,rangeIn);
     DPortCIn(digitalIn);
     tx1[3]  =(u8)((u16)analogIn[RHOUT]/100);	
     tx1[4]  =(u8)((u16)analogIn[RHOUT]%100);
	 tx1[5]  =0;	
     tx1[6]  =0;
	 tx1[7]  =(u8)((u16)analogIn[RHIN]/100);	
     tx1[8]  =(u8)((u16)analogIn[RHIN]%100);
	 tx1[9]  =(u8)deviceRun|localControl;	
     tx1[10] =(u8)((u16)analogIn[TIN]%100);
	 tx1[11] =(u8)((u16)analogIn[TOUT]/100);
     tx1[12] =(u8)((u16)analogIn[TOUT]%100);
	 tx1[19] =1;
     tx1[20] =alarmFlag;				
     tx1[21]=CRC_check(tx1,3,21);
}	   


void dataProcess(void)
{
    if(dataCbuff[9]==0x57)
    {
		System_On=dataCbuff[11];
		De_On=dataCbuff[12];
		DE_Level=dataCbuff[13]*100+dataCbuff[14];
		SS_Level=dataCbuff[15]*100+dataCbuff[16];
		tf_flag=dataCbuff[17];
    }
    APortCIn(analogIn,rangeIn);
    DPortCIn(digitalIn);
	
	analogIn[0]=analogIn[0]/10;
	TX1[11]=(u8)(analogIn[0]/100);	
    TX1[12]=(u8)(((u16)analogIn[0])%100);
    TX1[13]=(u8)(((u32)(analogIn[0]*100))%100);
	analogIn[1]=analogIn[1]/10;
	TX1[14]=(u8)(analogIn[1]/100);	
    TX1[15]=(u8)(((u16)analogIn[1])%100);
    TX1[16]=(u8)(((u32)(analogIn[1]*100))%100);
	analogIn[2]=analogIn[2]/10;
	TX1[17]=(u8)(analogIn[2]/100);	
    TX1[18]=(u8)(((u16)analogIn[2])%100);
    TX1[19]=(u8)(((u32)(analogIn[2]*100))%100);
	analogIn[3]=analogIn[3]/10;
	TX1[20]=(u8)(analogIn[3]/100);	
    TX1[21]=(u8)(((u16)analogIn[3])%100);
    TX1[22]=(u8)(((u32)(analogIn[3]*100))%100);
	analogIn[4]=(analogIn[4]/50-4)/16*48;
	TX1[23]=(u8)(analogIn[4]/100);	
    TX1[24]=(u8)(((u16)analogIn[4])%100);
    TX1[25]=(u8)(((u32)(analogIn[4]*100))%100);
	analogIn[5]=(analogIn[5]/50-4)/16*60+60;
	TX1[26]=(u8)(analogIn[5]/100);	
    TX1[27]=(u8)(((u16)analogIn[5])%100);
    TX1[28]=(u8)(((u32)(analogIn[5]*100))%100);    
	analogIn[6]=analogIn[6]/10;
	TX1[29]=(u8)(analogIn[6]/100);	
    TX1[30]=(u8)(((u16)analogIn[6])%100);
    TX1[31]=(u8)(((u32)(analogIn[6]*100))%100);	

	analogIn[12]=analogIn[12]/100;
	TX2[23]=(u8)(analogIn[12]/100);	
    TX2[24]=(u8)(((u16)analogIn[12])%100);
    TX2[25]=(u8)(((u32)(analogIn[12]*100))%100);
	analogIn[13]=analogIn[13]/100;
	TX2[26]=(u8)(analogIn[13]/100);	
    TX2[27]=(u8)(((u16)analogIn[13])%100);
    TX2[28]=(u8)(((u32)(analogIn[13]*100))%100);	
	analogIn[14]=analogIn[14]/100;
	TX2[29]=(u8)(analogIn[14]/100);	
    TX2[30]=(u8)(((u16)analogIn[14])%100);
    TX2[31]=(u8)(((u32)(analogIn[14]*100))%100);	
	analogIn[15]=analogIn[15]/100;
	TX2[32]=(u8)(analogIn[15]/100);	
    TX2[33]=(u8)(((u16)analogIn[15])%100);
    TX2[34]=(u8)(((u32)(analogIn[15]*100))%100);		
    
    TX1[37]=(u8)(((u16)analogOut[0])/100);
    TX1[38]=(u8)(((u32)(analogOut[0]*100))%100);
    TX1[39]=(u8)(((u32)(analogOut[0]*10000))%100);
 		
    TX1[35]=Digital_handle(digitalIn ,1);
    TX1[36]=Digital_handle(digitalOut,1);
    TX2[35]=Digital_handle(digitalIn ,2);
    TX2[36]=Digital_handle(digitalOut,2);
    TX1[50]=CRC_check(TX1,0,50);
    TX2[50]=CRC_check(TX2,0,50);
	
	TX9[12]=(u8)deviceRun|localControl;
	TX9[13]=(u8)(analogIn[RSLEVEL]/100);
	TX9[14]=(u8)(((u16)analogIn[RSLEVEL])%100);
	TX9[15]=(u8)(analogIn[WSLEVEL]/100);
	TX9[16]=(u8)(((u16)analogIn[WSLEVEL])%100);

	getlevel(analogIn[RSLEVEL],analogIn[WSLEVEL],analogIn[13],analogIn[6]); 
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
