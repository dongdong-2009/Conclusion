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

char dehStart(PARAMS *arin,PARAMS *arout);
char dehStop(PARAMS *arin,PARAMS *arout,char *dout);
char deh_algorithm(void);

int cnt=0, cntE=0;
int waterincharge=0; 
char timer4open;

char deh_algorithm()
{

 	 short int  dehlevelA=0;
	 float  outlethumidity,vavopen,t;
	 dehlevelA=deh_transfer();
	 
	 if(dehlevelA!=0) 
	 return dehlevelA;


   if(timer4open ==0)
	 {  
	    TurnOnTim(4);	
		timer4open =1;
		}

 	if(algorithmstart==1)
	  {
     
	 	outlethumidity =  RH2HR(ADC_value[TOUT], ADC_value[RHOUT]);
		if((outlethumidity-Setpoint[SPHUM])>2.0)

	    	{	cnt=0;
				waterincharge  =0;
				cntE++;
			    setAOonechanelPhyVal(CWVALVE,CHILLEDVALVEO,AOParams[CWVALVE].a);
				if(cntE==10.0)
				{ t = opencnts( outlethumidity-Setpoint[SPHUM])	;
			   	  dehlevelA = valveopen(t); 
				   cntE =0;
				  if(dehlevelA!=0)
				   
                 	 return dehlevelA;
				}
		    
		
		    }
		else if(((outlethumidity-Setpoint[SPHUM])<2.0)&&((outlethumidity-Setpoint[SPHUM])>0.02))
		
         { 
		   if  (ADC_value[CWVALVEFB]<=95.0) 
			 { 
			   vavopen=SolInletPID(Setpoint[SPHUM]);
			   setAOonechanelPhyVal(CWVALVE,vavopen,AOParams[CWVALVE].a);
			   
			    }

		  else
		    {
		    	cnt++;
		    	waterincharge++;
		    	if(cnt==40)
			    templocker =0 ;
	     	   
			    if(	waterincharge ==12)
		        {	
		          if (ADC_value[CPUMPFB]<=40.0)
			         
					 setAOonechanelPhyVal(CPUMP,50.0,AOParams[CPUMP].a);

				  else if((( RTD_value[TSIN] - templocker)<=0.05)||(templocker==0)) 
	     	        {	  
			           templocker = RTD_value[TSIN];
				       t = opencnts( outlethumidity-Setpoint[SPHUM])	;
                       dehlevelA=valveopen(t); 
					    cnt=0;
					   if(dehlevelA!=0) 
	                     return dehlevelA;

					  
					   
	    	         }
				      waterincharge  =0;
					  
			
		          }
			}
			}
//		 else if(((outlethumidity-Setpoint[SPHUM])<0.0)&&((Setpoint[SPHUM]-outlethumidity)<0.7))
		 else if((Setpoint[SPHUM]-outlethumidity)>0.05)

		 {  
			cnt=0;
			waterincharge  =0;

			   vavopen=SolInletPID( Setpoint[SPHUM]);
			   setAOonechanelPhyVal(CWVALVE,vavopen,AOParams[CWVALVE].a);  
			   if(ADC_value[CPUMPFB]>=32.0)
			   setAOonechanelPhyVal(CPUMP,ADC_value[CPUMPFB]-2.0,AOParams[CPUMP].a); 
		}
		else if(((outlethumidity-Setpoint[SPHUM])>2.5)&&(ADC_value[CWVALVEFB]>=95.0))
		 {
		 	  dehlevelA= 0x04;
		  }

				 algorithmstart   =0;
			
		 }	 	

 
     if(dehlevelA!=0) 
	 return dehlevelA;     
	 else
 	 return 0;
 
}

short int deh_level_alarm(void) //液位报警
{  
    if(ADC_value[DSLEVEL]>=DeSLevelHigh)//检查液位
    {
        return 0x01;
    }
    if(ADC_value[DSLEVEL]<=DeSLevelLow)
    {
        return 0x02;
    }
    if(ADC_value[SSLEVEL]>=StrSLevelHigh)
    {
        return 0x01;
    }
	if(ADC_value[SSLEVEL]<=StrSLevelLow)
    {
        return 0x02;
    }

	else return 0;
}


