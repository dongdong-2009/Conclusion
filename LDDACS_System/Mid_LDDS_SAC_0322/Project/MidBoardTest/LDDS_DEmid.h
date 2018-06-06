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
 float  tempRegisters[16]  = {0};
 float  bufRegisters[16]  = {0};
 float  boardRegisters[3]={0x66,0x22,0x88};
 char   DI_data[4]={0};
float	setPoint[3]={0};

float deAOReset(int port,float par1,float par2,float par3);     
float deDOReset(int port,float par1,float par2,float par3);    




#endif
