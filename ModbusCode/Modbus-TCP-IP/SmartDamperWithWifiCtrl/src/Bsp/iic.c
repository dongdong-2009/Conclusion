#include "IIC.h"

void IIC_Init(void)                //初始化IIC的IO口				 
// SCL:PC11    SDA:PC12
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );		   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12; //PIM C11, C12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	IIC_SCL=1;
	IIC_SDA=1;
}

/*===================================================*/
/* Usage        : IIC_Status()                       */
/* Argument     : None                               */
/* Return value : 8bit Status                        */
/*                0: SDA = 1, SCL = 1                */
/*                1: SDA = 1, SCL = 0                */
/*                2: SDA = 0, SCL = 1                */
/*                3: SDA = 0, SCL = 0                */
/*===================================================*/
u8 IIC_Status(void)
{
	SDA_IN(); //SDA设置为输入  
	SCL_IN(); //SCL设置为输入
	IIC_DELAY();
	return 3-((READ_SDA<<1)+READ_SCL);
}

/*===================================================*/
/* Usage        : IIC_Start()                        */
/* Argument     : None                               */
/* Return value : None                               */
/*===================================================*/
void IIC_Start(void)				//发送IIC开始信号，时长半周期
{
//   Time:0 - 1 - 2
//    SCL: --- ---\
//    SDA: ---\___
//start信号可能是总线处于空闲状态(SCL=1,SDA=1)发起的，也可能是从slave_ACK之后(SCL=1,SDA=0)直接restart的，也可能是从master_ACK之后(SCL=1,SDA=0)restart的
	SDA_OUT();
	IIC_SDA=1;	  	  
	delay_us(1);
	IIC_SCL=1;
	delay_us(5);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(6);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
	delay_us(2);
}

/*===================================================*/
/* Usage        : IIC_Stop()                         */
/* Argument     : None                               */
/* Return value : None                               */
/*===================================================*/
void IIC_Stop(void)	  			//发送IIC停止信号，时长半周期
{
//   Time:0 - 1 - 2
//    SCL: --- --- 
//    SDA: ___/--- 
	SDA_OUT();     //sda线输出
	IIC_SCL=0;
	IIC_SDA=0; 
	delay_us(4);	
	IIC_SCL=1; 
 	delay_us(6);   //STOP:when CLK is high DATA change form low to high
	IIC_SDA=1;     //发送I2C总线结束信号
	delay_us(6);
}

/*===================================================*/
/* Usage        : IIC_Wait_Ack()                     */
/* Argument     : None                               */
/* Return value : 1 - receive ACK                    */
/*              : 0 - receive NACK                   */
/*===================================================*/
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入
	IIC_SDA=1;     //主机释放数据总线，等待从机产生应答信号
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);  //等待从机对数据总线的操作，低电平代表应答
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)  //如果时间超时，没有应答信号就产生停止信号结束
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;            //时钟输出0
	return 0;             //如果有响应的话就返回0
} 

/*===================================================*/
/* Usage        : IIC_Ack()                         */
/* Argument     : None                               */
/* Return value : None                               */
/*===================================================*/
void IIC_Ack(void)
{
//   Time:0 - 1 - 2 - 3 - 4
//    SCL:\___ ___/--- --- 
//    SDA: XXX\___ ___ ___
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(5);
	IIC_SCL=0;
}

/*===================================================*/
/* Usage        : IIC_NAck()                         */
/* Argument     : None                               */
/* Return value : None                               */
/*===================================================*/
void IIC_NAck(void)
{
//   Time:0 - 1 - 2 - 3 - 4
//    SCL:\___ ___/--- --- 
//    SDA: ___/--- --- ---
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(5);
	IIC_SCL=0;
}

/*===================================================*/
/* Usage        : IIC_Send_Byte(0x22)                */
/* Argument     : None                               */
/* Return value : None                               */
/*===================================================*/
void IIC_Send_Byte(u8 txd)
{                        
  u8 t;   
	SDA_OUT(); 	    
  IIC_SCL=0;//拉低时钟开始数据传输
  for(t=0;t<8;t++)
  {
		//IIC_SDA=(txd&0x80)>>7;
    if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(2);   
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
  }	 
} 	    

/*===================================================*/
/* Usage        : IIC_Read_Byte(1)                   */
/* Argument     : None                               */
/* Return value : unsigned int8 read data            */
/*===================================================*/
u8 IIC_Read_Byte(void)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
  for(i=0;i<8;i++ )
	{
    IIC_SCL=0; 
    delay_us(2);
		IIC_SCL=1;
    receive<<=1;
    if(READ_SDA)receive++;   
		delay_us(1); 
  }					 
  return receive;
}

void D6F_PH_Init(void)
{
	IIC_Init();
	IIC_Start();
	IIC_Send_Byte(0xD8);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x0B);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x00);
	IIC_Wait_Ack();
	IIC_Stop();
}

u16 D6F_PH_Read_Reg(u8 RegAddr)
{
	u16 data=0;
	u8 tempH=0,tempL=0;
	
	// Write 0x06 (MS=1 & MCU_on) to the Sens_Ctrl register (0xD040)
	// It would be safe to read/write only after 33ms
	IIC_Start();
	IIC_Send_Byte(0XD8);  
	IIC_Wait_Ack();
	IIC_Send_Byte(0x00); 
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

	delay_ms(34);
	
	//Send address of internal register for requests
	// Write 0x2C to the Serial Control Register (0x02) to read from compensated flow register (0xD051 and 0xD052) through the Write buffer 0 (0x00) and Write buffer 1 (0x01)
	IIC_Start();
	IIC_Send_Byte(0xD8);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x00);
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
	IIC_Send_Byte(0xD8); // 
	IIC_Wait_Ack();
	IIC_Send_Byte(0x07);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(0xD9);
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
