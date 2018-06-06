#include "logic.h"

float de_Liq=28,ss_Liq=28,chil_temp=0,get_flag=0,CW_FB=0, sp_Hum =0, outair_T =0;
  int cnt=0, cntE=0;
  int waterincharge=0;
u8 deh_algorithm(float analogOut[],float rangeOut[])
{

 	 u8  dehlevelA=0;
	 float  outlethumidity,vavopen,t;
	 dehlevelA=deh_transfer();
	 
	 if(dehlevelA!=0) 
	 return dehlevelA;


   if(timer4open ==0)
	 {Tim4ST();	
		timer4open =1;
		}

 	if(algorithmstart==1)
	  {
     
	 	outlethumidity =  RH2HR(analogIn[TOUT], analogIn[RHOUT]);
		if((outlethumidity-SetpointValueL[SPHUM])>2.0)

	    	{	cnt=0;
				waterincharge  =0;
				cntE++;
			    APortOut(CWVALVE,CHILLEDVALVEO,rangeOut[CWVALVE]);
			   // concenalgorithm(SetpointValueL, analogIn, rangeIn, analogOut, rangeOut)	; 
				if(cntE==80)
				{ t = opencnts(1)	;
			   	  dehlevelA = valveopen(t); 
				  cntE =0;
				  if(dehlevelA!=0)
                  return dehlevelA;
				}
		    
		
		    }
		else if(((outlethumidity-SetpointValueL[SPHUM])<2.5)&&((outlethumidity-SetpointValueL[SPHUM])>0.02))
		
         { 
		   if  (analogIn[CWVALVEFB]<=95.0) 
			 { 
			   vavopen=SolInletPID(SetpointValueL[SPHUM], rangeOut);
			   APortOut(CWVALVE,vavopen,rangeOut[CWVALVE]);	
			   
			    }

		  else
		    {
		    	cnt++;
		    	waterincharge++;
		    	if(cnt==70)
			    templocker =0 ;
	     	   
			    if(	waterincharge ==20)
		        {	
		          if (analogIn[CPUMPFB]<=40.0)
			         APortOut(CPUMP,50.0,rangeOut[CPUMP]);

				  else if((( analogIn[TSIN] - templocker)<=0.05)||(templocker==0)) 
	     	        {	  
			           templocker = analogIn[TSIN];
				       t = opencnts( outlethumidity-SetpointValueL[SPHUM])	;
                       dehlevelA=valveopen(t); 
					    cnt=0;
					   if(dehlevelA!=0) 
	                     return dehlevelA;
					   
	    	         }
				      waterincharge  =0;
		          }
			}
			}
//		 else if(((outlethumidity-SetpointValueL[SPHUM])<0.0)&&((SetpointValueL[SPHUM]-outlethumidity)<0.7))
		 else if((SetpointValueL[SPHUM]-outlethumidity)>0.05)

		 {  
			   cnt=0;
			   waterincharge  =0;

			   vavopen=SolInletPID( SetpointValueL[SPHUM], rangeOut);
			   APortOut(CWVALVE,vavopen,rangeOut[CWVALVE]);	
			     
			   if(analogIn[CPUMPFB]>=32.0)
			   APortOut(CPUMP,analogIn[CPUMPFB]-2.0,rangeOut[CPUMP]);
		
		}
//		else if(((outlethumidity-SetpointValueL[SPHUM])>3.0)&&(analogIn[CWVALVEFB]>=99.0))
//		 {
//		 	//  dehlevelA= 0x04;
//		 }

				 algorithmstart   =0;
			
		 }	 	

 
      if(dehlevelA!=0) 
	    return dehlevelA;     
	  else
 	    return 0;
 
}

u8 deh_level_alarm(void) //液位报警
{  
    if(de_Liq>=DSLEVELMAXALARM)//检查液位
    {
        return 0x01;
    }
    if(de_Liq<=DSLEVELMINALARM)
    {
        return 0x02;
    }
    if(ss_Liq>=SSLEVELMAXALARM)
    {
        return 0x01;
    }
//	if(ss_Liq<=SSLEVELMINALARM)
//    {
//        return 0;
//    }

	else return 0;
}


u8 deh_transfer(void)//换液 等算法
{
   int dehlevelA=0; 

	if(de_Liq>=DSLEVELMAXALARM)
    {
        return 0x01;
    }
//	if(WS_Level>=WSLEVELMAXALARM)
//	{
//	    return 0x01; 
//	}
   if(de_Liq<=DSLEVELMINALARM)
    {
        return 0x02;
    }
    if(ss_Liq>=SSLEVELMAXALARM)
    {
        return 0x01;
    }
//	if(ss_Liq<=SSLEVELMINALARM)
//    {
//        //return 0x02;
//    }
	if(de_Liq>=DSLEVELSTART)	
	{
   	  dehlevelA= highlevel_alarm()		   ;
	  if(dehlevelA!=0) 
	  return dehlevelA;	                                         //换液标志位 置1
	}
   if(de_Liq<DSLEVELSTOP)						                //停止换液
	{
      dehlevelA= lowlevel_sv_alarm()	 ;
     if(dehlevelA!=0) 
	 return dehlevelA;
	                                                //换液标志位 清零
	}
	
	 return 0;
}


