#ifndef __TOUCH_H
#define __TOUCH_H

#define  Penirq_H    PORTD |= 1<<1
#define  Penirq_L    PORTD &= ~(1<<1)

#define  DOUT_H    PORTD |= 1<<4
#define  DOUT_L    PORTD &= ~(1<<4)

#define  DIN_H    PORTD |= 1<<5
#define  DIN_L    PORTD &= ~(1<<5)

#define  CS_H    PORTD |= 1<<6
#define  CS_L    PORTD &= ~(1<<6)

#define  DCLK_H    PORTD |= 1<<7
#define  DCLK_L    PORTD &= ~(1<<7)

#define ERR_RANGE 20
#define  CMD_RDX  0xD0
#define  CMD_RDY  0x90
#define READ_TIMES 15
#define LOST_VAL 5
#define  vx 15448
#define  vy 25940
#define  chx 7744
#define  chy 7526
struct tp_pix_
{
	unsigned int x;
	unsigned int y;
};
struct tp_pixu32_
{
	unsigned long x;
	unsigned long y;
};
extern struct tp_pix_  tp_pixad,tp_pixlcd;

unsigned char tpstate(void);
void spistar(void);  
void Touch_Adjust(void);
void point(void);
unsigned int ReadFromCharFrom7843(void);
char function(void);
#endif  