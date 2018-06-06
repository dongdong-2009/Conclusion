

#ifndef RTD_H
#define RTD_H
void RTD_init(void);
void RTD_Start(void);
void RTD_OffsetCal(void);
void rtd_process_1(void);
void rtd_process_2(void);
void LoadFromFlash(void);
void SaveToFlash(void);
#endif
