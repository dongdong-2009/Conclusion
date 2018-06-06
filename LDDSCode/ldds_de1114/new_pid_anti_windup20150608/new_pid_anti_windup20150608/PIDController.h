#pragma once
#include "stdafx.h"

class CPIDController
{
public:
	CPIDController(void);
	~CPIDController(void);
	// main fun: two steps
	void setpidpara(double para_kp,double para_ki,double para_kd,double samplingtime);
	double pidcontrol(double ref, double yout,double u0);
	
	// subroutine
	double isa_pid(double *buffer);

public:
	double b,c; // weights of setpoint and disturbance-rejection
	double kp,ki,kd,Ts; //pid para
	double UMAX,UMIN;	// satuation limits
	double u0,yk_1,yk_2; // for pid increment algorithm
};

