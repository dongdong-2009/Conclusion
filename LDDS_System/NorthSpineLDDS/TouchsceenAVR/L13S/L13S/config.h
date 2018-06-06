/******************************************
//测试系统
//芯片：ATmega16L
//频率：8MHz内频
//电压：3.3V
*******************************************/

#include <avr/interrupt.h>
#include <avr/io.h>
//type名称定义

void del(unsigned int u);
void delayus(unsigned int t);
void delayms(unsigned int t);
void timer0_init(void);
void timer1_init(void);
void timer2_init(void);
void timer3_init(void);
