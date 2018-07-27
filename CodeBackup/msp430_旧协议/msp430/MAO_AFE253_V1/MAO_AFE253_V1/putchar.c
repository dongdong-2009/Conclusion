

#include  "device.h"
#include "type_def.h"
#include "putchar.h"
#include <string.h>

__interrupt  void USART0_TX_sir(void);
__interrupt  void USART0_RX_isr(void);



int putchar(int c)
{
  if (c == '\n')      //         Convert EOL to CR/LF 
    RS232TXChar('\r'); 
  RS232TXChar(c);     
  return c;
}


#define TX_INT_DISABLE IE1 &= ~UTXIE0
#define TX_INT_ENABLE  IE1 |= UTXIE0
#define RX_INT_DISABLE IE1 &= ~URXIE0
#define RX_INT_ENABLE  IE1 |= URXIE0

#define RXBUFSIZE 8 // receive buffer size
static volatile unsigned char ucRXBuffer[RXBUFSIZE]; // receive buffer
// receive buffer indexes :
static volatile unsigned char ucRXReadIndex, ucRXWriteIndex;
// count of received bytes:
static volatile unsigned char ucRXCharCount;
#define TXBUFSIZE 32 // transmit buffer size
static volatile unsigned char ucTXBuffer[TXBUFSIZE]; // transmit buffer
// transmit buffer indexes:
static volatile unsigned char ucTXReadIndex, ucTXWriteIndex;
// not yet transmitted bytes:
static volatile unsigned char ucTXCharCount;
#define BUFFER_EMPTY 1 // 1: nothing to send
static volatile unsigned char bTXBufferEmpty; // flag for synchronization



//////////////////////////////////////////////////////////////
// Name: RS232TXChar
// Description: stores one char in TX buffer. If it's the first one,
// send it immediately. Rest is sent by TXInterrupt automatically
// Parameter: char cByte (to store in buffer)
// Returns: -
//////////////////////////////////////////////////////////////
void RS232TXChar (char cByte)
{
  ucTXBuffer[ucTXWriteIndex++] = cByte; // load byte to buffer and inc index
  ucTXWriteIndex &= TXBUFSIZE-1; // adjust index to borders of buffer
  TX_INT_DISABLE; // disable transmit interrupt (in IE2)
  ucTXCharCount++; // new char, inc count
  TX_INT_ENABLE; // enable interrupt (in IE2)
  if (bTXBufferEmpty && ucTXCharCount) // buffer had been empty
  {
    bTXBufferEmpty = !BUFFER_EMPTY; // reset empty flag
    TXBUF0 = ucTXBuffer[ucTXReadIndex++]; // load tx register, inc index
    ucTXReadIndex &= TXBUFSIZE-1; // adjust index
    ucTXCharCount--; // char sent, dec count
  }
}

//////////////////////////////////////////////////////////////
// Name: TXInterrupt
// Description: Transmit interrupt service routine called by transmit register
// empty
// Parameter: -
// Returns: -
//////////////////////////////////////////////////////////////
#pragma vector=USART0TX_VECTOR
__interrupt  void USART0_TX_sir(void)
{
  //_EINT();
  if (ucTXCharCount)
  { // send if chars are in buffer
    TXBUF0 = ucTXBuffer[ucTXReadIndex++]; // load tx register, inc index
    ucTXReadIndex &= TXBUFSIZE-1; // adjust index
    ucTXCharCount--; // char sent, dec count
  }
  else // buffer empty, nothing to do
    bTXBufferEmpty = BUFFER_EMPTY; // set empty flag
}

//////////////////////////////////////////////////////////////
// Name: RXInterrupt
// Description: Receive interrupt service routine called by receive register
// full
// Parameter: -
// Returns: -
//////////////////////////////////////////////////////////////
#pragma vector=USART0RX_VECTOR
__interrupt  void USART0_RX_isr(void)
{
  //_EINT();
  char tmp = RXBUF0;
  ucRXBuffer[ucRXWriteIndex++] = tmp; // store received byte and
  // inc receive index
  ucRXWriteIndex &= RXBUFSIZE-1; // reset index
  ucRXCharCount++; // received, inc count
}

