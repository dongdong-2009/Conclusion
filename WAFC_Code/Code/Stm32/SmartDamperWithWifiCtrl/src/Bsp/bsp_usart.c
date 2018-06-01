#include <stm32f10x.h>
#include "bsp_hwConfig.h"
#include "bsp_usart.h"

//定义系统中是否使用串口作为命令行终端

/**
  ******************************************************************************
  * @file    bsp_usart.c
  * @author :ty
  * @version 1.0.0
  * @date    2013-3-30
  * @brief   This file contains the drivers for the usart
  ******************************************************************************
  *
  */

volatile serial_rxbuf uartRxBuf[MAX_UART_CH_NUM];
volatile serial_txbuf uartTxBuf[MAX_UART_CH_NUM];
  
/**
  * @brief  init the usart buffer
  * @param  None
  * @retval None
  */
void BSP_USART_RxBufInit (volatile serial_rxbuf *buf) 
{
	buf->rear  = 0;
	buf->front = 0;
}

/**
  * @brief   put a character into the buffer
  * @param  buffer and character
  * @retval None
  */
unsigned int BSP_USART_RxBufIn (volatile serial_rxbuf *buf, unsigned char c) 
{
	unsigned int next;

	next = (buf->rear + 1) % SER_RXBUF_SIZE;   /* check if space is available */
	if (next == buf->front)  /* buffer full */
	{               
		return 0;
	}

	buf->buffer[buf->rear] = c;
	buf->rear = next;

	return 1;
}

/**
  * @brief   get a character out of  the buffer
  * @param  buffer and character
  * @retval None
  */
unsigned int BSP_USART_RxBufOut (volatile serial_rxbuf *buf, unsigned char *c) 
{
	unsigned int next;

	if (buf->front == buf->rear) /* check if data is available */
	{                   
		return 0;
	}

	next = (buf->front + 1) % SER_RXBUF_SIZE;

	*c = buf->buffer[buf->front];
	buf->front = next;

	return 1;
}

/**
  * @brief   get the buffer size
  * @param  buffer
  * @retval None
  */
unsigned int BSP_USART_RxBufSize (volatile serial_rxbuf *buf) 
{
	unsigned int used;

	used = (SER_RXBUF_SIZE + buf->rear - buf->front) % SER_RXBUF_SIZE;

	return (used);
}

/**
  * @brief   get the buffer size 
  * @param  None
  * @retval None
  */
unsigned int BSP_USART_GetRxBufSize (uint32_t ch) 
{
	unsigned int size = 0;
	if(ch >= MAX_UART_CH_NUM)
		ch = 0;
	size = BSP_USART_RxBufSize(&uartRxBuf[ch]);
	return size;
}  

/**
  * @brief  init the usart buffer
  * @param  None
  * @retval None
  */
void BSP_USART_TxBufInit (volatile serial_txbuf *buf) 
{
	buf->rear  = 0;
	buf->front = 0;
}

/**
  * @brief   put a character into the buffer
  * @param  buffer and character
  * @retval None
  */
unsigned int BSP_USART_TxBufIn (volatile serial_txbuf *buf, unsigned char c) 
{
	unsigned int next;

	next = (buf->rear + 1) % SER_TXBUF_SIZE;   /* check if space is available */
	if (next == buf->front)  /* buffer full */
	{               
		return 0;
	}

	buf->buffer[buf->rear] = c;
	buf->rear = next;

	return 1;
}

/**
  * @brief   get a character out of  the buffer
  * @param  buffer and character
  * @retval None
  */
unsigned int BSP_USART_TxBufOut (volatile serial_txbuf *buf, unsigned char *c) 
{
	unsigned int next;

	if (buf->front == buf->rear) /* check if data is available */
	{                   
		return 0;
	}

	next = (buf->front + 1) % SER_TXBUF_SIZE;

	*c = buf->buffer[buf->front];
	buf->front = next;

	return 1;
}

/**
  * @brief   get the buffer size
  * @param  buffer
  * @retval None
  */
unsigned int BSP_USART_TxBufSize (volatile serial_txbuf *buf) 
{
	unsigned int used;

	used = (SER_TXBUF_SIZE + buf->rear - buf->front) % SER_TXBUF_SIZE;

	return (used);
}

/**
  * @brief  对串口的缓冲区等进行初始化
  * @param  None
  * @retval None
  */
void BSP_USARTInit()
{
	uint32_t i = 0;
	
	for(i=0;i<MAX_UART_CH_NUM;i++)
	{
		BSP_USART_RxBufInit(&uartRxBuf[i]);
		BSP_USART_TxBufInit(&uartTxBuf[i]);
	}
}


/**
  * @brief  初始化调试串口
  * @param  None
  * @retval None
  */
