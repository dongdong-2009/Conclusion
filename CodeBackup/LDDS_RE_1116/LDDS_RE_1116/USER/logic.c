#include "logic.h"

float re_Liq=0,ws_Liq=0,hot_temp=0,get_flag=0, HWValveFB=0,temp_out=0.0,rh_out=0.0;
float Hot_valveS=0;
float temp_Liq=0;

//再生液位、泵等相关信息设置
u8 reg_levelset(void)
{
	return 0;
}

//再生算法设置
u8 reg_algorithm(float analogIn[], float arout[])
{
	return 0;
}

//再生系统液位报警信息
u8 RE_Level_Alarm(void)
{
	u8 Alarm_Flag=0;
	
	if(re_Liq>=RSLEVELMAXALARM)
		Alarm_Flag = 0x01;
	if(re_Liq<=RSLEVELMINALARM)
		Alarm_Flag = 0x02;
	if(ws_Liq>=WSLEVELMAXALARM)
		Alarm_Flag = 0x03;
	if(DE_Levelsingal>=SSLEVELMAXALARM)
		Alarm_Flag = 0x04;
	
	return Alarm_Flag;
}

//再生启动
u8 regStart(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8], u8 regflag)
{
  int reglevelA=0;
	Hot_valveS=100;
	
	while(get_flag==0)
	reglevelA=RE_Level_Alarm();          //读取故障信息	
	if(reglevelA!=0)                     //返回故障信息
		return reglevelA;
	
  APortOut(HWVALVE,Hot_valveS,10);     //打开热水阀
	analogOut[0]=Hot_valveS;             //记录热水阀输出值
	
	while(HWValveFB<=95)                 //判断热水阀是否打开，热水阀全开
	{ 
		reglevelA=RE_Level_Alarm();
		if(reglevelA!=0) 
			return reglevelA;
		delay_ms(10);
	}
	
	//启动液位不小于17厘米
	while(re_Liq<=17)                     //检查液位，小于17厘米时，打开ws阀
	{
		DPortOut(WSVALVE,1);
		delay_ms(10);	
	}	
	DPortOut(WSVALVE,0);                 //关闭ws阀
	delay_s(1);
	
	DPortOut(CPUMP,1);                   //开循环泵
	digitalOut[CPUMP]=1;                 //记录开循环泵
	delay_s(1);
	
	DPortOut(HEATPUMP,1);                //开热水泵
	digitalOut[HEATPUMP]=1;              //记录开热水泵
	
	while(hot_temp<50)                   //等待溶液被加热到50°
	{
		if(hot_temp>120)                   //防止温度跳变或突变
			hot_temp=0;
		
		reglevelA=RE_Level_Alarm();
		if(reglevelA!=0) 
			return reglevelA;
		delay_ms(100);                   
	}
	
	DPortOut(REFAN,1);                  //开风扇
	digitalOut[REFAN]=1;                //记录风扇
	
//	while(temp_out<40.0)                //判定出口空气温度是否大于40
//	{
//		reglevelA=RE_Level_Alarm();
//		if(reglevelA!=0) 
//			return reglevelA;
//		delay_ms(100);		
//	}
	
	return 0;
}

//再生停止
u8 regStop(float arin[12],float arout[8],u8 dout[8])
{
  DPortOut(HEATPUMP,0);                          //关热泵
	digitalOut[HEATPUMP]=0;  
  delay_s(5);	
	
	DPortOut(REFAN,0);                             //关风扇
	digitalOut[REFAN]=0;	
  delay_s(5);
	
	DPortOut(CPUMP,0);	                           //关循环泵
	digitalOut[CPUMP]=0;
	delay_s(5);
	
	APortOut(HWVALVE,0,arout[HWVALVE]);	           //关热水阀
  return 0;        
}

//再生清零
void reClever(float aout[12],u8 dout[8])
{
	u8 i;
	for(i=0;i<12;i++)
	{
		aout[i]=0;
		APortOut(i,0,1);
	}
	for(i=0;i<8;i++)
	{
		dout[i]=0;
		DPortOut(i,0);
	}
}

