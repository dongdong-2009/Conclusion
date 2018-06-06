/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "Globle.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "delay.h"

u8 nCount;
u8 mCount;
u8 UIreceivedCount = 0;
u8 receivedCount = 0;
u8 receiveFlag=0 ;
u8 UIreceiveFlag=0 ;
u16 SumRec=0;//接收到的校验和
u16 SumCal=0;//计算的校验和
char ReadPortsBuffer[132]={0};
char WritePortsBuffer[104]={0};
char ReadPIDBuffer[96]={0};
char WritePIDBuffer[97]={0};

unsigned int timercnt=0;

char  ReceivedBuffer[68]={0};
char  SentBuffer[97]={0};
char* ReceivedData = ReceivedBuffer + LENGTH;
char* SentData = SentBuffer + LENGTH;

	
char  UISendBuffer[24]={0} ;
char  ReqSubBuffer[24]={0x55,0x66,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0x12,0x66,0x55} ;
char  ReqSysBuffer[24]={0x55,0x66,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0x12,0x66,0x55} ;

char  UIwriteRegister[12]  ={0};
char  UIReceivedBuffer[24]={0};		 
char  UIReceivedBufferTemp[24]={0};

int counttemp=0;	 
char* UIReceivedData = UIReceivedBuffer + UILENGTH;
char* UISendData     = UISendBuffer + UILENGTH;

void  Usart_SendChar(char dat);
char  Usart_GetChar(USART_TypeDef* USARTx);
void  UsartSendData(int num,char* sendbuffer);
void  UartSendData(int num,char* sendbuffer) ;
void  Uart_SendChar(char dat);

volatile TASKSEL TaskSel = NON;			   //Runtime期任务选择 
u8 UITaskSel = 0;	

unsigned int  ReceivedNum = 0  ;
unsigned int  UIReceivedNum = 0 ;

//////////////////////////////////////////////////////////////////////////////
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

void TIM1_UP_IRQHandler(void)
{
  static int ScanTime = 2;  //端口固有扫描周期15s						 
  if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
  { 
	 TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);   

	if(TaskSel == NON)
	{
	    ScanTime--;
		if(ScanTime == 0)
	    {
	      readPorts();
	      readPID(ReadPIDBuffer);
	      ScanTime = 2;
     	}
    }
	else
	{
	    if(receiveFlag)  	
    	{
	      receiveFlag=0;
	      DataProcess();
		  ScanTime = 2;

	    }
	   
	}
  }	    	   
}


void TIM2_IRQHandler(void)
{
				 
  if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  { 
   	 TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update); 
//    if(counttemp==1000)  	
//	{
//	   UIreceiveFlag=0;
//	   UIDataProcess();
//
//	   	counttemp=0;
//	}
//		   counttemp++;
  }	    	   

   
}


void TIM3_IRQHandler(void)
{     

   if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
   {
      TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);      
    
         	algorithmstart =1;
			timercnt=0;
			receivedCount = 0; 
	  TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE); 

   }
  
}

/*定时器4中断处理*/
void TIM4_IRQHandler(void)
{
    u8 i;

   if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
   {
      TIM_ClearITPendingBit(TIM4,TIM_FLAG_Update); 
	  
	  mCount++;
	  if(mCount==0x50)
	  {
	     mCount=0;
	     for(i=0;i<24;i++)
		 {
   	       UIReceivedBuffer[i]=0x00; 

		 }
          UIreceivedCount=0; 
		
 		
         TIM_ITConfig(TIM4, TIM_IT_Update, DISABLE); 
	  }	 
   }
}

void USART1_IRQHandler(void)
{
// static unsigned int receivedCount = 0;
 char receivedData;
// char highByte,lowByte;
// char flag = 0; //the status flag of completion of receiving data
 int isTrue = 0;	// Check Code is right?
 //int i;
 
 if(USART_GetFlagStatus(USART1,USART_FLAG_ORE))
 {
   	receivedData = Usart_GetChar(USART1);
	USART_ClearITPendingBit(USART1, USART_FLAG_ORE);

 }

 if(USART_GetITStatus(USART1, USART_IT_RXNE))
 {

	  receivedData = USART_ReceiveData(USART1); 
	  ReceivedBuffer[receivedCount++] = receivedData;
	  
	  if(receivedCount==1)
        {
            TIM_Cmd(TIM1, DISABLE);  
	        TIM_SetCounter(TIM1,0);
		   	TIM_Cmd(TIM1, ENABLE);  
        }
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);

   } 

  if(receivedCount == 12)
   {
	  if((ReceivedBuffer[0]==0x55)&&(ReceivedBuffer[1]==0x66)&&(ReceivedBuffer[10]==0x66)&&(ReceivedBuffer[11]==0x55))
	    	  isTrue = PacketHeaderAnalysis(ReceivedBuffer);
	}	
 
  if(receivedCount == 68)
   {
	  if((ReceivedBuffer[0]==0x55)&&(ReceivedBuffer[1]==0x77)&&(ReceivedBuffer[66]==0x77)&&(ReceivedBuffer[67]==0x55))
	    	  isTrue = PacketHeaderAnalysis(ReceivedBuffer);
   }
	if(isTrue)
	{
		 ReceivedNum = receivedCount;
	     receivedCount = 0; 
		 receiveFlag=1;
     	 isTrue=0;

	}	

 //清除中断标志位
    DE1=1;
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 


}