u8 dehStart(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8])
{
    u8 dehlevelA=0;
    float reqtem = 18.0;
	while(get_flag==0);

    if(de_Liq>=DSLEVELMAXALARM)//检查液位
    {
        return 0x01;
    }
    if(de_Liq<=DSLEVELMINALARM)
    {
        return 0x02;
    }
    if(ss_Liq>=SSLEVELMAXALARM)
    {
        return 0x01;
    }
//	if(ss_Liq<=SSLEVELMINALARM)
//    {
//        //return 0x02;
//    }
    APortOut(CWVALVE,CHILLEDVALVEO,arout[CWVALVE]);//开冷水阀
	delay_s(5); 
    
	while(CW_FB<=95)//等待冷水阀全开
	{ 
		dehlevelA=deh_level_alarm();
		if(dehlevelA!=0) return dehlevelA;
		delay_ms(10);
	}
	while(de_Liq<=16.0)//检查液位是否小于22厘米
	{
		DPortOut(STVALVE,1); //开st阀
		delay_ms(10);	
	}

	DPortOut(STVALVE,0); //关st阀
	DPortOut(VSD_PUMP,1); //打开vsd pump
	APortOut(CPUMP,CPUMPO,arout[CPUMP]); //开循环泵
	delay_s(1);

//	while((chil_temp<=3)||(chil_temp>=20))
	 reqtem= 1.25* SetpointValueL[SPHUM]+7.875;
	 if(reqtem< 16.0)
	 reqtem = 16.0;
	 else if (reqtem> 19.0)
	 reqtem = 19.0;

	while(chil_temp>=reqtem) //等待溶液冷却 需要修改->等待溶液温度小于16度
	{
	    dehlevelA=deh_level_alarm();
		if(dehlevelA!=0) 
		   return dehlevelA;
	    
	 }
	DPortOut(VSD_FAN,1); //打开VSD 风扇
	APortOut(SFAN,SFANO,arout[SFAN]);  //打开vsd风扇
   
   	while(outair_T-chil_temp>=7) //等待溶液冷却 需要修改->等待溶液温度小于16度
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

u8 dehStop(float arin[12],float arout[8],u8 dout[8])
{
    DPortOut(VSD_FAN,0);  //关闭vsd 风扇
    delay_s(5);
	DPortOut(VSD_PUMP,0);	//关闭vsd 泵
		delay_s(5);
		APortOut(CWVALVE,0,arout[CWVALVE]); //关冷水阀
	  delay_s(5);
    return 0;        
}

void deClever(float aout[12],u8 dout[8])
{
	 u8 i,j,k;
	 for(i=0;i<2;i++)
	 {
	  	aout[i]=0;
		APortOut(i,0,1);
	 }
	

     APortOut(SSLEVELSD,SSLEVELMAXALARM/10.0*0.8,10);

     for(j=4;j<8;j++)
	 {
	  	aout[i]=0;
		APortOut(i,0,1);
	 }

	 for(k=0;k<8;k++)
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

void getlevel(float delevel,float sslevel,float chiltemp,float cwfb,float outairT)
{
	de_Liq=delevel;
	ss_Liq=sslevel;
	chil_temp=chiltemp;
	outair_T =outairT;
	get_flag=1;
	CW_FB=cwfb;
}



///***********warning**************////
u8 highlevel_alarm()

{	
 int dehlevelA=0;
 // while((de_Liq>DSLEVELMAXALARM)|(de_Liq<DSLEVELMINALARM))
  
     DPortOut(TRPUMP,1);	          //打开转移泵
	   
  while(de_Liq>DEAPPLEVEL)
	  {
	  	  de_Liq=analogIn[DSLEVEL];

	  }
     DPortOut(TRPUMP,0);	          //打开转移泵

  return dehlevelA;
}

u8 lowlevel_sv_alarm()

{	 
   	 int  dehlevelA=0;
  // while((de_Liq>DSLEVELMAXALARM)|(de_Liq<DSLEVELMINALARM))
  
	DPortOut(STVALVE,1);

  while((de_Liq<DEAPPLEVEL))
 	  {
	  	  de_Liq=analogIn[DSLEVEL];

	  }
  DPortOut(STVALVE,0);
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

float SolInletPID(float aimed_humidity,float arout[])
{
//   float km=0;

   float error=0.0;
   float vavopenorg=0;
   float outlethumidity;
   float  vavopen;

   outlethumidity =  RH2HR(analogIn[TOUT], analogIn[RHOUT]);

    error = aimed_humidity  -outlethumidity ;
	vavopenorg = analogIn[CWVALVEFB] ;

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

//  float softsensing()
//{	
//     
//	 float outlethumidity,inlethumidity;
//	 int casenum;
//	 u8 cnt;
//	
//	 float  errM[CONLENTH] = {0};
//	 float concentration ;
//   	 float minvalue,err,solinT;
////	 float hummatric[12][7]={0}; 
//	 int i,j;
//	 cnt=0;
//	 casenum=0;
//
//        	solinT = analogIn[TSIN];
//    outlethumidity =  RH2HR(analogIn[TOUT], analogIn[RHOUT]);
//    inlethumidity  =  RH2HR(analogIn[TIN], analogIn[RHIN]);
//  
//	casenum = floor((solinT-STATEM)/0.5)-1;
//
// 	if (casenum <0 )
//	   casenum = 0 ;
//    else if(casenum > TLENTH)
//	   casenum = TLENTH ;
//	if (inlethumidity>=12)
//	 { 
//	   for(i=0;i<CONLENTH;i++)
//	   { 	 for(j=0;j<TLENTH;j++)
//	           {  
//			     hummatric[i][j] =  hummatric12[i][j] ;
//			   
//			   }
//	   }
//	  }
// 
//	else 
//	{    for(i=0;i<CONLENTH;i++)
//	   { 	 for(j=0;j<TLENTH;j++)
//	           {  
//			     hummatric[i][j] =  hummatric10[i][j] ;
//			   
//			   }
//	   
//	   }
//	  }
//
//	 for (i=0;i<CONLENTH;i++)
//     {     err = (hummatric[i][casenum]- outlethumidity)*(hummatric[i][casenum]- outlethumidity); 
//           errM[i] = err;
//		 }
//	minvalue =errM[0];
//
//	 for(i=0;i<CONLENTH;i++) 
//	 {
//	 if(minvalue>errM[i])
//	  {
//	   minvalue = errM[i];
//	   cnt =i;	}
//	 }
//
//	 concentration=STACON+0.5*cnt;
//
////	 if((analogIn[FLOWRATE]<30.0)&&(concentration>=22.0))
////
////	    concentration = concentration - 2.0;
////
////	 else if((analogIn[FLOWRATE]<30.0)&&(concentration>=21.0))
////
////	    concentration = concentration - 1.0	;
//
//
//	  return concentration;
//	  
//
//	   }

float density(float temperature, float concen )
{
  u8  intcon;
  u8  inttemp;
  float densityvalue;
  intcon  = floor((concen*100)-21);
  inttemp = floor((temperature)-15);
   
      
  densityvalue =   con2dens[intcon][inttemp];

  return densityvalue;



}

 int valveopen(float t)
 {
	 u8  timecntF;
 	 u8    timecntI;
 	int i;
 	u8   alarmFlag=0;

 	DPortOut(STVALVE,1); 
 	timecntI =	floor(t/10)	;
 	timecntF = floor(t-10*timecntI);

 	for(i=0;i<timecntI;i++)
	{
	
	//	de_Liq=analogIn[DSLEVEL];
       if(de_Liq>DSLEVELSTART)
    	{
	 	DPortOut(STVALVE,0); 
    	} 
		
	   alarmFlag=deh_transfer();
	   delay_s(10);
	}



  alarmFlag=deh_level_alarm();

 if(alarmFlag!=0) 
   {
    DPortOut(STVALVE,0); 
    return alarmFlag; }

   delay_s(timecntF);

   DPortOut(STVALVE,0);
 
  return  alarmFlag;
 }

// void concenalgorithm(float Setpoint[],float analogIn[16],float rangeIn[12],float analogOut[8],float rangeOut[8])
//{
//  float t,concenNow,caim,concenfloat;
//  float TC=0;
//  int Taim;
//  float tempTa=20;//envionrment temp
//  float concens  =0.31;  
//  float SolInTNow,condiff;
//  SolInTNow  = analogIn[TSIN];
//  concenNow = softsensing( ) ;
//  //	intsolT =	int(SolInTNow);
//       TC  = caimdetermin( Setpoint, concenNow, SolInTNow);
//       Taim = floor(TC);
//       caim =floor(100*( TC- Taim))/100;
//		concenfloat =	 concenNow/100.0   ;
//		condiff =caim -concenfloat;
//      if (condiff>=0.01)
//
//       { 
//	   t = opentimecnt(tempTa, concenfloat, concens, caim);
//         valveopen(t);     
//		   } 
//
// }

// float caimdetermin(float setpoint[], float conNow,float SolInTNow )
//{
//  
//  float errN[CONLENTH]={0};
//  float errM[CONLENTH]={0};
//  float errC[CONLENTH]={0};
//  float set_hum;
//  u8 i;
//  float err, minvalueM, minvalueN,minvalueC,Taim, Caim,sum,cntM,cntN,cntC;
//  int casenumC,casenumT;
//  cntM =0;
//  cntN =0;
//  cntC =0;
//  set_hum =  setpoint[SPHUM];
//
//   casenumC = floor((conNow-STACON)/0.5);
//   casenumT =  floor((SolInTNow-STATEM)/0.5);
//   
//
//if(set_hum-hummatric[casenumC][casenumT+1]>0.5)
//{
//	Taim =	(int)(SolInTNow);
//	Caim =	(int)(conNow);
//}
//else if(hummatric[casenumC][casenumT]-set_hum>0.5)
//{
//  for (i=0;i<CONLENTH;i++)
//
// {     err = (hummatric[i][casenumT]- set_hum)*(hummatric[i][casenumT]- set_hum); 
//
//        errC[i] = err;
//		}
//          minvalueC =errC[0];
//
//   for(i=0;i<CONLENTH;i++) 
//  {
//  if(minvalueC>errC[i])
//   {
//    minvalueC= errC[i];
//    cntC =i; }
//   }
//
// Taim = (int)(SolInTNow);
// Caim =  STACON+	0.5*cntC;
//
//
//}
//else 
//{
//for (i=0;i<CONLENTH;i++)
//
// {     err = (hummatric[i][casenumT]- set_hum)*(hummatric[i][casenumT]- set_hum); 
//
//           errM[i] = err;
//   }
//for (i=0;i<CONLENTH;i++)
//
// {     err = (hummatric[i][casenumT+1]- set_hum)*(hummatric[i][casenumT+1]- set_hum); 
//
//           errN[i] = err;
//   }
//
// minvalueM =errM[0];
//
//   for(i=0;i<CONLENTH;i++) 
//  {
//  if(minvalueM>errM[i])
//   {
//    minvalueM = errM[i];
//    cntM =i; }
//  }
//
// minvalueN = errN[0];
//  for(i=0;i<CONLENTH;i++) 
//  {
//  if(minvalueN>errN[i])
//   {
//    minvalueN = errN[i];
//    cntN =i; }
//  }
// if(minvalueN <minvalueM )
//   	 {	Caim =STACON+0.5*cntN;
//	   Taim = (int)(	SolInTNow)+1;
//	 }
// else
//	 { Caim	=STACON +0.5*cntM;
//	   Taim = (int)(	SolInTNow);
//	 }
//
//
//}
//
//
//
//   sum = Taim+Caim/100;
//   return sum;
//}

//float opentimecnt(float tempTa,float concenw,float concens,float caim)
//
// {	float stube,vstr,Air_volume,mass_airflow_De,zeta,N_De;
//    float rouCT,rouSA,s1,s2,s3;
// 	float htank = 0;
//	float pi=3.14;
//	float t=0;
//	float Vde = 0.768*htank;
//	float  RH_De_in,   RH_De_out;
//	float  tempDe;
//
//	RH_De_out =  RH2HR(analogIn[TOUT], analogIn[RHOUT]);
//    RH_De_in  =  RH2HR(analogIn[TIN], analogIn[RHIN]);
//		htank =  analogIn[SSLEVEL]+0.3	;
//
//
//     rouCT = density(tempDe, concenw);
//	 rouSA = density(tempTa, concens);
//   	 stube = 0.03*0.03*pi;
//      vstr = 2*9.8*htank*stube;
//
//	 Air_volume  =1.0*0.4*0.4;
//     mass_airflow_De=Air_volume*1.29;
//     zeta = RH_De_in - RH_De_out ;
//     N_De = mass_airflow_De*zeta/(0.25*0.25*pi)/1000;
//	 s1 = (caim-concenw)*rouCT*Vde;
//     s2 = caim*N_De;
//     s3 = (concens-caim)*rouSA;
//
//	 t = s1/(vstr*s3+s2);
//	
//
//
//
//     return t ;  // if >1  open timer else use delay  
// }
/* the parameters of this function are calculated with the following method
1) measure the response of between the outlet air humidity and the concentration in the tank
2) calculate the parameters by considering the working concentration,the flowrate from strong solution buffer
3) notice do not open this valve too long, the threshold need to be carefully considered to avoid high level alarm of detank
*/

float opencnts(float error)

 {	
	float t=0, htank=0 ;

	htank =  analogIn[SSLEVEL]/100	;
	if (htank>=0.01)
	 t = (error/0.4)*65/sqrt(htank);
	else
	 t=0.0;
     return t ;  
 }
