#include "stm32f10x.h"
#include "led.h"
#include "timer.h"
#include "mb_config.h"
#include "mb_app.h"
#include "mb_core.h"
#include "mb_port.h"
#include "usart.h"

uint8_t step=0;

int main( void )
{
	LED_Init();              //LED�ƹܽų�ʼ��
	MB_Init(115200);         //��ʼ�������ʣ���ȷ��Modbusͨ��֡���ʱ�䣬��ʼ��USART5
	MB_RegInit();            //����洢�ռ䣬�Ĵ����洢��С��ʼ��
	//UART5_SendNData("123\r\n",5);
	MB_EventInit();          //�¼���ʼ��
	USART_IRQSet(0,1);			 //���������ж�   para1-����ʹ�ܣ�para2-����ʹ��
	LED_ON(1);               //����LED��
	while(1)
	{
		MB_Poll();              //�ӻ� 
    MB_M_app_demo(&step);		//������������
  }
}
