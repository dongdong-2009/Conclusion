/*
* gpio.c
*
*  Created on: 2013-4-20
*      Author: zjm
*/
#include "api.h"

extern unsigned char ReadConversionData_1;
extern unsigned char ReadConversionData_2;
extern unsigned char ReadConversionData_3;
extern unsigned char ReadConversionData_4;

extern uint16_t rx_index;
extern uint16_t tx_index;

extern RESULT send_result;
extern RESULT adc_result;

void GpioInit(void)
{
   // 按钮
    P1DIR &= ~(BIT2 + BIT3 + BIT6 + BIT7);
    P1OUT |= (BIT2 + BIT3 + BIT6 + BIT7);
    P1REN |= (BIT2 + BIT3 + BIT6 + BIT7);
   //ads转换完成中断 
    P2DIR &= ~(BIT2 + BIT3 + BIT4 + BIT5);
    P2OUT |= (BIT2 + BIT3 + BIT4 + BIT5);
    P2REN |= (BIT2 + BIT3 + BIT4 + BIT5);
    // IO SPI MISO
    P3OUT = BIT7;
    P3DIR = 0xEF;
    P3REN = BIT7;
    
    P4OUT = 0;
    P4DIR = 0xff;
    P5OUT = 0;
    P5DIR = 0xFF;
    // ADS1220
    P6OUT = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5;
    P6DIR = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5;
    // LED
    P7OUT = 0x00;
    P7DIR = 0xFF;
    P8OUT = 0;
    P8DIR = 0xff;
}


#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR (void)
{
    // Has a Data Ready occurred from the ADS1220?
    if (P2IFG & ADS_DRDY_N_1)
    {
        ReadConversionData_1 = 1;
    }
    if (P2IFG & ADS_DRDY_N_2)
    {
        ReadConversionData_2 = 1;
    }
    if (P2IFG & ADS_DRDY_N_3)
    {
        ReadConversionData_3 = 1;
    }
    if (P2IFG & ADS_DRDY_N_4)
    {
        ReadConversionData_4 = 1;
    }
    if(P2IFG & BIT7){
        tx_index = 0;
        rx_index = 0;
        send_result = adc_result;
        UCB0CTLW0 = UCSWRST;                       // **Put state machine in reset**
        UCB0CTLW0 |= UCMSB | UCSYNC;      // 3-pin, 8-bit SPI 
        UCB0CTLW0 &= ~UCSWRST;                     // **Initialize USCI state machine**
        UCB0IE |= (UCRXIE + UCTXIE);    
    }
    P2IFG = 0;
    //__low_power_mode_off_on_exit();      
}
