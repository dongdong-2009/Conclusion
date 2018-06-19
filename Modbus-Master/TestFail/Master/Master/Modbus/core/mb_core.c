#include "mb_core.h"
#include "mb_config.h"
#include "mb_crc.h"
#include "mb_port.h"
#include "mb_app.h"
#include "stm32f10x.h"
#include "usart.h"
#include "timer.h"
#include "stdio.h"
#include "stdlib.h"

static MB_EventType_t eQueuedEvent;
static BOOL     MB_EventMutex;		         //事件互斥锁，即一个信号发送后，如果还没有得到处理，那么不允许再次发送信号

unsigned char  MB_ADD=0x01;					       //从机地址  Slave-ID
unsigned short REG_HOLDING_START=0;			   //保持寄存器起始地址
unsigned short REG_HOLDING_NREGS=8;			   //保持寄存器个数
unsigned short REG_INPUT_START=0;          //输入寄存器起始地址
unsigned short REG_INPUT_NREGS=8;				   //寄存器采用动态分配

unsigned char  M_SendBuff[M_SendBuffLen];  //主机发送缓存区
unsigned short M_SendCnt=0;                //主机发送计数
unsigned short M_SendLen=0;                //主机发送字节长度

unsigned char  M_ReceiveBuff[M_ReceiveBuffLen];    //主机接收缓存区
unsigned short M_ReceiveCnt=0;                     //主机接收字节长度

unsigned char  S_SendBuff[S_SendBuffLen];          //从机发送缓存区
unsigned short S_SendCnt=0;                        //从机发送计数
unsigned short S_SendLen=0;                        //从机发送字节长度

unsigned char  S_ReceiveBuff[S_ReceiveBuffLen];    //从机接收缓存
unsigned short S_ReceiveCnt=0;                     //从机接收字节长度

unsigned short *usRegHoldingBuf;                   //保持寄存器缓存区
unsigned short *usRegInputBuf;                     //输入寄存器缓存区

mb_pro_t mb_pro_m;                                //主机信息结构体
mb_pro_t mb_pro_s;                                //从机信息结构体
unsigned long usTimerT35_50us;                    //发送间隔符

unsigned char MB_EventInit( void )
{
	MB_EventMutex = FALSE;		//事件锁
  return TRUE;
}

//状态切换
unsigned char MB_EventPost( MB_EventType_t eEvent )
{
	MB_EventMutex = TRUE;
  eQueuedEvent = eEvent;
  return TRUE;
}

//获取事件状态
unsigned char MB_EventGet( MB_EventType_t * eEvent )
{
	BOOL  xEventHappened = FALSE;
	if( MB_EventMutex )              //发送互斥锁
  {
		*eEvent = eQueuedEvent;
    MB_EventMutex = FALSE;
    xEventHappened = TRUE;
  }
  return xEventHappened;
}

MB_EventType_t MB_EventState()
{
	return eQueuedEvent;
}

//分配输入寄存器和保持寄存器存储空间
void MB_RegInit()
{
	usRegHoldingBuf=malloc(REG_HOLDING_NREGS*sizeof(unsigned short));  //分配REG_HOLDING_NREGS个unsigned short型存储类型，并将首地址存储在指针变量usRegHoldingBuf
	usRegInputBuf=malloc(REG_INPUT_NREGS*sizeof(unsigned short));
}

//根据波特率来确定Modbus间隔时间
void MB_Init(unsigned long ulBaudRate)
{
	/* Modbus RTU uses 8 Databits. */
  USART_Configuration(USART2, ulBaudRate);

	/* If baudrate > 19200 then we should use the fixed timer values
	 * t35 = 1750us. Otherwise t35 must be 3.5 times the character time.
	 */
	if( ulBaudRate > 19200 )
	{
		usTimerT35_50us = 35;       /* 1800us. */
	}
	else
	{
		/* The timer reload value for a character is given by:
		 *
		 * ChTimeValue = Ticks_per_1s / ( Baudrate / 11 )
		 *             = 11 * Ticks_per_1s / Baudrate
		 *             = 220000 / Baudrate
		 * The reload for t3.5 is 1.5 times this value and similary
		 * for t3.5.
		 */
		usTimerT35_50us = ( 7UL * 220000UL ) / ( 2UL * ulBaudRate );
	}
	TIM3_Int_Init(usTimerT35_50us,3600);
}

