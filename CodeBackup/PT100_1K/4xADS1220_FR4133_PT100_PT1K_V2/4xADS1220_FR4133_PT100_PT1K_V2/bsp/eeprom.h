/*
 * eeprom.h
 *
 *  Created on: 2013-4-28
 *      Author: zjm
 */
#ifndef EEPROM_H_
#define EEPROM_H_

#include "api.h"

#define FRAM_INFO_START (0x1800)

typedef struct {
    float ADS1220GainCorrection_1;
    float ADS1220GainCorrection_2;
    float ADS1220GainCorrection_3;
    float ADS1220GainCorrection_4;
    uint8_t EEPROMWrite_Flag;
    uint8_t CheckSum;
}_ConfigAndSaved;

extern _ConfigAndSaved ConfigAndSaved;

#define eeprom_read(addr, buf, size) memcpy(buf, (uint8_t *)FRAM_INFO_START, size)
int eeprom_write(uint16_t addr,uint8_t *data,uint16_t len);
void GetSavedData(void);
void SaveData(void);


#endif /* EEPROM_H_ */
