#include <stdio.h>
//#include "stm32f10x.h"		 	
#include "rtd.h"
#include "Globle.h"
#include "LddsPorts.h"	
#include "LddsVar.h"	
#include "delay.h"
#include "Dio.h" 
#include "ads1115.h"
#include "delay.h"
#include "DAC8554.h"
#include "MuxCfg.h"


#define UIEXI  1 // 1 indicates the exsit of an UI touch screen 

int main()
{
   	NVIC_Configuration();
//	delay_init();
	delay_ms(500);
	RTD_init();
   	stm32ads1115_1_init();
	DAC8554_GPIO_Config();
	MuxGpioCfg();
	DioCfg();
    UART_Configuration();
	LedInit();
    TIM1_Int_Init(20,7199);	//定时器初始化为5ms中断一次
	TIM2_Int_Init(30,7199); 
	TIM3_Int_Init(20,7199);
    TIM4_Int_Init(5,18000-1);

   while(1)
   {   
	 
      while(!panelControl&&(!panelCStatus))
      {  
		   panelControl =GetDiSingal(LOCALORREMOTE);
		   panelControl =1;
		   if(panelControl)
			{
			 	panelCStatus=1;	
			}
	   }
	  if(!panelControl)
		{
			deClever();
			panelCStatus=0;
		}

      if((deviceRun|localControl|System_On)&&(!runStatus)&&panelControl&&(alarmFlag==0))
        {
	        alarmFlag=dehStart(AIParams,AOParams);
			alarmFlag=alarmanaysis();
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
			alarmFlag=alarmanaysis();
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

	 while(runStatus&&panelControl&&((remoteControl&deviceRun)|localControl|System_On))	             //换液算法
     if(runStatus)
  	 {
		  alarmFlag= deh_algorithm() ;
		  alarmFlag=deh_transfer();
		  alarmFlag=alarmanaysis();

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



