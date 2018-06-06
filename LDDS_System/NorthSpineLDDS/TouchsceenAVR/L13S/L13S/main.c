#include "config.h"
#include "LCD.h"
#include "touch.h"
#include "Sensor.h"
#include "usart1.h"
#include "usart0.h"
#include <avr/interrupt.h>

void port_Init(void)
{
 	  PORTA = 0x01;
 	  DDRA  = 0xFF;
 	  PORTB = 0x40;
 	  DDRB  = 0xFF;
 	  PORTC = 0x00;
 	  DDRC  = 0xFF;
 	  PORTD = 0x00;
 	  DDRD  = 0xE1;
	  PORTE = 0x04;
 	  DDRE  = 0xFE;
	  PORTF = 0x00;
 	  DDRF  = 0xFF;
	  PORTG = 0x00;
 	  DDRG  = 0xFB;
}

void init_devices(void)
{
 	 cli();
	 port_Init();
	 uart0_init();
	 uart1_init();
 	 MCUCR = 0x00;
 	 EICRA = 0x00; //extended ext ints
 	 EICRB = 0x00; //extended ext ints
 	 EIMSK = 0x00;
 	 TIMSK = 0x45; //timer interrupt sources
	 ETIMSK = 0x04; //extended timer interrupt sources
 	 sei();
}

int main(void)
{
 	init_devices();
	spistar();
	Lcd_Init();
	timer1_init();
	timer2_init();
	timer3_init();
	timer0_init();
	ACBinit();
	Mainfunction();

}