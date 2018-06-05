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
#include "logic.h"
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

//num---format---address---pattern---autom     发送53个字节数据
//autom---automanual,数据运行状态，是自动发送，还是手动发送 
//初始化
frame frm=
{
	0x00,
  0x00,
  0x00,
  0x00,
  0x00   
};

//num---format---pattern         发送24个字节数据
//初始化
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

//定时器1，定时清空USART1中数据
void TIM1_UP_IRQHandler(void)
{
	u8 i;
  if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)    //判断定时器1中断是否发生
  {
		TIM_ClearITPendingBit(TIM1,TIM_FLAG_Update); 	   //清楚中断待处理位
	  nCount++;
	  if(nCount==0x17)                                 //定时时间                 
	  {
			nCount=0;
	    for(i=0;i<53;i++)                              //清空USART1中换缓存数据
			{
				usart1_buff[i]=0x00; 
			}
			frm.num=0;
			TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);    //关闭定时器1中断
	  }		
  }  
}

//定时器2，定时清空USART2中数据
/*定时器2中断处理*/
void TIM2_IRQHandler(void)
{
	u8 i;
  if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)         //判断定时器2中断是否发生
  {
		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);          //清除定时器2中断请求位
	  mCount++;
	  if(mCount==0x50)                                      //定时时间计算
	  {
			mCount=0;
	    for(i=0;i<24;i++)                                   //清空USART2中数据
			{
				usart2_buff[i]=0x00; 
			}
      disfrm.num=0;  		
      TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);        //禁止定时器2中断使能
	  }	 
  }
}


/*定时器3中断处理，主要处理串口接收数据*/
void TIM3_IRQHandler(void)
{     
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)      //判断定时器3中断是否发生
  {
		TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);       //清除定时器3中断请求位
		dataProcess();                                     //大板数据处理
		dataResponseLocal();                               //小板数据处理
		//concentration=ConCalculate();
  }  
}

/*串口1中断处理*/
void USART1_IRQHandler(void)
{
	u8 i;
	
  if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)         //检查USART溢出错误标志位
  {
		USART_ClearFlag(USART1,USART_FLAG_ORE);                   //读SR其实就是清除标志   清除USART待处理中断标志位，清除溢出错误标志位
    USART_ReceiveData(USART1);                                //返回USART1最近接收到的数据    
  }
	
  if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)          //检查USART接收数据寄存器非空标志位
  {
		usart1_buff[frm.num]=USART_ReceiveData(USART1);           //将USART中数据存放在缓存中
    frm.num++;
    if(frm.num==1)
    {
			TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);              //使能定时器1中断，清空串口1缓存中数据     
    }
    USART_ClearITPendingBit(USART1,USART_IT_RXNE);            //清除接收中断标志位
  }
	
	//接收到完整的数据
  if(frm.num==53)
  {
		frm.num=0;
    frm.format=1;
		
		//帧头或帧尾
    if((usart1_buff[0]!=0x55)||(usart1_buff[1]!=0x66)||(usart1_buff[51]!=0x66)||(usart1_buff[52]!=0x55))
			frm.format=0;
		
		//地址信息正确
    if((usart1_buff[2]==address1[0])&&(usart1_buff[3]==address1[1])&&(usart1_buff[4]==address1[2])&&(usart1_buff[5]==address1[3])&&(usart1_buff[6]==address1[4])&&(usart1_buff[7]==address1[5]))
			frm.address=1;
	 	else
	    frm.format=0;
		
		//如果接收的数据表为transfer data，DE和RE之间的数据交互
    if(usart1_buff[9]==0x57)
		  frm.pattern=5;  
		else
		  frm.format=0;
		
		//检查Local还是remote
    if(usart1_buff[49]==0x00)
      frm.autom=0;
	  else if(usart1_buff[49]==0x01)
	    frm.autom=1;
	  else
	    frm.format=0; 
		
		//数据正确且为transfer data 
    if(frm.format)
    {
			if(frm.pattern==5)
	    {
				if(frm.address==1)
				{
					for(i=0;i<53;i++) 
	        dataCbuff[i]=usart1_buff[i];     //将串口缓存中数据 转存到dataCbuff中
				}
		  }
     }
				 
		 //数据正确，但是LOCAL模式
    if(frm.format&&(!frm.autom))
    {
			Usart_Tx();                    //使能数据发送位
      usart_senddata(TX9);           //发送数据TX9
      Usart_Rx();                    //使能数据接收位，使串口时刻处于接收状态
    }
  }
	//SendInformation();
}

