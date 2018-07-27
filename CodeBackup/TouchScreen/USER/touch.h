#ifndef __TOUCH_H
#define __TOUCH_H
#include "stm32f10_timer.h"
#include "LCD.h"

#define TP_PRES_DOWN 0x80  //触屏被按下	  
#define TP_CATH_PRES 0x40  //有按键按下了 

//与触摸屏芯片连接引脚	   
#define PEN  	PCin(10)  	//PC10 INT
#define DOUT 	PCin(2)   	//PC2  MISO
#define TDIN 	PCout(3)  	//PC3  MOSI
#define TCLK 	PCout(1)  	//PC1  SCLK
#define TCS  	PCout(0)  	//PC0  CS  

#define ERR_RANGE 30
#define  CMD_RDX  	 0xD0
#define  CMD_RDY  	 0x90

#define READ_TIMES 10
#define LOST_VAL 2

struct tp_pix_
{
	u16 x;
	u16 y;
};

#define  vx 8102
#define  vy 12028
#define  chx 3900
#define  chy 3680

extern struct tp_pix_  tp_pixad,tp_pixlcd;


char function(void);
void touch_clear(void);
void TP_Write_Byte(u8 num);						//向控制芯片写入一个数据
u16 TP_Read_AD(u8 CMD);							//读取AD转换值
u16 TP_Read_XOY(u8 xy);							//带滤波的坐标读取(X/Y)
u8 TP_Read_XY(u16 *x,u16 *y);					//双方向读取(X+Y)
u8 TP_Read_XY2(u16 *x,u16 *y);					//带加强滤波的双方向坐标读取
//void TP_Drow_Touch_Point(u16 x,u16 y,u16 color);//画一个坐标校准点
//void TP_Draw_Big_Point(u16 x,u16 y,u16 color);	//画一个大点
//u8 TP_Scan(u8 tp);								//扫描
void TP_Save_Adjdata(void);						//保存校准参数
//u8 TP_Get_Adjdata(void);						//读取校准参数
void TP_Adjust(void);							//触摸屏校准
void TP_Init(void);								//初始化
																 
void TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac);//显示校准信息
#endif  
