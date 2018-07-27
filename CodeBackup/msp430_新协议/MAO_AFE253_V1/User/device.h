
#ifndef DEVICE_H
#define DEVICD_H
#include "MSP430afe253.h"
#include "type_def.h"
#include <in430.h>

#define SD24CONF0_          (0x00B7u)  /* SD24 Internal Configuration Register 0 */
DEFC(   SD24CONF0         , SD24CONF0_)
#define SD24CONF1_          (0x00BFu)  /* SD24 Internal Configuration Register 1 */
DEFC(   SD24CONF1         , SD24CONF1_)
                                      /* Please use only the recommended settings */
#define MCLK 1

#endif