//////////////////////////////////////////////////////////////
// Name: ucRS232RXBufferCount
// Description: How many chars are stored in RX buffer ?
// if main routine wants to read chars, it has
// to check first if ucRS232RXBufferCount() returns !=0
// Parameter: -
// Returns: number of chars in receive buffer
//////////////////////////////////////////////////////////////
unsigned char RS232RXBufferCount (void)
{ 
  return (ucRXCharCount);
}
//////////////////////////////////////////////////////////////
// Name: cRS232GetChar
// Description: Get one char from RX buffer. Multiple calls will
// return all chars.
// Parameter: -
// Returns: next valid char in receive buffer
//////////////////////////////////////////////////////////////
char RS232GetChar (char *ch)
{
  char Byte;
  if (ucRXCharCount)
  { // char still available
    Byte = ucRXBuffer[ucRXReadIndex++]; // get byte from buffer
    ucRXReadIndex &= RXBUFSIZE-1; // adjust index
    RX_INT_DISABLE; // disable rx interrupt (IE2)
    ucRXCharCount--; // one char read, dec count
    RX_INT_ENABLE; // done, enable int (IE2)
    *ch = Byte;
    return (1);
  }
  else
    return (0); // if there is no new char
}


//////////////////////////////////////////////////////////////
// Name: send_bytes
// Description: 发送特定长度的字符到发送缓冲区
// return 实际发送的字节数.
// Parameter: char *bytes，发送字符串的首地址。int len，发送字符长度
//////////////////////////////////////////////////////////////
int rs232_send_bytes(unsigned char *bytes,int len)
{
  unsigned int i;
  for(i = 0;i < len;i++)
  {
    RS232TXChar(bytes[i]);
  }
  return(i);
} 

int rs232_send_string(char *string)
{
  unsigned int i,str_len;
  str_len = strlen(string);
  for(i = 0;i < str_len;i++)
  {
    RS232TXChar(string[i]);
  }
  //RS232TXChar('\r');
  //RS232TXChar('\n');
  return(i);
}

void InitUART(unsigned long baud)
{
  //UART
   ucRXWriteIndex = ucRXReadIndex = ucRXCharCount = 0;
   ucTXWriteIndex = ucTXReadIndex = ucTXCharCount = 0;
   bTXBufferEmpty = BUFFER_EMPTY; // reset empty flag
   UCTL0 = CHAR+SWRST;                   // 8-bit character
switch(baud)
{
  case 9600:
    UTCTL0 = SSEL0;                     // UCLK = ACLK
    UBR00 = 0x03;                         // 32k/9600 
    UBR10 = 0x00;                         //
    UMCTL0 = 0x4a;                        // 
    break;
  
  case 19200:
    UTCTL0 = SSEL1;                       // UCLK = SMCLK
    UBR00 = 0xDA;                         // 4MHz/19200 
    UBR10 = 0x00;                         //
    UMCTL0 = 0x55;                        // 
    break;
  case 57600:
    UTCTL0 = SSEL1;                       // UCLK = SMCLK
    UBR00 = 0x48;                         // 4Mhz/57600 
    UBR10 = 0x00;                         //
    UMCTL0 = 0x7B;                        // 
    break;
  case 115200:
    UTCTL0 = SSEL1;                       // UCLK = SMCLK
    //UBR00 = 0x24;                         // 4Mhz/115.2k 
    //UBR10 = 0x00;                         //
    //UMCTL0 = 0x29;                        // 
    UBR00 = 0x48;                         // 8Mhz/115.2k 
    UBR10 = 0x00;                         //
    UMCTL0 = 0xEF;                        // 
    //UBR00 = 0x38;                         // 6.536Mhz/115.2k 
    //UBR10 = 0x00;                         //
    //UMCTL0 = 0xFF;                        // 
    break;
  default:
    while(1){;}
    //break;
  }
  U0ME |= UTXE0+URXE0 ;                 // Enabled USART0 TXD/RXD

  P1SEL |= (BIT3 + BIT4);               // P2.4,5 = USART0 TXD/RXD
  P1DIR |= BIT3;                        // P2.4 output direction

  U0IFG &= ~URXIFG0;                    // Clear USART0 RX interrupt flag

  UCTL0 &= ~(SWRST);                    // 8-bit character - clr SWRST bit
  
  U0IE |= URXIE0+UTXIE0;                // Enable USART0 RX + TX interrupt
}
