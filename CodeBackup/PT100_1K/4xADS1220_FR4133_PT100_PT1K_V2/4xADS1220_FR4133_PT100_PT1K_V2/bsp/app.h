

#ifndef APP_H
#define APP_H
#include <msp430.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

typedef union
{
    struct
    {
        uint8_t byte[20];  //
    };
    struct
    {
        uint16_t flag;
        int32_t temp_1;  //
        int32_t temp_2;
        int32_t temp_3;
        int32_t temp_4;
    };
    
}RESULT;  //ÎÞ·ûºÅÕûÊý




#define INFO_D  (0x1000)

extern const unsigned long MY_ADDR_DEFAULT;
extern  char *myAddr;



#endif