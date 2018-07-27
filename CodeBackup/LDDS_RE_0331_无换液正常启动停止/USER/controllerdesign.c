											  
#include "stm32f10x.h"

#include "controllerdesign.h"
#include "stm32f10_timer.h"
#include "mcp3208.h"
#include "stm32f10_dac.h"
#include "stm32f10_gpio.h"

/*******************************************************************************
  * @brief  program.
  * @param  None
  * @retval None
  initial set point is fix for a customer adviced value
  ******************************************************************************/
//AI
/* 

#define COOLINGSOURCE_TEMP 		       0
#define SOLUTION_TEMP 				   1
#define INLET_TEMP					   2
#define INLET_ HUMIDITY				   3
#define OUTLET_TEMP					   4
#define OUTLET_HUMIDITY				   5
#define SOLUTION_FLOWRATE			   6
#define DE_SOLU_LEVEL	               7
#define DILU_T_SOLU_LEVEL	           8
#define STR_T_SOLU_LEVEL	           9
   
*/

//DO
/* 	 
#define   START 			  0
#define   TRANSFERPUMP		  1
#define	  SV1				  2
#define	  SV3				  3
#define	  LIQUIDLEVEL		  4
#define	  OTHER			      5
#define	  SV3OPTIONAL_PUMP	  6
*/
//AO
/*
#define   DE_PUMP 			  0
#define   DE_FAN			  1
#define   DE_CS 			  2
*/

u8 dehStart(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8])
{
    float deLiq,dewflow,detemp;
    float detime=0;

    deLiq=APortIn(DE_SOLU_LEVEL,arin[DE_SOLU_LEVEL]);

    if(deLiq>=DELIQMAX)
    {
        highlevel_alarm(ain[DE_SOLU_LEVEL]);
        return 0;
    }
    if(deLiq<=DELIQMIN)
    {
        if(SV3ORPUMP==0|SV3ORPUMP==2)
		lowlevel_sv_alarm(ain[DE_SOLU_LEVEL]);
		else if(SV3ORPUMP==1|SV3ORPUMP==2)
		{lowlevel_pump_alarm(ain[DE_SOLU_LEVEL]);
		 }

        return 0;
    }

    APortOut(DE_PUMP,DECPUMPDEF,arout[DE_PUMP]);

    delay_s(8); 

    dewflow=APortIn(SOLUTION_FLOWRATE,arin[SOLUTION_FLOWRATE]);

    if(dewflow<DEWFLOWMIN)
    {
        circulation_alarm(arout); 
        return 0;
    }
    
    //开冷源；
    do
    {        
        detemp=APortIn(SOLUTION_TEMP,0);
        delay_s(5);
        detime++;
        if(detime>(int)(DEWTIM/5))
        {
            coolingsource_alarm();
            return 0;
        }
            
    }while(detemp>DESTEMPMAX);


    APortOut(DE_FAN,DEFANDEF,arout[DE_FAN]); 


    return 0;
}

u8 dehStop(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8])
{
    
    APortOut(DE_FAN,DEFANSTOP,arout[DE_FAN]); 	    //stop fun

	                                                    //Stop cooling source

    APortOut(DE_PUMP,DECPUMPSTOP,arout[DE_PUMP]);       //stop pump


    return 0;
}


//This function is only need to be called when the setpoint is changed
void Lookup_table(float Daq[],float setpoint[],float arout[8])
{  
  
   u8 	 modified_setpoint;
   float 	 aimed_temp;
   float     tempstep ;
   float     ao_value;
   modified_setpoint= (u8)(setpoint[0]-2);

   switch(modified_setpoint) 
   {
        case 1: aimed_temp=11;  break;
        case 2: aimed_temp=12;  break;
        case 3: aimed_temp=13;  break;
        case 4: aimed_temp=14;  break;
        case 5: aimed_temp=15;  break;
        case 6: aimed_temp=16;  break;
        case 7: aimed_temp=17;  break;
        default:aimed_temp=20;
    }

	tempstep = aimed_temp-Daq[1];

    ao_value	= CS_VAL-tempstep*CS_STEP_VAL;

    APortOut(DE_PUMP,ao_value,arout[DE_PUMP]); 
     
}

 
u8 ctrlalgorthim(float Daq[],float setpoint[],u8 flowratecnt,float arout[8] )
  
