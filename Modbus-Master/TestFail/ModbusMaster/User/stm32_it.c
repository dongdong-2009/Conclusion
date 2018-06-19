#include "stm32_it.h"
#include "delay.h"
#include "Modbus_m.h"

extern u8 ReceBuffer[BufferSize];       //Receive Buffer
extern uint8_t Uart1_SCnt;
extern uint8_t Uart1_Send_buffer[150];
extern uint8_t Uart1_RCnt;
extern uint8_t Uart1_SendBuffSize;
extern u8 MBStatus;

void USART1_IRQHandler(void)
{
			//判断串口是否发生指定中断，是否发生溢出错误中断
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE))
		{
			USART_ReceiveData(USART1);
			USART_ClearFlag(USART1, USART_FLAG_ORE);//清除相应的标志位
		}
		
		if(USART_GetFlagStatus(USART1,USART_FLAG_NE)!=RESET)
		{
			USART_ReceiveData(USART1);
			USART_ClearFlag(USART1,USART_FLAG_NE);
		}
		
		if(USART_GetFlagStatus(USART1,USART_FLAG_FE)!=RESET)
		{
			USART_ReceiveData(USART1);
			USART_ClearFlag(USART1,USART_FLAG_FE);
		}
		
		if(USART_GetFlagStatus(USART1,USART_FLAG_PE)!=RESET)
		{
			USART_ReceiveData(USART1);
			USART_ClearFlag(USART1,USART_FLAG_PE);
		}
		
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
		{
			USART_ClearFlag(USART1,USART_IT_RXNE);
			USART_ClearITPendingBit(USART1, USART_IT_RXNE); 
			ReceBuffer[Uart1_RCnt]=USART_ReceiveData(USART1);		//连续接收
			Uart1_RCnt++;
			
			//处理从机响应
			if(MBStatus==ku8MBSuccess)
			{
				if(Uart1_RCnt==8)
				{
					if(ReceBuffer[0]!=SlaveID)
					{
						MBStatus=ku8MBInvalidSlaveID;
						return ;
					}
					if(ReceBuffer[1]!=FunCode)
					{
						MBStatus=ku8MBInvalidFunction;
						return ;
					}
				}
			}

			
			
		}
		
		if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
		{
			USART_ClearITPendingBit(USART1,USART_IT_TXE);
			if(Uart1_SCnt<Uart1_SendBuffSize)
			{
				USART_SendData(USART1,Uart1_Send_buffer[Uart1_SCnt++]);
			}
			else
			{
				Uart1_SCnt=0;
				delay_ms(5);
				DE1=1;
				USART_ITConfig(USART1,USART_IT_TXE,DISABLE);			  	//发送完成 关闭中断
			}	
		}
}
