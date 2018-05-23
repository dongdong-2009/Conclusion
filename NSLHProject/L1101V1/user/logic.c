#include "logic.h"

u8 NSLH_Alarm()
{
	u8 Alarm_Flag=0;
	
	return Alarm_Flag;
	
}

//system normal mode
u8 NSLH_Start(float ain[12],float aout[12],u8 din[8],u8 dout[8])
{
	u8 alarm=0; 
	while(ReceiveFlag==0)
	alarm=NSLH_Alarm();
	if(alarm!=0)
		return alarm;
	//上电
	APortOut(ERVFan,1);
	Delay_ms(1);
	
	DPortOut(PTBFan,1);
	Delay_ms(1);
	
	RTContrPassive(off_coilTempSv,off_coilTemp,RoomTempSv,RoomTemp);
	RTContrHybrid(off_coilTempSv,off_coilTemp,RoomTempSv,RoomTemp);

	//wait for 10 min until the system is stable
	TurnOnTim(2);
	while(!TimeFlag);
	
	CO2Control(CO2,CO2Sv);
	
	return 0;
}

//system BMS start 
u8 NSLH_BMSStart(float ain[12],float aout[12],u8 din[8],u8 dout[8])
{
	u8 alarm=0; 
	while(ReceiveFlag==0)
	alarm=NSLH_Alarm();
	if(alarm!=0)
		return alarm;
	
	//通电
	DPortOut(ERVFan,1);
	DPortOut(PTBFan,1);
	
	//运行
	APortOut(ERVSAF,10);
	APortOut(ERVEAF,10);
	ERVFANRUN=1;
	
	if(ERVFANRUN==1)
		{
			TurnOnTim(2);
			while(!TimeFlag);
		}
		
	NSLH_UnOccMode(ain,aout,din,dout);
	
	return 0;
}

//system UnOccupined mode
void NSLH_UnOccMode(float ain[12],float aout[12],u8 din[8],u8 dout[8])
{
	u8 alarm=0; 
	while(ReceiveFlag==0)
	alarm=NSLH_Alarm();
	if(alarm!=0)
		NSLH_Clear(aout,dout);

	//关闭ERV
	APortOut(ERVSAF,0);
	APortOut(ERVEAF,0);
	ERVFANRUN=0;
	
	if(RoomTemp>28.0)
		{
			off_coilTempSv=off_coilTempSv-0.25;
			if(off_coilTempSv>16.0)
				{
					valve=PID_ValveControl(off_coilTempSv,off_coilTemp);
					ValveOpen(valve);
					TurnOnTim(2);
					while(!TimeFlag);
				}
		}
	else
		{
			valve=PID_ValveControl(17.0,off_coilTemp);
			ValveOpen(valve);
		}
}

//system stop
u8 NSLH_Stop(float ain[12],float aout[12],u8 din[8],u8 dout[8])
{
	u8 alarm=0;
	alarm=NSLH_Alarm();
	if(alarm!=0)
		return alarm;
	
	DPortOut(PTBFan,0);
	Delay_ms(1);
	DPortOut(ERVFan,0);
	Delay_ms(1);
	APortOut(CHWV,0);
	return 0;	
}

//System clear turn off the AO and DO
void NSLH_Clear(float aout[8],u8 dout[8])
{
	int j;
	for(j=0;j<8;j++)
	{
		APortOut(j,0);
		aout[j]=0;
		Delay_ms(1);
		
		DPortOut(j,0);
		dout[j]=0;
		Delay_ms(1);		
	}
}

//co2 control
void CO2Control(float co2, float co2Sv)
{
		if(co2>co2Sv)
			{
				APortOut(ERVSAF,10);
				APortOut(ERVEAF,10);
				ERVFANRUN=1;
			}
		else if(co2<(co2Sv-200))
			{
				APortOut(ERVSAF,0);
				APortOut(ERVEAF,0);
				ERVFANRUN=0;
			}			
}

//occupined: Occupined sensor 0---UnOccupined Mode  1---Occupined
//occupined=DPortIn(OccuState)
void Get_value(float offcoilTemp,float chwIN,float chwOut,u8 occupined,u8 BMS)
{
	off_coilTemp=offcoilTemp;
	chwInTemp=chwIN;
	chwOutTemp=chwOut;
	UnOccupined=(!occupined)|(!TSControl);  //Touch Screen OFF OR Occupined Sensor detected NOBODY
	BMSControl=BMS;
	ReceiveFlag=1;                          //Data Receive Flag: 1---Received  0---Not Received
}

float PyhsicalValue(float range, float data,float Pyhsicallow, float Pyhsicalhigh)
{
	float value;
	value=(Pyhsicalhigh-Pyhsicallow)*data/range;
	return value;
}

//Temperature Control Passive Mode  Roomsv=25.0
void RTContrPassive(float Offcoilsv,float Offcoilpv,float Roomsv,float Roompv)
{
	if((PTBFANRUN==0)&&(Roompv<Roomsv+1))
		{
			valve=PID_ValveControl(Offcoilsv,Offcoilpv);
			ValveOpen(valve);
		}
}

//Temperature Control Hybrid Mode
void RTContrHybrid(float Offcoilsv,float Offcoilpv,float Roomsv,float Roompv)
{
	if(Roompv>=26.0)
		{
			APortOut(PTBFanSpeed,10);
			PTBFANRUN=1;
			valve=PID_ValveControl(Offcoilsv,Offcoilpv);
			ValveOpen(valve);			
		}
	else if(25.0<=Roompv&&Roompv<26.0)
		{
			TurnOnTim(2);
			while(!TimeFlag);
			APortOut(PTBFanSpeed,10);  //风扇速度可调
			PTBFANRUN=1;
			valve=PID_ValveControl(Offcoilsv,Offcoilpv);
			ValveOpen(valve);			
		}
	else if((23.0<=Roompv)&&(Roompv<25.0)&&PTBFANRUN)
		{	
			FanSpeed=PID_FanControl(Roomsv,Roompv);
			APortOut(PTBFanSpeed,FanSpeed);
			//PTBFANRUN=0;
		}
	else if(Roompv<23.0)
		{
			APortOut(PTBFanSpeed,0);
			PTBFANRUN=0;
			RTContrPassive(Offcoilsv,Offcoilpv,Roomsv,Roompv);
		}
}


////Roomsv=25
//void TempContol(float Offcoilsv,float Offcoilpv,float Roomsv,float Roompv)
//{
//	if(((TempPassive==1)&&(Roompv<Roomsv)))
//		{
//			TempPassive=0;
//			DPortOut(PTBFan,0);
//			DO_data[PTBFan]=0;
//			valve=PID_Control(Offcoilsv,Offcoilpv);
//			ValveOpen(valve);
//		}
//	else if((TempPassive==0)&&(Roompv<Roomsv-2))
//		{
//			TempPassive=1;
//			DPortOut(PTBFan,0);
//			DO_data[PTBFan]=0;
//			valve=PID_Control(Offcoilsv,Offcoilpv);
//			ValveOpen(valve);
//		}
//	else if(23.0<Roompv&&Roompv<25.0)
//		{
//			DPortOut(PTBFan,1);
//			DO_data[PTBFan]=1;
//			Delay_ms(1);
//			FanSpeed=PID_Control(Roomsv,Roompv);
//			APortOut(PTBFanSpeed,FanSpeed);		
//		}
//	else
//		{
//			DPortOut(PTBFan,1);
//			DO_data[PTBFan]=1;
//			APortOut(PTBFanSpeed,10);
//			Delay_ms(1);
//		}
//}

void ValveOpen(float value)
{
	APortOut(CHWV,value);
}

