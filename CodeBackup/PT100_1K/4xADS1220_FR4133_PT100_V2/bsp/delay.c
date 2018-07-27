


#include <msp430.h>
#include "delay.h"
#include "api.h"

char delay_flag;

void timer_a1_init(void)
{
    TA1CTL |= TACLR;
    TA1CCR0 = 32768/100 - 1;  // 10ms    
    TA1CCTL0 = CCIE ; 
    TA1CCR1 = 32768/10 -1 ;     /// 100ms
    TA1CCTL1 = CCIE ; 
    TA1CTL |= TASSEL_1 + ID_0 + MC_2 + TACLR;        // ACLK, Cont Mode; start timer
    
}

void start_timer_a1_A1(void)
{
    if((TA1CCTL1 &= CCIE) == 0){
        TA1CCR1 = TA1R + (32768/(1000/1) -1);  
        TA1CCTL1 = CCIE ; 
    }
}
void stop_timer_a1_A1(void)
{
    TA1CCTL1 = 0; 
}
int timer_a1_is_on(void){
    if(TA1CCTL1 & CCIE){
        return 0;
    }else{
        return -1;
    }
}
__interrupt void TIMER1_A0_ISR (void);


#pragma vector = TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR (void)
{
    TA1CCR0 += (32768/100) - 1;  // 10ms  
    __low_power_mode_off_on_exit();
}

__interrupt void TIMER1_A1_ISR (void);


#pragma vector = TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR (void)
{
    switch(__even_in_range(TA1IV,0x0A))
    {
    case  TA1IV_NONE: break;              // Vector  0:  No interrupt
    case  TA1IV_TACCR1:                   // Vector  2:  TACCR1 CCIFG
        {
            TA1CCR1 += (32768/(1000/1) -1);  
            __low_power_mode_off_on_exit();
        }
        break; 
    case TA1IV_TACCR2:               // Vector  4:  TACCR2 CCIFG
        {
            
        }break;             
        
    case 6: break;                  // Vector  6:  Reserved CCIFG
    case 8: break;                  // Vector  8:  Reserved CCIFG
    case TA1IV_TAIFG: 
        {
            
        }break;              // Vector 10:  TAIFG
    default: 	break;
    }    
}