void MB_Poll()
{
	MB_EventType_t eEvent;

	if( MB_EventGet( &eEvent ) == TRUE )
	{
		switch(eEvent)
		{
			case EV_IDLE:
				break;
			
			case EV_M_SEND:						  //主机状态部分
				//			mb_ms_SendData(&gb_mb_pro);
				//			MB_EventPost(EV_M_WAIT);
				USART_IRQSet(1,0);
				break;
			
			case EV_M_WAIT:						  //等待接收，同时校验等待超时
				break;
			
			case EV_M_RECEIVEING:				//正在接收，同时校验完成超时
				break;
			
			case EV_M_RECEIVED:					//接收完成
				//此处对接收的数据进行处理
				M_ReceiveCnt=0;					  //该值表示接收数据的长度，当数据处理完成后记得清零，因为我没有对接收做处理，所以直接清零
				MB_EventPost(EV_IDLE);		//接收处理完成，一次协议通讯结束，切换到idle状态
				break;
			
			case EV_S_RECEIVEING:				//从机正在接收，同时校验完成超时
				break;
			
			case EV_S_RECEIVED:					//从机数据接收完成
				//对数据进行处理
				MB_S_Execute(S_ReceiveBuff,S_ReceiveCnt);
				S_ReceiveCnt=0;
				MB_EventPost(EV_S_SEND);	//处理完成，切换到发送状态发送响应
				break;
			
			case EV_S_SEND:
				USART_IRQSet(1,0);				//开始发送，发送完成后会自动切换到空闲状态
				break;
			
			default:
				break;
		}
	}
}

//主机发送数据包打包
void MB_M_FormatData()
{
	unsigned short crcval=0;
	unsigned char *databuff=M_SendBuff+MB_DATA_INDEX;   //databuff的起始地址是在M_SendBuff的起始地址上偏移MB_DATA_INDEX位   databuff[0]=M_SendBuff[MB_DATA_INDEX];
	
	M_SendBuff[MB_ADDR_INDEX]=MB_ADD;                 //ID
	M_SendBuff[MB_FUNCID_INDEX]=mb_pro_m.funcid;      //Function Code

	switch(mb_pro_m.funcid)
	{
		case FUNCID_READHDREG:                                   //功能码0x03
		{
			databuff[0]=((unsigned short)mb_pro_m.startadd)>>8;    //地址高位
			databuff[1]=(unsigned short)mb_pro_m.startadd;         //地址低位
			databuff[2]=((unsigned short)mb_pro_m.regN)>>8;        //数量高位
			databuff[3]=(unsigned short)mb_pro_m.regN;             //数量低位

			crcval=usMBCRC16((unsigned char *)M_SendBuff,6);       //计算CRC校验码
			databuff[4]=( unsigned char )( crcval & 0xFF );        //校验码低位
			databuff[5]=( unsigned char )( crcval >> 8 );          //校验码高位
			M_SendLen=8;                                           //发送数据长度为8
			M_SendCnt=0;
			break;
		}
		
		case FUNCID_READIPREG:                                     	//读输入寄存器
		{
			databuff[0]=((unsigned short)mb_pro_m.startadd)>>8;       //起始地址高位
			databuff[1]=(unsigned short)mb_pro_m.startadd;            //起始地址低位
			databuff[2]=((unsigned short)mb_pro_m.regN)>>8;           //寄存器数量高位
			databuff[3]=(unsigned short)mb_pro_m.regN;                //寄存器数量低位

			crcval=usMBCRC16((unsigned char *)M_SendBuff,6);          //计算CRC校验码
			databuff[4]=( unsigned char )( crcval & 0xFF );           //CRC校验码低位
			databuff[5]=( unsigned char )( crcval >> 8 );             //CRC校验码高位
			M_SendLen=8;                                              //发送数据长度
			M_SendCnt=0;
			break;
		}
	
		case FUNCID_WROHDREG:                                       //功能码0x06
		{
			databuff[0]=((unsigned short)mb_pro_m.startadd)>>8;       //起始地址高位
			databuff[1]=(unsigned short)mb_pro_m.startadd;            //起始地址低位
			databuff[2]=mb_pro_m.databuff[0];                         //数据高位
			databuff[3]=mb_pro_m.databuff[1];                         //数据低位

			crcval=usMBCRC16((unsigned char *)M_SendBuff,6);          //计算CRC校验码
			databuff[4]=( unsigned char )( crcval & 0xFF );           //CRC校验码低位
			databuff[5]=( unsigned char )( crcval >> 8 );             //CRC校验码低位
			M_SendLen=8; 																							//发送数据长度
			M_SendCnt=0;
			break;
		}
		case FUNCID_WRNHDREG:                                       //功能码0x10
		{
			unsigned char i=0;
			databuff[0]=((unsigned short)mb_pro_m.startadd)>>8;       //起始地址高位
			databuff[1]=(unsigned short)mb_pro_m.startadd;            //起始地址低位

			databuff[2]=((unsigned short)mb_pro_m.regN)>>8;           //寄存器数量高位
			databuff[3]=(unsigned short)mb_pro_m.regN;                //寄存器数量低位

			databuff[4]=(unsigned short)mb_pro_m.regN*2;              //发送字节数目
			for(i=0;i<mb_pro_m.regN;i++)                              //注意字节顺序
			{
				databuff[5+i*2]=mb_pro_m.databuff[i*2+1];		            //数据低位       
				databuff[6+i*2]=mb_pro_m.databuff[i*2];                 //数据高位
			}

			crcval=usMBCRC16((uint8_t *)M_SendBuff,7+mb_pro_m.regN*2); //计算CRC校验码
			databuff[5+mb_pro_m.regN*2]=( uint8_t )( crcval & 0xFF );  //CRC校验码低位
			databuff[6+mb_pro_m.regN*2]=( uint8_t )( crcval >> 8 );    //CRC校验码高位
			M_SendLen=9+mb_pro_m.regN*2;                               //数据发送长度
			M_SendCnt=0;
			break;
		}
		default:
			break;
	}

}

