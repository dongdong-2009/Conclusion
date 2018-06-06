#include "logic.h"

float re_Liq=0,ws_Liq=0,hot_temp=0,get_flag=0, HWValveFB=0;
float Hot_valveS=0;

u8 reg_levelset(void)
{
	return 0;
}

u8 reg_algorithm(float analogIn[], float arout[])
{
	return 0;
}
u8 reg_level_alarm(void)
{	  
    if(re_Liq>=RSLEVELMAXALARM)
    {
        return 0x01;
    }
    if(re_Liq<=RSLEVELMINALARM)
    {
        return 0x02;
    }
    if(ws_Liq>=WSLEVELMAXALARM)
    {
        return 0x03;
    }
	return 0;
}

u8 reg_transfer(u8 vflag)
{
	if(re_Liq>=RSLEVELMAXALARM)
    {
        return 0x01;
    }
	if(SS_Level>=SSLEVELMAXALARM)
	{
	    return 0x04; 
	}
    if(re_Liq<=RSLEVELMINALARM)
    {
        return 0x02;
    }
    if(ws_Liq>=WSLEVELMAXALARM)
    {
        return 0x03;
    }
	if((vflag==1)&&(re_Liq>RSLEVELSTOP))	//等算法
	{
		DPortOut(TFVALVE,1);
		digitalOut[TFVALVE]=1;
	}
	else if((vflag==0)||(re_Liq<=RSLEVELSTOP))
	{
		DPortOut(TFVALVE,0);
		digitalOut[TFVALVE]=0;
	}
	if((vflag==0)&&(re_Liq<=RSLEVELSTOP))
	{
		DPortOut(WSVALVE,1);
		digitalOut[WSVALVE]=1;
	}
	else if((vflag==0)&&(re_Liq>19))
	{
		DPortOut(WSVALVE,0);
		digitalOut[WSVALVE]=0;
	}
//	if((re_Liq>=RSLEVELSTART)&&(SS_Level<=SSLEVELMAX))	//等算法
//	{
//		DPortOut(WSVALVE,0);
//		DPortOut(TFVALVE,1);
//	}
//	if(re_Liq<=RSLEVELSTOP)
//	{
//		DPortOut(TFVALVE,0);
//		DPortOut(WSVALVE,1);
//	}
	APortOut(HWVALVE,Hot_valveS,10);
	analogOut[0]=Hot_valveS;
	return 0;
}


u8 regStart(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8], u8 regflag)
{
    int reglevelA=0;
	Hot_valveS=100;
	while(get_flag==0)
	reglevelA=reg_level_alarm();
	if(reglevelA!=0) return reglevelA;
    APortOut(HWVALVE,Hot_valveS,10);
	analogOut[0]=Hot_valveS;
	while(HWValveFB<=95)
	{ 
		reglevelA=reg_level_alarm();
		if(reglevelA!=0) return reglevelA;
		delay_ms(10);
	}
	while(re_Liq<=17)
	{
		DPortOut(WSVALVE,1);
		delay_ms(10);	
	}
	DPortOut(WSVALVE,0);
	delay_s(1);
	DPortOut(CPUMP,1);
	digitalOut[CPUMP]=1;
	delay_s(1);
	DPortOut(HEATPUMP,1);
	digitalOut[HEATPUMP]=1;
	while(hot_temp<50)
//	while(hot_temp<35)
	{
		if(hot_temp>120)hot_temp=0;
		reglevelA=reg_level_alarm();
		if(reglevelA!=0) return reglevelA;
		delay_ms(100);                   
	}
	DPortOut(REFAN,1);
	digitalOut[REFAN]=1;
    return 0;
}

u8 regStop(float arin[12],float arout[8],u8 dout[8])
{
    DPortOut(HEATPUMP,0);    
    delay_s(5);	
	DPortOut(REFAN,0);    
    delay_s(5);	   
	DPortOut(CPUMP,0);
	delay_s(5);
	APortOut(HWVALVE,0,arout[HWVALVE]);
    return 0;        
}

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

void reDefault(void)
{
 	u8 i;
	for(i=0;i<12;i++)
	{
	 	APortOut(i,0,100);
	}
}

void getlevel(float relevel,float wslevel,float hottemp,float hwvfb)
{
	re_Liq=relevel;
	ws_Liq=wslevel;
	hot_temp=hottemp;
	HWValveFB=hwvfb;
	get_flag=1;
}
