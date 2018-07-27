

#include "stdint.h"
#include "device.h"
#include "sd24.h"
#include "type_def.h"

#include "flashwrite.h"
#include "math.h"
#include "Utilities.h"

#include "spi.h"


typedef union
{
    struct
    {
        char byte[10];  //
    };
    struct
    {
        unsigned int flag;
        unsigned int rms_a;  //
        unsigned int rms_b;
        unsigned int rms_c;   
    };
    
}RESULT;  //无符号整数



void init_system(void);
void main (void);
void TimerA_init(void);
static void CALCULATERPARAMETER(void);//计算参数
int16_t dc_filter(register int32_t *p, register int16_t x);

int32_t V_dc_estimate_0, V_dc_estimate_1, V_dc_estimate_2; 
RESULT adc_result = {0x55,0xAA};
RESULT send_result;

uint8_t rx_buf[10];
uint16_t rx_index;

unsigned int tx_index = 0;
// 从ESP模块返回的参数
extern U8 g_byNewValue;
extern int sd24_sample_0, sd24_sample_1, sd24_sample_2;
extern unsigned int sample_count;//log_sample_count;
extern unsigned long long ch0_accum,ch1_accum,ch2_accum;
extern int ch0_short, ch1_short, ch2_short;
extern unsigned long long _ch0_accum, _ch1_accum, _ch2_accum;
extern long* Mul_result;

int __low_level_init(void)
{
    WDTCTL = WDTPW + WDTHOLD;             // Stop WDT
    //    P1OUT ^= 0x01;
    //    P1DIR |= 0x01;  // P1.0 toggle on each reset
    return 1;
}

void main (void)
{
    volatile unsigned int i;
    
    BCSCTL1 = CALBC1_8MHZ;                    // Set range
    DCOCTL = CALDCO_8MHZ;                     // Set DCO step + modulation */
    
    BCSCTL1 &= ~XT2OFF;                       // Activate XT2 high freq xtal
//    BCSCTL3 |= XT2S_2+LFXT1S_2;               // 3 ?16MHz crystal or resonator
//    do
//    {
//        IFG1 &= ~OFIFG;                         // Clear OSCFault flag
//        for (i = 0xFFF; i > 0; i--);            // Time for flag to set
//    }
//    while (IFG1 & OFIFG);                     // OSCFault flag still set?
//    //BCSCTL2 |= SELS+SELM_2;                   // MCLK = XT2 HF XTAL (safe)
//    BCSCTL2 |= SELS;                   // SMCLK = XT2 HF XTAL (safe)
    InitAnalogFrontEnd();
    
    //TimerA_init();
    flash_init();
    
    P1SEL = 0xE0;                             // Setup P1 for SPI mode
    P2DIR &= ~BIT0;
    P2OUT |= BIT0;
    P2REN |= BIT0;
    P2IES &= ~BIT0;
    
    P1OUT &= ~(BIT0 + BIT4);
    P1DIR |= BIT0 + BIT4;

    U0BR0 = 2;
    U0BR1 = 0;
    U0MCTL = 0;
    U0CTL = CHAR + SYNC + SWRST;              // 8-bit, SPI, Slave
    U0TCTL = STC;                      // Polarity, UCLK, 3-wire
    ME1 = USPIE0;                             // Module enable
    U0CTL &= ~SWRST;                          // SPI enable
    tx_index = 0;
    send_result = adc_result;
    __enable_interrupt();
    start_sd24(); 
    P2IFG = 0;
    P2IE = BIT0;
    while (1)
    {
        WDTCTL = WDT_ARST_1000;
        if(g_byNewValue)
        {
            g_byNewValue = 0; 
            if(++sample_count>= 410) // 
            {
                SD24CCTL2 &= ~SD24SC;
                sample_count=0;
            }
            sd24_sample_0 -= ch0_short;
            //sd24_sample_0 = dc_filter(&V_dc_estimate_0, sd24_sample_0);
            MPYS = sd24_sample_0;
            OP2 = sd24_sample_0;
            _ch0_accum += *Mul_result;
            
            sd24_sample_1 -= ch1_short;
            //sd24_sample_1 = dc_filter(&V_dc_estimate_1, sd24_sample_1);
            MPYS = sd24_sample_1;
            OP2 = sd24_sample_1;
            _ch1_accum += *Mul_result;
            
            sd24_sample_2 -= ch2_short;
            //sd24_sample_2 = dc_filter(&V_dc_estimate_2, sd24_sample_2);
            MPYS = sd24_sample_2;
            OP2 = sd24_sample_2;
            _ch2_accum += *Mul_result;
            
            if(!sample_count)
            {
                P1OUT |= BIT0;
                ch0_accum = _ch0_accum;///800;
                ch1_accum = _ch1_accum;///800;
                ch2_accum = _ch2_accum;///800;
                _ch0_accum = _ch1_accum = _ch2_accum = 0;
                CALCULATERPARAMETER();
                P1OUT &= ~BIT0;
                start_sd24();   
                
            }
        }
    } // End of while (1)
} // End of main()
static void CALCULATERPARAMETER(void)//计算参数
{
    
    unsigned long a, b, c;
    WDTCTL = WDT_ARST_1000;
    a = (sqrt64(ch0_accum/410));// /(unsigned long long)976));
    b = (sqrt64(ch1_accum/410));// /(unsigned long long)976));
    c = (sqrt64(ch2_accum/410));// /(unsigned long long)976));
    __gie_disable();
    adc_result.rms_a = a;
    adc_result.rms_b = b;
    adc_result.rms_c = c;
    __gie_enable();
}


