

#ifndef ADC10_H
#define ADC10_H


enum{
    Moto = 0,
    Cap,
    Power
};

void adc10_init(void);
int get_adc10_NTC(uint16_t *ptr_ntc_p1, uint16_t *ptr_ntc_p2);
int AdcGetSample(uint16_t adc_ch);
extern uint16_t CalRtxToTemp(uint16_t nRTX);

#endif
