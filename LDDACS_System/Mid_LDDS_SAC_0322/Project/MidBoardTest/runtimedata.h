#ifndef _RUNTIMEDATA_H
#define _RUNTIMEDATA_H


//void writePorts( void);

float delay_fun(int port,float par1,float par2,float par3);
void  readPorts(void);


void  emergencyCheck(void);
void  transferCheck(void);
void  statusCheck(void);
void  lowbufCheck(void);

#endif /*RUNTIMEDATA_H*/


