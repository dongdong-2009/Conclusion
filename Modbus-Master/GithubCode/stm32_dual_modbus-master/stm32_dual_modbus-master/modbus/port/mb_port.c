#include "mb_port.h"
#include "mb_config.h"
#include "mb_core.h"

#include "stm32f10x.h"

/*******************************************************���ڲ���*****************************************/
void SendChar(unsigned char ch)
{
	USART_SendData(UART5,ch);
}

unsigned char GetChar()
{
	return USART_ReceiveData(UART5);
}

void USART_IRQSet(unsigned char txIrq,unsigned char rxIrq)
{
	if(1 == rxIrq)
	{
		//RS_485_RX_EN();
		USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
	}
	else
	{
		USART_ITConfig(UART5, USART_IT_RXNE, DISABLE);
	}

	if(1 == txIrq)
	{
		//RS_485_TX_EN();
		USART_ITConfig(UART5, USART_IT_TXE, ENABLE);
	}
	else
	{
		USART_ITConfig(UART5, USART_IT_TXE, DISABLE);
	}
}

void Send_IRQ()
{
	MB_EventType_t sta=MB_EventState();
	switch(sta)
	{
	case EV_M_SEND:
	{
		if(M_SendLen>0)
		{
			SendChar(*(M_SendBuff+M_SendCnt));
			M_SendCnt++;
			M_SendLen--;
		}
		else		//�������һ���ֽ�
		{
			USART_IRQSet(0,1);				//�رշ���
			MB_EventPost(EV_M_WAIT);
			//������ʱ�����г�ʱ��ʱ
			TIM_SetAutoreload(TIM3,usTimerT35_50us*50);
			TIM_IRQSet(1);
		}
		break;
	}
	case EV_S_SEND:
	{
		if(S_SendLen>0)
		{
			SendChar(*(S_SendBuff+S_SendCnt));
			S_SendCnt++;
			S_SendLen--;
		}
		else
		{
			USART_IRQSet(0,1);				//�رշ���,�򿪽���
			MB_EventPost(EV_IDLE);
		}

		break;
	}
	}

}

void Receive_IRQ()
{
	uint8_t ch;
	ch=GetChar();

	MB_EventType_t sta=MB_EventState();
	switch(sta)
	{
	case EV_M_WAIT:		//��Ӧû�г�ʱ
		M_ReceiveBuff[M_ReceiveCnt++]=ch;
		TIM_SetAutoreload(TIM3,usTimerT35_50us);	//�ָ���ʱ����ʱ
		MB_EventPost(EV_M_RECEIVEING);			//�л�״̬
		break;
	case EV_M_RECEIVEING:
		M_ReceiveBuff[M_ReceiveCnt++]=ch;
		break;
	case EV_IDLE:		//����״̬����������,˵���ǿ�ʼ�˴ӻ�״̬
		S_ReceiveBuff[S_ReceiveCnt++]=ch;
		MB_EventPost(EV_S_RECEIVEING);			//�л�״̬
		break;
	case EV_S_RECEIVEING:
		S_ReceiveBuff[S_ReceiveCnt++]=ch;
		break;
	}

	//������ˢ�¶�ʱ��
	TIM_IRQSet(1);
}

void TIM_IRQSet(unsigned char tmIrq)
{
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_SetCounter(TIM3,0);
	if(tmIrq==1)
	{
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	}
	else
	{
		TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE);
	}
}

void Time_IRQ()		//3.5Tʱ�䵽�������ɣ�
{
	TIM_IRQSet(0);	//�رն�ʱ��

	MB_EventType_t sta=MB_EventState();
	switch(sta)
	{
	case EV_M_WAIT:							//���յȴ���ʱ
		MB_EventPost(EV_IDLE);			//�������˴�ͨѶ
		TIM_SetAutoreload(TIM3,usTimerT35_50us);	//�ָ���ʱ����ʱ
		break;
	case EV_M_RECEIVEING:
		MB_EventPost(EV_M_RECEIVED);		//�������
		break;
	case EV_S_RECEIVEING:
		USART_IRQSet(0,0);		//������ɣ��رս����ж�
		MB_EventPost(EV_S_RECEIVED);			//�л������մ���
		break;
	}
}

/*****************************************************��ʱ������*******************************************/