{ 
  float	step=0;
  float	ao_value[3]={0};
 
  step = setpoint[0]-Daq[5] ;

  if (step>0.1|step<-0.1)
  	
  {if  (flowratecnt == FR_ACCRCY)
  {	 
   flowratecnt = 0;
  }
  else if (flowratecnt == 0)
	{ 
	  	 
	 ao_value[2]	= coolingsouce_adj(step);

 	 APortOut(DE_PUMP,ao_value[2],arout[DE_PUMP]); 

	  ///赋值给buffer
	}
 else
   {

	 ao_value[0]	= flowrate_adj(step);

 	 APortOut(DE_PUMP,ao_value[0],arout[DE_PUMP]); 
	  
	 ///赋值给buffer
	 flowratecnt++;
   } 
    }

 return    flowratecnt; 

}



//void solutiontransfer(float Daq[] )
//
//{  
//       if((Daq[DILU_T_SOLU_LEVEL]<= DT_APP_LEVEL)&(Daq[DE_SOLU_LEVEL]>=DELIQMIN))
//	         {
//		        
//					DPortOut(TRANSFERPUMP,STRT_T_PUMP);
//
//                    while (Daq[DE_SOLU_LEVEL]> DELIQMIN);
//
//                    DPortOut(TRANSFERPUMP,~STRT_T_PUMP);
//
//         	 if((Daq[STR_T_SOLU_LEVEL]>= ST_APP_LEVEL )&(Daq[DE_SOLU_LEVEL]<=DELIQMAX)&(SV3ORPUMP==0))
//	         {	 
//			    
//				  DPortOut(SV3,STRT_SV3);
//
//		          while (Daq[DE_SOLU_LEVEL]<DE_APP_LEVEL);
//
//		          DPortOut(SV3,~STRT_SV3);
//
//	          }
//	         if((Daq[STR_T_SOLU_LEVEL]>= ST_APP_LEVEL )&(Daq[DE_SOLU_LEVEL]<=DELIQMAX)&(SV3ORPUMP==1))
//	          {	  
//			    
//
//				   DPortOut(SV3OPTIONAL_PUMP,STRT_TO_PUMP);
//
//                  while (Daq[DE_SOLU_LEVEL]<DE_APP_LEVEL);
//
//               
//				   DPortOut(SV3OPTIONAL_PUMP,~STRT_TO_PUMP);
//
//               }
//	         }
//	
//	
//  }
//

// AO[0] dehumidifier pump  AO[1] dehumidifier fun
float coolingsouce_adj(u8 tempstep)
{ 
  float  CS_Adj_val = CS_VAL ;

  if(tempstep>0)   
   CS_Adj_val=CS_Adj_val-CS_STEP_VAL;
  else
   CS_Adj_val=CS_Adj_val+CS_STEP_VAL;  

   return 	CS_Adj_val	;

}

float flowrate_adj(u8 flowratestep)
{ 
  float   FR_Adj_val =FR_VAL;

  if(flowratestep>0)
   
  FR_Adj_val=FR_Adj_val-FR_STEP_VAL;

  else

  FR_Adj_val=FR_Adj_val+FR_STEP_VAL;

  return   FR_Adj_val ;
     
}


///***********warning**************////
void highlevel_alarm(float Daq)

{	 
 
  DPortOut(TRANSFERPUMP,STRT_T_PUMP);

  while (Daq> DE_APP_LEVEL);

  DPortOut(TRANSFERPUMP,~STRT_T_PUMP);

}

void lowlevel_sv_alarm(float Daq)

{	 
 
  DPortOut(SV3,STRT_SV3);

  while (Daq <DE_APP_LEVEL);

  DPortOut(SV3,~STRT_SV3);

}

void lowlevel_pump_alarm(float Daq)

{	 
  DPortOut(SV3OPTIONAL_PUMP,STRT_TO_PUMP);

  while (Daq<DE_APP_LEVEL);

  DPortOut(SV3OPTIONAL_PUMP,~STRT_TO_PUMP);

}

void coolingsource_alarm(void)

{	 
  
}	 


void circulation_alarm(float arout[])

{	 
   APortOut(DE_PUMP,DECPUMPSTOP,arout[DE_PUMP]);
}


///// provided the length of Daq is 10
u8 arrary_compare(float Setpoint_temp[],float Setpoint[])
{	 float difference =0;
		u8 value =0;
		u8 i=0;

   	for (i=0;i<10;i++)
	{
		difference = Setpoint_temp[i]-Setpoint[i];
		if(difference!=0)
     	{value =1;
    	break;}
		else
		{value =0;
    	continue;}
	}

    return value;
}

float *plastdata(float *pData_temp,float *pData)

 {	u8 i;
 
   for(i=0;i<SETPlENGTH;i++)
        {
              *pData_temp= *pData;
               pData++;
               pData_temp++;

        }

        return pData_temp;
	}
	