short int deh_transfer(void)//换液 等算法
{
   int dehlevelA=0; 

	if(ADC_value[DSLEVEL]>=DeSLevelHigh)
    {
        return 0x01;
    }
//	if(WS_Level>=WSLEVELMAXALARM)
//	{
//	    return 0x01; 
//	}
   if(ADC_value[DSLEVEL]<=DeSLevelLow)
    {
        return 0x02;
    }
    if(ADC_value[SSLEVEL]>=StrSLevelHigh)
    {
        return 0x01;
    }
	if(ADC_value[SSLEVEL]<=StrSLevelLow)
    {
        return 0x02;
    }
	if(ADC_value[DSLEVEL]>=DeSLevelTrasf)	
	{
   	  dehlevelA= highlevel_alarm()		   ;
	  if(dehlevelA!=0) 
	  return dehlevelA;	                                        
	}
   if(ADC_value[DSLEVEL]<DSLEVELSTOP)						                
	{
      dehlevelA= lowlevel_sv_alarm()	 ;
     if(dehlevelA!=0) 
	 return dehlevelA;
	                                                
	}
	
	 return 0;
}

char dehStart(PARAMS *arin,PARAMS *arout)

{
    short int dehlevelA=0;
    float reqtem = 18.0;
	//while(get_flag==0);

    if(ADC_value[DSLEVEL]>=DeSLevelHigh)//检查液位
    {
        return 0x01;
    }
    if(ADC_value[DSLEVEL]<=DeSLevelLow)
    {
        return 0x02;
    }
    if(ADC_value[SSLEVEL]>=StrSLevelHigh)
    {
        return 0x01;
    }
	if(ADC_value[SSLEVEL]<=StrSLevelLow)
    {
        return 0x02;
    }
	setAOonechanelPhyVal(CWVALVE,CHILLEDVALVEO,arout[CWVALVE].a);
	Delay_s(5); 
    
	while(ADC_value[CWVALVEFB]<=95)//等待冷水阀全开
	{ 
		dehlevelA=deh_level_alarm();
		if(dehlevelA!=0) return dehlevelA;
		Delay_ms(10);
	}
	while(ADC_value[DSLEVEL]<=16.0)//检查液位是否小于22厘米
	{
    	 DO_onechannel(STVALVE,1);
		Delay_ms(10);	
	}

	 DO_onechannel(STVALVE,0);
	 DO_onechannel(VSD_PUMP,1);

	setAOonechanelPhyVal(CPUMP,CPUMPO,arout[CPUMP].a);

	Delay_s(1);

//	while((chil_temp<=3)||(chil_temp>=20))
	 reqtem= 1.25* Setpoint[SPHUM]+7.875;
	 if(reqtem< 16.0)
	 reqtem = 16.0;
	 else if (reqtem> 19.0)
	 reqtem = 19.0;

	while(RTD_value[TSIN]>=reqtem) //等待溶液冷却 需要修改->等待溶液温度小于16度
	{
	    dehlevelA=deh_level_alarm();

		if(dehlevelA!=0) 
		return dehlevelA;
	    
	 }

	DO_onechannel(VSD_FAN,1);
   	setAOonechanelPhyVal(SFAN,SFANO,arout[CPUMP].a);


   	while(ADC_value[TOUT]-RTD_value[TSIN]>=7) //等待溶液冷却 需要修改->等待溶液温度小于16度
	{

		dehlevelA=deh_level_alarm();
		if(dehlevelA!=0) 
		   return dehlevelA;
		    

	 }	

	 dehlevelA=deh_transfer();
     if(dehlevelA!=0) 
	 	return dehlevelA;

    return 0;
}


char dehStop(PARAMS *arin,PARAMS *arout,char *dout)
{
 
	 DO_onechannel(VSD_FAN,0);
     Delay_s(5);
 	 DO_onechannel(VSD_FAN,0);
	 Delay_s(5);
	 setAOonechanelPhyVal(CWVALVE,100,arout[CWVALVE].a);
	 Delay_s(5);
     return 0;        
}

