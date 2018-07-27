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
	RCC_Configuration(); 						//系统时钟配置
  Usart_Configuration(); 					//串口配置
  port_Configuration(); 					//端口配置
  analog_in_init(); 							//电流电压输入模块初始化
	rtd_init();											//温度模块初始化
  dac_init();											//电流电压输出初始化
  Time_Configuration();  					//定时器配置
	UsartST();											//开启串口1中断
	UartST(); 											//开启串口2中断
  Tim3ST(); 											//开启时钟3（数据处理）中断
	
	while(1)
  {
		//旋转按钮一共可以有三个状态：remote---local---stop, remote---1, stop/local---0
		while(!panelControl&&(!panelCStatus))      //读取旋转按钮输入信息，并判断面板控制状态
		{
			panelControl=DPortIn(0);                 //读取旋转按钮信息
			if(panelControl)                         //panelControl remote/local 模式  
			{
				panelCStatus=1;
			}
		}
		if(!panelControl)                          //判断系统旋钮是否关闭,处于stop状态
		{
			DPortOut(RE_ALARM,1);                    //报警信息
			
			reClever(analogOut,digitalOut);          //AO和DO全部清零，系统关闭，无操作
			panelCStatus=0;                          //面板控制状态设为0
		}
		//如果device run是上位机控制指令，而localControl是小板发布的控制指令
		//device run---1---start, device run---0---stop
		//localControl---1---start, localControl---0---stop
		//系统启动条件判断
		if((deviceRun|localControl|System_On)&&(!runStatus)&&panelControl)  //开启，并判断报警
		{
			//读取系统启动状态信息，是否存在故障
		 	alarmFlag=regStart(digitalIn, digitalOut,analogIn,rangeIn,analogOut,rangeOut,panelControl);
			re_alarm=(enum _alarm)alarmFlag;
			if(alarmFlag!=0)
			{
				DPortOut(RE_ALARM,1);
				
				DPortOut(HEATPUMP,0);
				delay_s(1);
				DPortOut(REFAN,0);                             //关风扇  
				delay_s(1);	   
				DPortOut(CPUMP,0);	                           //关循环泵
			}
			runStatus=1;                                 //设备运行正常
		}
		//系统停止条件判断
		//上位机发送停止命令，小板发送停止命令，系统处于运行状态，旋转按钮置1，系统正常运行
		if((!deviceRun)&&(!localControl)&&(!System_On)&&runStatus&&panelControl&&(re_alarm==start_normal))   //当没有故障时停止系统
		{
			//读取系统停止运行状态信息
		 	alarmFlag=regStop(rangeIn, rangeOut,digitalOut);
			re_alarm=(enum _alarm)alarmFlag;
			if(alarmFlag!=0)
			{
				DPortOut(RE_ALARM,1);
				
				DPortOut(HEATPUMP,0);
				delay_s(1);
				DPortOut(REFAN,0);                             //关风扇  
				delay_s(1);	   
				DPortOut(CPUMP,0);	                           //关循环泵
			}
			//reClever(analogOut,digitalOut);
			runStatus=0;
		}
		//device run 是上位机控制，控制系统remote模式
		//device run 和remote control 时刻都是0，表示系统并没有上位机控制，主要是通过小板控制启停，或者通过面板旋钮使小板处于remote/local模式
		while(runStatus&&panelControl&&((remoteControl&deviceRun)|localControl|System_On))
		if(runStatus) 														         //系统正常运行
		{
			Tran_Flag=JudgeFlag();
			//风扇开的时候，才会进行浓度计算。风扇没有开的话，浓度则设定为21
			alarmFlag=SS_Re_Transfer(Tran_Flag);             //启动换液
			re_alarm=(enum _alarm)alarmFlag;                 //提取报警信息
			if(alarmFlag!=0)
			{
				DPortOut(RE_ALARM,1);
				
				DPortOut(HEATPUMP,0);
				delay_s(1);
				DPortOut(REFAN,0);                             //关风扇  
				delay_s(1);	   
				DPortOut(CPUMP,0);	                           //关循环泵
			}
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
	ErrorStatus HSEStartUpStatus;                    //定义外部高速晶体启动状态枚举变量；
	RCC_DeInit();                                    //复位RCC寄存器到默认值；
	RCC_HSEConfig(RCC_HSE_ON);                       //打开外部的高速晶振； 
	HSEStartUpStatus = RCC_WaitForHSEStartUp();      //等待外部高速时钟准备好
	if(HSEStartUpStatus == SUCCESS)
	{
		RCC_HCLKConfig(RCC_SYSCLK_Div1);               //配置AHB
		RCC_PCLK2Config(RCC_HCLK_Div1);                //配置APB2 
		RCC_PCLK1Config(RCC_HCLK_Div2);                //配置APB1       
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);             //PLL=8M*9=72M
		RCC_PLLCmd(ENABLE);                                              //时能PLL
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);              //等待PLL就绪	      
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);                       //配置系统时钟=PLL	  
		while(RCC_GetSYSCLKSource() != 0x08);                            //检查PLL时钟是否作为系统时钟	       
	}
}

