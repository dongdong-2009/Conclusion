#include "D6F_PH.h"

void D6F_PH_Init(void)
{
	IIC_Init();
	IIC_Start();
	IIC_Send_Byte(0xD8); //DevID+WriteCmd
	IIC_Wait_Ack();
	IIC_Send_Byte(0x0B); //I2C Addr
	IIC_Wait_Ack();
	IIC_Send_Byte(0x00);
	IIC_Wait_Ack();
	IIC_Stop();
}

void D6F_PH_EXE_MCU(void)
{
	// Write 0x06 (MS=1 & MCU_on) to the Sens_Ctrl register (0xD040)
	// It would be safe to read/write only after 33ms
	IIC_Start();
	IIC_Send_Byte(0XD8);   //DevID+WriteCmd
	IIC_Wait_Ack();
	IIC_Send_Byte(0x00);  //I2C Addr
	IIC_Wait_Ack();
	IIC_Send_Byte(0xD0); 
	IIC_Wait_Ack();
	IIC_Send_Byte(0x40);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x18);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x06);
	IIC_Wait_Ack();
	IIC_Stop();
	
	//must wait 34ms or longer before reading registers
}

u16 D6F_PH_Read_Reg(u8 RegAddr)
{
	u16 data=0;
	u8 tempH=0,tempL=0;
	
	//Send address of internal register for requests
	// Write 0x2C to the Serial Control Register (0x02) to read from compensated flow register (0xD051 and 0xD052) through the Write buffer 0 (0x00) and Write buffer 1 (0x01)
	IIC_Start();
	IIC_Send_Byte(0xD8); //DevID+WriteCmd
	IIC_Wait_Ack();
	IIC_Send_Byte(0x00); //I2C Addr
	IIC_Wait_Ack();
	IIC_Send_Byte(0xD0); // Pressure stores in 0xD051
	IIC_Wait_Ack();
	IIC_Send_Byte(RegAddr);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x2C);
	IIC_Wait_Ack();
	IIC_Stop();
	
	// Read the compensated Flow Registers 2 bytes through the Read buffer 0 (0x07) and Read buffer 1 (0x08)
	IIC_Start();
	IIC_Send_Byte(0xD8); //DevID+WriteCmd
	IIC_Wait_Ack();
	IIC_Send_Byte(0x07); //I2C Addr
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(0xD9); //DevID+ReadCmd
	IIC_Wait_Ack();
	tempH=IIC_Read_Byte();
	IIC_Ack();
	tempL=IIC_Read_Byte();
	IIC_NAck();
	IIC_Stop();
	
	data=tempH*256+tempL;
	return data;
}

float D6F_PH_Pressure(void)
{
	float pressure=0.0;
	u16 data;
	data=D6F_PH_Read_Reg(0x51);
	pressure = ((float)(data-1024))/600-50;
	return pressure;
}

float D6F_PH_Temperature(void)
{
	float temperature=0.0;
	u16 data;
	
	data=D6F_PH_Read_Reg(0x61);
	temperature = ((float)(data-10214))/37.39;
	return temperature;
}

