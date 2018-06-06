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



#define UIEXI  0// 1 indicates the exsit of an UI touch screen 

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
			panelControl=1;
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
			reAOReset(0,0,0,0)  ;
		    reDOReset(0,0,0,0)  ;   
			panelCStatus=0;
		}

      if((deviceRun|localControl|System_On)&&(!runStatus)&&panelControl&&(alarmFlag==0))
        {
	       		//��ȡϵͳ����״̬��Ϣ���Ƿ���ڹ���
		 	alarmFlag=regStart(AIParams,AOParams,DO_data);
			//re_alarm=(enum _alarm)alarmFlag;
			if(alarmFlag!=0)
			{
				DO_onechannel(RE_ALARM,1);
				DO_onechannel(HEATPUMP,0);
				Delay_s(1);
				DO_onechannel(REFAN,0);                             //�ط���  
				Delay_s(1);	   
				DO_onechannel(CPUMP,0);	                           //��ѭ����
			}
			runStatus=1;                                 //�豸��������

        }
      if(((!deviceRun)|(localDeviceRun&(!localControl)))&&runStatus&&panelControl)
        {
            	//��ȡϵͳֹͣ����״̬��Ϣ
		 	alarmFlag=regStop(AIParams,AOParams,DO_data);
		//	re_alarm=(enum _alarm)alarmFlag;
			if(alarmFlag!=0)
			{
				DO_onechannel(RE_ALARM,1);
				
				DO_onechannel(HEATPUMP,0);
				Delay_s(1);
				DO_onechannel(REFAN,0);                             //�ط���  
				Delay_s(1);	   
				DO_onechannel(CPUMP,0);	                           //��ѭ����
			}
			//reClever(analogOut,digitalOut);
			runStatus=0;
        }
	 while(runStatus&&panelControl&&((remoteControl&deviceRun)|localControl|System_On))	             //��Һ�㷨
     if(runStatus)
  	 {
		  DeltaCon=DeltaConPC;
		  Tran_Flag=JudgeFlag();
			//���ȿ���ʱ�򣬲Ż����Ũ�ȼ��㡣����û�п��Ļ���Ũ�����趨Ϊ21
			alarmFlag=SS_Re_Transfer(Tran_Flag);             //������Һ
		//	re_alarm=(enum _alarm)alarmFlag;                 //��ȡ������Ϣ
			if(alarmFlag!=0)
			{
				DO_onechannel(RE_ALARM,1);
				
				DO_onechannel(HEATPUMP,0);
				Delay_s(1);
				DO_onechannel(REFAN,0);                             //�ط���  
				Delay_s(1);	   
				DO_onechannel(CPUMP,0);	                           //��ѭ����
			}
	 }
 
   }

}



