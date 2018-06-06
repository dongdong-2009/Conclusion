#include"config.h"

void del(unsigned int u)
{
 	 int j,k=0;
	 for(j=u;j>0;j--)
	 for(k=0;k<1140;k++);
}

void delayus(unsigned int t)
{
 	 unsigned int i;
	 for(i=0;i<t;i++)
	 {
	  	asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
		asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	 }
}

void delayms(unsigned int t)
{
 	 unsigned int i,j;
	 for(i=0;i<t;i++)
	 {
	  	for(j=0;j<2288;j++);
	 }
}

void timer0_init(void)
{
 	 TCCR0 = 0x00; //stop
 	 ASSR  = 0x00; //set async mode
 	 TCNT0 = 0x64; //set count
 	 OCR0  = 0x9C;
 	 TCCR0 = 0x07; //start timer
}

void timer1_init(void)
{
 	 TCCR1B = 0x00; //stop
 	 TCNT1H = 0xC2; //setup
 	 TCNT1L = 0xF7;
 	 OCR1AH = 0x3D;
 	 OCR1AL = 0x09;
 	 OCR1BH = 0x3D;
 	 OCR1BL = 0x09;
 	 OCR1CH = 0x3D;
 	 OCR1CL = 0x09;
 	 ICR1H  = 0x3D;
 	 ICR1L  = 0x09;
 	 TCCR1A = 0x00;
 	 TCCR1B = 0x05; //start Timer
}

void timer2_init(void)
{
 	 TCCR2 = 0x00; //stop
 	 TCNT2 = 0x64; //setup
 	 OCR2  = 0x9C;
 	// TCCR2 = 0x05; //start
}

void timer3_init(void)
{
 TCCR3B = 0x00; //stop
 TCNT3H = 0xFF; //setup
 TCNT3L = 0xF6;
 OCR3AH = 0x00;
 OCR3AL = 0x0A;
 OCR3BH = 0x00;
 OCR3BL = 0x0A;
 OCR3CH = 0x00;
 OCR3CL = 0x0A;
 ICR3H  = 0x00;
 ICR3L  = 0x0A;
 TCCR3A = 0x00;
 TCCR3B = 0x03; //start Timer
}
