
#include "api.h"

RESULT send_result;

uint8_t rx_buf[16];
uint16_t rx_index;
uint16_t tx_index = 0;

void spi_slave_init(void){
  P5SEL0 |= BIT1 + BIT2 + BIT3;               // P1.5,6,7 USCI_A0 option select
  
  P2DIR &= ~BIT7;
  P2OUT |= BIT7;
  P2REN |= BIT7;
  P2IES |= BIT7;
  P2IFG = 0;
  P2IE |= BIT7;
//  UCB0CTL1 = UCSWRST;                       // **Put state machine in reset**
//  UCB0CTL0 |= UCCKHL | UCMSB | UCSYNC;      // 3-pin, 8-bit SPI 
//  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
//  UCB0IE |= (UCRXIE + UCTXIE);    
}

#pragma vector=USCI_B0_VECTOR
__interrupt void SPI0_slave (void)
{
  switch(__even_in_range(UCB0IV,USCI_UART_UCTXCPTIFG))
  {
  case USCI_NONE: break;
  case USCI_UART_UCRXIFG:
    UCB0IFG &=~ UCRXIFG;            // Clear interrupt
    {
      rx_buf[rx_index] = UCB0RXBUF;
      rx_index++;
      if(rx_index >= sizeof(RESULT)){
        tx_index = 0;
        rx_index = 0;
        UCB0IE &= ~(UCRXIE + UCTXIE);                  
      }
    }break;
  case USCI_UART_UCTXIFG: 
    {
      UCB0IFG &=~ UCTXIFG;            // Clear interrupt
      UCB0TXBUF = send_result.byte[tx_index];  
      tx_index++;
    }break;
  case USCI_UART_UCSTTIFG: break;
  case USCI_UART_UCTXCPTIFG: break;
  }  
}