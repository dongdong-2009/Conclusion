#include "timer.h"

void TimConfigure(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��
	
	TIM_DeInit(TIM4);
	TIM_TimeBaseStructure.TIM_Period = 20; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 
	TIM_TimeBaseStructure.TIM_Prescaler =7199; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	TIM_ClearFlag(TIM4,TIM_IT_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);    //ʹ�ܻ���ʧ��ָ����TIM�ж�//TIM2 //ʹ��
	TIM_Cmd(TIM4, ENABLE);             //ʹ�ܶ�ʱ���ж�
}
