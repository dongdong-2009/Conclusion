
/*****************************************************************
**  各独立键盘定义，端口：P2，使用下降沿中断
****************************************************************/

#ifdef   Utilities_GLOBALS
#define  Utilities_EXT
#else
#define  Utilities_EXT  extern
#endif


#define _STOP_WDG()  WDTCTL = WDTPW+WDTHOLD
Utilities_EXT void __gie_disable(void);
Utilities_EXT void __gie_enable(void); 

unsigned long sqrt32(register unsigned long h);
unsigned long sqrt64(register unsigned long long h);
void soft_delay1ms(unsigned long time);
char * int2str(int conved);
