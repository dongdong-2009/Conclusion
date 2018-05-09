#include "stm32f10x_it.h"
#include "Globle.h"
#include "modbus.h"
#include "touchscreen.h"
#include "string.h"
/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

void TIM1_UP_IRQHandler(void)
{ 
	if (TIM_GetITStatus(TIM1, TIM_IT_Update)!= RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //清除中断标志
		TIM_Cmd(TIM1,DISABLE);                       //停止定时器
		DE1=0;                                       //停止接收，切换为发送状态
    RS485_FrameFlag=1;                           //置位帧结束标记符
	}
}

void USART1_IRQHandler(void)
{ 
	u8 res;                                                //存储接收到的数据
  u8 err;                                                //串口硬件错误出发的中断
  if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)     //接收中断
  {
		if(USART_GetFlagStatus(USART1,USART_FLAG_NE|USART_FLAG_FE|USART_FLAG_PE)) 
			err=1;//检查到噪音、帧错误或校验错误
    else 
			err=0;
    
		res=USART_ReceiveData(USART1);            //读接收到的字节，同时相关标志自动清除
		if((RS485_RX_CNT<2047)&&(err==0))         //接收到的字节数量，在合理的范围内，同时无其他错误
    {
			RS485_RX_BUFF[RS485_RX_CNT]=res;        //获取数据
      RS485_RX_CNT++;                         //计数

      TIM_ClearITPendingBit(TIM1,TIM_IT_Update);           //清除定时器溢出中断
      TIM_SetCounter(TIM1,0);                   //当接收到一个新的字节时,将定时器1复位为0,重新计时(相当于watchdog)
      TIM_Cmd(TIM1,ENABLE);                    //使能定时器1，开始计时
    }
  }
}


void USART2_IRQHandler(void)
{ 
	char flag=0;
	int IsTrue=0;
	static unsigned int receivedCount = 0;
	char receivedData;
	
	if(USART_GetFlagStatus(USART2,USART_FLAG_ORE))
	{
		receivedData = Usart_GetChar(USART2);
		USART_ClearITPendingBit(USART2, USART_FLAG_ORE);//清除相应的标志位
	}
	
	if(USART_GetFlagStatus(USART2,USART_FLAG_NE)!=RESET)
	{
		USART_ClearFlag(USART2,USART_FLAG_NE);
	}
		
	if(USART_GetFlagStatus(USART2,USART_FLAG_FE)!=RESET)
	{
		USART_ClearFlag(USART2,USART_FLAG_FE);
	}
		
	if(USART_GetFlagStatus(USART2,USART_FLAG_PE)!=RESET)
	{
		USART_ClearFlag(USART2,USART_FLAG_PE);
	}
	
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		receivedData=Usart_GetChar(USART2);
		TSReceivedBuffer[receivedCount++]=receivedData;
			if(receivedCount==24)
			{
				if((TSReceivedBuffer[22]==0x66)&&(TSReceivedBuffer[23]==0x55))
				{
					flag=1;
				}
			}
			if(flag)
			{
				ReceivedNum=receivedCount;
				receivedCount=0;
				IsTrue = CheckTSReceivedData(TSReceivedBuffer);
				if(IsTrue)
				{
					TSPacketAnalysis(TSReceivedBuffer);
					if(TSTaskSel == READDATA)
					{
						TSSentDataGeneration(16,TSReadPortsBuffer,SentBuffer);
						DE2=0;
						UsartSendData(24,(char*)SentBuffer);
					}
					else if(TSTaskSel == SETDATA)
					{
						DE2=0;
						UsartSendData(24,(char*)tx2);
					}
					else if(TSTaskSel == START)
					{
						localControl=1;
						DE2=0;
						UsartSendData(24,(char*)tx3);
					}
					else if(TSTaskSel == TSSTOP)
					{
						localControl=0;
						DE2=0;
						UsartSendData(24,(char*)tx4);
					}
				}
			}
		else
		{
	   	Uart2_RCnt=0;	
		}
  }
  
  if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  {
		USART_ClearITPendingBit(USART2,USART_IT_TXE);
		Uart2_SCnt=0;
		delay_ms(10);
		DE2=1;
		USART_ITConfig(USART2,USART_IT_TXE,DISABLE);			  	//发送完成 关闭中断
  }
}

void TIM2_IRQHandler(void)
{
	static int ScanTime = 3;                           //端口固有扫描周期3s
	//检查指定的TIM中断发生与否，是否发生更新
  if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		{
			//RunTime无任务时，每隔15s读取端口数据和PID参数
			if(TSTaskSel == NON)
				{
					ScanTime--;
					if(ScanTime == 0)
						{
							TSreadPorts(TSReadPortsBuffer);
							ScanTime = 3;
						}
				}	
			else
			{
				//如果有任务，就进行对应的任务操作
				ScanTime = 3;
				TSDataProcess();	
			}
		}	   
	//清除中断标志位，TIM更新标志位
	TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
}


