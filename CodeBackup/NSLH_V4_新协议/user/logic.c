#include "logic.h"

u8 NSLH_Alarm()
{
	u8 Alarm_Flag=0;
	
	return Alarm_Flag;
	
}

u8 NSLH_Start(float ain[12],float aout[12],u8 din[8],u8 dout[8])
{
	u8 alarm=0; 
	while(ReceiveFlag==0)
	alarm=NSLH_Alarm();
	if(alarm!=0)
		return alarm;
	
	if(RoomTemp>RoomTempSv)
		{
			RTContrHybird(off_coilTempSv,off_coilTemp,RoomTempSv,RoomTemp);
		}
	else
		{
			RTContrPassive(off_coilTempSv,off_coilTemp,RoomTempSv,RoomTemp);
		}
	
	//wait for 10 min until the system is stable
	TurnOnTim(2);
	while(TimeFlag);
	
	CO2Control(CO2,CO2Sv);
	
	return 0;
}

u8 NSLH_BMSStart(float ain[12],float aout[12],u8 din[8],u8 dout[8])
{
	u8 alarm=0; 
	while(ReceiveFlag==0)
	alarm=NSLH_Alarm();
	if(alarm!=0)
		return alarm;
		
	DPortOut(ERVFan,1);
	dout[ERVFan]=1;
	
	if(dout[ERVFan]==1)
		TurnOnTim(2);
	while(TimeFlag);
	
	NSLH_OccMode(ain,aout,din,dout);
	
	return 0;
}

void NSLH_OccMode(float ain[12],float aout[12],u8 din[8],u8 dout[8])
{
	u8 alarm=0; 
	while(ReceiveFlag==0)
	alarm=NSLH_Alarm();
	if(alarm!=0)
		NSLH_Clear(aout,dout);

	DPortOut(ERVFan,0);
	dout[ERVFan]=0;
	
	if(RoomTemp>28.0)
		{
			off_coilTempSv=off_coilTempSv-0.25;
			if(off_coilTempSv>16.0)
				{
					valve=PID_Control(off_coilTempSv,off_coilTemp);
					ValveOpen(valve);
					TurnOnTim(2);
					while(TimeFlag);
				}
		}
	else
		{
			valve=PID_Control(17.0,off_coilTemp);
			ValveOpen(valve);
		}
}

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
	return 0;	
}

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

void CO2Control(float co2, float co2Sv)
{
		if(co2>co2Sv)
			{
				DPortOut(ERVFan,1);
				DO_data[ERVFan]=1;
			}
		else if(co2<(co2Sv-200))
			{
				DPortOut(ERVFan,0);
				DO_data[ERVFan]=0;
			}			
}

void Get_value(float offcoilTemp,float chwIN,float chwOut,u8 occupined)
{
	off_coilTemp=offcoilTemp;
	chwInTemp=chwIN;
	chwOutTemp=chwOut;
	UnOccupined=occupined|(!TSControl);
	ReceiveFlag=1;
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
	if(TempPassive==1)
		{	
			TurnOnTim(2);
			while(TimeFlag);
			if(Roompv<Roomsv)
				{
					valve=PID_Control(Offcoilsv,Offcoilpv);
					ValveOpen(valve);
					DPortOut(PTBFan,0);
					DO_data[PTBFan]=0;
				}
		}
	else if((TempPassive==0)&&(Roompv<Roomsv-2))
		{
			valve=PID_Control(Offcoilsv,Offcoilpv);
			ValveOpen(valve);
			DPortOut(PTBFan,0);
			DO_data[PTBFan]=0;
		}
}

void RTContrHybird(float Offcoilsv,float Offcoilpv,float Roomsv,float Roompv)
{
	if(TempPassive==0)
		{
			if(23.0<=Roompv&&Roompv<25.0)
				{
					DPortOut(PTBFan,1);
					DO_data[PTBFan]=1;
					Delay_ms(1);
					FanSpeed=PID_Control(Roomsv,Roompv);
					APortOut(PTBFanSpeed,FanSpeed);		
				}
			else if(Roompv>=25.0)
				{
					DPortOut(PTBFan,1);
					DO_data[PTBFan]=1;
					APortOut(PTBFanSpeed,10);
					Delay_ms(1);
				}
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
