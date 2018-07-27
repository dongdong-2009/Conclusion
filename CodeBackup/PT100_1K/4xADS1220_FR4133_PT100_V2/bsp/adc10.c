
#include "api.h"


uint16_t ADC_Result;    

void adc10_init(void){
    
    SYSCFG2 |= ADCPCTL2 | ADCPCTL3 | ADCPCTL5 | ADCPCTL6 | ADCPCTL7;
    
};

int get_adc10_NTC(uint16_t *ptr_ntc_p1, uint16_t *ptr_ntc_p2){
    WDOG_Feed();    
    P1OUT |= BIT4;  // Çý¶¯ÈÈÃôµç×è
    BSP_DELAY_USECS(10*1000);   
    ADCCTL0 = ADCSHT_10 | ADCON;                       // 16ADCclks, MSC, ADC ON
    ADCCTL1 = ADCDIV_1 | ADCSHP |ADCSSEL_0 | ADCCONSEQ_0;               // ADC clock MODCLK, sampling timer, s/w trig.,single sequence
    ADCCTL2 |= ADCRES;                                         // 10-bit conversion results
    
    ADCMCTL0 = ADCINCH_3 | ADCSREF_0;                          // A0~2(EoS); Vref=1.5V
    ADCCTL0 |= ADCENC | ADCSC;          // Sampling and conversion start
    while(!(ADCIFG & ADCIFG0));
    ADCIFG = 0;   
    ADC_Result = (int)ADCMEM0;
    *ptr_ntc_p1 = ADC_Result;
    
    ADCCTL0 &= ~ADCENC;
    ADCMCTL0 = ADCINCH_2 | ADCSREF_0;                          // A0~2(EoS); Vref=1.5V
    ADCCTL0 |= ADCENC | ADCSC;          // Sampling and conversion start
    while(!(ADCIFG & ADCIFG0));
    ADC_Result = (int)ADCMEM0;
    *ptr_ntc_p2 = ADC_Result;
    
    P1OUT &= ~BIT4;
    
    ADCCTL0 = 0;
    ADCMCTL0 = 0;
    return 0;
}

int AdcGetSample(uint16_t adc_ch){
    WDOG_Feed();
    
    ADCCTL0 = ADCSHT_10 | ADCON;                       // 16ADCclks, MSC, ADC ON
    ADCCTL1 = ADCDIV_1 | ADCSHP |ADCSSEL_0 | ADCCONSEQ_0;               // ADC clock MODCLK, sampling timer, s/w trig.,single sequence
    ADCCTL2 |= ADCRES;                                         // 10-bit conversion results
    
    // Configure reference
    PMMCTL0_H = PMMPW_H;                                      // Unlock the PMM registers
    PMMCTL2 |= INTREFEN;                                      // Enable internal reference
    BSP_DELAY_USECS(400);                                      // Delay for reference settling
    switch(adc_ch){
    case Moto:
        ADCMCTL0 = ADCINCH_5 | ADCSREF_1;                          // A0~2(EoS); Vref=1.5V
        break;
    case Cap:
        ADCMCTL0 = ADCINCH_6 | ADCSREF_1;                          // A0~2(EoS); Vref=1.5V
        break;
    case Power:
        ADCMCTL0 = ADCINCH_7 | ADCSREF_1;                          // A0~2(EoS); Vref=1.5V
        break;
        
    default :
        break;
    }
    
    ADCCTL0 |= ADCENC | ADCSC;          // Sampling and conversion start
    while(!(ADCIFG & ADCIFG0));
    ADCIFG = 0;
    ADC_Result = (int)ADCMEM0;
    PMMCTL2 &= ~INTREFEN;                   // Disable internal reference
    ADCCTL0 = 0;
    ADCMCTL0 = 0;
    return ADC_Result;;
}


// ADC interrupt service routine

//#pragma vector=ADC_VECTOR
//__interrupt void ADC_ISR(void){
//    switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
//    {
//    case ADCIV_NONE: 
//        break;                              
//    case ADCIV_ADCOVIFG: 
//        break;             
//    case ADCIV_ADCTOVIFG: 
//        break;            
//    case ADCIV_ADCHIIFG: 
//        break;             
//    case ADCIV_ADCLOIFG: 
//        break;             
//    case ADCIV_ADCINIFG: 
//        break;             
//    case ADCIV_ADCIFG:
//        ADC_Result = (int)ADCMEM0;          // Store ADC10 channel 1 result
//        adc_falg = 1;
//        __bic_SR_register_on_exit(LPM0_bits); // Exit LPM0 on return
//        break;                                             
//    default: 
//        break; 
//    }  
//}

