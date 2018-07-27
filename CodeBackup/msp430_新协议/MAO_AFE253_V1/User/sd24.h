#ifndef E_METER_H
#define E_METER_H


extern int  sd24_rawdata[3];
extern int  sd24_calibrator[3];
extern char conversion_done;

void InitAnalogFrontEnd(void);
void start_sd24(void);
void stop_sd24(void);

#endif //E_METER_H


