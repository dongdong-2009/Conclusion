#include "stm32f10x_it.h"
#include "LDDSPorts.h"
#include "globle.h"
#include "LevelMange.h"

void alarmCheck(void)
{
   u8 type=0;
   if(tempRegisters[CASETRANSFER]!=0)
   {
   	
		switch(type)
		{
	  		case 0x01:
	    		//WSTHighLevelST(); 
				break;
		  	 
	  		case 0x02: 
	    		SSTHighLevelST(); 
				break;
	   
	  		case 0x03: 
	  			BufTLowLevelST();  
				break;
	  
	  		case 0x04:
	  			DeTHighLevelST();  
				break;

	  		default:
			break;
	  }
   }
   else if(tempRegisters[CASEEMERGENCY]!=0)
   {
   	  	switch(type)
	{
	  case 0x01:
	     DeTFullAlm();
		break;
	   	 
	  case 0x02: 
	    DeTEmptyAlm();
		break;
	   
	  case 0x03: 
	  	BufTEmptyAlm();
		break;
	  
	  case 0x04:
	    ReTFullAlm();
		break;

	  case 0x05: 
	    WSTFullEm();
		break;

	  case 0x06:
	    SSTFullEm();     
		break;
			  
	  case 0x07: 
	    SSTEmptyEm();     
		break;

	  case 0x08: 
	  	DeTFullWSTHighEm();  
		break;	  
		
	  case 0x09:
	    DeTFullEm();    
		break;

	  case 0x0A:  
//	   SSTLowLevel();   
		break;
	
	  }
   
   }
 

}


//void  WSTHighLevelST(void)
//{

//}
 
void  SSTHighLevelST(void)
{
   if(tempRegisters[LOWBUF]==0x66)
   {
   	  if(tempRegisters[SSTLEVEL]>=SHA1)
	  	  DO_onechannel(TSF_VAV,1);
	  while(tempRegisters[BUFLEVEL]<BHA1)
		  DO_onechannel(TSF_VAV,0);
   
   }
} 

void  BufTLowLevelST(void) 
{
	 if(tempRegisters[BUFLEVEL]<=BHA1)
	   DO_onechannel(TSF_VAV,1);
	  while(tempRegisters[BUFLEVEL]<=BHA2)
	   DO_onechannel(TSF_VAV,0);
}

void  DeTHighLevelST(void) 
{
     if(tempRegisters[DELEVEL]>DHA1)
	   DO_onechannel(TSF_PUMP,1);
	 while(tempRegisters[BUFLEVEL]<=BHA2)
	   DO_onechannel(TSF_PUMP,0);

}
void  DeTFullAlm(void)
{
  if(ADC_value[DELEVEL]>DHA3)
	  {
	  	DO_onechannel(TSF_VAV,0);
	    DO_onechannel(TSF_PUMP,0);
	  }

}	   	 
void  DeTEmptyAlm(void)
{
     if(tempRegisters[DELEVEL]<DLA)
	  {
	  	DO_onechannel(TSF_VAV,0);
	    DO_onechannel(TSF_PUMP,0);
	  }
}	   
void  BufTEmptyAlm(void)
{
	 if(tempRegisters[BUFLEVEL]>BHA2)
	  {
	  	DO_onechannel(TSF_VAV,0);
	    DO_onechannel(TSF_PUMP,0);
	  }
}	  
void  ReTFullAlm(void)
{
	if(tempRegisters[RELEVEL]>RHA2)
	  {
	  	DO_onechannel(TSF_VAV,0);
	    DO_onechannel(TSF_PUMP,0);
	  }
}

//void  WSTFullEm(void)
//{
//
//}

void  SSTFullEm(void)     
{      
  if(tempRegisters[BUFLEVEL]>SHA1)
  {
	  DO_onechannel(TSF_VAV,0);
	  DO_onechannel(TSF_PUMP,0);
  }

}			  
void  SSTEmptyEm(void)     
{

}
void  DeTFullWSTHighEm(void)  
{

}		
void  DeTFullEm(void)    
{
   if(tempRegisters[DELEVEL]>DHA2)
   	  DO_onechannel(TSF_PUMP,1);
   
   while((tempRegisters[WSTLEVEL]>WHA1)|(tempRegisters[DELEVEL]<DLA))
   	  DO_onechannel(TSF_PUMP,0);



}
//void  SSTLowLevel(void)   
//{
//
//}

