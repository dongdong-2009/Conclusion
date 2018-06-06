#include "pid.h"

void pid_init(_pid *pid, float process_point, float set_point)
{ 
	pid->pv = process_point; 
	pid->sp = set_point; 
} 
void pid_tune(_pid *pid, float p_gain, float i_gain, float d_gain, float dead_band) 
{ 
	pid->pgain = p_gain; 
	pid->igain = i_gain; 
	pid->dgain = d_gain; 
	pid->deadband =dead_band;  
} 
void pid_setinteg(_pid *pid,float new_integ)
{ 
	pid->integral = new_integ;
		 
} 
void pid_bumpless(_pid *pid) 
{
	pid->last_error = pid->sp - pid->pv;  
} 

float pid_calc(_pid *pid)
{ 
	int err;
	float pterm, dterm, result, ferror;  	

	err = (pid->sp) - (pid->pv); 
	if (abs(err) > pid->deadband) 
	{ 
		ferror = (float) err; /*do integer to float conversion only once*/ 
		pterm = pid->pgain * ferror; 
		if (pterm > 100 || pterm < -100)
		{
			pid->integral = 0.0; 
		}
		else 
		{ 
			pid->integral += pid->igain * ferror; 
			if (pid->integral > 100.0) 
			{
				pid->integral = 100.0; 
			}
			if (pid->integral < 0.0)
			{
			    pid->integral = 0.0;
			} 
		} 
		dterm = ((float)(err - pid->last_error)) * pid->dgain; 
		result = pterm + pid->integral + dterm; 
	} 
	else 
	    result = pid->integral; 
	pid->last_error = err; 
	return (result); 
}















