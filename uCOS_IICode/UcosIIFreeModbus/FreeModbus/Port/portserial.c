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
@brief:���ƽ��պͷ���״̬
@Param��xRxEnable:����ʹ��  xTxEnable:����ʹ��
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
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);   //ʹ�ܽ��պͽ����ж�
		GPIO_SetBits(GPIOA,GPIO_Pin_11);									 //���ƶ˸ߵ�ƽʱ������ģʽ
	}
	else
	{
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);   //�رս��պͽ����ж�
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);									//���ƶ˵͵�ƽʱ������ģʽ
	}
	
	if(xTxEnable)
	{
		USART_ITConfig(USART1, USART_IT_TC, ENABLE);      //ʹ�ܷ�������ж�
	}
	else
	{
		USART_ITConfig(USART1, USART_IT_TC, DISABLE);     //�رշ�������ж�
	}
}

/*
*@brief:���ڳ�ʼ��
*@ucPORT:���ں�
*@ulBaudRate:������
*@ucDataBits:����λ
*@eParity:У��λ
*@retval:None
*/
BOOL
xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
	(void) ucPORT;       //���޸Ĵ���
	(void) ucDataBits;   //���޸����ݳ���
	(void) eParity;      //���޸�У���ʽ
    
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	
	// ��GPIOA��USART1��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//����USART1��IO��ʼ��	GPIOA 9--TX 10--RX 11--DE
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
	
	
	//����USART1���ó�ʼ��
	USART_DeInit(USART1);
	//���ڲ����ʵ���Ϣ���ã�USART1��USART2������ͬ
	USART_InitStruct.USART_BaudRate = ulBaudRate;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStruct);
	USART_Cmd(USART1,ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	//�����ж�������λ�ú�ƫ����  
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);    //������λ��FLASH�����������ַ��ƫ����Ϊ0 
	
	//�������ȼ����飺��ռ���ȼ��ʹ����ȼ���
	//������������ȼ�����λ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  //��ռ���ȼ�4λ�������ȼ�0λ
  
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;          //USART1�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
	
	return TRUE;
}

/*
@brief:����һ���ֽ�����
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
@brief����������
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
		//mb.c eMBInit������ pxMBFrameCBTransmitterEmpty = xMBRTUTransmitFSM 
	
		//����״̬��
		pxMBFrameCBTransmitterEmpty(  );
}

/* Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
static void prvvUARTRxISR( void )
{
		//mb.c eMBInit������ pxMBFrameCBByteReceived = xMBRTUReceiveFSM
		
		//����״̬��
    pxMBFrameCBByteReceived(  );
}

void USART1_IRQHandler(void)
{
	//���������ж�
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		prvvUARTRxISR(); 
		//����жϱ�־λ
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	
	//��������ж�
	if(USART_GetITStatus(USART1, USART_IT_TC) == SET)
	{
		prvvUARTTxReadyISR();
		//����жϱ�־λ
		USART_ClearITPendingBit(USART1, USART_IT_TC);
	}
}