void deClever()
{
	 short int i,j,k;
	 for(i=0;i<2;i++)
	 {
	  	
		setAOonechanelPhyVal(i,0,1);


	 }
	

	 setAOonechanelPhyVal(SSLEVELSD,StrSLevelHigh/10.0*0.8,10);

     for(j=4;j<8;j++)
	 {
	  	
		setAOonechanelPhyVal(i,0,1);
	 }

	 for(k=0;k<8;k++)
	 {

		DO_onechannel(i,0);
	 }
}

void deDefault(void)
{
 	short int i;
	for(i=0;i<12;i++)
	{
	 	setAOonechanelPhyVal(i,0,1);
	}
}

//void getlevel(float delevel,float sslevel,float chiltemp,float cwfb,float outairT)
//{
//	de_Liq=delevel;
//	ss_Liq=sslevel;
//	chil_temp=chiltemp;
//	outair_T =outairT;
//	get_flag=1;
//	CW_FB=cwfb;
//}



///***********warning**************////
short int highlevel_alarm()

{	
 int dehlevelA=0;
 float 	  de_Liq=0;
 // while((de_Liq>DSLEVELMAXALARM)|(de_Liq<DSLEVELMINALARM))
  
	 DO_onechannel(VSD_PUMP,1);

	 de_Liq=ADC_value[DSLEVEL];
	   
  while(de_Liq>DeSLevelOpt)
	  {
	  	  de_Liq=ADC_value[DSLEVEL];
		  dehlevelA=deh_level_alarm();
		  if(dehlevelA!=0) 
	     { 

			  DO_onechannel(TRPUMP,0);

			 return dehlevelA;
		 }

	  }
	  DO_onechannel(TRPUMP,0);

  return dehlevelA;
}

short int lowlevel_sv_alarm()

{	 
   	 int  dehlevelA=0;
	 float 	de_Liq=0;
  // while((de_Liq>DSLEVELMAXALARM)|(de_Liq<DSLEVELMINALARM))
  
	DO_onechannel(STVALVE,1);

	de_Liq=ADC_value[DSLEVEL];

  while((de_Liq<DeSLevelOpt))
 	  {
	  	  de_Liq=ADC_value[DSLEVEL];
		  dehlevelA=deh_level_alarm();
		  if(dehlevelA!=0) 
	     { 
		
			  DO_onechannel(STVALVE,0);
			 return dehlevelA;
		 }
	  }

  DO_onechannel(STVALVE,0);
  return dehlevelA;

}



float RH2HR(float temp, float relativehum)
{ 
	float p_sat=0.0;
	float humityratio=0.0;
	
	   p_sat       = (4.9569*temp*temp-54.75*temp+1437.4)/1000;
		 humityratio = 1000 *(0.622*relativehum/100*p_sat/(101.325-relativehum/100*p_sat));
		 
		 return   humityratio;
	
} 

