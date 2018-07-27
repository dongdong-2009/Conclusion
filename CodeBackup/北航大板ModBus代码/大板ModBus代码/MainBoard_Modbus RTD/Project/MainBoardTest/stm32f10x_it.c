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
u16 SumRec=0;//接收到的校验和
u16 SumCal=0;//计算的校验和
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

void USART1_IRQHandler(void)
{ 
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
		if(BusyFlag)return;
		
		TIM_Cmd(TIM2, DISABLE);  //关闭定时器
		TIM_SetCounter(TIM2,0);//清除计时
		
		Uart1_receive_buffer[Uart1_RCnt]=USART_ReceiveData(USART1);		//连续发送
		if(TimerOverFlag) //如果时间溢出 代表新的modbus 数据包开始
		{
			TimerOverFlag=0;
			BegainRxFlag=1;
			Uart1_RCnt++;
		}
		else if(BegainRxFlag)
		{
			Uart1_RCnt++;
		}
  }
  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  { 	 
	 if(Uart1_SCnt<Uart1_SendBuffSize)
	 {
	 	USART_SendData(USART1,Uart1_Send_buffer[Uart1_SCnt++]);
	 }
	 else
	 {
		Uart1_SCnt=0;
		 delay_ms(5);
		 DE1=1;
		 
		USART_ITConfig(USART1,USART_IT_TXE,DISABLE);			  	//发送完成 关闭中断
	 }	 
  }
	TIM_Cmd(TIM2, ENABLE);  //关闭定时器
}
/*ModBus 计算CRC码的步骤为：

(1).预置16位寄存器为FFFFH。称此寄存器为CRC寄存器；

(2).把第一个8位数据与CRC寄存器的低位相异或，把结果放于CRC寄存器；

(3).把寄存器的内容右移一位(朝低位)，用0填补最高位，检查最低位；

(4).如果最低位为0：重复第3步(再次移位)如果最低位为1：CRC寄存器与多项式A001（1010 0000 0000 0001）进行异或；

(5).重复步骤3和4，直到右移8次，这样整个8位数据全部进行了处理；

(6).重复步骤2到步骤5，进行下一个8位数据的处理；

(7).最后得到的CRC寄存器即为CRC码。(CRC码 = CRC_L +CRC_H)

*/
/*****************crc校验**********************************************/

//crc生成函数，并将crc存储在预先定于的数组中

//调用方式crc16（指向数据的指针，需要校验的数据长度）
u16 crc16(u8 *ptr,u8 len)
{
	unsigned long wcrc=0XFFFF;//预置16位crc寄存器，初值全部为1
	int i=0,j=0;//定义计数
	for(i=0;i<len;i++)//循环计算每个数据
		{
			wcrc^=*ptr++;//将八位数据与crc寄存器亦或.指针地址增加，指向下个数据
			for(j=0;j<8;j++)//循环计算数据的
				{
					if(wcrc&0X0001)//判断右移出的是不是1，如果是1则与多项式进行异或。
						{
							wcrc=wcrc>>1^0XA001;//先将数据右移一位再与上面的多项式进行异或
						}
					else//如果不是1，则直接移出
						{
							wcrc>>=1;//直接移出
						}
				}
		}
	return wcrc<<8|wcrc>>8;//低八位在前，高八位在后
}

void delay_nms(u16 time)
{    
	 u16 i=0;  
	 while(time--)
	 {
			i=12000;  //自己定义
			while(i--) ;    
	 }
}

void zh_USART_SendData(u8 ch)
{
   
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//等待上一个字节发送完毕
    USART_SendData(USART1,ch);   
}
//发送len个字节
void zh_USART_SendString(u8* s,u8 len)
{
	  
    int i;
    for(i=0;i<len;i++)
    {
        zh_USART_SendData(s[i]);
    }
}

