/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: portserial.c,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

#include "port.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- static functions ---------------------------------*/
static void prvvUARTTxReadyISR( void );
static void prvvUARTRxISR( void );

/* ----------------------- Start implementation -----------------------------*/

/*
@brief:控制接收和发送状态
@Param：xRxEnable:接收使能  xTxEnable:发送使能
@Retval:None
*/
void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    /* If xRXEnable enable serial receive interrupts. If xTxENable enable
     * transmitter empty interrupts.
     */
	if(xRxEnable)
	{
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);   //使能接收和接收中断
		GPIO_SetBits(GPIOA,GPIO_Pin_11);									 //控制端高电平时，接收模式
	}
	else
	{
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);   //关闭接收和接收中断
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);									//控制端低电平时，发送模式
	}
	
	if(xTxEnable)
	{
		USART_ITConfig(USART1, USART_IT_TC, ENABLE);      //使能发送完成中断
	}
	else
	{
		USART_ITConfig(USART1, USART_IT_TC, DISABLE);     //关闭发送完成中断
	}
}

/*
*@brief:串口初始化
*@ucPORT:串口号
*@ulBaudRate:波特率
*@ucDataBits:数据位
*@eParity:校验位
*@retval:None
*/
BOOL
xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
	(void) ucPORT;       //不修改串口
	(void) ucDataBits;   //不修改数据长度
	(void) eParity;      //不修改校验格式
    
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	
	// 打开GPIOA与USART1的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//串口USART1的IO初始化	GPIOA 9--TX 10--RX 11--DE
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
	
	//串口USART1配置初始化
	USART_DeInit(USART1);
	//串口波特率等信息设置，USART1和USART2配置相同
	USART_InitStruct.USART_BaudRate = ulBaudRate;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStruct);
	USART_Cmd(USART1,ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	//设置中断向量表位置和偏移量  
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);    //向量表位于FLASH，向量表基地址的偏移量为0 
	
	//设置优先级分组：先占优先级和从优先级。
	//输入参数：优先级分组位长度
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  //先占优先级4位，从优先级0位
  
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;          //USART1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
	
	return TRUE;
}

/*
@brief:发送一个字节数据
*/
BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
    /* Put a byte in the UARTs transmit buffer. This function is called
     * by the protocol stack if pxMBFrameCBTransmitterEmpty( ) has been
     * called. */
	USART_SendData(USART1, ucByte);
  return TRUE;
}

/*
@brief：接收数据
*/
BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
    /* Return the byte in the UARTs receive buffer. This function is called
     * by the protocol stack after pxMBFrameCBByteReceived( ) has been called.
     */
	*pucByte = USART_ReceiveData(USART1);
  return TRUE;
}

/* Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
static void prvvUARTTxReadyISR( void )
{
		//mb.c eMBInit函数中 pxMBFrameCBTransmitterEmpty = xMBRTUTransmitFSM 
	
		//发送状态机
		pxMBFrameCBTransmitterEmpty(  );
}

/* Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
static void prvvUARTRxISR( void )
{
		//mb.c eMBInit函数中 pxMBFrameCBByteReceived = xMBRTUReceiveFSM
		
		//接收状态机
    pxMBFrameCBByteReceived(  );
}

void USART1_IRQHandler(void)
{
	//发生接收中断
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		prvvUARTRxISR(); 
		//清除中断标志位
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	
	//发送完成中断
	if(USART_GetITStatus(USART1, USART_IT_TC) == SET)
	{
		prvvUARTTxReadyISR();
		//清除中断标志位
		USART_ClearITPendingBit(USART1, USART_IT_TC);
	}
}
