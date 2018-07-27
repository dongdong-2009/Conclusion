#ifndef E_METER_H
#define E_METER_H
   
extern unsigned long long ch0_accum,ch1_accum,ch2_accum;

void InitAnalogFrontEnd(void);
void start_sd24(void);
void stop_sd24(void);

#endif //E_METER_H


