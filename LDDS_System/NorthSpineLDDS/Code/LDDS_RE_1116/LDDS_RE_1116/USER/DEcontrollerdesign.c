/*******************************************************************************
  * @brief  program.
  * @param  None
  * @retval None
  initial set point is fix for a customer adviced value
  ******************************************************************************/
#include "DEcontrollerdesign.h"


u8 dehStart(float Setpoint[3], u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8],u8 dehflag)
{
    float dehLiq,dehtemp,dehflow,dehpump,dehperr,dehfan,dehferr;
    int dehtime=0;


   	dout[DESTART]=DESTVALUE;   
    DPortOut(DESTART,dout[DESTART]);//启动变频器  
	APortOut(DE_CS,75,arout[DE_CS]);

//    dehLiq=APortIn(LEVEL,arin[LEVEL]);     
////    if(dehLiq>=DELIQMAX)
////    { 
////      //  DPortOut(FAUT_HIGHLEVEL,1);//高低液位都报警	   
////        return 0x01;     
////    }
////    if(dehLiq<=DELIQMIN)
////    {
////       // DPortOut(FAUT_HIGHLEVEL,1);//高低液位都报警
////        return 0x02;
////    } 
//// /* labtest*/
// 
//
////      DPortOut(DEPUMPSTART,1); 
//	  if((!remoteControl)|localControl)
//      APortOut(DE_PUMP,DEPUMPSP,arout[DE_PUMP]);//泵  
//	  else
//	  APortOut(DE_PUMP,aout[DE_PUMP],arout[DE_PUMP]);
//
//
//    delay_s(10);
//////	dehpump=APortIn(PUMPFB,arin[PUMPFB]);
//////    dehperr=fabs(dehpump-aout[DE_PUMP]); 
//////	if(dehperr>=5.0)
//////	{
//////		return 0x08;            
//////	}      
//////	
//
//    dehflow=APortIn(FLOW,arin[FLOW]);
////    if(dehflow<DEWFLOWMIN)
////    {   
////        return 0x08;       
////    } 
////   do
////    {   
////	    dehtemp = APortIn(INSOLUTION_TEMP,0);
////        delay_s(5);
//////        dehtime++;
//////     if(dehtime>=(int)(DEWTIM/5))
//////        {                 
//////            return 0x04;
//////        }
//////            
////     }while((dehtemp>=DESTEMPSP)&&dehflag);
//
////	DPortOut(DEFUNSTART,1);
//  if((!remoteControl)|localControl)
//       APortOut(DE_FAN,DEFANSP,arout[DE_FAN]);// 风机
//    else
//	   APortOut(DE_FAN,aout[DEFANSP],arout[DE_FAN]);// 风机 
//       delay_s(10);
//	    aimed_solultiontemp  =  Lookup_table(ain,Setpoint,arin,dehflag);	 
////    dehfan=APortIn(FANFB,arin[FANFB]);
//////    dehferr=fabs(dehfan-aout[DE_FAN]); 
//////    if(dehferr>=5.0)
//////    {
//////        return 6;            
//////    } 
//       
     return 0;
}
u8 dehStop(float arin[12],float arout[8],u8 dout[8])
{ 
    float dehpump,dehperr,dehfan,dehferr; 
	
    APortOut(DE_FAN,0,arout[DE_FAN]);
//	DPortOut(DEFUNSTART,0);	 
    delay_s(5);
    dehfan=APortIn(FANFB,arin[FANFB]);
    dehferr=fabs(dehfan-0); 
//    if(dehferr>=5.0)
//    {
//        return 6;            
//    }
    APortOut(DE_PUMP,0,arout[DE_PUMP]);
//	DPortOut(DEPUMPSTART,0);
	delay_s(5);
	dehpump=APortIn(PUMPFB,arin[PUMPFB]);
//    dehperr=fabs(dehpump-0); 
//	if(dehperr>=5.0)
//	{
//		return 3;            
//	}    
	dout[DESTART]=DESPVALUE;  
	DPortOut(DESTART,dout[DESTART]);
	return 0;	            
}
void deInit(float aout[8])
{
	aout[DE_PUMP]=DEPUMPSP;
	aout[DE_FAN] =DEFANSP; 
	aout[DE_CS]  =0;      
}
void deClever(float aout[8],u8 dout[8])
{
	u8 i;
	for(i=0;i<8;i++)
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

//This function is only need to be called when the setpoint is changed
float Lookup_table(float analogIn[],float setpoint[],float arout[],u8 panelControl)
{  
//   float 	 aimed_temp;
//   float     humidity_table[9]={4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.0};//digital input data storge
   float     deltam=0;
   float 	 outlethumidity=0;
   float     inlethumidity=0;
   float     SolInTemp=0;
   float   	 deltamHD=0;
   float     deltamLD =0;
   float     aimed_deltam=0;
   float     aimed_SolInTem=0;

   outlethumidity =  RH2HR(analogIn[OUTLET_TEMP], analogIn[OUTLET_HUMIDITY]);
   inlethumidity  =  RH2HR(analogIn[INLET_TEMP], analogIn[INLET_HUMIDITY]);
          deltam  =  inlethumidity-outlethumidity;
        SolInTemp = analogIn[INSOLUTION_TEMP] ;

         deltamHD = -0.3943*SolInTemp+12.122;
         deltamLD = -0.4837*SolInTemp+11.738; 


    aimed_deltam = inlethumidity -	setpoint[SETP_HUMIDITY]	;

	 if(abs(deltamLD-deltam)<=abs(deltamHD-deltam))
          { //densitylabel   = LOWDENSITY; 
		  	aimed_SolInTem =   (11.738- aimed_deltam)/0.4837;
		  }
	 else 
   		  {
		   // densitylabel  =HIGHDENSITY;
			aimed_SolInTem =   (12.122- aimed_deltam)/0.3943;
		  }
  
	return aimed_SolInTem;
}

 


 u8 solutiontransfer(float Daq[],u8 panelControl,float rangeIn[])

{  
//		
//	float desollevel=0;	
//	delay_ms(2);
//       desollevel=APortIn(LEVEL,rangeIn[LEVEL]);
//    if(panelControl)
//      {	if(desollevel>DELIQMIN)
//        DPortOut(TRANFERPUMP,1);
//          while((desollevel>DELIQMIN)&&panelControl)
//         { 	delay_ms(1);
//		    desollevel=APortIn(LEVEL,rangeIn[LEVEL]);	 
//           }
//         DPortOut(TRANFERPUMP,0);	 
//	   delay_s(2);
//      DPortOut(SV3,1);
//    while((desollevel<DE_APP_LEVEL)&&panelControl)
//      { 		delay_ms(1);
//	       desollevel=APortIn(LEVEL,rangeIn[LEVEL]);	 
//       }  
//
//      DPortOut(SV3,0);	 
//        return 0;
//   }
//  else 
  return 1;	
  }

u8 flowrate_set(float flowratestep,float arout[],float analogIn[] )
{
   float      FR_Adj_val = FR_VAL;
	u8         pumpflag   = 0     ;
	float      flowarte_pump_fb=0 ;
	
     flowarte_pump_fb=  analogIn[PUMPFB];
     delay_ms(100);
	 if(flowratestep>=50)
	 {        
				FR_Adj_val=50;
				pumpflag = 1;
	 }
	 else if(flowratestep<=30)
	 {
               FR_Adj_val=30;
			    pumpflag = 2;
   }
	else
	{        FR_Adj_val =flowratestep;
			  pumpflag = 0;
	 }      
   APortOut(DE_PUMP,FR_Adj_val,arout[DE_PUMP]);
    
      return   pumpflag	  ;
}


u8 cs_set(float csvacstep,float arout[],float analogIn[] )
{
   float      Open_Adj_val = 50;
	u8         csflag   = 0     ;
	float      cs_vav_fb=0 ;
	
     cs_vav_fb=  analogIn[CSFB];
     delay_ms(100);
	 if(csvacstep>=50)
	 {        
				Open_Adj_val=50;
				csflag = 1;
	 }
	 else if(csvacstep<=30)
	 {
               Open_Adj_val=30;
			    csflag = 2;
   }
	else
	{        Open_Adj_val =csvacstep;
			    csflag = 0;
	 }      
   APortOut(DE_CS,Open_Adj_val,arout[DE_CS]);
    
      return   csflag	  ;
}


///***********warning**************////
u8 highlevel_alarm(float Daq,u8 panelControl,float rangeIn[12])

{	

  float  desollevel= Daq ;
  u8 panelControlR=1;

  desollevel=APortIn(LEVEL,rangeIn[LEVEL]);
  while((desollevel>DE_APP_LEVEL)&&panelControl)
{
  desollevel=APortIn(LEVEL,rangeIn[LEVEL]);
   }

    panelControlR=DPortIn(0); 
   if(!panelControlR)
	return 1;
   else
   return 0;
}

u8 lowlevel_sv_alarm(float Daq,u8 panelControl,float rangeIn[12])

{	 
    float  desollevel= Daq ; 
	  desollevel=APortIn(LEVEL,rangeIn[LEVEL]);

  while((desollevel<DE_APP_LEVEL)&&panelControl)
  {
//          DPortOut(SV4,STRT_SV4);
   desollevel=APortIn(LEVEL,rangeIn[LEVEL]);
   }


 // DPortOut(SV4,~STRT_SV4);

 //  panelControlR=DPortIn(0); 
   if(!panelControl)
	return 1;
   else
   return 0;

}

u8 lowlevel_pump_alarm(float Daq,u8 panelControl,float  rangeIn[12])

{	 
 
   if(!panelControl)
	return 1;
   else
   return 0;
}

void coolingsource_alarm(void)

{	 
  
}	 

void circulation_alarm(float arout[],u8 panelControl,float arin[])

{	 
   //  APortOut(DE_PUMP,0,arout[DE_PUMP]);

}




float RH2HR(float temp, float relativehum)
{ 
	float p_sat=0.0;
	float humityratio=0.0;
	
	   p_sat       = (4.9569*temp*temp-54.75*temp+1437.4)/1000;
		 humityratio = 1000 *(0.622*relativehum/100*p_sat/(101.325-relativehum/100*p_sat));
		 
		 return   humityratio;
	
}

 

//u8 lesacalogrithm(float Setpoint[],float analogIn[16],float rangeIn[12],float analogOut[8],float rangeOut[8], u8 panelControl)
//{
//   float  outlethumidity, inlethumidity ,diffhum,flowarte_pump_fb,flowratestep,pumpflag;
//   float  CS_valve_fb,Csopenstep,csflag;
//
//    outlethumidity =  RH2HR(analogIn[OUTLET_TEMP], analogIn[OUTLET_HUMIDITY]);
//    inlethumidity  =  RH2HR(analogIn[INLET_TEMP], analogIn[INLET_HUMIDITY]);
//	diffhum        =  outlethumidity- Setpoint[SETP_TEMPERATURE];
//
//   if((diffhum<0)&&(diffhum<-0.5))
//	{
//	  flowarte_pump_fb=  analogIn[PUMPFB];
//	  flowratestep  =flowarte_pump_fb-10;
//	  pumpflag = flowrate_set(flowratestep, rangeOut, analogIn);  
//	  
//	  CS_valve_fb  = analogIn[CSFB];
//	  Csopenstep  =  CS_valve_fb - 3 ;
//	  csflag = cs_set( Csopenstep,rangeOut,analogIn) ;
//
//	  }
//   else if ((diffhum>0)&&(diffhum>0.5))
//	{
//	  flowarte_pump_fb=  analogIn[PUMPFB];
//	  flowratestep  =flowarte_pump_fb+10;
//	  pumpflag = flowrate_set(flowratestep, rangeOut, analogIn);  
//	  
//	  CS_valve_fb  = analogIn[CSFB];
//	  Csopenstep  =  CS_valve_fb + 3 ;
//	  csflag = cs_set( Csopenstep,rangeOut,analogIn) ;
//
//	  }
//	 pumplimcheck(pumpflag,flowratestep);
//	return 0;
//
//}




void concenalgorithm(float Setpoint[],float analogIn[16],float rangeIn[12],float analogOut[8],float rangeOut[8], u8 panelControl)
{
  float t,concenNow,caim,concenfloat;
  float TC=0;
  int Taim;
  float tempTa=20;//envionrment temp
  float tempDe;
  float concens  =0.31;  
  float SolInTNow,condiff;
  int intsolT;
  float vavopen;
  tempDe  = analogIn[OUTSOLUTION_TEMP];
  SolInTNow  = analogIn[INSOLUTION_TEMP];
  concenNow = softsensing( analogIn) ;
  //	intsolT =	int(SolInTNow);
       TC  = caimdetermin( Setpoint, concenNow, SolInTNow);
       Taim = floor(TC);
       caim =floor(100*( TC- Taim))/100;
		concenfloat =	 concenNow/100.0   ;
		condiff =caim -concenfloat;
      if (condiff>=0.005)

       { 
	   t = opentimecnt(analogIn , tempTa, concenfloat, concens, caim);
           valveopen(t);     
		   } 

 }



void pumplimcheck(u8 pumpflag,float step)
{			
    if((pumpflag==1)&(step>0))
	      flowratecntH++; 
	else if((pumpflag==2)&(step<0))
		  flowratecntL++; 
	else
	 { flowratecntH=0;
	  flowratecntL=0;    
				}
		}


//float checktendency(float outletHRN[12],u8 n,float step,float Setpoint[3])
//{   
//     u8 nlow;
//	 u8 i=0;
//	 u8 j=0;
//	 float sumlow =0.0;
//	 float sumhigh =0.0;
//	 float valuelow =0.0;
//	 float valuehigh = 0.0;	  //newvalue
//	 float a=0.0;
//	 float b=0.0;
//
//	
//	 nlow=(u8)(n/2);
//	 for (i=0; i <= nlow;i++)
//   { 
//      sumlow = sumlow + outletHRN[i];
//   }
//          valuelow = sumlow/nlow; //old
//
//	 
//	 for (j=nlow+1; j <= n;j++)
//   { 
//       sumhigh= sumhigh + outletHRN[j];
//   } 
//     valuehigh = sumhigh/(n-nlow);
//
//		 a =   valuelow  -  Setpoint[1];
//		 b =   valuehigh -  Setpoint[1];
//			   
//		if((a>0)&&(b>0)&&(a>b) )
//		 {
//			if(b>0.5)
//			  step =1;
//			else
//			  step =0.5;
//		       }
//
//		if((a>0)&&(b<0))
//		 {
//			if(b<-0.5)
//			  step =-0.5;
//			else
//			  step =-1;
//
//			  }
//
//		if((a>0)&&(b>0)&&(a<b))
//		 {
//			  step =1;
//			 
//			  }
//
//		if((a<0)&&(b<0)&&(a>b))
//		{
//		      step =-1;
//			    
//			  }
//		if((a<0)&&(b>0))
//		{ 
//		   if(b>0.5)
//			  step =-1;
//			else
//			  step =-0.5; 
//			  }	
//		if((a<0)&&(b<0)&&(a<b))		 
//		{ 
//			if(b>-0.5)
//			  step =0.5;
//			else
//			  step =-1;
//
//		      }
//
//
//		 return 		 step;	
//
//	}
//u8 SolInletPID(float analogInold[16],float analogIn[16],float aimed_solultiontemp,float arout[],u8 panelControl)
//{
//   float km=0;
//   float ki=0;
//   float kd=0;
//   float error=0;
//   float pumpfreq=0;
//   float c=1;
//   float massflowrate=0;
//   float deltamassflowrate=0;
//   u8  pumpflag=0;
//  if(panelControl)
//  {
//   km=(15.50-14.69)	/(26.08-19.41)	 ;
//   error = analogIn[INSOLUTION_TEMP]-analogInold[INSOLUTION_TEMP];
//   deltamassflowrate = c/km*error+ki*error+kd*error;
//	massflowrate =		deltamassflowrate +analogIn[FLOW];
//   pumpfreq	 = 	-1.623* massflowrate+55.2123;
//   pumpflag = flowrate_set(pumpfreq,arout,analogIn)	;
//
//
//   }
//   else
//   return 0;
//
//   return pumpflag;
//}

//u8 SolInletPID(float analogInold[16],float analogIn[16],float aimed_solultiontemp,float arout[],u8 panelControl)
//{
//   float km=0;
//   float ki=0;
//   float kd=0;
//   float error=0;
//   float pumpfreq=0;
//   float c=1;
//   float massflowrate=0;
//   float deltamassflowrate=0;
//   u8  pumpflag=0;
//
////	Q = Clicl*mlicl*(anglogIn[OUTSOLUTION_TEMP]-anglogIn[INSOLUTION_TEMP])
////	k = Q/mwater;
////	//valve and flowrate relationship
////	mwater
////
////  deltainlettemp = aimed_solutiontemp-anglogIn[INSOLUTION_TEMP];
////
////  deltasolutemp	 = 
////  delatwatertemp =
//
//  if(panelControl)
//  {
//   km=(15.50-14.69)	/(26.08-19.41)	 ;
//   error = analogIn[INSOLUTION_TEMP]-analogInold[INSOLUTION_TEMP];
//   deltamassflowrate = c/km*error+ki*error+kd*error;
//	massflowrate =		deltamassflowrate +analogIn[FLOW];
//   pumpfreq	 = 	-1.623* massflowrate+55.2123;
//   pumpflag = flowrate_set(pumpfreq,arout,analogIn)	;
//
//
//   }
//   else
//   return 0;
//
//  aimed_solultiontemp 
//
//
//
//   return pumpflag;
//}
//


//u8  flowrate_adj(float flowratestep,float arin[],float arout[],float analogIn[] )
//{ 
//    float      FR_Adj_val = FR_VAL;
//	u8         pumpflag   = 0     ;
//	float      flowarte_pump_fb=0 ;
//	
////	 flowarte_pump_fb =APortIn(PUMPFB,arin[PUMPFB]);
//   flowarte_pump_fb=  analogIn[PUMPFB];
//     delay_ms(100);
//	 if((flowarte_pump_fb>=50)&(flowratestep<=0))
//	 {        
//				FR_Adj_val=50;
//				pumpflag = 1;
//	 }
//	 else if((flowarte_pump_fb<=30)&(flowratestep>=0))
//	 {
//               FR_Adj_val=30;
//			    pumpflag = 2;
//   }
//
//   else
//		 
//     {
//		   pumpflag = 0;
//
//           if(flowratestep==0.5)
//						 
//               FR_Adj_val=flowarte_pump_fb-HAL_FR_STEP_VAL;
//		   
//		   else if(flowratestep==-0.5)
//
//		       FR_Adj_val=flowarte_pump_fb+HAL_FR_STEP_VAL;
//		   
//		   else if(flowratestep==1)
//		 
//		       FR_Adj_val=flowarte_pump_fb-FR_STEP_VAL;	
//		   		 
//           else	if(flowratestep==-1)
//
//		       FR_Adj_val=flowarte_pump_fb+FR_STEP_VAL;	
//
//		   else 		 
//               FR_Adj_val=flowarte_pump_fb;
//					 
//     }
//
//     APortOut(DE_PUMP,FR_Adj_val,arout[DE_PUMP]); 
//
//     return pumpflag;
//}

///// provided the length of Daq is 10
//u8 arrary_compare(float Setpoint_temp[],float Setpoint[])
//{	 
////float difference =0;
////		u8 value =0;
////		u8 i=0;
////
////   	for (i=0;i<10;i++)
////	{
////		difference = Setpoint_temp[i]-Setpoint[i];
////		if(difference!=0)
////     	{value =1;
////    	break;}
////		else
////		{value =0;
////    	continue;}
////	}
////
//    return 0;
//}

//void ctrlalgorthim(float Daq[],float setpoint[],float arout[8],float arin[12],float outlethumN[12],float outletTemN[12] )
//  
//{ 
//    float	step=1.0;
//	float   humidityratio=0;
//	float   n=12; 
//	float   outletHRN[12]={0}  ;
////	u8      i=0;
// 	u8      pumpflag = 0;
//  
//	      
//	 u8 nlow;
//	 u8 i=0;
//	 u8 j=0;
//	 float sumlow =0.0;
//	 float sumhigh =0.0;
//	 float valuelow =0.0;
//	 float valuehigh = 0.0;	  //newvalue
//	 float a=0.0;
//	 float b=0.0;
//
//    humidityratio =  RH2HR(Daq[OUTLET_TEMP], Daq[OUTLET_HUMIDITY]);	
//    step          =  humidityratio-setpoint[1] ;
//	for(i=0;i<12;i++)
//	{
//	 outletHRN[i]	=RH2HR(outletTemN[i], outlethumN[i]);	
//  	}
//
//  if (step>0.05|step<-0.05)
//  	
//
//	
//	 nlow=(u8)(n/2);
//	 for (i=0; i <= nlow;i++)
//   { 
//      sumlow = sumlow + outletHRN[i];
//   }
//          valuelow = sumlow/(nlow+1); //old
//
//	 
//	 for (j=nlow+1; j <= n;j++)
//   { 
//       sumhigh= sumhigh + outletHRN[j];
//   } 
//     valuehigh = sumhigh/((n-nlow)+1);
//
//		 a =   valuelow  -  setpoint[1];
//		 b =   valuehigh -  setpoint[1];
//			   
//		if((a>0)&&(b>0)&&(a>b) )
//		 {
//			if(b>0.5)
//			  step =1;
//			else
//			  step =0.5;
//		       }
//
//		if((a>0)&&(b<0))
//		 {
//			if(b<-0.5)
//			  step =-0.5;
//			else
//			  step =-1;
//
//			  }
//
//		if((a>0)&&(b>0)&&(a<b))
//		 {
//			  step =1;
//			 
//			  }
//
//		if((a<0)&&(b<0)&&(a>b))
//		{
//		      step =-1;
//			    
//			  }
//		if((a<0)&&(b>0))
//		{ 
//		   if(b>0.5)
//			  step =-1;
//			else
//			  step =-0.5; 
//			  }	
//		if((a<0)&&(b<0)&&(a<b))		 
//		{ 
//			if(b>-0.5)
//			  step =0.5;
//			else
//			  step =-1;
//
//		      }
//	   pumpflag = flowrate_adj(step,arin,arout,Daq);
//	   pumplimcheck(pumpflag,step);
//		 
//}																			 0--
//

float SolInletPID(float analogIn[16],float aimed_humidity,float arout[],u8 panelControl)
{
   float km=0;
   float ki=0;
   float kd=0;
   float error=0.0;
   float vavopenorg=0;
   float c=1;
   float outlethumidity;
   float massflowrate=0;
   float  vavopen;
//          pumpfreq =  exp(pumpfreq);

//  km=(15.50-14.69) /(26.08-19.41)  ;

   outlethumidity =  RH2HR(analogIn[OUTLET_TEMP], analogIn[OUTLET_HUMIDITY]);

    error = aimed_humidity  -outlethumidity ;
	vavopenorg = analogIn[CSFB] ;
  //  massflowrate = c/km*error+ki*error+kd*error;
   vavopen =vavopenorg+80.0/0.4*error+0;
   if(vavopen>80.0)
	 vavopen=80.0;
   else if(vavopen<0.0)
	 vavopen=0.0;

   return vavopen;
}

  float softsensing(float analogIn[16])
{	
     
	 float outlethumidity,inlethumidity;
	 int casenum;
	 u8 cnt;
	
	 float  errM[18] = {0};
	// float concentration ;
   	 float minvalue,err,solinT;
//	 float hummatric[12][7]={0}; 
	 int i,j;
	 cnt=0;
	 casenum=0;

        	solinT = analogIn[INSOLUTION_TEMP];
    outlethumidity =  RH2HR(analogIn[OUTLET_TEMP], analogIn[OUTLET_HUMIDITY]);
    inlethumidity  =  RH2HR(analogIn[INLET_TEMP], analogIn[INLET_HUMIDITY]);
  
	casenum = floor((solinT-12)/0.5)-1;

 	if (casenum <0 )
	   casenum = 0 ;
    else if(casenum > 17)
	   casenum = 17 ;
	if (inlethumidity>=16)
	 { 
	   for(i=0;i<18;i++)
	   { 	 for(j=0;j<17;j++)
	           {  
			     hummatric[i][j] =  hummatric17[i][j] ;
			   
			   }
	   }
	  }
    	else if	((inlethumidity<16)&&(inlethumidity>=13))

	{    for(i=0;i<18;i++)
	   { 	 for(j=0;j<17;j++)
	           {  
			     hummatric[i][j] =  hummatric14[i][j];
			   
			   }
	   }
	  } 
	else 
	{    for(i=0;i<18;i++)
	   { 	 for(j=0;j<17;j++)
	           {  
			     hummatric[i][j] =  hummatric11[i][j] ;
			   
			   }
	   
	   }
	  }

	 for (i=0;i<18;i++)
     {     err = (hummatric[i][casenum]- outlethumidity)*(hummatric[i][casenum]- outlethumidity); 
           errM[i] = err;
		 }
	minvalue =errM[0];

	 for(i=0;i<18;i++) 
	 {
	 if(minvalue>errM[i])
	  {
	   minvalue = errM[i];
	   cnt =i;	}
	 }

	 concentration=21+cnt;
	  return concentration;
	  

	   }


//   float softsensing(float analogIn[16],float aimed_solultiontemp)
//{	
//     float X[NEURALNUM];
//     float maifr = 0.16;
//	 float sum0[NEURALNUM]  ={0};
//	 float single,sumLine;
//	 float concentration =0;
//	 u8 i=0;  
//	 u8 j=0;
//	
//	X[0] =  maifr;
//   	X[1] =  analogIn[FLOW];    
//   	X[2] =	analogIn[OUTLET_HUMIDITY];
//   	X[3] =  analogIn[OUTLET_TEMP];
//   	X[4] =  analogIn[INLET_HUMIDITY];
//   	X[5] =  analogIn[INLET_TEMP];
//   	X[6] =  analogIn[OUTSOLUTION_TEMP];
//	X[7] =  analogIn[INSOLUTION_TEMP];
//
//     for( i=0;i<NEURALNUM;i++)
//	  
//	  {  sumLine =0;
//
//	   for ( j =0;j<NEURALNUM;j++)
//
//	   	 { single = Betas[j]*(X[j]-Centers[i][j])* (X[j]-Centers[i][j]); 
//		   sumLine = sumLine+single;
//		 }
//	  	  
//	      concentration =concentration + Thetas[i]*sumLine ; 
//	   }	  
//	  return concentration;
//	  
//	   }
 float opentimecnt(float analogIn[],float tempTa,float concenw,float concens,float caim)

 {	float stube,vstr,Air_volume,mass_airflow_De,zeta,N_De;
    float rouCT,rouSA,s1,s2,s3;
	float htank = 0.25;
	float pi=3.14;
	float t=0;
	float Vde = 0.768*htank;
	float  RH_De_in,   RH_De_out;
	float  tempDe;
	float 	 inlethumidity,outlethumidity;
	u8 cnt;
	tempDe    = analogIn[OUTSOLUTION_TEMP];
	inlethumidity  = analogIn[INLET_HUMIDITY];
	outlethumidity = analogIn[OUTLET_HUMIDITY] ;
	RH_De_out =  RH2HR(analogIn[OUTLET_TEMP], analogIn[OUTLET_HUMIDITY]);
    RH_De_in  =  RH2HR(analogIn[INLET_TEMP], analogIn[INLET_HUMIDITY]);

     rouCT = density(tempDe, concenw);
	 rouSA = density(tempTa, concens);
   	 stube = 0.0025/pi;
      vstr = 2*9.8*htank*stube;

	 Air_volume  = 1.0*0.4*0.4;
     mass_airflow_De=Air_volume*1.29;
     zeta = RH_De_in - RH_De_out ;
     N_De = mass_airflow_De*zeta/(0.25*0.25*pi)/1000;
	 s1 = (caim-concenw)*rouCT*Vde;
     s2 = caim*N_De;
     s3 = (concens-caim)*rouSA;

	 t = s1/(vstr*s3+s2);
	



     return t ;  // if >1  open timer else use delay  
 }
 void valveopen(float t)
 {
 u8  timecntF;
 u8    timecntI;
 int i;
 
    DPortOut(SV4,1); 
 timecntI =	floor(t/10)	;
 timecntF = floor(t-10*timecntI);
 for(i=0;i<timecntI;i++)
{
	delay_s(10);

	}

 delay_s(timecntF);

	DPortOut(SV4,0);
 
 }
//float Lookup_table(float analogIn[],float setpoint[],float arout[],u8 panelControl)
//{  
////   float 	 aimed_temp;
////   float     humidity_table[9]={4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.0};//digital input data storge
//												   
//   float     deltam=0;
//   float 	 outlethumidity=0;
//   float     inlethumidity=0;
//   float     SolInTemp=0;
//   float   	 deltamHD=0;
//   float     deltamLD =0;
//   float     aimed_deltam=0;
//   float     aimed_SolInTem=0;
//
//   outlethumidity =  RH2HR(analogIn[OUTLET_TEMP], analogIn[OUTLET_HUMIDITY]);
//   inlethumidity  =  RH2HR(analogIn[INLET_TEMP], analogIn[INLET_HUMIDITY]);
//          deltam  =  inlethumidity-outlethumidity;
//        SolInTemp = analogIn[INSOLUTION_TEMP] ;
//
//         deltamHD = -0.3943*SolInTemp+12.122;
//         deltamLD = -0.4837*SolInTemp+11.738; 
//
//
//    aimed_deltam = inlethumidity -	setpoint[SETP_HUMIDITY]	;
//
//	 if(abs(deltamLD-deltam)<=abs(deltamHD-deltam))
//          { //densitylabel   = LOWDENSITY; 
//		  	aimed_SolInTem =   (11.738- aimed_deltam)/0.4837;
//		  }
//	 else 
//   		  {
//		   // densitylabel  =HIGHDENSITY;
//			aimed_SolInTem =   (12.122- aimed_deltam)/0.3943;
//		  }
//  
//	return aimed_SolInTem;
//}

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



float caimdetermin(float setpoint[], float conNow,float SolInTNow )
{
  
  float errN[18]={0};
  float errM[18]={0};
  float errC[18]={0};
  float set_hum;
  u8 i,j;
  float err, minvalueM, minvalueN,minvalueC,Taim, Caim,sum,cntM,cntN,cntC;
  int casenumC,casenumT;
  cntM =0;
  cntN =0;
  cntC =0;
  set_hum =  setpoint[SETP_HUMIDITY];

   casenumC = floor(conNow-21);
   casenumT =  floor((SolInTNow-12)/0.5);
   

if(set_hum-hummatric[casenumC][casenumT+1]>0.5)
{
	Taim =	(int)(SolInTNow);
	Caim =	(int)(conNow);
}
else if(hummatric[casenumC][casenumT]-set_hum>0.5)
{
  for (i=0;i<18;i++)

 {     err = (hummatric[i][casenumT]- set_hum)*(hummatric[i][casenumT]- set_hum); 

        errC[i] = err;
		}
          minvalueC =errC[0];

   for(i=0;i<18;i++) 
  {
  if(minvalueC>errC[i])
   {
    minvalueC= errC[i];
    cntC =i; }
   }

 Taim = (int)(SolInTNow);
 Caim =  21+	cntC;


}
else 
{
for (i=0;i<18;i++)

 {     err = (hummatric[i][casenumT]- set_hum)*(hummatric[i][casenumT]- set_hum); 

           errM[i] = err;
   }
for (i=0;i<18;i++)

 {     err = (hummatric[i][casenumT+1]- set_hum)*(hummatric[i][casenumT+1]- set_hum); 

           errN[i] = err;
   }

 minvalueM =errM[0];

   for(i=0;i<18;i++) 
  {
  if(minvalueM>errM[i])
   {
    minvalueM = errM[i];
    cntM =i; }
  }

 minvalueN = errN[0];
  for(i=0;i<18;i++) 
  {
  if(minvalueN>errN[i])
   {
    minvalueN = errN[i];
    cntN =i; }
  }
 if(minvalueN <minvalueM )
   	 {	Caim =21+	cntN;
	   Taim = (int)(	SolInTNow)+1;
	 }
 else
	 { Caim	=21 +cntM;
	   Taim = (int)(	SolInTNow);
	 }


}



   sum = Taim+Caim/100;
   return sum;
}

