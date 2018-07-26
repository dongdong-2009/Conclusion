#include "24LC512.h"
#include "systick_timer.h"

//向指定地址写一个数据
void LC512_WriteByte(u16 addr,u8 data)
{
	IIC_Start();
	IIC_Send_Byte(LC512_Write_Addr);      //写命令
	IIC_Wait_Ack();
	IIC_Send_Byte((u8)(addr/256));         //写地址高位
	IIC_Wait_Ack();
	IIC_Send_Byte((u8)(addr%256));            //写地址低位
	IIC_Wait_Ack();
	IIC_Send_Byte(data);                  //写数据
	IIC_Wait_Ack();
	IIC_Stop();                           //停止信号
	Delay_ms(5);
}

//在指定地址读一个数据
u8 LC512_ReadByte(u16 addr)
{
	u8 temp=0;
	
	IIC_Start();
	IIC_Send_Byte(LC512_Write_Addr);
	IIC_Wait_Ack();
	IIC_Send_Byte((u8)(addr/256));
	IIC_Wait_Ack();
	IIC_Send_Byte((u8)(addr%256));
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(LC512_Read_Addr);
	IIC_Wait_Ack();
	temp=IIC_Read_Byte(0);   //产生非应答信号
	IIC_Stop();
	
	return temp;	
}

//向任意地址写入length个字节，写入数据存放在buffer中
void LC512_Write(u8 *buffer, u16 addr,u16 length)
{
	IIC_Start();
	IIC_Send_Byte(LC512_Write_Addr);
	IIC_Wait_Ack();
	IIC_Send_Byte((u8)(addr/256));
	IIC_Wait_Ack();
	IIC_Send_Byte((u8)(addr%256));
	IIC_Wait_Ack();
	while(length!=0)
	{
		IIC_Send_Byte(*buffer++);
		IIC_Wait_Ack();
		addr++;
		length--;
		if(addr%Page_Byte==0)
		{
			IIC_Stop();
			Delay_ms(5);
			IIC_Start();
			IIC_Send_Byte(LC512_Write_Addr);
			IIC_Wait_Ack();
			IIC_Send_Byte((u8)(addr/256));
			IIC_Wait_Ack();
			IIC_Send_Byte((u8)(addr%256));
			IIC_Wait_Ack();
		}
	}
	IIC_Stop();
	Delay_ms(5);	
}


//从任意地址读出length个字节，存放在buffer数组中
void LC512_Read(u8 *buffer, u16 addr,u16 length)
{
	IIC_Start();
	IIC_Send_Byte(LC512_Write_Addr);
	IIC_Wait_Ack();
	IIC_Send_Byte((u8)(addr/256));
	IIC_Wait_Ack();
	IIC_Send_Byte((u8)(addr%256));
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(LC512_Read_Addr);
	IIC_Wait_Ack();
	while(--length)
	{
		*buffer++=IIC_Read_Byte(1);
	}
	*buffer=IIC_Read_Byte(0);
	IIC_Stop();
}

//清楚所有的数据
void LC512_Clear(void)
{
	u16 temp=(Max_Addr+1)/Page_Byte;
	u16 addr=0;
	u16 i=0,j=0;
	
	for(i=0;i<temp;i++)
	{
		IIC_Start();
		IIC_Send_Byte(LC512_Write_Addr);
		IIC_Wait_Ack();
		IIC_Send_Byte((u8)(addr/256));
		IIC_Wait_Ack();
		IIC_Send_Byte((u8)(addr%256));
		IIC_Wait_Ack();
		for(j=0;j<128;j++)
		{
			IIC_Send_Byte(0x00);
			IIC_Wait_Ack();
		}
		IIC_Stop();
		Delay_ms(5);
		addr+=Page_Byte;
	}
}
