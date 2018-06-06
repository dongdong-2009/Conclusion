#include "logic.h"

float de_Liq=0,ss_Liq=0,chil_temp=0,get_flag=0,CW_FB=0;

u8 deh_algorithm(float analogIn[], float arout[])
{
   return 0;
}

u8 deh_level_alarm(void)
{  
    if(de_Liq>=DSLEVELMAXALARM)
    {
        return 0x01;
    }
    if(de_Liq<=DSLEVELMINALARM)
    {
        return 0x02;
    }
    if(ss_Liq>=SSLEVELMAXALARM)
    {
        return 0x03;
    }
	else return 0;
}


u8 deh_transfer(void)
{
	if(de_Liq>=DSLEVELMAXALARM)
    {
        return 0x01;
    }
	if(WS_Level>=WSLEVELMAXALARM)
	{
	    return 0x04; 
	}
//	if((de_Liq>=DSLEVELSTART)&&(WS_Level<=WSLEVELMAX))

//	else if(de_Liq<DSLEVELSTART) tf_flag=0;
    if(de_Liq<=DSLEVELMINALARM)
    {
        return 0x02;
    }
//	if(de_Liq<=DSLEVELSTART)
    if(ss_Liq>=SSLEVELMAXALARM)
    {
        return 0x03;
    }
	if((de_Liq>=DSLEVELSTART)&&(WS_Level<=WSLEVELMAX))
	{
		DPortOut(STVALVE,0);
		DPortOut(TRPUMP,1);
		tf_flag=1;
	}
	else if(de_Liq<DSLEVELSTOP)
	{
		DPortOut(STVALVE,1);
		DPortOut(TRPUMP,0);
		tf_flag=0;
	}
	return 0;
}


u8 dehStart(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8], u8 regflag)
{
    u8 dehlevelA=0;

	while(get_flag==0);

    if(de_Liq>=DSLEVELMAXALARM)
    {
        return 0x01;
    }
    if(de_Liq<=DSLEVELMINALARM)
    {
        return 0x02;
    }
    if(ss_Liq>=SSLEVELMAXALARM)
    {
        return 0x03;
    }

    APortOut(CWVALVE,CHILLEDVALVEO,arout[CWVALVE]);
	delay_s(5); 
    while(CW_FB<=95)
	{ 
		dehlevelA=deh_level_alarm();
		if(dehlevelA!=0) return dehlevelA;
		delay_ms(10);
	}
	while(de_Liq<=30)
	{
		DPortOut(STVALVE,1);
		delay_ms(10);	
	}
	DPortOut(STVALVE,0);
	DPortOut(VSD_PUMP,1);
	APortOut(CPUMP,CPUMPO,arout[CPUMP]);
	delay_s(1);

//	while((chil_temp<=3)||(chil_temp>=20))
	while((chil_temp<=3)||(chil_temp>=50))
	{
		dehlevelA=deh_level_alarm();
		delay_ms(10);
		if((dehlevelA==1)||(dehlevelA==2)||(dehlevelA==3)) 
		return dehlevelA;	    
	 }
	DPortOut(VSD_FAN,1);
	APortOut(SFAN,SFANO,arout[SFAN]);

    return 0;
}

u8 dehStop(float arin[12],float arout[8],u8 dout[8])
{
    DPortOut(VSD_FAN,0);  
    delay_s(5);
	DPortOut(VSD_PUMP,0);
		delay_s(5);
		APortOut(CWVALVE,100,arout[CWVALVE]);
	  delay_s(5);
    return 0;        
}

void deClever(float aout[12],u8 dout[8])
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

void deDefault(void)
{
 	u8 i;
	for(i=0;i<12;i++)
	{
	 	APortOut(i,0,100);
	}
}

void getlevel(float delevel,float sslevel,float chiltemp,float cwfb)
{
	de_Liq=delevel;
	ss_Liq=sslevel;
	chil_temp=chiltemp;
	get_flag=1;
	CW_FB=cwfb;
}
