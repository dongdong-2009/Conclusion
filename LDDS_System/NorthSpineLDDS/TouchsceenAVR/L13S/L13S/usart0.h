
#include "data.h"
void uart0_init(void);
//void send_data0(unsigned int typeA,unsigned int data1,unsigned int data2,unsigned int data3,unsigned int data4,unsigned int data5,unsigned int data6,unsigned int data7);
void send_data0(unsigned typeA);
void Reciver_process0(void);
void getsend(unsigned char getdata,unsigned char i);
void getsensor(unsigned int getTem,unsigned int getHum,unsigned int locflag);
void getdo(unsigned char do1,unsigned char do2);