float SolInletPID(float aimed_humidity)
{
//   float km=0;

   float error=0.0;
   float vavopenorg=0;
   float outlethumidity;
   float  vavopen;

   outlethumidity =  RH2HR(ADC_value[TOUT], ADC_value[RHOUT]);

    error = aimed_humidity  -outlethumidity ;
	vavopenorg = ADC_value[CWVALVEFB] ;

  if(vavopenorg>=60.0)
  {	vavopen =  vavopenorg-40.0/0.8/6.5*error;
     if(vavopen<=60.0)
		   vavopen =58.0;
   }	
  else if (vavopenorg>=30.0)
  {	   vavopen =  vavopenorg-30.0/1.0/6.5*error;
		  if(vavopen<=30.0)
		   vavopen =28.0;
		  else if(vavopen>=60.0)
		   vavopen =62.0;
  }
//  else if (vavopenorg>=20.0)
//  {
//     vavopen =  vavopenorg-30.0/1.0/5.5*error;
//	  if(vavopen<=20.0)
//		   vavopen =18.0;
//	  else if  (vavopen>=40.0)
//		   vavopen =43.0;
// }
  else
 { 
       vavopen =vavopenorg-30.0/1.2/5.5*error;
 }
    
 	if((error<-0.25)&((vavopen -vavopenorg)<2.6)&((vavopen -vavopenorg)>0.0))
     vavopen =vavopenorg+2.6;
	 else if ((error>0.25)&((vavopenorg -vavopen)<2.6)& ((vavopenorg -vavopen)>0.0) )
	 vavopen =vavopenorg-2.6;
  
   if(vavopen>100.0)
	 vavopen=100.0;
   else if((vavopen<2.7)&&(vavopen>0.0))
	 vavopen=2.7;
   else if(vavopen<0.0)
	 vavopen=0.1;
   
   
   return vavopen;
}

  float softsensing()
{	
     
	 float outlethumidity,inlethumidity;
	 int casenum;
	 short int cnt;
	
	 float  errM[CONLENTH] = {0};
	 float concentration ;
   	 float minvalue,err,solinT;
//	 float hummatric[12][7]={0}; 
	 int i,j;
	 cnt=0;
	 casenum=0;

        	solinT = RTD_value[TSIN];
    outlethumidity =  RH2HR(ADC_value[TOUT], ADC_value[RHOUT]);
    inlethumidity  =  RH2HR(ADC_value[TIN], ADC_value[RHIN]);
  
	casenum = floor((solinT-STATEM)/0.5)-1;

 	if (casenum <0 )
	   casenum = 0 ;
    else if(casenum > TLENTH)
	   casenum = TLENTH ;
	if (inlethumidity>=12)
	 { 
	   for(i=0;i<CONLENTH;i++)
	   { 	 for(j=0;j<TLENTH;j++)
	           {  
			     hummatric[i][j] =  hummatric12[i][j] ;
			   
			   }
	   }
	  }
 
	else 
	{    for(i=0;i<CONLENTH;i++)
	   { 	 for(j=0;j<TLENTH;j++)
	           {  
			     hummatric[i][j] =  hummatric10[i][j] ;
			   
			   }
	   
	   }
	  }

	 for (i=0;i<CONLENTH;i++)
     {     err = (hummatric[i][casenum]- outlethumidity)*(hummatric[i][casenum]- outlethumidity); 
           errM[i] = err;
		 }
	minvalue =errM[0];

	 for(i=0;i<CONLENTH;i++) 
	 {
	 if(minvalue>errM[i])
	  {
	   minvalue = errM[i];
	   cnt =i;	}
	 }

	 concentration=STACON+0.5*cnt;

//	 if((analogIn[FLOWRATE]<30.0)&&(concentration>=22.0))
//
//	    concentration = concentration - 2.0;
//
//	 else if((analogIn[FLOWRATE]<30.0)&&(concentration>=21.0))
//
//	    concentration = concentration - 1.0	;


	  return concentration;
	  

	   }

