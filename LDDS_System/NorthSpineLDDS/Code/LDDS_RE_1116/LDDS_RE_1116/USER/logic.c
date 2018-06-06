#include "logic.h"

float re_Liq=0,ws_Liq=0,hot_temp=0,get_flag=0, HWValveFB=0,temp_out=0.0,rh_out=0.0;
float Hot_valveS=0;
float temp_Liq=0;

//����Һλ���õ������Ϣ����
u8 reg_levelset(void)
{
	return 0;
}

//�����㷨����
u8 reg_algorithm(float analogIn[], float arout[])
{
	return 0;
}

//����ϵͳҺλ������Ϣ
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

//��������
u8 regStart(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8], u8 regflag)
{
  int reglevelA=0;
	Hot_valveS=100;
	
	while(get_flag==0)
	reglevelA=RE_Level_Alarm();          //��ȡ������Ϣ	
	if(reglevelA!=0)                     //���ع�����Ϣ
		return reglevelA;
	
  APortOut(HWVALVE,Hot_valveS,10);     //����ˮ��
	analogOut[0]=Hot_valveS;             //��¼��ˮ�����ֵ
	
	while(HWValveFB<=95)                 //�ж���ˮ���Ƿ�򿪣���ˮ��ȫ��
	{ 
		reglevelA=RE_Level_Alarm();
		if(reglevelA!=0) 
			return reglevelA;
		delay_ms(10);
	}
	
	//����Һλ��С��17����
	while(re_Liq<=17)                     //���Һλ��С��17����ʱ����ws��
	{
		DPortOut(WSVALVE,1);
		delay_ms(10);	
	}	
	DPortOut(WSVALVE,0);                 //�ر�ws��
	delay_s(1);
	
	DPortOut(CPUMP,1);                   //��ѭ����
	digitalOut[CPUMP]=1;                 //��¼��ѭ����
	delay_s(1);
	
	DPortOut(HEATPUMP,1);                //����ˮ��
	digitalOut[HEATPUMP]=1;              //��¼����ˮ��
	
	while(hot_temp<50)                   //�ȴ���Һ�����ȵ�50��
	{
		if(hot_temp>120)                   //��ֹ�¶������ͻ��
			hot_temp=0;
		
		reglevelA=RE_Level_Alarm();
		if(reglevelA!=0) 
			return reglevelA;
		delay_ms(100);                   
	}
	
	DPortOut(REFAN,1);                  //������
	digitalOut[REFAN]=1;                //��¼����
	
//	while(temp_out<40.0)                //�ж����ڿ����¶��Ƿ����40
//	{
//		reglevelA=RE_Level_Alarm();
//		if(reglevelA!=0) 
//			return reglevelA;
//		delay_ms(100);		
//	}
	
	return 0;
}

//����ֹͣ
u8 regStop(float arin[12],float arout[8],u8 dout[8])
{
  DPortOut(HEATPUMP,0);                          //���ȱ�
	digitalOut[HEATPUMP]=0;  
  delay_s(5);	
	
	DPortOut(REFAN,0);                             //�ط���
	digitalOut[REFAN]=0;	
  delay_s(5);
	
	DPortOut(CPUMP,0);	                           //��ѭ����
	digitalOut[CPUMP]=0;
	delay_s(5);
	
	APortOut(HWVALVE,0,arout[HWVALVE]);	           //����ˮ��
  return 0;        
}

//��������
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

//����Ĭ������
void reDefault(void)
{
 	u8 i;
	for(i=0;i<12;i++)
	{
	 	APortOut(i,0,100);
	}
}

//Һλ��ȡ����
void getlevel(float relevel,float wslevel,float hottemp,float hwvfb,float tempout)
{
	re_Liq=relevel;
	ws_Liq=wslevel;
	hot_temp=hottemp;
	HWValveFB=hwvfb;
	temp_out=tempout;
	get_flag=1;
}

