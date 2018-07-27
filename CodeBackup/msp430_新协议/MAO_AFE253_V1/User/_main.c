
#include "stdint.h"
#include "device.h"
#include "sd24.h"
#include "math.h"
#include "Utilities.h"
#include "spi.h"

#define SAMPLE  100.0

struct data {
        char byte[9];  
        int rms_a;  
        int rms_b;
        int rms_c;
};

//SD24 related variable definition
int calibrated_data[3]; //rawdata minus sd_calibrator
int sample_count= 0;//log_sample_count;
unsigned long long sample_accum[3]={0};

//SPI related variable definition
struct data  adc_result, send_result;
uint8_t rx_buf[9];
uint16_t rx_index;
uint16_t tx_index;
char *p= &(send_result.byte[0]);

//local function delaration
static void CALCULATERPARAMETER(unsigned long long *sample_accum);//计算参数

void main (void)
{
    volatile unsigned int i;
    
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
    InitAnalogFrontEnd();
    
 //---------Setup P1 for SPI Mode && Configure P2.0 for external interrrupt-------//
     
    P2DIR &= ~BIT0;                       //P2.0 for external interrrupt  mode
    P2OUT |= BIT0;
    P2REN |= BIT0;
    P2IES |= BIT0;
    
    P1OUT &= ~(BIT0 + BIT4);             //Close SPI SOMI port  && Close  indicator LED
    P1DIR |= BIT0 + BIT4;
    
    P1SEL = 0xE0;                        // Setup P1 for SPI mode
    U0BR0 = 2;
    U0BR1 = 0;
    U0MCTL = 0;
    U0CTL = CHAR + SYNC + SWRST;              // 8-bit, SPI, Slave
    U0TCTL = STC;                      // Polarity, UCLK, 3-wire
    ME1 = USPIE0;                             // Module enable
    U0CTL &= ~SWRST;                          // SPI enable 
    
    start_sd24();                 // turn on SD24
    P1OUT |= BIT0;               //turn on LED
    P2IFG = 0;
    P2IE = BIT0;                 //Enable external interrupt
    __enable_interrupt();          // GIE --- enable interrupt
    
    while (1)
    { 
        if(conversion_done)
        {    
            conversion_done = 0; 
            sample_count++;
             
            for(int i =0;i<3;i++)
            {
              calibrated_data[i] = sd24_rawdata[i] - sd24_calibrator[i];
              sample_accum[i] += calibrated_data[i];
            }
            
            if(sample_count>= SAMPLE) 
            {
                stop_sd24();      
                P1OUT &= ~BIT0;           //turn off LED
                sample_count=0;
                CALCULATERPARAMETER(sample_accum);
                soft_delay1ms(60);
                P1OUT |= BIT0;            //turn on LED
                start_sd24();
            }
        }
    }
} 

static void CALCULATERPARAMETER(unsigned long long *sample_accum)
{
    
    float ave_sample[3];
    
    for(int i=0; i<3;i++)
    {
       ave_sample[i] = (float)(sample_accum[i]/SAMPLE);
       sample_accum[i] = 0;
    }
                         
    adc_result.rms_a = (int)((ave_sample[0]*51*1.2/65536.0 + 0.005) *100); 
    adc_result.rms_b = (int)((ave_sample[1]*51*1.2/65536.0 + 0.005) *100); 
    adc_result.rms_c = (int)((ave_sample[2]*51*1.2/65536.0 + 0.005) *100); 
    
    adc_result.rms_a = (int)fabs(adc_result.rms_a);
    adc_result.rms_b = (int)fabs(adc_result.rms_b);
    adc_result.rms_c = (int)fabs(adc_result.rms_c);
    
    adc_result.byte[0] = 0x01;
    adc_result.byte[1] = (char)(adc_result.rms_a / 100);   //整数部分
    adc_result.byte[2] = (char)(adc_result.rms_a % 100);   //整数部分 
    
    adc_result.byte[3] = 0x02;
    adc_result.byte[4] = (char)(adc_result.rms_b / 100);   //整数部分
    adc_result.byte[5] = (char)(adc_result.rms_b % 100);   //整数部分 
    
    adc_result.byte[6] = 0x03;
    adc_result.byte[7] = (char)(adc_result.rms_c / 100);   //整数部分
    adc_result.byte[8] = (char)(adc_result.rms_c % 100);   //整数部分                               
}


#pragma vector=USART0TX_VECTOR
__interrupt void SPI0_tx (void)
{
     TXBUF0 = p[tx_index];
     tx_index++; 
}

#pragma vector=USART0RX_VECTOR
__interrupt void SPI0_rx (void)
{
    rx_buf[rx_index] = RXBUF0;
    rx_index++;
    if(rx_index >= 9)
     {
        tx_index = 0;
        rx_index = 0;
        P1OUT &= ~BIT4;           //关闭SPI输出端口
        IE1 &= ~(UTXIE0 + URXIE0); 
      }
}

#pragma vector= PORT2_VECTOR
__interrupt void port2 (void)
{
   if(P2IFG & BIT0)
   {
    P2IFG = 0;
    tx_index = 0;
    rx_index = 0;
    send_result = adc_result;
    P1OUT |= BIT4;         // 开启SPI MISO端口
    U0CTL |= SWRST;              // 8-bit, SPI, Slave
    ME1 |= USPIE0;              // Module enable
    U0CTL &= ~SWRST;           // SPI enable
    IE1 |= UTXIE0 + URXIE0;   
   }
}