void TimerA_init(void)
{
    CCTL0 = CCIE;                             // CCR0 interrupt enabled
    CCR0 = 32768/1;
    CCTL1 = CCIE;
    CCR1 = 32768/4;
    TACTL = TASSEL_1 + MC_2 + TAIE;                  // ACLK, continuous mode
    
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
    CCR0 += 32768/1;                            // Add Offset to CCR0
}
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1 (void)
{
    switch(__even_in_range( TAIV, 10))
    {
    case  2:                           
        {
            CCR1 += 32768/2;
        }break;
    case  4: break;                          // CCR2 not used
    case 10:                                 // overflow
        {
            
        }break;
    }
}


#pragma vector=USART0TX_VECTOR
__interrupt void SPI0_tx (void)
{
    TXBUF0 = send_result.byte[tx_index];  
    tx_index++;
    
}
#pragma vector=USART0RX_VECTOR
__interrupt void SPI0_rx (void)
{
    rx_buf[rx_index] = RXBUF0;
    rx_index++;
    if(rx_index > 7){
        P1OUT &= ~BIT4; //关闭SPI输出端口
        tx_index = 0;
        rx_index = 0;
        IE1 &= ~(UTXIE0 + URXIE0);
        
    }
}
#pragma vector= PORT2_VECTOR
__interrupt void port2 (void)
{
    P2IFG = 0;
    P1OUT |= BIT4; // 开启SPI输出端口
    tx_index = 0;
    rx_index = 0;
    send_result = adc_result;
    U0CTL |= SWRST;              // 8-bit, SPI, Slave
    ME1 |= USPIE0;                             // Module enable
    U0CTL &= ~SWRST;                          // SPI enable
    IE1 |= UTXIE0 + URXIE0;   
}

int16_t dc_filter(register int32_t *p, register int16_t x)
{
    //One would like to estimate DC by something like:
    //  z += ((((int32_t) x << 15) - z) >> 14);
    //  return  x - (z >> 15);
    //but this:
    //  z += ((((int32_t) x << 16) - z) >> 14);
    //  return  x - (z >> 16);
    //is a bit faster, and the shift by 16 will never
    //cause an overflow in this application. However,
    //remember this is not a generic DC filter!
    *p += ((((int32_t) x << 16) - *p) >> 14);
    x -= (*p >> 16);
    return x;
}
