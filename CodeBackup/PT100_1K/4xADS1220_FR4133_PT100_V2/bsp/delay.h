

#ifndef __DELAY_H__
#define __DEALY_H__

#define    DELAY_100MS     BIT0
#define    DELAY_1S        BIT1
#define    RF_ISR          BIT2

extern char delay_flag;

void timer_a1_init(void);

void start_timer_a1_A1(void);
void stop_timer_a1_A1(void);
int timer_a1_is_on(void);
#endif