void BSP_CliDbg_HwInit(uint32_t ulWantedBaud)
{
#ifdef UART_CLI_DB
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(CLI_DB_USART_CLK, ENABLE);
				
	/* Configure USART */
	USART_InitStructure.USART_BaudRate = ulWantedBaud;
	USART_InitStructure.USART_WordLength = CLI_DB_USART_WORDLEN;
	USART_InitStructure.USART_StopBits = CLI_DB_USART_STOPBITS;
	USART_InitStructure.USART_Parity = CLI_DB_USART_PARITY;
	USART_InitStructure.USART_Mode = CLI_DB_USART_MODE;
	USART_InitStructure.USART_HardwareFlowControl = CLI_DB_USART_HARDFLOW;	
	USART_Init(CLI_DB_USART_TYPE, &USART_InitStructure);
	  	
	
	/* Configure Rx as input floating */
	RCC_APB2PeriphClockCmd(CLI_DB_USART_PORT_RX_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = CLI_DB_USART_PORT_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(CLI_DB_USART_PORT_RX_PORT, &GPIO_InitStructure);
	  
	/* Configure Tx as alternate function push-pull */
	RCC_APB2PeriphClockCmd(CLI_DB_USART_PORT_TX_CLK, ENABLE);	
	GPIO_InitStructure.GPIO_Pin =CLI_DB_USART_PORT_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(CLI_DB_USART_PORT_TX_PORT, &GPIO_InitStructure);

	if (CLI_DB_USART_IRQ_ENABLE == ENABLE)
	{
		/* Enable USART Receive and Transmit interrupts */
		USART_ITConfig(CLI_DB_USART_TYPE, CLI_DB_USART_IRQ_TYPE, ENABLE);

		NVIC_InitStructure.NVIC_IRQChannel = CLI_DB_USART_NVIC_IRQ_CHAN;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = CLI_DB_USART_NVIC_IRQ_PRE_PRI;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = CLI_DB_USART_NVIC_IRQ_CMD;

		/* Enable the USARTy Interrupt */
		NVIC_Init(&NVIC_InitStructure);
	}
			
	USART_Cmd( CLI_DB_USART_TYPE, ENABLE );		
#endif
}

/**
  * @brief  初始化wifi串口
  * @param  None
  * @retval None
  */
void BSP_WifiUart_HwInit(uint32_t ulWantedBaud)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable USART clock: UASRT1 -> APB2, USART2-5 -> APB1 */
	RCC_APB1PeriphClockCmd(WIFI_USART_CLK, ENABLE);
				
	/* Configure USART */
	USART_InitStructure.USART_BaudRate = ulWantedBaud;
	USART_InitStructure.USART_WordLength = WIFI_USART_WORDLEN;
	USART_InitStructure.USART_StopBits = WIFI_USART_STOPBITS;
	USART_InitStructure.USART_Parity = WIFI_USART_PARITY;
	USART_InitStructure.USART_Mode = WIFI_USART_MODE;
	USART_InitStructure.USART_HardwareFlowControl = WIFI_USART_HARDFLOW;	
	USART_Init(WIFI_USART_TYPE, &USART_InitStructure);
	  	
	
	/* Configure Rx as input floating */
	RCC_APB2PeriphClockCmd(WIFI_USART_PORT_RX_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = WIFI_USART_PORT_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(WIFI_USART_PORT_RX_PORT, &GPIO_InitStructure);
	  
	/* Configure Tx as alternate function push-pull */
	RCC_APB2PeriphClockCmd(WIFI_USART_PORT_TX_CLK, ENABLE);	
	GPIO_InitStructure.GPIO_Pin = WIFI_USART_PORT_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(WIFI_USART_PORT_TX_PORT, &GPIO_InitStructure);
	
	if (WIFI_USART_IRQ_ENABLE == ENABLE)
	{
		/* Enable USART Receive and Transmit interrupts */
		USART_ITConfig(WIFI_USART_TYPE, WIFI_USART_IRQ_TYPE, ENABLE);

		NVIC_InitStructure.NVIC_IRQChannel = WIFI_USART_NVIC_IRQ_CHAN;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = WIFI_USART_NVIC_IRQ_PRE_PRI;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = WIFI_USART_NVIC_IRQ_CMD;

		/* Enable the USARTy Interrupt */
		NVIC_Init(&NVIC_InitStructure);
	}
			
	USART_Cmd( WIFI_USART_TYPE, ENABLE );		
}

/**
  * @brief  初始化RS485串口
  * @param  None
  * @retval None
  */
void BSP_RS485Uart_HwInit(void)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RS485_USART_CLK, ENABLE);
				
	/* Configure USART */
	USART_InitStructure.USART_BaudRate = RS485_USART_BAUDRATE;
	USART_InitStructure.USART_WordLength = RS485_USART_WORDLEN;
	USART_InitStructure.USART_StopBits = RS485_USART_STOPBITS;
	USART_InitStructure.USART_Parity = RS485_USART_PARITY;
	USART_InitStructure.USART_Mode = RS485_USART_MODE;
	USART_InitStructure.USART_HardwareFlowControl = RS485_USART_HARDFLOW;	
	USART_Init(RS485_USART_TYPE, &USART_InitStructure);
	  	
	/* Configure Rx as input floating */
	RCC_APB2PeriphClockCmd(RS485_USART_PORT_RX_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = RS485_USART_PORT_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(RS485_USART_PORT_RX_PORT, &GPIO_InitStructure);
	  
	/* Configure Tx as alternate function push-pull */
	RCC_APB2PeriphClockCmd(RS485_USART_PORT_TX_CLK, ENABLE);	
	GPIO_InitStructure.GPIO_Pin = RS485_USART_PORT_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(RS485_USART_PORT_TX_PORT, &GPIO_InitStructure);
	
	/* Configure DE as input floating */
	RCC_APB2PeriphClockCmd(RS485_USART_PORT_DE_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = RS485_USART_PORT_DE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(RS485_USART_PORT_DE_PORT, &GPIO_InitStructure);
	
	if (RS485_USART_IRQ_ENABLE == ENABLE)
	{
		/* Enable USART Receive and Transmit interrupts */
		USART_ITConfig(RS485_USART_TYPE, RS485_USART_IRQ_TYPE, ENABLE);

		NVIC_InitStructure.NVIC_IRQChannel = RS485_USART_NVIC_IRQ_CHAN;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = RS485_USART_NVIC_IRQ_PRE_PRI;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = RS485_USART_NVIC_IRQ_SUB_PRI;
		NVIC_InitStructure.NVIC_IRQChannelCmd = RS485_USART_NVIC_IRQ_CMD;

		/* Enable the USARTy Interrupt */
		NVIC_Init(&NVIC_InitStructure);
	}
			
	USART_Cmd( RS485_USART_TYPE, ENABLE );		
}

void BSP_CliDbg_PollSend(unsigned char  *buf, unsigned int len)
{
#ifdef UART_CLI_DB

    while ( len != 0 )
    {
      	CLI_DB_USART_TYPE->DR = (*buf & (uint16_t)0x01FF);
		while((CLI_DB_USART_TYPE->SR & USART_SR_TXE)==0);	    // 等待数据发送完毕
		buf++;
		len--;
    }
#endif
}

/**
  * @brief  send the date from the lower serial buffer
  * @param  
  * @retval the actual length of the data buffer
  */
void BSP_WifiUart_PollSend(unsigned char  *buf, unsigned int len)
{
    while ( len != 0 )
    {
      	WIFI_USART_TYPE->DR = (*buf & (uint16_t)0x01FF);
		while((WIFI_USART_TYPE->SR & USART_SR_TXE)==0);	    // 等待数据发送完毕
		buf++;
		len--;
    }
}

void UART4_IRQHandler(void)
{
#ifdef UART_CLI_DB

	uint8_t txData;
	uint16_t hUSART_SR = UART4->SR;
	uint16_t hUSART_DR = UART4->DR;
	
	/* Valid data received */
	if (hUSART_SR & USART_SR_RXNE) 
	{
		//读DR清除该中断
		BSP_USART_RxBufIn(&(uartRxBuf[CLI_DB_USART]),hUSART_DR);
		
	}
	
	/*data sended*/
	if(hUSART_SR & USART_SR_TXE)
	{
		if(BSP_USART_TxBufOut(&(uartTxBuf[CLI_DB_USART]),&txData) == 0)
		{
			//stop the usart interrupt
			UART4->CR1 &= (~USART_FLAG_TXE);
		}
		else
		{
			UART4->DR = txData;
		}
	}
#endif
}

void USART2_IRQHandler(void)
{
	uint8_t txData;
	uint16_t hUSART_SR = USART2->SR;
	uint16_t hUSART_DR = USART2->DR;
	
	/* Valid data received */
	if (hUSART_SR & USART_SR_RXNE) 
	{
		//读DR清除该中断
		BSP_USART_RxBufIn(&(uartRxBuf[WIFI_UART]),hUSART_DR);
	}
	
	/*data sended*/
	if(hUSART_SR & USART_SR_TXE)
	{
		if(BSP_USART_TxBufOut(&(uartTxBuf[WIFI_UART]),&txData) == 0)
		{
			//stop the usart interrupt
			USART2->CR1 &= (~USART_FLAG_TXE);
		}
		else
		{
			USART2->DR = txData;
		}
	}

}

void USART1_IRQHandler(void)
{
	uint8_t txData;
	uint16_t hUSART_SR = USART1->SR;
	
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE))
	{
		USART_ClearITPendingBit(USART1, USART_FLAG_ORE);//清除相应的标志位
	}	
	
	
	/* Valid data received */
	if (hUSART_SR & USART_SR_RXNE) 
	{
		//读DR清除该中断
		BSP_USART_RxBufIn(&(uartRxBuf[WIFI_UART]),USART1->DR);
	}
	
	/*data sended*/
	if(hUSART_SR & USART_SR_TXE)
	{
		if(BSP_USART_TxBufOut(&(uartTxBuf[WIFI_UART]),&txData) == 0)
		{
			//stop the usart interrupt
			USART1->CR1 &= (~USART_FLAG_TXE);
		}
		else
		{
			USART1->DR = txData;
		}
	}

}

/*----------------------end of file-----------------------------*/

