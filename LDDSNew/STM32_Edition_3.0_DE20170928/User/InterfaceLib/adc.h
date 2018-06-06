#ifndef ADC_H
#define ADC_H

void ADC_init(void);
void ADC_onechannel(char channel,float *adc_value);
void ADC_allchannels(float *adc_value);

#endif
