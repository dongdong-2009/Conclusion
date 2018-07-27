/*
* 24c08.c
*
*  Created on: 2013-4-28
*      Author: zjm
*/
#include "api.h"


//int eeprom_read(uint16_t addr, uint8_t *buf, uint16_t size) {
//    memcpy(buf, (uint8_t *)FRAM_START, size);
//    
//    return ((int) size);
//}

_ConfigAndSaved ConfigAndSaved;

int eeprom_write(uint16_t addr, uint8_t *data, uint16_t len) {
    uint8_t *FRAM_write_ptr;                         // Segment D pointer
    uint8_t *p_source = (uint8_t *)data;
    unsigned int i;
    
    SYSCFG0 &= ~DFWP;
    FRAM_write_ptr = (uint8_t *)FRAM_INFO_START;             // Initialize Flash segment D pointer
    for (i = 0; i < len; i++) {
        *FRAM_write_ptr++ = *p_source++;          // copy value segment C to segment D
    }
    SYSCFG0 |= DFWP;
    return len;
}

void SaveData(void) {
    uint8_t *dp;
    
    if (ConfigAndSaved.EEPROMWrite_Flag != 0xA5)
        return;
    
    dp = (void *) &ConfigAndSaved;
    ConfigAndSaved.CheckSum = ChkSum(dp, sizeof(_ConfigAndSaved)-1);
    eeprom_write(0, (void *) &ConfigAndSaved, sizeof(_ConfigAndSaved));
}

void GetSavedData(void) {
    uint8_t *dp;
    uint8_t chk = 0;
    eeprom_read(0, (void *) &ConfigAndSaved, sizeof(_ConfigAndSaved));
    dp = (void *) &ConfigAndSaved;
    chk = ChkSum(dp, sizeof(ConfigAndSaved)-1);
    
    if ((chk != ConfigAndSaved.CheckSum) 
        || (ConfigAndSaved.EEPROMWrite_Flag != 0xA5)) 
    {
        ConfigAndSaved.EEPROMWrite_Flag = 0xA5;
        ConfigAndSaved.ADS1220GainCorrection_1 = 1.0;
        ConfigAndSaved.ADS1220GainCorrection_2 = 1.0;
        ConfigAndSaved.ADS1220GainCorrection_3 = 1.0;
        ConfigAndSaved.ADS1220GainCorrection_4 = 1.0;
        SaveData();
    }
}
