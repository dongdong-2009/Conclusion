#ifndef DIO_H
#define DIO_H

#include <stdint.h>
void IO_Configuration(void);
void DO_onechannel(uint8_t port,char level);
void DI_onechannel(uint8_t port,char* DI_data);
void DI_allchannels(char* DI_data);
void DO_allchannels(uint8_t* DO_data);

#endif
