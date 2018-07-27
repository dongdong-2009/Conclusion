#include "stdafx.h"
#include "PIDController.h"


CPIDController::CPIDController(void)
{
	// init value
	b=1;
	c=1;
	UMAX=2;
	UMIN=0;
	u0=0;
	yk_1 = 0;
	yk_2 = 0;
}


CPIDController::~CPIDController(void)
{

}

//////////////////////////
// main fun
/////////////////////////
// step1 set pid para
void CPIDController::setpidpara(double para_kp,double para_ki,double para_kd,double samplingtime)
{
	kp = para_kp;
	ki = para_ki;
	kd = para_kd;
	Ts = samplingtime;
}

//step2: pid control output
double CPIDController::pidcontrol(double sp, double curr_y,double u0, double v0)	// changed by lyh, 20150608
{
	double *buffer;
	buffer = new double[10];
	
	// set controller
	buffer[0] = kp;
	buffer[1] = ki;
	buffer[2] = kd;
	buffer[3] = Ts;
	buffer[4] = sp;
	buffer[5] = yk_1;
	buffer[6] = curr_y;		// yk = curr_y;
	buffer[7] = yk_2;
	buffer[8] = u0;			// pid controller output
	buffer[9] = v0;			// actuator output,i.e., plant actual input 

	double uout;
	uout = isa_pid(buffer);
	delete buffer;

	// store yk_1,yk_2,u0 for increment algorithm
	yk_2 = yk_1;
	yk_1 = curr_y;
	u0 = uout;

	return uout;
}

////////////////////////////////////////////////////
//
//  subroutine
//
///////////////////////////////////////////////////
// Incremental I_PD
// yin process output
// u_pre Previous PID output
// NO need Sgn, all negative feedback, PID can be negative
// I_PD Program:
// PID = Kp*(b*SP-y) + Ki*(SP-y) + Kd*(c*SP-y);	// ISA-PID
double CPIDController::isa_pid(double *buffer)
{	
	double uout;  
	double sp_c;
	double deta_u;

	// changed by lyh, 20150608; according to yang le, zhu yunhe, sun youxian 2002
	// sp_c = sp + 1/kp * (v_k_1 - u_k_1 )

	sp_c = buffer[4] + 1/buffer[0] * (buffer[9] - buffer[8] );

	// uout = u0 + deta_u
	//	= u0 + kp(ek-ek_1) + ki*Ts*ek + kd*(ek-2*ek_1+ek_2)/Ts
	//      = u0 + kp(yk_1-yk) + ki*Ts*(sp_c-yk) + kd*(2*yk_1-yk-yk_2)/Ts

	deta_u = buffer[0]*(buffer[5] - buffer[6]) + 
		   buffer[1] * buffer[3] *(sp_c - buffer[6]) + 
		   buffer[2] * (buffer[5] * 2 - buffer[6] - buffer[7]) / buffer[3];

    	
	// Limit o/p
    	if (deta_u  < UMIN){
		deta_u = UMIN;
    	}
	if (deta_u > UMAX){
		deta_u = UMAX;
    	}
	
	uout = buffer[8] + deta_u;


    	return  uout; 
} 