void DealModBus(void)
{
	
	u16 REG0X03[24];//功能吗0x03对应的寄存器地址为0x0001-0x00019  AD12路+RTD4路+DI8路=24
	u16 REG0X06[16];//功能吗0x06对应的寄存器地址为0x0001-0x00010  DA8路+DO8路=16
	u16 DatLength=0;
	u16 StartRegAdd=0;
	u8 i,sendLen;
	if(Uart1_receive_buffer[0]!=modbus_deviceId)  //核对本机地址
	{
		return; //地址错误
	}
	SumCal=crc16(&Uart1_receive_buffer[0],Uart1_RCnt-2);//计算出校验和
	SumRec=(Uart1_receive_buffer[Uart1_RCnt-2]<<8)+Uart1_receive_buffer[Uart1_RCnt-1];//这里默认接收到的校验和也是低八位在前，高八位在后
	if(SumCal!=SumRec)
	{		
		         //校验和错误
		return ;
	}
	
	for(i=0;i<12;i++)            //AD寄存器地址对于0x0001~0x000C
	{
		REG0X03[i]=AdREG[i];
	}
	for(i=0;i<4;i++)            //RTD寄存器地址对于0x000D~0x0011
	{
		REG0X03[12+i]=RTDREG[i];
	}
	for(i=0;i<8;i++)            //DI寄存器地址对于0x00012~0x0019
	{
		REG0X03[16+i]=DiREG[i];
	}
	
	for(i=0;i<8;i++)            //DA寄存器地址对于0x0001~0x0008
	{
		REG0X06[i]=DAREG[i];
	}
	for(i=0;i<8;i++)            //DO寄存器地址对于0x0009~0x0010
	{
		REG0X06[8+i]=DoREG[i];
	}
	
	StartRegAdd=Uart1_receive_buffer[2]*256+Uart1_receive_buffer[3];//计算其实寄存器地址
	DatLength=Uart1_receive_buffer[4]*256+Uart1_receive_buffer[5];  //计算寄存器地址长度
	 
	
	sendLen=0;
	Uart1_Send_buffer[sendLen++]=modbus_deviceId;
	Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[1];
	
	
	switch(Uart1_receive_buffer[1])     //功能码
	{
		case 0x03:
							if((StartRegAdd+DatLength)>24)return;
							Uart1_Send_buffer[sendLen++]=DatLength*2;
							for(i=0;i<DatLength;i++)                     //读取单个或者多个寄存器
							{
								Uart1_Send_buffer[sendLen++]=REG0X03[StartRegAdd+i]>>8;
								Uart1_Send_buffer[sendLen++]=REG0X03[StartRegAdd+i];
							}
			        break;
		case 0x06:						                                //写单个寄存器
							if(StartRegAdd>=12)return;
							REG0X06[StartRegAdd]=Uart1_receive_buffer[4]*256+Uart1_receive_buffer[5];
							Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[2];
							Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[3];
							Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[4];
							Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[5];
							break;
		default:                           //不支持的功能吗
							Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[2];
							Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[3];
							Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[4];
							Uart1_Send_buffer[sendLen++]=Uart1_receive_buffer[5];
							Uart1_Send_buffer[1]=0x80;//功能码最高位置1
							Uart1_Send_buffer[2]=0x01; //设置异常码为01-无效功能
							break; 
	}
	SumCal=crc16(&Uart1_Send_buffer[0],sendLen);//计算出校验和
	Uart1_Send_buffer[sendLen++]=SumCal>>8;//crc低字节
  Uart1_Send_buffer[sendLen++]=SumCal&0xff;//crc高字节
	
	RS485MOED_S;                              //485输出
  zh_USART_SendString(&Uart1_Send_buffer[0],sendLen);//发送响应帧
  delay_nms(2);
	RS485MOED_R;                              //485接收
	
	for(i=0;i<8;i++)            //DA寄存器地址对于0x0001~0x0008
	{
		DAREG[i]=REG0X06[i];
	}
	for(i=0;i<8;i++)            //DO寄存器地址对于0x0009~0x0010
	{
		DoREG[i]=REG0X06[8+i];
	}
	
}
/**
  * @brief  This function handles USART2 global interrupt request.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
   if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
//	 USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//	 if(Uart2_RCnt<SendBuffSize)
//	 {
//		Uart2_receive_buffer[Uart2_RCnt]=USART_ReceiveData(USART2);		//连续发送
//		Uart2_RCnt++;
//		}
//	else
//			{
//	   	Uart2_RCnt=0;	
//		}
		Uart2_receive_buffer[Uart2_RCnt]=USART_ReceiveData(USART2);		//连续发送
		switch(Uart2_RCnt)
		{
			case 0:if(Uart2_receive_buffer[Uart2_RCnt]=='H')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 1:if(Uart2_receive_buffer[Uart2_RCnt]=='R')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 2:if(Uart2_receive_buffer[Uart2_RCnt]=='T')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 3:if(Uart2_receive_buffer[Uart2_RCnt]=='O')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 4:if(Uart2_receive_buffer[Uart2_RCnt]=='U')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 5:if(Uart2_receive_buffer[Uart2_RCnt]=='S')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 6:if(Uart2_receive_buffer[Uart2_RCnt]=='A')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 7:if(Uart2_receive_buffer[Uart2_RCnt]=='R')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 8:if(Uart2_receive_buffer[Uart2_RCnt]=='T')Uart2_RCnt++;
							else Uart2_RCnt=0;break;
			case 9:if(Uart2_receive_buffer[Uart2_RCnt]=='2'){Uart2_RCnt=0;Uart4852_TestFlag=1;}
							else Uart2_RCnt=0;break;
			default:break;
		}
  }
  
  if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  { 	 
	 if(Uart2_SCnt<Uart2_SendBuffSize)
	 {
	 	USART_SendData(USART2,Uart2_Send_buffer[Uart2_SCnt++]);
	 }
	 else
	 {
		Uart2_SCnt=0;
		 delay_ms(5);
		 DE2=1;
		USART_ITConfig(USART2,USART_IT_TXE,DISABLE);			  	//发送完成 关闭中断
	 }	 
  }
}
void USART3_IRQHandler(void)
{
   if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
//	 USART_ClearITPendingBit(USART3,USART_IT_RXNE);
//	 if(Uart3_RCnt<SendBuffSize)
//	 {
//		Uart3_receive_buffer[Uart3_RCnt]=USART_ReceiveData(USART3);		//连续发送
//		Uart3_RCnt++;
//	}
//	else
//	{
//	   	Uart3_RCnt=0;	
//	}
		
		Uart3_receive_buffer[Uart3_RCnt]=USART_ReceiveData(USART3);		//连续发送
		switch(Uart3_RCnt)
		{
			case 0:if(Uart3_receive_buffer[Uart3_RCnt]=='O')Uart3_RCnt++;break;
			case 1:if(Uart3_receive_buffer[Uart3_RCnt]=='K')Wifi_TestFlag=1;Uart3_RCnt=0;break;
			default:break;
		}
  }
  
  if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
  { 	 
	 if(Uart3_SCnt<Uart3_SendBuffSize)
	 {
	 	USART_SendData(USART3,Uart3_Send_buffer[Uart3_SCnt++]);
	 }
	 else
	 {
		Uart3_SCnt=0;
		USART_ITConfig(USART3,USART_IT_TXE,DISABLE);			  	//发送完成 关闭中断
	 }	 
  }
}



void TIM2_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		   TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
			 TimerOverFlag=1;
			 if(BegainRxFlag==1)
			 {
				 BegainRxFlag=0;
				 BusyFlag=1;
				 DealModBus();                 //modbus处理
				 Uart1_RCnt=0;
				 BusyFlag=0;
			 }
		}
}

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
