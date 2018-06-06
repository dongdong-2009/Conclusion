#ifndef _RUNTIMEDATA_H
#define _RUNTIMEDATA_H


void writePorts( void);

float delay_fun(int port,float par1,float par2,float par3);
void readPorts(void);
void readPID(char* readPIDBuffer);
void writePID(char* writePIDBuffer);


#endif /*RUNTIMEDATA_H*/


