#ifndef __PID_H
#define __PID_H


#include "stm32f10x.h"
#include <stdio.h>
#include <stdlib.h>
#include "variables.h"




void pid_init(_pid *warm, float process_point, float set_point);
void pid_tune(_pid *pid, float p_gain, float i_gain, float d_gain, float dead_band);
void pid_setinteg(_pid *pid,float new_integ);
void pid_bumpless(_pid *pid);
float pid_calc(_pid *pid);


extern _pid *pid[8];


#endif
















