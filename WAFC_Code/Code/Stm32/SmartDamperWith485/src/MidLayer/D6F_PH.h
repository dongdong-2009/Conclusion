#ifndef __D6F_PH_H
#define __D6F_PH_H

#include "iic.h"

void D6F_PH_Init(void);
void D6F_PH_EXE_MCU(void);
u16 D6F_PH_Read_Reg(u8 RegAddr);
float D6F_PH_Pressure(void);
float D6F_PH_Temperature(void);

#endif


