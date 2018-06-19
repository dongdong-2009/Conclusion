#ifndef __MB_PORT_H
#define __MB_PORT_H

void SendChar(unsigned char ch);

unsigned char GetChar(void);

void USART_IRQSet(unsigned char txIrq,unsigned char rxIrq);
void Send_IRQ(void);
void Receive_IRQ(void);

void TIM_IRQSet(unsigned char tmIrq);
void Time_IRQ(void);

#endif
