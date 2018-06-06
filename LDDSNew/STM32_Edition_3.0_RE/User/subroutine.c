#include <stdio.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "runtimedata.h"
#include "usart.h"
#include "timer.h"

char ReadPortsBuffer[132]={0};
 char WritePortsBuffer[104]={0};
 char ReadPIDBuffer[96]={0};
 char WritePIDBuffer[97]={0};

unsigned int timercnt=0;

char  ReceivedBuffer[200]={0};
char  SentBuffer[175]={0};
char* ReceivedData = ReceivedBuffer + LENGTH;
char* SentData = SentBuffer + LENGTH;

	
char  UISendBuffer[22]={0} ;
char  UIwriteRegister[12]  ={0};
char  UIReceivedBuffer[24]={0};
char* UIReceivedData = UIReceivedBuffer + UILENGTH;
char* UISendData     = UISendBuffer + UILENGTH;

volatile TASKSEL TaskSel = NON;			   //Runtime期任务选择 
volatile UITASKSEL UITaskSel = UINON;	

unsigned int  ReceivedNum = 0  ;
unsigned int  UIReceivedNum = 0 ;

//////////////////////////////////////////////////////////////////////////////

void TIM1_UP_IRQHandler(void)
{
  static int ScanTime = 3;  //端口固有扫描周期15s						 
  if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
  { 
//    data++; 
//	if(data==10) data = 0; 

   	if(TaskSel == NON)
	{
	    ScanTime--;
		if(ScanTime == 0)
	    {
	      readPorts();
	      readPID(ReadPIDBuffer);
	      ScanTime = 3;
     	}
    }
	else
	{
	    ScanTime = 3;
	    DataProcess();	
	}
  }	    	   
 TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);   
}


void TIM2_IRQHandler(void)
{
  static int ScanTime = 3;  				 
  if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  { 
   

   	if(UITaskSel == UINON)
	{
	    ScanTime--;
		if(ScanTime == 0)
	    {
	      readPorts();
	      readPID(ReadPIDBuffer);
	      ScanTime = 3;
     	}
    }
	else
	{
	    ScanTime = 3;
	    UIDataProcess();	
	}
  }	    	   
 TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);   
}


void TIM3_IRQHandler(void)
{     

   if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
   {
      TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);      
     
			
			TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE); 
		    timercnt++;
			if(timercnt==30)	 
			{algorithmstart =1;
			 timercnt=0;
			}
   }
  
}





void USART1_IRQHandler(void)
{
 static unsigned int receivedCount = 0;
 char receivedData;
 char highByte,lowByte;
 char flag = 0; //the status flag of completion of receiving data
 int isTrue = 0;	// Check Code is right?
 int i;

 if(USART_GetFlagStatus(USART1,USART_FLAG_ORE))
 {
   	receivedData = Usart_GetChar(USART1);
	USART_ClearITPendingBit(USART1, USART_FLAG_ORE);
 }

 if(USART_GetITStatus(USART1, USART_IT_RXNE))
 {
    receivedData = Usart_GetChar(USART1); 
	ReceivedBuffer[receivedCount++] = receivedData;
	if(receivedCount >= 2)
	{
	   	highByte = ReceivedBuffer[receivedCount-2];
	    lowByte =  ReceivedBuffer[receivedCount-1];
		if((highByte & lowByte & 0xff) == 0xff)
		 flag = 1;
	}

	if(flag)
	{
	    flag = 0;
		ReceivedNum = receivedCount;
	    receivedCount = 0;  
	    isTrue = PacketHeaderAnalysis(ReceivedBuffer);
		if(isTrue)
		{
			  if(TaskSel == READPORTS)
		  	  {
//			      readPorts();
//				  readCtrlSignal();
//				  sendBufferFill (ReadPortsBuffer);
				  MiddleDataGeneration(165,ReadPortsBuffer,SentData);		  
			      PacketHeaderGeneration(SentBuffer);
			      UsartSendData(165+LENGTH,SentBuffer);
			 	  Usart_SendChar(0xff);
				  Usart_SendChar(0xff);
			  }
			  else if(TaskSel == READPID)
			  {
			      MiddleDataGeneration(96,ReadPIDBuffer,SentData);	
				  	  
			      PacketHeaderGeneration(SentBuffer);
			      UsartSendData(96+LENGTH,SentBuffer);
				  Usart_SendChar(0xff);
				  Usart_SendChar(0xff);
			  }
			  else if(TaskSel == WRITEPORTS)
			  {
			      UsartSendData(ReceivedNum,ReceivedBuffer);
				  for(i=0;i<104;i++)
					 WritePortsBuffer[i] = ReceivedBuffer[i+LENGTH];
			
			  }
			  else if(TaskSel == WRITEPID)
			  {
			     UsartSendData(ReceivedNum,ReceivedBuffer);
				 for(i=0;i<97;i++)
				   WritePIDBuffer[i] = ReceivedData[i];
			  }
		   
		}		
     }	
 }
 //清除中断标志位
 USART_ClearITPendingBit(USART1, USART_IT_RXNE); 
}


