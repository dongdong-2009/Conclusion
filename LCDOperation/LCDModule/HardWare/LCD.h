#ifndef __LCD_H
#define __LCD_H

#include "stdlib.h"
#include "stm32f10x_fsmc.h"
#include "sys.h"
#include "delay.h"

#define	LCD_REST PBout(1) //LCD REST    		 PB1 	

//LCD地址结构体
typedef struct
{
	u16 LCD_REG;   //地址为0x6007FFFE   往这里写寄存器地址
	u16 LCD_RAM;   //地址为0x60080000   往这里写具体数据
} LCD_TypeDef;

//将NE1连接到LCD_CS,只要我们操作的地址在第一个存储块内即可
//Bank1:60000000h--63ffffffh   Bank2:64000000h--67ffffffh 
//Bank3:68000000h--6bffffffh   Bank4:6c000000h--6fffffffh 
//A18作为数据命令区分线 
//注意设置时STM32内部会右移一位对齐，具体参考STM32手册中FSMC部分
//0X60000000是存储块1(NOR闪存或PSRAM)的首地址
//地址线是A18,偏移量为2^19=0x80000,地址从0-18
//结构体中定义为u16类型，将A18偏移量减去2，0x60080000-2=0x6007FFFE根据内部成员对其规则
#define LCD_BASE        ((u32)(0x60000000 | 0x0007FFFE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)

//LCD的画笔颜色和背景色	   
extern u16  POINT_COLOR;//默认红色    
extern u16  BACK_COLOR; //背景颜色.默认为白色

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	   0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 
#define BRRED 			     0XFC07 
#define GRAY  			     0X8430

//GUI颜色
#define BLUEBG           0X7DFF

//Pannel颜色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅色  
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)
#define LIGHTGRAY        0XEF5B //浅灰色


#define LCD_H 282
#define LCD_W 480

#define HDP 479
#define HT 531
#define HPS 43
#define LPS 8
#define HPW 10

#define VDP 271
#define VT 288
#define VPS 12
#define FPS 4
#define VPW 10

void LCD_WR_DATA(u16 data);                //写数据
void LCD_WR_REG(u16 reg);                  //写地址
void LCD_WR_REG_DATA(int reg,int data);    //写地址和数据
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);  //设置起始地址和结束地址，选定区域
void LCD_WriteRAM_Prepare(void);           //开始写入GRAM
void LCD_SetCursor(u16 Xpos, u16 Ypos);    //设置光标
void LCD_Clear(u16 color);                 //清屏
u16 LCD_RD_DATA(void);                     //读取LCD数据
u16 LCD_ReadReg(u8 LCD_Reg);               //读寄存器数据
u16 LCD_ReadPoint(u16 x,u16 y);            //读取某个点的颜色 
void LCD_DrawPoint(u16 x,u16 y);                                //画点 固定颜色
void LCD_DrawFastPoint(u16 x,u16 y,u16 color);                  //画点自定义颜色
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);              //画线
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);         //画矩形
void Draw_Circle(u16 x0,u16 y0,u8 r);                           //在指定位置画指定大小的圆
void showhanzi16(unsigned int x,unsigned int y,unsigned char index);  //在指定位置显示一个汉字(16*16大小)
void showhanzi32(unsigned int x,unsigned int y,unsigned char index);  //在指定位置显示一个汉字(32*32大小)
void showimage(u16 x,u16 y);																					//显示40*40图片
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);						    //显示一个字符
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);  //显示一个字符串,12/16字体
u32 LCD_Pow(u8 m,u8 n);                                               //m^n函数
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  						    //显示一个数字
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);				//显示 数字
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);                 //在指定区域内，填充某个颜色
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);					//指定区域，填充指定颜色，颜色采用查表法
void LCD_Init(void);
#endif