//���ʪ�Ⱥ;���ʪ��ת��
float RH2HR(float temp, float relativehum)
{
	float p_sat=0.0;
	float humityratio=0.0;
	p_sat = (4.9569*temp*temp-54.75*temp+1437.4)/1000;
	humityratio = 1000 *(0.622*relativehum/100*p_sat/(101.325-relativehum/100*p_sat));
	return   humityratio; 
}

//Ũ�ȼ���
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
		
		//�ﵽָ���Ļ�ҺŨ��
		if((solution>=DELTAHumidity)&&(solution<=DELTAHumidity+6.0))
		{
			Flag=1;
		}
		else
			Flag=0;
	}
	
	return Flag;
}

//��Һ����
u8 SS_Re_Transfer(u8 TFlag)
{
	int AlarmFlag=0;
	//u8 ConFlag=0;
	
	if(get_flag==0)                              //Һλ��ȡ��Ϣ�Ƿ�����
		AlarmFlag=RE_Level_Alarm();                //��ȡ������Ϣ
	if(AlarmFlag!=0)
		return AlarmFlag;                          //���ر�����Ϣ
		
	if((get_flag==1)&&(AlarmFlag==0))
	{		
		//����Һλ���޴���
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
	
		//ws tank Һλ���ܹ���
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
		
		//��ʪϵͳ��SS tankҺλ������108���ܻ�Һ
		if(DE_Levelsingal>=108)
		{
			DPortOut(TFVALVE,0);
			delay_us(10);
		}
		
		//��ʪϵͳSS_TankҺλ���ͣ�����ϵͳ������ʲô����¶�Ҫ����ʪ������Һ
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
		
				//����Һλ���ͣ�����Һλ
		if((re_Liq<=24)&&(TFlag==0)&&(ConFlag==0))
		{					
			DPortOut(WSVALVE,1);
			delay_us(10);
		}
		else if((re_Liq>=RSLEVELSTART-2)&&(ConFlag==0))          //����Һλ����28cm
		{
			DPortOut(WSVALVE,0);
			delay_us(10);
		}
		
		//��Һ����������SSҺλ����108������Һλ������Ũ�ȴﵽ
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
		
		//ϵͳֹͣ---Ũ�ȹ��ߣ�Һλ����28cm---���ȹرգ�ѭ���ùر�
		if((AbDelta<43.0)&&(re_Liq<RSLEVELSTART-2)&&(TFlag==0)&&(StatusFlag==1))
		{
			DPortOut(REFAN,0);                             //�ط���  
			digitalOut[REFAN]=0;
			delay_us(1);
			
			DPortOut(CPUMP,0);                             //��ѭ����                      
			digitalOut[CPUMP]=0;
			delay_us(1);
			
			DPortOut(HEATPUMP,0);                          //���ȱ�
			digitalOut[HEATPUMP]=0;  
			delay_s(5);	
			
			DPortOut(WSVALVE,1);                           //��ws����
			delay_us(1);
			
			ConFlag=1;
		}
		else if((re_Liq>=RSLEVELSTART-2)&&(ConFlag==1)&&(StatusFlag==0))   //ϵͳ���¿���---���ȿ���
		{
			DPortOut(WSVALVE,0);                          //�ر�WS����
			delay_us(10);

//			while(temp_out>40.0)                //�ж����ڿ����¶��Ƿ����40
//			{
//				temp_out=analogIn[TOUT];
//				delay_ms(100);		
//			}
			
			AlarmFlag=RE_Level_Alarm(); 
			if(AlarmFlag!=0)
				return AlarmFlag;
			
			DPortOut(CPUMP,1);                            //��ѭ����                        
			digitalOut[CPUMP]=1;			
			delay_us(10);
			
			DPortOut(HEATPUMP,1);                         //����ˮ��
			digitalOut[HEATPUMP]=1;                       //��¼����ˮ��
			delay_us(10);
			
			while(hot_temp<50)                            //��ˮ�¶ȴﵽ50
			{
				hot_temp=analogIn[13];
				delay_ms(1);
				AlarmFlag=RE_Level_Alarm(); 
				if(AlarmFlag!=0)
					return AlarmFlag;
				delay_ms(1);
			}
			
			DPortOut(REFAN,1);                           //������
			digitalOut[REFAN]=1;
			delay_us(10);
//			
//			while(temp_out<40.0)                //�ж����ڿ����¶��Ƿ����40
//			{
//				temp_out=analogIn[TOUT];
//				delay_ms(100);		
//			}
			
			ConFlag=0;
		}
		
		//��ҺŨ�ȹ��ߣ�����ҺλҲ����28ʱ������δ���Ũ�ȹ��ߣ�Һλ����
		if((AbDelta<43.0)&&(re_Liq>=RSLEVELSTART-2)&&(StatusFlag==1)&&(TFlag==0))
		{
			DPortOut(REFAN,0);                          //�ط���
			digitalOut[REFAN]=0;
			delay_us(10);
			
			DPortOut(CPUMP,0);                          //��ѭ����  
			digitalOut[CPUMP]=0;			
			delay_us(1);
			
			DPortOut(HEATPUMP,0);                          //���ȱ�
			digitalOut[HEATPUMP]=0;  
			delay_s(5);	
			
			DPortOut(WSVALVE,1);                        //��WS��
			delay_us(1);
			
			ConFlag=2;
		}
		else if((ConFlag==2)&&(StatusFlag==0))
		{
			while(re_Liq<RSLEVELSTART+1)                //�ﵽָ��Һλ�͹ر�WS����
			{
				re_Liq=analogIn[RSLEVEL];                 //��������
				
				AlarmFlag=RE_Level_Alarm(); 
				if(AlarmFlag!=0)
					return AlarmFlag;
				//delay_ms(1);
			}			
			DPortOut(WSVALVE,0);
			delay_us(1);

//			while(temp_out>40.0)                //�ж����ڿ����¶��Ƿ����40
//			{
//				temp_out=analogIn[TOUT];
//				delay_ms(100);		
//			}
			
			if((re_Liq>=30.0)&&(DE_Levelsingal<108))    //��������ϵͳ
			{
//				while(temp_out>30.0)                //�ж����ڿ����¶��Ƿ����40
//				{
//					temp_out=analogIn[TOUT];
//					delay_ms(100);		
//				}
				
				AlarmFlag=RE_Level_Alarm(); 
				if(AlarmFlag!=0)
					return AlarmFlag;
				
				DPortOut(CPUMP,1);                        //��ѭ����
				digitalOut[CPUMP]=1;
				delay_us(1);
				
				DPortOut(HEATPUMP,1);                         //����ˮ��
				digitalOut[HEATPUMP]=1;                       //��¼����ˮ��
				delay_us(10);
				
				while(hot_temp<50)                       //��ˮ�¶ȴﵽ50��
				{
					hot_temp=analogIn[13];
					delay_ms(1);
					
					AlarmFlag=RE_Level_Alarm(); 
					if(AlarmFlag!=0)
					return AlarmFlag;
					//delay_ms(1);					
				}
			
				DPortOut(REFAN,1);                       //������
				digitalOut[REFAN]=1;
				delay_us(10);

//				while(temp_out<40.0)                //�ж����ڿ����¶��Ƿ����40
//				{
//					temp_out=analogIn[TOUT];
//					delay_ms(100);		
//				}
				
				ConFlag=0;
			}			
		}
	}
	
	else                                            //ϵͳ����ʱ���ر��ȱã����Ⱥ�ѭ����
	{
		DPortOut(RE_ALARM,1);                         //��������ź�
				
		DPortOut(HEATPUMP,0);                         //�ر��ȱ�
		delay_s(1);
		DPortOut(REFAN,0);                            //�ط���  
		delay_s(1);	   
		DPortOut(CPUMP,0);	                          //��ѭ����
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
	if(count==Number)                       //�Ƚ��ȳ�������ƽ��ֵ
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