/*串口1发送数据*/
void usart_senddata(u8 arr[])
{	
	u8 i;
  for(i=0;i<53;i++)
	{
		USART_ClearFlag(USART1,USART_FLAG_TC);                        //清除数据发送完成标志位
	  USART_SendData(USART1,arr[i]);                                //发送数据
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	}
}

/*串口2中断处理*/
void USART2_IRQHandler(void)
{
	u8 i;
  if(USART_GetFlagStatus(USART2,USART_FLAG_ORE)==SET)                   //检查USART溢出错误标志位      
  {
		USART_ClearFlag(USART2,USART_FLAG_ORE);                             //读SR其实就是清除标志  清空USART溢出错误标志位
    USART_ReceiveData(USART2);		                                      //串口2接收数据
  }
	
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)                    //串口接收数据寄存器非空标志位
  {
		usart2_buff[disfrm.num]=USART_ReceiveData(USART2);                  //将数据存储在串口2数据缓存中
    disfrm.num++;
    if(disfrm.num==1)
    {
			TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);                        //使能定时器2，清空串口2数据缓存
    }
    USART_ClearITPendingBit(USART2,USART_IT_RXNE);                      //清除串口2接收数据非空标志位
  }   
	//接收数据完成
  if(disfrm.num==24)
  {
		disfrm.num=0;
    disfrm.format=1;
		
		//帧头或帧尾出错
    if((usart2_buff[0]!=0x55)||(usart2_buff[1]!=0x66)||(usart2_buff[22]!=0x66)||(usart2_buff[23]!=0x55))
			disfrm.format=0;
		
		//判断数据类型
    if(usart2_buff[2]==0x01)
		  disfrm.pattern=1;
		else if(usart2_buff[2]==0x02)
		  disfrm.pattern=2;
		else if(usart2_buff[2]==0x03)
		{ 
			disfrm.pattern=3;
			localControl=1; 		
		}
    else if(usart2_buff[2]==0x04)
		{
			disfrm.pattern=4;
			localControl=0; 
		}
		else
		  disfrm.format=0;
    if(CRC_check(usart2_buff,USTART,USTOP)!=usart2_buff[21])
			disfrm.format=0;
    if(disfrm.format)
		{
			for(i=0;i<24;i++) 
      { 
				dataUbuff[i]=usart2_buff[i];                        //串口2数据转存
		  }
		}
		if(disfrm.format)
    {
			Uart_Tx();                                           //使能串口数据发送位
      i=disfrm.pattern;
      switch(i)
      {
				//case 1: usart2_senddata(tx1);delay_ms(100);usart2_senddata2(TX1);delay_ms(100);usart2_senddata2(TX2);break;
				case 1: usart2_senddata(tx1);delay_ms(500);usart2_senddata2(TX1);delay_ms(500);usart2_senddata2(TX2);break;            //发送小板和大板数据
        case 2: usart2_senddata(tx2);break;
        case 3: usart2_senddata(tx3);break;		            //start
        case 4: usart2_senddata(tx4);break;               //stop      
        default:break;
      }
      Usart_Rx();                                         //使能串口数据接收位，使串口时刻处于接收装填
    } 
  }    
}

/*串口2发送数据*/
//发送小板程序
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

//发送大板程序
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

//void SendInformation()
//{
//	int Format=1;                        //数据格式
//	int Address=0;                       //数据地址
//	
//	//判断数据帧头帧尾
//	if((TX9[0]!=0x55)||(TX9[1]!=0x66)||(TX9[51]!=0x66)||(TX9[52]!=0x55))
//		Format=0;		
//  
//	//判断数据地址信息
//	if((TX9[2]==address1[0])&&(TX9[3]==address1[1])&&(TX9[4]==address1[2])&&(TX9[5]==address1[3])&&(TX9[6]==address1[4])&&(TX9[7]==address1[5]))
//		Address=1;
//	else
//		Format=0;	
//	
//	if(Format==1)
//	{
//		//数据为Transfer Data,即RE和DE之间交互通信的数据
//		if(TX9[9]==0x57)
//		{
//			if(Address==1)
//			{
//				Usart_Tx();                    //使能数据发送位
//				usart_senddata(TX9);           //发送数据TX9
//				Usart_Rx();                    //使能数据接收位，使串口时刻处于接收状态				
//			}
//		}
//	}  
//}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
