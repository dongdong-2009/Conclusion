#ifndef ANALOGIN_H
#define ANALOGIN_H

#include "stdint.h"
#include "stm32f10x.h"

#pragma pack(1)

struct _adc_data{
    uint8_t b55;
    uint8_t baa;
    uint16_t data[4];
};

struct _rtd_data{
    uint8_t b55;
    uint8_t baa;
    int32_t temp_1;  //每个测温模块连接两个测温传感器
    int32_t temp_2;
    int32_t temp_3;
    int32_t temp_4;
    uint8_t  nuse1;
    uint8_t  nuse2;
};

#pragma pack()
extern struct _adc_data adc_buffer[4];
extern struct _rtd_data rtd_buffer[2];

extern void analog_in_init(void);
void rtd_init(void);

float readSenor(u8 port,float range);
float readTemp(u8 port);
void APortCIn(float aarr[16],float range[12]);
float APortIn(u8 port, float range);

#endif
