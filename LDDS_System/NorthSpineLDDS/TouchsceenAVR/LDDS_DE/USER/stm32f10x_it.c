/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

frame frm=
{
    0x00,
    0x00,
    0x00,
    0x00,
    0x00   
};
disframe disfrm=
{
    0x00,
    0x00,
    0x00
};

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
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

void TIM1_UP_IRQHandler(void)
{
    u8 i;

   if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
   {
      TIM_ClearITPendingBit(TIM1,TIM_FLAG_Update); 
	  
	  nCount++;
	  if(nCount==0x17)
	  {
	     nCount=0;
	     for(i=0;i<53;i++)
		 {
		    usart1_buff[i]=0x00; 
		 }
		 frm.num=0;
         TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE); 
	  }		
		 
   }
  
}

/*定时器2中断处理*/
void TIM2_IRQHandler(void)
{
    u8 i;

   if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
   {
      TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update); 
	  
	  mCount++;
	  if(mCount==0x50)
	  {
	     mCount=0;
	     for(i=0;i<24;i++)
		 {
		    usart2_buff[i]=0x00; 
		 }
         disfrm.num=0;  		
         TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE); 
	  }	 
   }
}

/*定时器3中断处理，主要处理串口接收数据*/
void TIM3_IRQHandler(void)
{     

   if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
   {
      TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);      
      dataProcess();
	  dataResponseLocal();
	//  Usart_Rx();
      usart_senddata(TX9);
    //  Usart_Tx();
   }
  
}

/*串口1中断处理*/
void USART1_IRQHandler(void)
{
    u8 i;
    if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)
    {
        USART_ClearFlag(USART1,USART_FLAG_ORE); //读SR其实就是清除标志
        USART_ReceiveData(USART1);        
    }
    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
    {
        usart1_buff[frm.num]=USART_ReceiveData(USART1);

        frm.num++;
        if(frm.num==1)
        {
            TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);             
        }
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);        
    }
    if(frm.num==53)
    {
        frm.num=0;
        frm.format=1;
        if((usart1_buff[0]!=0x55)||(usart1_buff[1]!=0x66)||(usart1_buff[51]!=0x66)||(usart1_buff[52]!=0x55))
            frm.format=0;
        if((usart1_buff[2]==address1[0])&&(usart1_buff[3]==address1[1])&&(usart1_buff[4]==address1[2])&&(usart1_buff[5]==address1[3])&&(usart1_buff[6]==address1[4])&&(usart1_buff[7]==address1[5]))
		    frm.address=1;
	 	else
	        frm.format=0;
        if(usart1_buff[9]==0x57)
		    frm.pattern=5;
		else
		    frm.format=0;
        if(usart1_buff[49]==0x00)
         	frm.autom=0;
	    else if(usart1_buff[49]==0x01)
	        frm.autom=1;
	    else
	        frm.format=0; 
        if(CRC_check(usart1_buff,CSTART,CSTOP)!=usart1_buff[50])
            frm.format=0;
        if(frm.format)
        {
           	if(frm.pattern==5)
	        {
			     if(frm.address==1)
				 {
				 	for(i=0;i<53;i++) 
	                	dataCbuff[i]=usart1_buff[i];
				 }
		    }
        }
    }
}

/*串口1发送数据*/
void usart_senddata(u8 arr[])
{
    u8 i;
    for(i=0;i<53;i++)
	{
	      USART_ClearFlag(USART1,USART_FLAG_TC);
	      USART_SendData(USART1,arr[i]);
		  while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	}
}

/*串口4中断处理*/
void USART2_IRQHandler(void)
{
    u8 i;

    if(USART_GetFlagStatus(USART2,USART_FLAG_ORE)==SET)
    {
        USART_ClearFlag(USART2,USART_FLAG_ORE); //读SR其实就是清除标志
        USART_ReceiveData(USART2);		
    }
    if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
    {
        usart2_buff[disfrm.num]=USART_ReceiveData(USART2);
        disfrm.num++;
        if(disfrm.num==1)
        {
            TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
        }
        USART_ClearITPendingBit(USART2,USART_IT_RXNE);
    }    

    if(disfrm.num==24)
    {
        disfrm.num=0;
        disfrm.format=1;
        if((usart2_buff[0]!=0x55)||(usart2_buff[1]!=0x66)||(usart2_buff[22]!=0x66)||(usart2_buff[23]!=0x55))
            disfrm.format=0;
        if(usart2_buff[2]==0x01)
		    disfrm.pattern=1;
		else if(usart2_buff[2]==0x02)
		    disfrm.pattern=2;
		else if(usart2_buff[2]==0x03)
		   { disfrm.pattern=3;
		   		   	 localControl=1;  		
		   }
        else if(usart2_buff[2]==0x04)
		    {disfrm.pattern=4; 
					   	 localControl=0; 
			}
		else
		    disfrm.format=0;
        if(CRC_check(usart2_buff,USTART,USTOP)!=usart2_buff[21])
            disfrm.format=0;
        if(disfrm.format)
        {
            for(i=0;i<24;i++) 
               { dataUbuff[i]=usart2_buff[i];
				  }

        }

        if(disfrm.format)
        {
            Uart_Tx();
            i=disfrm.pattern;
            switch(i)
            {
				case 1: usart2_senddata(tx1);delay_ms(500);usart2_senddata2(TX1);delay_ms(500);usart2_senddata2(TX2);break;
                case 2: usart2_senddata(tx2);break;
                case 3: usart2_senddata(tx3);break;	//start
                case 4: usart2_senddata(tx4);break; //stop
            }
            Uart_Rx();
    
        } 

    }
    
}

/*串口4发送数据*/
void usart2_senddata(u8 arr[])
{
    u8 i;
    for(i=0;i<24;i++)
	{
	      USART_ClearFlag(USART2,USART_FLAG_TC);
          delay_us(1000);
	      USART_SendData(USART2,arr[i]);
		  while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	}
}

void usart2_senddata2(u8 arr[])
{
    u8 i;
    for(i=0;i<53;i++)
	{
	      USART_ClearFlag(USART2,USART_FLAG_TC);
          delay_us(1000);
	      USART_SendData(USART2,arr[i]+0x33);
		  while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	}
}


   	   
	   
	  
	  

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