float density(float temperature, float concen )
{
  short int  intcon;
  short int  inttemp;
  float densityvalue;
  intcon  = floor((concen*100)-21);
  inttemp = floor((temperature)-15);
   
      
  densityvalue =   con2dens[intcon][inttemp];

  return densityvalue;



}

 int valveopen(float t)
 {
 char  timecntF;
 char    timecntI;
 int i;
 char   alarmFlag=0;
 float 	  de_Liq =0;

DO_onechannel(STVALVE,1);


 timecntI =	floor(t/10)	;
 timecntF = floor(t-10*timecntI);

 for(i=0;i<timecntI;i++)
{
	Delay_s(10);
    de_Liq=ADC_value[DSLEVEL];
   
   if(de_Liq>DeSLevelTrasf)
	{

		DO_onechannel(STVALVE,0);
	}  

}
  alarmFlag=deh_level_alarm();

 if(alarmFlag!=0) 
   {

	 DO_onechannel(STVALVE,0);
    return alarmFlag; }

   Delay_s(timecntF);

  DO_onechannel(STVALVE,0);
 
  return  alarmFlag;
 }

 void concenalgorithm(float Setpoint[],float analogIn[16],float rangeIn[12],float analogOut[8],float rangeOut[8])
{
  float t,concenNow,caim,concenfloat;
  float TC=0;
  int Taim;
  float tempTa=20;//envionrment temp
  float concens  =0.31;  
  float SolInTNow,condiff;
  SolInTNow  = analogIn[TSIN];
  concenNow = softsensing( ) ;
  //	intsolT =	int(SolInTNow);
       TC  = caimdetermin( Setpoint, concenNow, SolInTNow);
       Taim = floor(TC);
       caim =floor(100*( TC- Taim))/100;
		concenfloat =	 concenNow/100.0   ;
		condiff =caim -concenfloat;
      if (condiff>=0.01)

       { 
	   t = opentimecnt(tempTa, concenfloat, concens, caim);
         valveopen(t);     
		   } 

 }

 float caimdetermin(float setpoint[], float conNow,float SolInTNow )
{
  
  float errN[CONLENTH]={0};
  float errM[CONLENTH]={0};
  float errC[CONLENTH]={0};
  float set_hum;
  short int i;
  float err, minvalueM, minvalueN,minvalueC,Taim, Caim,sum,cntM,cntN,cntC;
  int casenumC,casenumT;
  cntM =0;
  cntN =0;
  cntC =0;
  set_hum =  setpoint[SPHUM];

   casenumC = floor((conNow-STACON)/0.5);
   casenumT =  floor((SolInTNow-STATEM)/0.5);
   

if(set_hum-hummatric[casenumC][casenumT+1]>0.5)
{
	Taim =	(int)(SolInTNow);
	Caim =	(int)(conNow);
}
else if(hummatric[casenumC][casenumT]-set_hum>0.5)
{
  for (i=0;i<CONLENTH;i++)

 {     err = (hummatric[i][casenumT]- set_hum)*(hummatric[i][casenumT]- set_hum); 

        errC[i] = err;
		}
          minvalueC =errC[0];

   for(i=0;i<CONLENTH;i++) 
  {
  if(minvalueC>errC[i])
   {
    minvalueC= errC[i];
    cntC =i; }
   }

 Taim = (int)(SolInTNow);
 Caim =  STACON+	0.5*cntC;


}
else 
{
for (i=0;i<CONLENTH;i++)

 {     err = (hummatric[i][casenumT]- set_hum)*(hummatric[i][casenumT]- set_hum); 

           errM[i] = err;
   }
for (i=0;i<CONLENTH;i++)

 {     err = (hummatric[i][casenumT+1]- set_hum)*(hummatric[i][casenumT+1]- set_hum); 

           errN[i] = err;
   }

 minvalueM =errM[0];

   for(i=0;i<CONLENTH;i++) 
  {
  if(minvalueM>errM[i])
   {
    minvalueM = errM[i];
    cntM =i; }
  }

 minvalueN = errN[0];
  for(i=0;i<CONLENTH;i++) 
  {
  if(minvalueN>errN[i])
   {
    minvalueN = errN[i];
    cntN =i; }
  }
 if(minvalueN <minvalueM )
   	 {	Caim =STACON+0.5*cntN;
	   Taim = (int)(	SolInTNow)+1;
	 }
 else
	 { Caim	=STACON +0.5*cntM;
	   Taim = (int)(	SolInTNow);
	 }


}



   sum = Taim+Caim/100;
   return sum;
}

float opentimecnt(float tempTa,float concenw,float concens,float caim)

 {	float stube,vstr,Air_volume,mass_airflow_De,zeta,N_De;
    float rouCT,rouSA,s1,s2,s3;
 	float htank = 0;
	float pi=3.14;
	float t=0;
	float Vde = 0.768*htank;
	float  RH_De_in,   RH_De_out;
	float  tempDe;

	RH_De_out =  RH2HR(ADC_value[TOUT], ADC_value[RHOUT]);
    RH_De_in  =  RH2HR(ADC_value[TIN], ADC_value[RHIN]);
		htank =  ADC_value[SSLEVEL]+0.3	;


     rouCT = density(tempDe, concenw);
	 rouSA = density(tempTa, concens);
   	 stube = 0.03*0.03*pi;
      vstr = 2*9.8*htank*stube;

	 Air_volume  =1.0*0.4*0.4;
     mass_airflow_De=Air_volume*1.29;
     zeta = RH_De_in - RH_De_out ;
     N_De = mass_airflow_De*zeta/(0.25*0.25*pi)/1000;
	 s1 = (caim-concenw)*rouCT*Vde;
     s2 = caim*N_De;
     s3 = (concens-caim)*rouSA;

	 t = s1/(vstr*s3+s2);
	



     return t ;  // if >1  open timer else use delay  
 }


float opencnts(float error)

 {	
	float t=0, htank=0 ;

	htank =  ADC_value[SSLEVEL]/100	;
	 t = (error/0.4)*65/sqrt(htank);
     return t ;  
 }