//再生默认设置
void reDefault(void)
{
 	u8 i;
	for(i=0;i<12;i++)
	{
	 	APortOut(i,0,100);
	}
}

//液位读取函数
void getlevel(float relevel,float wslevel,float hottemp,float hwvfb,float tempout)
{
	re_Liq=relevel;
	ws_Liq=wslevel;
	hot_temp=hottemp;
	HWValveFB=hwvfb;
	temp_out=tempout;
	get_flag=1;
}

//相对湿度和绝对湿度转换
float RH2HR(float temp, float relativehum)
{
	float p_sat=0.0;
	float humityratio=0.0;
	p_sat = (4.9569*temp*temp-54.75*temp+1437.4)/1000;
	humityratio = 1000 *(0.622*relativehum/100*p_sat/(101.325-relativehum/100*p_sat));
	return   humityratio; 
}

//浓度计算
float ConCalculate(void)
{
	float inlethumidity, outlethumidity, deltaHumidity;               //inlethumidity outlethumidity and deltahumidity
	float SolutionTemp;                                               //solution temperature
	float liqidconcentration;                                         //solution concentration
                                                 	
	SolutionTemp = analogIn[TSIN];
	outlethumidity = RH2HR(analogIn[TOUT], analogIn[RHOUT]);
  inlethumidity  = RH2HR(analogIn[TIN], analogIn[RHIN]);
	deltaHumidity = outlethumidity - inlethumidity;
	
	liqidconcentration = 4.0603-0.1846*deltaHumidity +0.6926*SolutionTemp+0.0108*deltaHumidity*deltaHumidity-0.0062*deltaHumidity*SolutionTemp-0.0027*SolutionTemp*SolutionTemp;
	//concentration = -0.0147-0.3402*deltaHumidity +0.8689*SolutionTemp+0.0121*deltaHumidity*deltaHumidity-0.0045*deltaHumidity*SolutionTemp-0.0043*SolutionTemp*SolutionTemp;

	return liqidconcentration;
}

u8 JudgeFlag(void)
{
	u8 Flag=0;
	float solution=0.0;
	float OutHum=0.0;
	float InHum=0.0;
	float DeltaHum=0.0;
	
	OutHum=RH2HR(analogIn[TOUT], analogIn[RHOUT]);
	InHum=RH2HR(analogIn[TIN], analogIn[RHIN]);
	
	if(StatusFlag==1)
	{
		DeltaHum=OutHum-InHum;
		solution=DeltaHum;
		//solution=recursive_average_filter(DeltaHum);
//		solution= AverageFilter(DeltaHum);
		
		//达到指定的换液浓度
		if((solution>=DELTAHumidity)&&(solution<=DELTAHumidity+6.0))
		{
			Flag=1;
		}
		else
			Flag=0;
	}
	
	return Flag;
}

