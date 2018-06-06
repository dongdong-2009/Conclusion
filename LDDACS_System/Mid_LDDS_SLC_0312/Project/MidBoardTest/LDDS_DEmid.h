#ifndef _LDDS_DEMID_H
#define _LDDS_DEMID_H

//	 u8 count=0;
//u8 TestTimer=0;
//unsigned long int count1=0x00ff;

/* control variable -----------------------------------------------*/

char panelControl=0;
char panelCStatus=0;  
char remoteControl=0;
char localControl=0;
char localDeviceRun=0;
char deviceRun=0;
char runStatus=0;
char alarmFlag=0;	
char algorithmstart=0;

/*  initialization -----------------------------------------------*/
void UART_Configuration(void);
void NVIC_Configuration(void);
void TIM4_Int_Init(u16 arr,u16 psc);
void TIM2_Int_Init(u16 arr,u16 psc);
void LedInit(void);

/*  global register -----------------------------------------------*/

 float  UIregister[12]={0}	;
 float  Registers[16]  = {0};
 float  wRegisters[16]	={0};
 float  ADC_value[6] = {0}; 
 float  ADC_data[6]  = {0};
 char   CurrentflagAI[6]={0};
 float  tempRegisters[16]={0};

 float  DAC_value[4]  = {0};
 float  DAC_data[4]   = {0};
 char   CurrentflagAO[4]={0};

 char   DI_data[4]    = {0};
 char   DO_data[4]    = {0};

 
PARAMS AOParams[4] = {{50.0,0.0},{50.0,0.0},{100.0,0.0},{1,0.0}};
PARAMS AIParams[6] = {{5.0,0},{10.0,0},{10.0,0},{10.0,0},{6,0},{10,0}};
AUTOSEL AOAM[4] = {AUTO,AUTO,AUTO,AUTO};
AUTOSEL REGAM[16] = {AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO,AUTO};

float deAOReset(int port,float par1,float par2,float par3);     
float deDOReset(int port,float par1,float par2,float par3);    




#endif