//从机数据处理
void MB_S_Execute(uint8_t *buff,uint16_t len)
{
	uint16_t crcval=0;
//	uint8_t mbId=buff[0];                //slave ID
	uint8_t func=buff[1];                //function Code

	uint16_t add=((unsigned short)buff[2]<<8)+buff[3]; //计算起始地址

	S_SendBuff[0]=MB_ADD;                //从机发送数据从机地址
	S_SendBuff[1]=func;                  //从机发送数据功能码

	switch(func)
	{
		case FUNCID_READHDREG:		//读保持寄存器
		{
			unsigned short num=((unsigned short)buff[4]<<8)+buff[5];                       //计算读取寄存器数量
			if(add<REG_HOLDING_START||(add+num)>(REG_HOLDING_START+REG_HOLDING_NREGS))     //地址有误
			{
				//发送错误码
			}
			else
			{
				//正常响应数据
				mb_pro_s.funcid=func;
				mb_pro_s.startadd=add;
				mb_pro_s.regN=num;
				mb_pro_s.mode=1;
				mb_pro_s.databuff=S_SendBuff+3;                //填写发送数据
				S_SendBuff[2]=2*num;                           //字节数
				eMBRegHoldingCB(&mb_pro_s);		                 //此函数会填充数据段
				crcval=usMBCRC16(S_SendBuff,3+2*num);
				S_SendBuff[3+2*num]=( unsigned char )( crcval & 0xFF );   //CRC低位
				S_SendBuff[4+2*num]=( unsigned char )( crcval >> 8 );     //CRC高位
				S_SendLen=5+2*num;                                        //发送长度
				S_SendCnt=0;
			 }
				break;
		 }
		
	case FUNCID_READIPREG:		//读输入寄存器
	{
		unsigned short num=((unsigned short)buff[4]<<8)+buff[5];
		if(add<REG_INPUT_START||(add+num)>(REG_INPUT_START+REG_INPUT_NREGS))
		{
			//发送错误码
		}
		else
		{
			//正常响应数据
			mb_pro_s.funcid=func;
			mb_pro_s.startadd=add;
			mb_pro_s.regN=num;
			mb_pro_s.mode=1;
			mb_pro_s.databuff=S_SendBuff+3;
			S_SendBuff[2]=2*num;         //字节数
			eMBRegInputCB(&mb_pro_s);		 //此函数会填充数据段
			crcval=usMBCRC16(S_SendBuff,3+2*num);
			S_SendBuff[3+2*num]=( unsigned char )( crcval & 0xFF );
			S_SendBuff[4+2*num]=( unsigned char )( crcval >> 8 );
			S_SendLen=5+2*num;
			S_SendCnt=0;
		 }
		 break;
	 }
	
	case FUNCID_WROHDREG:		//写单个保持寄存器
	{
		if(add<REG_HOLDING_START||add>(REG_HOLDING_START+REG_HOLDING_NREGS-1))
		{
			//发送错误码
		}
		else
		{
			//正常响应数据
			mb_pro_s.funcid=func;
			mb_pro_s.startadd=add;
			mb_pro_s.regN=1;
			mb_pro_s.mode=2;
			mb_pro_s.databuff=buff+4;
			S_SendBuff[2]=buff[2];                      //起始地址高低位
			S_SendBuff[3]=buff[3];
			S_SendBuff[4]=buff[4];                      //寄存器数量高地位
			S_SendBuff[5]=buff[5];
			eMBRegHoldingCB(&mb_pro_s);
			crcval=usMBCRC16(S_SendBuff,6);
			S_SendBuff[6]=( unsigned char )( crcval & 0xFF );
			S_SendBuff[7]=( unsigned char )( crcval >> 8 );
			S_SendLen=8;
			S_SendCnt=0;
		}
		break;
	}
	
	case FUNCID_WRNHDREG:		//写多个保持寄存器
	{
		unsigned short num=((unsigned short)buff[4]<<8)+buff[5];
		if(add<REG_HOLDING_START||add+num>(REG_HOLDING_START+REG_HOLDING_NREGS))
		{
			//发送错误码
		}
		else
		{
			//正常响应数据
			mb_pro_s.funcid=func;
			mb_pro_s.startadd=add;
			mb_pro_s.regN=num;
			mb_pro_s.mode=2;
			S_SendBuff[2]=buff[2];                 //起始地址高低位
			S_SendBuff[3]=buff[3];
			S_SendBuff[4]=buff[4];                 //寄存器数量高地位
			S_SendBuff[5]=buff[5];
			mb_pro_s.databuff=buff+7;
			eMBRegHoldingCB(&mb_pro_s);
			crcval=usMBCRC16(S_SendBuff,6);
			S_SendBuff[6]=( unsigned char )( crcval & 0xFF );
			S_SendBuff[7]=( unsigned char )( crcval >> 8 );
			S_SendLen=8;
			S_SendCnt=0;
		}
		break;
	}
	
	default: break;
	}
}