/**
  * @brief  This function handles USART2 global interrupt request.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
 	char receivedData=0;
	char isTrue=0;
//	char highByte,lowByte;
 	char flag = 0,i=0; //the status flag of completion of receiving data

// 	int isTrue = 0;	// Check Code is right?

  
    if(USART_GetFlagStatus(USART2,USART_FLAG_ORE)==SET)
    {
        USART_ClearFlag(USART2,USART_FLAG_ORE); //读SR其实就是清除标志
        USART_ReceiveData(USART2);		
    }

   if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
    {
	  receivedData = USART_ReceiveData(USART2); 
	  UIReceivedBufferTemp[UIreceivedCount++] = receivedData;
	  
	  if(UIreceivedCount==1)
        {
             TIM_Cmd(TIM2, DISABLE);  //关闭定时器
	         TIM_SetCounter(TIM2,0);//清除计时
		     TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
        }
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
    }    

  if(UIreceivedCount == 24)
   {

	  UIReceivedNum = UIreceivedCount;
	  UIreceivedCount = 0; 

	  if((UIReceivedBufferTemp[0]==0x55)&&(UIReceivedBufferTemp[1]==0x66)&&(UIReceivedBufferTemp[22]==0x66)&&(UIReceivedBufferTemp[23]==0x55))
		{
		  flag = 1;
		}
      if(flag)
	        isTrue =  CheckUIReceivedData(UIReceivedBufferTemp)  ;
    
     if(flag&isTrue)
    	{
	      	for(i=0;i<24;i++) 
                UIReceivedBuffer[i]=UIReceivedBufferTemp[i];
		      	
		    UIDataProcess();
			isTrue=0;		
			flag = 0;
			UIreceiveFlag=1;
	    	UIreceivedCount = 0;  
	   }
	
    }	
 
   //  USART_ITConfig(USART2,USART_IT_TXE,DISABLE);			  	//发送完成 关闭中断
	DE2=1;
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 
    TIM_Cmd(TIM2, ENABLE);  

}


/*********************************************************************************************************
* Functoin name:       Usart_SendChar
* Descriptions:        USART发送一个字符
* input paraments:     USARTx：用到的串口号
*						dat：需要发送的数据
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/

void Usart_SendChar(char dat)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//等待上一个字节发送完毕
    USART_SendData(USART1,dat);   
}

/*********************************************************************************************************
* Functoin name:       Uart_SendChar
* Descriptions:        UART发送一个字符
* input paraments:     UARTx：用到的串口号
*						dat：需要发送的数据
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/
void Uart_SendChar(char dat)
{  
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);//等待上一个字节发送完毕
   USART_ClearFlag(USART2,USART_FLAG_TC);
    USART_SendData(USART2,dat);   
}


/*********************************************************************************************************
* Functoin name:       void UsartSendData(int num,char* sendbuffer)
* Descriptions:        USART发送num个字符
* input paraments:     num：发送数据的个数
*					   sendbuffer：待发送数据的缓存数组
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/

void UsartSendData(int num,char* sendbuffer)
{
   int i;
   for(i=0;i<num;i++)
   {
     Usart_SendChar(sendbuffer[i]); 
   }
}


/*********************************************************************************************************
* Functoin name:       void UartSendData(int num,char* sendbuffer)
* Descriptions:        USART发送num个字符
* input paraments:     num：发送数据的个数
*					   sendbuffer：待发送数据的缓存数组
* output paraments:    无    
* Returned values:     无
*********************************************************************************************************/
void UartSendData(int num,char* sendbuffer)
{
   int i;
   for(i=0;i<num;i++)
   {
     Uart_SendChar(sendbuffer[i]); 
   }
}


/*********************************************************************************************************
* Functoin name:       Usart_GetCahr
* Descriptions:        USART接收一个字符
* input paraments:     USARTx：用到的串口号
* output paraments:    无    
* Returned values:     dat:接收到的数据
*********************************************************************************************************/
char Usart_GetChar(USART_TypeDef* USARTx)
{
	char dat;
//	while(!USART_GetFlagStatus(USARTx,USART_FLAG_RXNE));
	dat = (char)(USART_ReceiveData(USARTx)&0xff);	
	return dat;		
}


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
