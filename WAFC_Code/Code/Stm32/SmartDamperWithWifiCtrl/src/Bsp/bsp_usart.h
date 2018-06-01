#ifndef _BSP_USART_H
#define _BSP_USART_H

/*-------------------- global variables-------------------------*/
#undef UART_CLI_DB	

#ifdef UART_CLI_DB
#define MAX_UART_CH_NUM			3
#define WIFI_UART		0
#define CLI_DB_USART 	1
#define RS485_UART		2
#else
#define MAX_UART_CH_NUM			2
#define WIFI_UART		0
#define RS485_UART		1
#endif

#define COMM_BUF_SIZE		512

#define SER_RXBUF_SIZE COMM_BUF_SIZE
typedef struct _Serial_RxBuffer
{
	unsigned int  front;          //对列头指针,输出元素
	unsigned int  rear;			  //队列尾指针，输入元素
	unsigned char buffer[SER_RXBUF_SIZE];
}serial_rxbuf;
extern volatile serial_rxbuf uartRxBuf[MAX_UART_CH_NUM];

#define SER_TXBUF_SIZE 	COMM_BUF_SIZE
typedef struct _Serial_TxBuffer
{
	unsigned int  front;          //对列头指针,输出元素
	unsigned int  rear;			  //队列尾指针，输入元素
	unsigned char buffer[SER_TXBUF_SIZE];
}serial_txbuf;
extern volatile serial_txbuf uartTxBuf[MAX_UART_CH_NUM];


/*----------------------------extern functions---------------------*/
void BSP_USART_RxBufInit (volatile serial_rxbuf *); 
unsigned int BSP_USART_RxBufIn (volatile serial_rxbuf *, unsigned char);
unsigned int BSP_USART_RxBufOut (volatile serial_rxbuf *, unsigned char *); 
unsigned int BSP_USART_RxBufSize (volatile serial_rxbuf *); 
unsigned int BSP_USART_GetRxBufSize (uint32_t);

void BSP_USART_TxBufInit (volatile serial_txbuf *); 
unsigned int BSP_USART_TxBufIn (volatile serial_txbuf *, unsigned char);
unsigned int BSP_USART_TxBufOut (volatile serial_txbuf *, unsigned char *); 
unsigned int BSP_USART_TxBufSize (volatile serial_txbuf *); 

void BSP_USARTInit(void);

void BSP_CliDbg_HwInit(uint32_t);
void BSP_CliDbg_PollSend(unsigned char *, unsigned int);

void BSP_WifiUart_HwInit(uint32_t);
void BSP_RS485Uart_HwInit(void);
void BSP_WifiUart_PollSend(unsigned char *, unsigned int);
#endif
/*----------------------end of file----------------------*/

