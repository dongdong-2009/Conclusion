/*******************************************************************************
  * @brief  program.
  * @param  None
  * @retval None
  initial set point is fix for a customer adviced value
  ******************************************************************************/
#include "stm32f10x.h"
#include "math.h"
#include "LddsSp.h"
#include "runtimedata.h"
#include "timer.h"	
#include "systick_timer.h"	
#include "extvart.h"
float re_Liq=0,ws_Liq=0,hot_temp=0,get_flag=0, HWValveFB=0,temp_out=0.0,rh_out=0.0;
float Hot_valveS=0;
float temp_Liq=0;
char regStart(PARAMS *arin,PARAMS *arout,char *dout);           //����ϵͳ����
char regStop(PARAMS *arin,PARAMS *arout,char *dout);                                    //����ϵͳ�ر�
float ValueBuf[Number];
float valuebuf[Number+1];
//����ϵͳҺλ������Ϣ

char RE_Level_Alarm(void)
{
	u8 Alarm_Flag=0;
	
	if(re_Liq>=RsLevelMaxAlarm)
		Alarm_Flag = 0x01;
	if(re_Liq<=RsLevelMinAlarm)
		Alarm_Flag = 0x02;
	if(ws_Liq>=WkSLevelAlarm)
		Alarm_Flag = 0x03;
	if(DE_Levelsingal>=SSLevelAlarm)
		Alarm_Flag = 0x04;
	
	return Alarm_Flag;
}

//��������
char regStart(PARAMS *arin,PARAMS *arout,char *dout)
{
   int reglevelA=0;
	Hot_valveS=100;
	
	while(get_flag==0)
	reglevelA=RE_Level_Alarm();          //��ȡ������Ϣ	
	if(reglevelA!=0)                     //���ع�����Ϣ
		return reglevelA;
	
    setAOonechanelPhyVal(HWVALVE,Hot_valveS,10);     //����ˮ��
	ADC_value[0]=Hot_valveS;             //��¼��ˮ�����ֵ
	
	while(HWValveFB<=95)                 //�ж���ˮ���Ƿ�򿪣���ˮ��ȫ��
	{ 
		reglevelA=RE_Level_Alarm();
		if(reglevelA!=0) 
			return reglevelA;
		Delay_ms(10);
	}
	
	//����Һλ��С��17����
	while(re_Liq<=17)                     //���Һλ��С��17����ʱ����ws��
	{
		DO_onechannel(WSVALVE,1);
		Delay_ms(10);	
	}	
	DO_onechannel(WSVALVE,0);                 //�ر�ws��
	Delay_s(1);
	
	DO_onechannel(CPUMP,1);                   //��ѭ����
	//digitalOut[CPUMP]=1;                 //��¼��ѭ����
	Delay_s(1);
	
	DO_onechannel(HEATPUMP,1);                //����ˮ��
//	digitalOut[HEATPUMP]=1;              //��¼����ˮ��
	
	while(hot_temp<50)                   //�ȴ���Һ�����ȵ�50��
	{
		if(hot_temp>120)                   //��ֹ�¶������ͻ��
			hot_temp=0;
		
		reglevelA=RE_Level_Alarm();
		if(reglevelA!=0) 
			return reglevelA;
		Delay_ms(100);                   
	}
	
	DO_onechannel(REFAN,1);                  //������
//	digitalOut[REFAN]=1;                //��¼����
	
	while(temp_out<40.0)                //�ж����ڿ����¶��Ƿ����40
	{
		reglevelA=RE_Level_Alarm();
		if(reglevelA!=0) 
			return reglevelA;
		Delay_ms(100);		
	}
	
	return 0;
}

//����ֹͣ
char regStop(PARAMS *arin,PARAMS *arout,char *dout)
{
    DO_onechannel(HEATPUMP,0);                          //���ȱ�
    //digitalOut[HEATPUMP]=0;  
    Delay_s(5);	
	
	DO_onechannel(REFAN,0);                             //�ط���
	//digitalOut[REFAN]=0;	
    Delay_s(5);
	
	DO_onechannel(CPUMP,0);	                           //��ѭ����
	//digitalOut[CPUMP]=0;
	Delay_s(5);
	
	setAOonechanelPhyVal(HWVALVE,0,arout[HWVALVE].a);	           //����ˮ��
    return 0;        
}

//��������
void reClever()
{
	u8 i;
	for(i=0;i<12;i++)
	{
	//	aout[i]=0;
		setAOonechanelPhyVal(i,0,1);
	}
	for(i=0;i<8;i++)
	{
	//	dout[i]=0;
		DO_onechannel(i,0);
	}
}

