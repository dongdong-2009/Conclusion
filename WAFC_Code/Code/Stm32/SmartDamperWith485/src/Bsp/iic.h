#ifndef __IIC_H
#define __IIC_H
#include "bsp_hwConfig.h"
#include "bsp_systimer.h"

//IO��������
//SCL: PC11      SDA: PC12
#define SCL_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}
#define SCL_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}
#define SDA_IN()  {GPIOC->CRH&=0XFFF0FFFF;GPIOC->CRH|=8<<16;}
#define SDA_OUT() {GPIOC->CRH&=0XFFF0FFFF;GPIOC->CRH|=3<<16;}

//IO��������	 
#define IIC_SCL    PC_out(11) //SCL
#define IIC_SDA    PC_out(12) //SDA	 
#define READ_SDA   PC_in(12)  //����SDA 
#define READ_SCL   PC_in(11)  //����SCL

//IIC��������
#define IIC_SCL_1  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}
#define IIC_SCL_0  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;PCout(11)=0;}
#define IIC_SDA_1  {GPIOC->CRH&=0XFFF0FFFF;GPIOC->CRH|=8<<16;}
#define IIC_SDA_0  {GPIOC->CRH&=0XFFF0FFFF;GPIOC->CRH|=3<<16;PCout(12)=0;}

#define IIC_DELAY() delay_us(4) //����I2C�����ٶȣ�ÿһ��Delay��ʾ1/4������, ����4��ʾ16usһ�����ڣ�����Ƶ��1000KHz/4/4=62.5KHz

//ÿһ��λ���������͵�ƽ
//IIC���в�������
void IIC_Init(void);  

u8 IIC_Status(void);  

void IIC_Start(void);	
void IIC_Stop(void);	
u8 IIC_Wait_Ack(void);
void IIC_Ack(void);	
void IIC_NAck(void); 
void IIC_Send_Byte(u8 txd);
u8 IIC_Read_Byte(void);


#endif
