//换液函数
u8 SS_Re_Transfer(u8 TFlag)
{
	int AlarmFlag=0;
	//u8 ConFlag=0;
	
	if(get_flag==0)                              //液位读取信息是否正常
		AlarmFlag=RE_Level_Alarm();                //获取报警信息
	if(AlarmFlag!=0)
		return AlarmFlag;                          //返回报警信息
		
	if((get_flag==1)&&(AlarmFlag==0))
	{		
		//再生液位超限处理
		if(re_Liq>=RSLEVELSTART+3)
		{
			DPortOut(TFVALVE,1);
			delay_us(10);			
			
			while(re_Liq>RSLEVELSTART+1)
			{
				re_Liq=analogIn[RSLEVEL];
			}
			DPortOut(TFVALVE,0);
			delay_us(10);	
		}
	
		//ws tank 液位不能过高
		if(ws_Liq>(WSLEVELMAX-25)&&(re_Liq<RSLEVELSTART-2))
		{
			DPortOut(WSVALVE,1);
			delay_us(10);
		}
		else if((ws_Liq<10||re_Liq>=RSLEVELSTART-2)&&(ConFlag==0))
		{
			DPortOut(WSVALVE,0);
			delay_us(10);
		}
		
		//除湿系统，SS tank液位不超过108才能换液
		if(DE_Levelsingal>=108)
		{
			DPortOut(TFVALVE,0);
			delay_us(10);
		}
		
		//除湿系统SS_Tank液位过低，再生系统无论在什么情况下都要给除湿导入溶液
		if((DE_Levelsingal<=10)&&(re_Liq>RSLEVELSTOP)&&(LevelFlag==0))
		{
			DPortOut(TFVALVE,1);
			delay_us(10);
		}
		else if((DE_Levelsingal>15)||(re_Liq<=RSLEVELSTOP))
		{
			DPortOut(TFVALVE,0);
			delay_us(10);
		}
		
				//再生液位过低，增加液位
		if((re_Liq<=24)&&(TFlag==0)&&(ConFlag==0))
		{					
			DPortOut(WSVALVE,1);
			delay_us(10);
		}
		else if((re_Liq>=RSLEVELSTART-2)&&(ConFlag==0))          //再生液位大于28cm
		{
			DPortOut(WSVALVE,0);
			delay_us(10);
		}
		
		//换液三个条件：SS液位低于108，再生液位正常，浓度达到
		if((DE_Levelsingal<108)&&(TFlag==1)&&(re_Liq>RSLEVELSTOP))
		{
			LevelFlag=1;
			DPortOut(TFVALVE,1);
			delay_us(10);
		}
		else if((LevelFlag==1)&&((re_Liq<=RSLEVELSTOP)||(TFlag==0)||(DE_Levelsingal>=108)))
		{
			LevelFlag=0;
			DPortOut(TFVALVE,0);
			delay_us(10);
		}
		
		//系统停止---浓度过高，液位低于28cm---风扇关闭，循环泵关闭
		if((AbDelta<43.0)&&(re_Liq<RSLEVELSTART-2)&&(TFlag==0)&&(StatusFlag==1))
		{
			DPortOut(REFAN,0);                             //关风扇  
			digitalOut[REFAN]=0;
			delay_us(1);
			
			DPortOut(CPUMP,0);                             //关循环泵                      
			digitalOut[CPUMP]=0;
			delay_us(1);
			
			DPortOut(HEATPUMP,0);                          //关热泵
			digitalOut[HEATPUMP]=0;  
			delay_s(5);	
			
			DPortOut(WSVALVE,1);                           //开ws阀门
			delay_us(1);
			
			ConFlag=1;
		}
		else if((re_Liq>=RSLEVELSTART-2)&&(ConFlag==1)&&(StatusFlag==0))   //系统重新开启---风扇开启
		{
			DPortOut(WSVALVE,0);                          //关闭WS阀门
			delay_us(10);

//			while(temp_out>40.0)                //判定出口空气温度是否大于40
//			{
//				temp_out=analogIn[TOUT];
//				delay_ms(100);		
//			}
			
			AlarmFlag=RE_Level_Alarm(); 
			if(AlarmFlag!=0)
				return AlarmFlag;
			
			DPortOut(CPUMP,1);                            //开循环泵                        
			digitalOut[CPUMP]=1;			
			delay_us(10);
			
			DPortOut(HEATPUMP,1);                         //开热水泵
			digitalOut[HEATPUMP]=1;                       //记录开热水泵
			delay_us(10);
			
			while(hot_temp<50)                            //热水温度达到50
			{
				hot_temp=analogIn[13];
				delay_ms(1);
				AlarmFlag=RE_Level_Alarm(); 
				if(AlarmFlag!=0)
					return AlarmFlag;
				delay_ms(1);
			}
			
			DPortOut(REFAN,1);                           //开风扇
			digitalOut[REFAN]=1;
			delay_us(10);
//			
//			while(temp_out<40.0)                //判定出口空气温度是否大于40
//			{
//				temp_out=analogIn[TOUT];
//				delay_ms(100);		
//			}
			
			ConFlag=0;
		}
		
		//溶液浓度过高，但是液位也大于28时，该如何处理，浓度过高，液位过高
		if((AbDelta<43.0)&&(re_Liq>=RSLEVELSTART-2)&&(StatusFlag==1)&&(TFlag==0))
		{
			DPortOut(REFAN,0);                          //关风扇
			digitalOut[REFAN]=0;
			delay_us(10);
			
			DPortOut(CPUMP,0);                          //关循环泵  
			digitalOut[CPUMP]=0;			
			delay_us(1);
			
			DPortOut(HEATPUMP,0);                          //关热泵
			digitalOut[HEATPUMP]=0;  
			delay_s(5);	
			
			DPortOut(WSVALVE,1);                        //开WS阀
			delay_us(1);
			
			ConFlag=2;
		}
		else if((ConFlag==2)&&(StatusFlag==0))
		{
			while(re_Liq<RSLEVELSTART+1)                //达到指定液位就关闭WS阀门
			{
				re_Liq=analogIn[RSLEVEL];                 //更新数据
				
				AlarmFlag=RE_Level_Alarm(); 
				if(AlarmFlag!=0)
					return AlarmFlag;
				//delay_ms(1);
			}			
			DPortOut(WSVALVE,0);
			delay_us(1);

//			while(temp_out>40.0)                //判定出口空气温度是否大于40
//			{
//				temp_out=analogIn[TOUT];
//				delay_ms(100);		
//			}
			
			if((re_Liq>=30.0)&&(DE_Levelsingal<108))    //重新启动系统
			{
//				while(temp_out>30.0)                //判定出口空气温度是否大于40
//				{
//					temp_out=analogIn[TOUT];
//					delay_ms(100);		
//				}
				
				AlarmFlag=RE_Level_Alarm(); 
				if(AlarmFlag!=0)
					return AlarmFlag;
				
				DPortOut(CPUMP,1);                        //开循环泵
				digitalOut[CPUMP]=1;
				delay_us(1);
				
				DPortOut(HEATPUMP,1);                         //开热水泵
				digitalOut[HEATPUMP]=1;                       //记录开热水泵
				delay_us(10);
				
				while(hot_temp<50)                       //热水温度达到50度
				{
					hot_temp=analogIn[13];
					delay_ms(1);
					
					AlarmFlag=RE_Level_Alarm(); 
					if(AlarmFlag!=0)
					return AlarmFlag;
					//delay_ms(1);					
				}
			
				DPortOut(REFAN,1);                       //开风扇
				digitalOut[REFAN]=1;
				delay_us(10);

//				while(temp_out<40.0)                //判定出口空气温度是否大于40
//				{
//					temp_out=analogIn[TOUT];
//					delay_ms(100);		
//				}
				
				ConFlag=0;
			}			
		}
	}
	
	else                                            //系统故障时，关闭热泵，风扇和循环泵
	{
		DPortOut(RE_ALARM,1);                         //输出报警信号
				
		DPortOut(HEATPUMP,0);                         //关闭热泵
		delay_s(1);
		DPortOut(REFAN,0);                            //关风扇  
		delay_s(1);	   
		DPortOut(CPUMP,0);	                          //关循环泵
	}
	
	APortOut(HWVALVE,Hot_valveS,10);
	analogOut[0]=Hot_valveS;
	
	return 0;
}

float AverageFilter(float data)
{
	int counter;
	float sum=0.0;
	float average=0.0;
	ValueBuf[count++]=data;
	if(count==Number)                       //先进先出，再求平均值
		count=0;
	for(counter=0;counter<Number;counter++)
	{
		sum+=ValueBuf[counter];
	}
	average=sum/Number;
	return average;
}

float recursive_average_filter(float data)
{
	float sum=0.0;
	float average=0.0;
	int i;
	valuebuf[Number]=data;
	for(i=0;i<Number;i++)
	{
		valuebuf[i]=valuebuf[i+1];
		sum+=valuebuf[i];
	}
	average=sum/Number;
	
	return average;
}