//����Ĭ������
void reDefault(void)
{
 	u8 i;
	for(i=0;i<12;i++)
	{
	 	setAOonechanelPhyVal(i,0,100);
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
                                                 	
	SolutionTemp = RTD_value[TSIN];
	outlethumidity = RH2HR(ADC_value[TOUT], ADC_value[RHOUT]);
  inlethumidity  = RH2HR(ADC_value[TIN], ADC_value[RHIN]);
	deltaHumidity = outlethumidity - inlethumidity;
	
	liqidconcentration = 4.0603-0.1846*deltaHumidity +0.6926*SolutionTemp+0.0108*deltaHumidity*deltaHumidity-0.0062*deltaHumidity*SolutionTemp-0.0027*SolutionTemp*SolutionTemp;
	//concentration = -0.0147-0.3402*deltaHumidity +0.8689*SolutionTemp+0.0121*deltaHumidity*deltaHumidity-0.0045*deltaHumidity*SolutionTemp-0.0043*SolutionTemp*SolutionTemp;

	return liqidconcentration;
}

char JudgeFlag(void)
{
	u8 Flag=0;
	float solution=0.0;
	float OutHum=0.0;
	float InHum=0.0;
	float DeltaHum=0.0;
	
	OutHum=RH2HR(ADC_value[TOUT], ADC_value[RHOUT]);
	InHum=RH2HR(ADC_value[TIN], ADC_value[RHIN]);
	
	if(StatusFlag==1)
	{
		DeltaHum=OutHum-InHum;
		solution=DeltaHum;
		//solution=recursive_average_filter(DeltaHum);
//		solution= AverageFilter(DeltaHum);
		
		//�ﵽָ���Ļ�ҺŨ��
	//if((solution>=DELTAHumidity)&&(solution<=DELTAHumidity+6.0))
	if((solution>=DeltaCon)&&(solution<=DeltaCon+6.0))
		{
			Flag=1;
		}
		else
			Flag=0;
	}
	
	return Flag;
}

//��Һ����
char SS_Re_Transfer(char TFlag)
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
		if(re_Liq>=RsLevelStart+3)
		{
			DO_onechannel(TFVALVE,1);
			Delay_us(10);			
			
			while(re_Liq>RsLevelStart+1)
			{
				re_Liq=ADC_value[RSLEVEL];
			}
			DO_onechannel(TFVALVE,0);
			Delay_us(10);	
		}
	
		//ws tank Һλ���ܹ���
		if(ws_Liq>(WkSLevelHigh-25)&&(re_Liq<RsLevelStart-2))
		{
			DO_onechannel(WSVALVE,1);
			Delay_us(10);
		}
		else if((ws_Liq<10||re_Liq>=RsLevelStart-2)&&(ConFlag==0))
		{
			DO_onechannel(WSVALVE,0);
			Delay_us(10);
		}
		
		//����Һλ���ͣ�����Һλ
		if(re_Liq<=RsLevelStop)
		{					
			DO_onechannel(WSVALVE,1);
			Delay_us(10);
		}
		else if((re_Liq>=RsLevelStart-2)&&(ConFlag==0))          //����Һλ����28cm
		{
			DO_onechannel(WSVALVE,0);
			Delay_us(10);
		}
		
		//��ʪϵͳ��SS tankҺλ������108���ܻ�Һ
		if(DE_Levelsingal>=108)
		{
			DO_onechannel(TFVALVE,0);
			Delay_us(10);
		}
		
		//��Һ����������SSҺλ����108������Һλ������Ũ�ȴﵽ
		if((DE_Levelsingal<108)&&(TFlag==1)&&(re_Liq>RsLevelStop))
		{
			DO_onechannel(TFVALVE,1);
			Delay_us(10);
		}
		else
		{
			DO_onechannel(TFVALVE,0);
			Delay_us(10);
		}
		
		//ϵͳֹͣ---Ũ�ȹ��ߣ�Һλ����28cm---���ȹرգ�ѭ���ùر�
		if((AbDelta<43.0)&&(re_Liq<RsLevelStart-2)&&(TFlag==0)&&(StatusFlag==1))
		{
			DO_onechannel(REFAN,0);                             //�ط���  
			//digitalOut[REFAN]=0;
			Delay_us(1);
			
			DO_onechannel(CPUMP,0);                             //��ѭ����                      
		//	digitalOut[CPUMP]=0;
			Delay_us(1);
			
			DO_onechannel(HEATPUMP,0);                          //���ȱ�
			//digitalOut[HEATPUMP]=0;  
			Delay_s(5);	
			
			DO_onechannel(WSVALVE,1);                           //��ws����
			Delay_us(1);
			
			ConFlag=1;
		}
		else if((re_Liq>=RsLevelStart-2)&&(StatusFlag==0)&&(ConFlag==1))   //ϵͳ���¿���---���ȿ���
		{
			DO_onechannel(WSVALVE,0);                          //�ر�WS����
			Delay_us(10);

			while(temp_out>30.0)                //�ж����ڿ����¶��Ƿ����40
			{
				temp_out=ADC_value[TOUT];
				Delay_ms(100);		
			}
			
//			while(InletSolutemp>50)
//			{
//				InletSolutemp=analogIn[TSIN];
//				delay_ms(1);
//			}
			
			DO_onechannel(CPUMP,1);                            //��ѭ����                        
//			digitalOut[CPUMP]=1;			
			Delay_us(10);
			
			DO_onechannel(HEATPUMP,1);                         //����ˮ��
//			digitalOut[HEATPUMP]=1;                       //��¼����ˮ��
			Delay_us(10);
			
			while(hot_temp<50)                            //��ˮ�¶ȴﵽ50
			{
				hot_temp=RTD_value[TSOUT];
				Delay_ms(1);			
			}
			
			DO_onechannel(REFAN,1);                           //������
//			digitalOut[REFAN]=1;
			Delay_us(10);
			
			while(temp_out<40.0)                //�ж����ڿ����¶��Ƿ����40
			{
				temp_out=ADC_value[TOUT];
				Delay_ms(100);		
			}
			
			ConFlag=0;
		}
		
		//��ҺŨ�ȹ��ߣ�����ҺλҲ����28ʱ������δ���Ũ�ȹ��ߣ�Һλ����
		if((AbDelta<43.0)&&(re_Liq>=RsLevelStart-2)&&(StatusFlag==1)&&(TFlag==0))
		{
			DO_onechannel(REFAN,0);                          //�ط���
			//digitalOut[REFAN]=0;
			Delay_us(10);
			
			DO_onechannel(CPUMP,0);                          //��ѭ����  
			//digitalOut[CPUMP]=0;			
			Delay_us(1);
			
			DO_onechannel(HEATPUMP,0);                          //���ȱ�
		//	digitalOut[HEATPUMP]=0;  
			Delay_s(5);	
			
			DO_onechannel(WSVALVE,1);                        //��WS��
			Delay_us(1);
			
			ConFlag=2;
		}
		else if((StatusFlag==0)&&(ConFlag==2))
		{
			while(re_Liq<RsLevelStart+1)                //�ﵽָ��Һλ�͹ر�WS����
			{
				re_Liq=ADC_value[RSLEVEL];                 //��������
			}			
			DO_onechannel(WSVALVE,0);
			Delay_us(1);
			
			if((re_Liq>=30.0)&&(DE_Levelsingal<108))    //��������ϵͳ
			{
				while(temp_out>30.0)                //�ж����ڿ����¶��Ƿ����40
				{
					temp_out=ADC_value[TOUT];
					Delay_ms(100);		
				}

//				while(InletSolutemp>50)
//				{
//					InletSolutemp=analogIn[TSIN];
//					delay_ms(1);
//				}
				
				DO_onechannel(CPUMP,1);                        //��ѭ����
			//	digitalOut[CPUMP]=1;
				Delay_us(1);
				
				DO_onechannel(HEATPUMP,1);                         //����ˮ��
			//digitalOut[HEATPUMP]=1;                       //��¼����ˮ��
				Delay_us(10);
				
				while(hot_temp<50)                       //��ˮ�¶ȴﵽ50��
				{
					hot_temp=RTD_value[TSOUT];
					Delay_ms(1);			
				}
			
				DO_onechannel(REFAN,1);                       //������
			//	digitalOut[REFAN]=1;
				Delay_us(10);

				while(temp_out<40.0)                //�ж����ڿ����¶��Ƿ����40
				{
					temp_out=ADC_value[TOUT];
					Delay_ms(100);		
				}
				
				ConFlag=0;
			}			
		}
	}
	
	else                                            //ϵͳ����ʱ���ر��ȱã����Ⱥ�ѭ����
	{
		DO_onechannel(RE_ALARM,1);                         //��������ź�
				
		DO_onechannel(HEATPUMP,0);                         //�ر��ȱ�
		Delay_s(1);
		DO_onechannel(REFAN,0);                            //�ط���  
		Delay_s(1);	   
		DO_onechannel(CPUMP,0);	                          //��ѭ����
	}
	
	setAOonechanelPhyVal(HWVALVE,Hot_valveS,10);
	//analogOut[0]=Hot_valveS;
	
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
