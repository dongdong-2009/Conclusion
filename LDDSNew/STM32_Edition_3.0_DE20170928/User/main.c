#include <stdio.h>
#include "stm32f10x.h"		 
#include "timer.h"	
#include "adc.h"
#include "rtd.h"
#include "dac.h"
#include "digital_io.h"
#include "usart.h"
#include "systick_timer.h"
#include "extvart.h"

#include "Lddsmain.h"



#define UIEXI  1 // 1 indicates the exsit of an UI touch screen 

int main()
{

	Delay_s(1);
	IO_Configuration();

    ADC_init();
    RTD_init();
    DAC_init();
    Usart_Initi();
	InitializeTimer(0,5);
	TurnOnTim(0);

	if(UIEXI)

	{ 
	    Uart_Initi();
 	    InitializeTimer(1,10);
	   
	 }



    while(1)
   {   
	 
      while(!panelControl&&(!panelCStatus))
      {  
		   DI_onechannel(LOCALORREMOTE,DI_data);		//DI single port
		   panelControl =DI_data[LOCALORREMOTE];
		   if(panelControl)
			{
				if(UIEXI)
				  {   
				      TurnOnTim(1);	  //for UI
                      TurnOnUart4();
				   }

			 	panelCStatus=1;	
			}
	   }
	  if(!panelControl)
		{
			deAOReset(0,0,0,0)  ;
		    deDOReset(0,0,0,0)  ;   
			panelCStatus=0;
		}

      if((deviceRun|localControl|System_On)&&(!runStatus)&&panelControl&&(alarmFlag==0))
        {
	        alarmFlag=dehStart(AIParams,AOParams);
		  	runStatus=1;
			if	(alarmFlag!=0)
			{
			    DO_onechannel(ALARM,1);
                deClever();  
				runStatus=0;
			}

        }
      if(((!deviceRun)|(localDeviceRun&(!localControl)))&&runStatus&&panelControl)
        {
            alarmFlag=dehStop(AIParams,AOParams,DO_data);
		    runStatus=0;
            if(alarmFlag!=0)
            {
			  	DO_onechannel(ALARM,1);
			    deClever();
				runStatus=0;
            }

        }
      if(alarmFlag!=0)
        {
			  	DO_onechannel(ALARM,1);
			    deClever();
				runStatus=0;
        }
	 while(runStatus&&panelControl&&((remoteControl&deviceRun)|localControl|System_On))	             //ªª“∫À„∑®
     if(runStatus)
  	 {
		 if(autoControl==1)
		 {
		   alarmFlag= deh_algorithm() ;
		 
		 }
		  alarmFlag=deh_transfer();
		  if (localControl)
		    	Setpoint[0]= UIregister[2];
		  else
		   		Setpoint[0]=  SetpointPC[SPHUM];
                                         
		  if(alarmFlag!=0)
		  {
			    DO_onechannel(ALARM,1);
			    deClever();
				runStatus=0;
		  }
	 }
 
   }

}