//读取小板发送数据信息 24字节
void dataResponseLocal(void)
{
	//读取AI和DI输入信息
	APortCIn(TempanalogIn,rangeIn);
  DPortCIn(digitalIn);
	
	//outlet humidity
  tx1[3]=(u8)((u16)TempanalogIn[RHOUT]/100);	
  tx1[4]=(u8)((u16)TempanalogIn[RHOUT]%100);
	
	tx1[5]=0;	
  tx1[6]=0;
	
	//inlet humidity
	tx1[7]=(u8)((u16)TempanalogIn[RHIN]/100);	
  tx1[8]=(u8)((u16)TempanalogIn[RHIN]%100);
	
	//设备运行信息
	tx1[9]=(u8)deviceRun|localControl|System_On;	
	
	//入口温度
  tx1[10]=(u8)((u16)TempanalogIn[TIN]%100);
	
	//出口温度
	tx1[11]=(u8)((u16)TempanalogIn[TOUT]/100);
  tx1[12]=(u8)((u16)TempanalogIn[TOUT]%100);
	tx1[19]=1;
  tx1[20]=alarmFlag;	                            //报警信息			
  tx1[21]=CRC_check(tx1,3,21);                    //校验码
}	    

//大板数据处理，53字节
void dataProcess(void)
{
	//解析数据包
	if(dataCbuff[9]==0x57)                      						//收到 transfer data
  {																												//拆分数据包
		//System_On=dataCbuff[11];                     
		De_On=dataCbuff[12];
		DE_Level=dataCbuff[13]*100+dataCbuff[14];             //除湿液位
		SS_Level=dataCbuff[15]*100+dataCbuff[16];             //强溶液液位
		tf_flag=dataCbuff[17];                                //换液标志位
		Concentration=dataCbuff[19]*100+dataCbuff[20];        //除湿浓度
  }
	
	System_On=digitalIn[REMOTEONFF];                        //读取DI输入信息                      
	
	//读取传感器数据返回值  sensor data return
  APortCIn(TempanalogIn,rangeIn);                         //读取模拟输入信息量
  DPortCIn(digitalIn);                                    //读取数字输入信息量
		
	analogIn[0]=TempanalogIn[0]/10;                             //inlet temperature
	TX1[11]=(u8)(analogIn[0]/100);	
  TX1[12]=(u8)(((u16)analogIn[0])%100);
  TX1[13]=(u8)(((u32)(analogIn[0]*100))%100);
	
	analogIn[1]=TempanalogIn[1]/10;                             //inlet humidity
	TX1[14]=(u8)(analogIn[1]/100);	
  TX1[15]=(u8)(((u16)analogIn[1])%100);
  TX1[16]=(u8)(((u32)(analogIn[1]*100))%100);
	
	analogIn[2]=TempanalogIn[2]/10;                             //outlet temperature
	TX1[17]=(u8)(analogIn[2]/100);	
  TX1[18]=(u8)(((u16)analogIn[2])%100);
  TX1[19]=(u8)(((u32)(analogIn[2]*100))%100);
	
	RHout=analogIn[RHOUT];
	
	analogIn[3]=TempanalogIn[3]/10;                             //outlet humidity
	TX1[20]=(u8)(analogIn[3]/100);	
  TX1[21]=(u8)(((u16)analogIn[3])%100);
  TX1[22]=(u8)(((u32)(analogIn[3]*100))%100);
	
	analogIn[4]=(TempanalogIn[4]/50-4)/16*48;                  //RE level
	TX1[23]=(u8)(analogIn[4]/100);	
  TX1[24]=(u8)(((u16)analogIn[4])%100);
  TX1[25]=(u8)(((u32)(analogIn[4]*100))%100);
	
	analogIn[5]=(TempanalogIn[5]/50-4)/16*60+60;              // weak solution level
	TX1[26]=(u8)(analogIn[5]/100);	
  TX1[27]=(u8)(((u16)analogIn[5])%100);
  TX1[28]=(u8)(((u32)(analogIn[5]*100))%100);    
	
	analogIn[6]=TempanalogIn[6]/10;
	TX1[29]=(u8)(analogIn[6]/100);	
  TX1[30]=(u8)(((u16)analogIn[6])%100);
  TX1[31]=(u8)(((u32)(analogIn[6]*100))%100);	
		
	analogIn[7]=TempanalogIn[7]/8;
	TX1[32]=(u8)(analogIn[7]/100);	
  TX1[33]=(u8)(((u16)analogIn[7])%100);
  TX1[34]=(u8)(((u32)(analogIn[7]*100))%100);
	
	analogIn[8]=AbOutHum;                             //出口绝对湿度
	TX2[11]=(u8)(analogIn[8]/100);	
  TX2[12]=(u8)(((u16)analogIn[8])%100);
  TX2[13]=(u8)(((u32)(analogIn[8]*100))%100);
	
	analogIn[9]=AbInHum;                             //入口绝对湿度
	TX2[14]=(u8)(analogIn[9]/100);	
  TX2[15]=(u8)(((u16)analogIn[9])%100);
  TX2[16]=(u8)(((u32)(analogIn[9]*100))%100);
	
	analogIn[10]=AbdeltaHum;                             //出入口绝对湿度差
	TX2[17]=(u8)(analogIn[10]/100);	
  TX2[18]=(u8)(((u16)analogIn[10])%100);
  TX2[19]=(u8)(((u32)(analogIn[10]*100))%100);
	
	//TX1和TX2分别存放两张表信息：TX1：analogIn[0]---analogIn[7]   TX2:analogIn[8]---analogIn[15]	
	analogIn[11]=AbDelta;                             //计算的浓度信息
	TX2[20]=(u8)(analogIn[11]/100);	
  TX2[21]=(u8)(((u16)analogIn[11])%100);
  TX2[22]=(u8)(((u32)(analogIn[11]*100))%100);
	
	analogIn[12]=TempanalogIn[12]/100;                      //solution inlet temperature
	TX2[23]=(u8)(analogIn[12]/100);	
  TX2[24]=(u8)(((u16)analogIn[12])%100);
  TX2[25]=(u8)(((u32)(analogIn[12]*100))%100);
		
	analogIn[13]=TempanalogIn[13]/100;                    //solution outlet temperature
	TX2[26]=(u8)(analogIn[13]/100);	
  TX2[27]=(u8)(((u16)analogIn[13])%100);
  TX2[28]=(u8)(((u32)(analogIn[13]*100))%100);	
	
	analogIn[14]=TempanalogIn[14]/100;                    //hot water inlet temperature
	TX2[29]=(u8)(analogIn[14]/100);	
  TX2[30]=(u8)(((u16)analogIn[14])%100);
  TX2[31]=(u8)(((u32)(analogIn[14]*100))%100);	
	
	analogIn[15]=TempanalogIn[15]/100;                    //hot water outlet temperature
	TX2[32]=(u8)(analogIn[15]/100);	
  TX2[33]=(u8)(((u16)analogIn[15])%100);
  TX2[34]=(u8)(((u32)(analogIn[15]*100))%100);		
    
	TX1[37]=(u8)(((u16)analogOut[0])/100);                //hot water valve
  TX1[38]=(u8)(((u32)(analogOut[0]*100))%100);
  TX1[39]=(u8)(((u32)(analogOut[0]*10000))%100);
 		
  TX1[35]=Digital_handle(digitalIn ,1);                 //存放DI信息
  TX1[36]=Digital_handle(digitalOut,1);                 //存放DO信息
  
	TX2[35]=Digital_handle(digitalIn ,2);                 //存放DI信息
  TX2[36]=Digital_handle(digitalOut,2);                 //存放DO信息
  
	TX1[50]=CRC_check(TX1,0,50);                          //校验位信息
  TX2[50]=CRC_check(TX2,0,50);                          //校验位信息
	
	//TX9存放transfer data，用于DE和RE系统之间数据交互
	//TX9[12]=(u8)deviceRun|localControl;
	TX9[11]=System_On;
	TX9[12]=runStatus;                                         //系统运行状态
	TX9[13]=(u8)(analogIn[RSLEVEL]/100);                       //再生液位
	TX9[14]=(u8)(((u16)analogIn[RSLEVEL])%100);    
	TX9[15]=(u8)(analogIn[WSLEVEL]/100);                       //weak solution 液位
	TX9[16]=(u8)(((u16)analogIn[WSLEVEL])%100);
	TX9[19]=(u8)(analogIn[11]/100);                            //浓度信息
	TX9[20]=(u8)(((u16)analogIn[11])%100);
	
	//获取液位信息
	getlevel(analogIn[RSLEVEL],analogIn[WSLEVEL],analogIn[13],analogIn[6],analogIn[TOUT]); 
		
	//除湿系统中SS tank液位信息
  //读取AI端口，AI7，DE系统SS tank液位信息
	DE_Levelsingal=analogIn[DE_LEVEL];
	
	//溶液入口温度
	InletSolutemp=analogIn[TSIN];                    //原始数据
	//InletSoluTemp=AverageFilter(InletSolutemp);      //滤波数据
	//InletSoluTemp=recursive_average_filter(InletSolutemp);
	
	AbOutHum = RH2HR(analogIn[TOUT], analogIn[RHOUT]);
	AbInHum = RH2HR(analogIn[TIN], analogIn[RHIN]);
	
	//风扇和循环泵开的情况下，才开始进行浓度计算
	if((digitalOut[CPUMP]==1)&&(digitalOut[REFAN]==1)&&(InletSolutemp>67.0))
	{
		StatusFlag=1;
	}
	else
	{
		StatusFlag=0;
	}
	
	//浓度计算，风扇开启的状态下，系统正常运行
	if(StatusFlag==1)
	{
		AbDelta=AbOutHum-AbInHum;
		//AbdeltaHum=AverageFilter(AbDelta);
		AbdeltaHum=recursive_average_filter(AbDelta);
	}
	else if(StatusFlag==0)
	{
		//AbdeltaHum=100;
		AbDelta=100;
	}	
		
}

//函数重定义，串口输出打印信息
PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1,(u8)ch);
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	return ch;
}
