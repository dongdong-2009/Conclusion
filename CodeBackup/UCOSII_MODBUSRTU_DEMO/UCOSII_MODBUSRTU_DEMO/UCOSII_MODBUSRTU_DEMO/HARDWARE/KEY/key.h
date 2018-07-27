#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 

#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)//��ȡ����2 
#define KEY3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����3(WK_UP) 


#define KEY_WAKEUP 		4
#define KEY_USER2			3
#define KEY_USER1			2
#define KEY_TEMPER		1

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
