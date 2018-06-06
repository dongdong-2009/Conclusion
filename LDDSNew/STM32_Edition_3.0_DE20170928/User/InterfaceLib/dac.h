#ifndef DAC_H_
#define DAC_H_

#include <stdint.h>
extern void DAC_init(void);
extern void DAC_allchannel(float* value);
extern void DAC_onechannel(uint8_t channel, float value);
//extern void DAC_onechannelphysical(uint8_t port,float dacvl,float range) ;
//extern void DAC_allchannelphysical(float *dacvl,float *range);

#endif /* DAC_H_ */
