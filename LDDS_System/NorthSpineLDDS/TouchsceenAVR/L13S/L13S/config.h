/******************************************
//����ϵͳ
//оƬ��ATmega16L
//Ƶ�ʣ�8MHz��Ƶ
//��ѹ��3.3V
*******************************************/

#include <avr/interrupt.h>
#include <avr/io.h>
//type���ƶ���

void del(unsigned int u);
void delayus(unsigned int t);
void delayms(unsigned int t);
void timer0_init(void);
void timer1_init(void);
void timer2_init(void);
void timer3_init(void);
