#ifndef __MYIIC_H
#define __MYIIC_H

#include "stm32f10x.h"
#include "Globe.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//IIC驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////


 
//IO口操作,只对单一的IO口!
//确保n的值小于16!


//IO方向设置
#define SDA_IN()  {GPIOE->CRL&=0XFFF0FFFF;GPIOE->CRL|=(u32)8<<16;}   //上拉下拉输入模式
#define SDA_OUT() {GPIOE->CRL&=0XFFF0FFFF;GPIOE->CRL|=3<<16;}        //推挽输出模式

//IO操作函数	   PE3---SCL   PE4---SDA
#define IIC_SCL    PEout(3) //SCL
#define IIC_SDA    PEout(4) //SDA	 
#define READ_SDA   PEin(4)  //输入SDA 

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);

#endif
















