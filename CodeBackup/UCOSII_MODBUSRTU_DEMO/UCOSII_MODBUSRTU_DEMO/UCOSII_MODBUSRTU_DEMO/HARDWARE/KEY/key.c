#include "key.h"
#include "delay.h"
	    
//������ʼ������ 
//PA0 - WAKEUP, PA8 - USER1, PC13 - TEMPER, PD3 - USER2
void KEY_Init(void)
{
	
 	GPIO_InitTypeDef GPIO_InitStructure;
	//��ʼ��KEY0-->GPIOA.13,KEY1-->GPIOA.15  ��������
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);//ʹ��PORTA,PORTEʱ��

 	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_8;//PA0 PA8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;//PC13
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;//PD3
 	GPIO_Init(GPIOD, &GPIO_InitStructure);//
	
} 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//����ֵ��
//0��û���κΰ�������
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
 	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return 1;
		else if(KEY1==0)return 2;
		else if(KEY2==0)return 3;
 		else if(KEY3==0)return 4;
 	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1)key_up=1; 	    
	return 0;// �ް�������
}
