#ifndef _TIMER_H 
#define _TIMER_H

#define SubRoutine1()  TIM2_IRQHandler(void)
#define SubRoutine2()  TIM3_IRQHandler(void)
#define SubRoutine3()  TIM4_IRQHandler(void)
#define SubRoutine4()  TIM5_IRQHandler(void) 

void InitializeTimer(int n,float time);
void TurnOnTim(int x);
void TurnOffTim(int x);
void SubRoutineExit(int x);
int  SubRoutineEntry(int x);
#endif /*_TIMETR_H*/