void USART2_IRQHandler(void)
{
    static unsigned int receivedCount = 0;
 	char receivedData=0;
//	char highByte,lowByte;
 	char flag = 0; //the status flag of completion of receiving data

 	int isTrue = 0;	// Check Code is right?
 //	int i;


  if(USART_GetFlagStatus(USART2,USART_FLAG_ORE))
    {
    	receivedData = USART_ReceiveData(USART2);
    	USART_ClearITPendingBit(USART2, USART_FLAG_ORE);
     }

  if(USART_GetITStatus(USART2,USART_IT_RXNE))

    {
      receivedData = Usart_GetChar(USART2); 
	  UIReceivedBuffer[receivedCount++] = receivedData;

	  
    }    
  if(receivedCount == 24)
	  {
	  if((UIReceivedBuffer[22]==0x66)&&(UIReceivedBuffer[23]==0x55))
		 flag = 1;
    	}

  if(flag)
	{
	    flag = 0;
		UIReceivedNum = receivedCount;
	    receivedCount = 0;  

	    isTrue = UIPacketAnalysis(UIReceivedBuffer);	//need to change 

		if(isTrue)
		{
			  
			 delay_fun(1,20.0,0,0) ; 		 //IMPT for communication

			  if(UITaskSel == READDATA)
		  	  {
			     	UIPacketHeaderGeneration(UISendBuffer) ;
				    UIsendBufferFill(UISendBuffer) ;
					UartSendData(19+UILENGTH,UISendBuffer);
			 		Uart_SendChar(0x66);
				    Uart_SendChar(0x55);
			
//				   	UartSendData(24,tx1);
			  }
			  else if(UITaskSel == SETDATA)
			  {
					UIregisterFill(UIReceivedBuffer);  
					UIPacketHeaderGeneration(UISendBuffer) ;
					UIMiddleDataGeneration(19,UISendBuffer+UILENGTH);	
					UartSendData(19+UILENGTH,UISendBuffer);
					Uart_SendChar(0x66);
				  	Uart_SendChar(0x55);	 

//				   	UartSendData(24,tx2);
  
//				   
			  }
			  else if(UITaskSel == START)
			  {
			       
                 	UIPacketHeaderGeneration(UISendBuffer) ;
					UIMiddleDataGeneration(19,UISendBuffer+UILENGTH);	
					UartSendData(19+UILENGTH,UISendBuffer);
					Uart_SendChar(0x66);
				  	Uart_SendChar(0x55);
	          		 localControl =1;	

//				   	UartSendData(24,tx3);
				   
			  }
			  else if(UITaskSel == STOP)
			  {
			    	UIPacketHeaderGeneration(UISendBuffer) ;
					UIMiddleDataGeneration(19,UISendBuffer+UILENGTH);
					UartSendData(19+UILENGTH,UISendBuffer);
					Uart_SendChar(0x66);
				  	Uart_SendChar(0x55);
                    UartSendData(19+UILENGTH,UISendBuffer);
                	localControl =0;
		            localDeviceRun =1;

//				   	UartSendData(24,tx4);
			    
			  }
		   
		}		
   

    }

   	  USART_ClearITPendingBit(USART2,USART_IT_RXNE);
}
