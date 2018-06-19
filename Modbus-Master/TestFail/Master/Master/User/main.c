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
	LED_Init();              //LED灯管脚初始化
	MB_Init(115200);         //初始化波特率，来确定Modbus通信帧间隔时间，初始化USART5
	MB_RegInit();            //分配存储空间，寄存器存储大小初始化
	//UART5_SendNData("123\r\n",5);
	MB_EventInit();          //事件初始化
	USART_IRQSet(0,1);			 //开启接收中断   para1-接收使能，para2-发送使能
	LED_ON(1);               //开启LED灯
	while(1)
	{
		MB_Poll();              //从机 
    MB_M_app_demo(&step);		//主机发送样例
  }
}
