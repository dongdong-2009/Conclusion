#ifndef __LCD_H
#define __LCD_H

#include "stdlib.h"
#include "stm32f10x_fsmc.h"
#include "sys.h"
#include "delay.h"

#define	LCD_REST PBout(1) //LCD REST    		 PB1 	

//LCD��ַ�ṹ��
typedef struct
{
	u16 LCD_REG;   //��ַΪ0x6007FFFE   ������д�Ĵ�����ַ
	u16 LCD_RAM;   //��ַΪ0x60080000   ������д��������
} LCD_TypeDef;

//��NE1���ӵ�LCD_CS,ֻҪ���ǲ����ĵ�ַ�ڵ�һ���洢���ڼ���
//Bank1:60000000h--63ffffffh   Bank2:64000000h--67ffffffh 
//Bank3:68000000h--6bffffffh   Bank4:6c000000h--6fffffffh 
//A18��Ϊ�������������� 
//ע������ʱSTM32�ڲ�������һλ���룬����ο�STM32�ֲ���FSMC����
//0X60000000�Ǵ洢��1(NOR�����PSRAM)���׵�ַ
//��ַ����A18,ƫ����Ϊ2^19=0x80000,��ַ��0-18
//�ṹ���ж���Ϊu16���ͣ���A18ƫ������ȥ2��0x60080000-2=0x6007FFFE�����ڲ���Ա�������
#define LCD_BASE        ((u32)(0x60000000 | 0x0007FFFE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)

//LCD�Ļ�����ɫ�ͱ���ɫ	   
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

//������ɫ
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

//GUI��ɫ
#define BLUEBG           0X7DFF

//Pannel��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			     0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
#define LIGHTGRAY        0XEF5B //ǳ��ɫ


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

void LCD_WR_DATA(u16 data);                //д����
void LCD_WR_REG(u16 reg);                  //д��ַ
void LCD_WR_REG_DATA(int reg,int data);    //д��ַ������
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);  //������ʼ��ַ�ͽ�����ַ��ѡ������
void LCD_WriteRAM_Prepare(void);           //��ʼд��GRAM
void LCD_SetCursor(u16 Xpos, u16 Ypos);    //���ù��
void LCD_Clear(u16 color);                 //����
u16 LCD_RD_DATA(void);                     //��ȡLCD����
u16 LCD_ReadReg(u8 LCD_Reg);               //���Ĵ�������
u16 LCD_ReadPoint(u16 x,u16 y);            //��ȡĳ�������ɫ 
void LCD_DrawPoint(u16 x,u16 y);                                //���� �̶���ɫ
void LCD_DrawFastPoint(u16 x,u16 y,u16 color);                  //�����Զ�����ɫ
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);              //����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);         //������
void Draw_Circle(u16 x0,u16 y0,u8 r);                           //��ָ��λ�û�ָ����С��Բ
void showhanzi16(unsigned int x,unsigned int y,unsigned char index);  //��ָ��λ����ʾһ������(16*16��С)
void showhanzi32(unsigned int x,unsigned int y,unsigned char index);  //��ָ��λ����ʾһ������(32*32��С)
void showimage(u16 x,u16 y);																					//��ʾ40*40ͼƬ
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);						    //��ʾһ���ַ�
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);  //��ʾһ���ַ���,12/16����
u32 LCD_Pow(u8 m,u8 n);                                               //m^n����
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  						    //��ʾһ������
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);				//��ʾ ����
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);                 //��ָ�������ڣ����ĳ����ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);					//ָ���������ָ����ɫ����ɫ���ò��
void LCD_Init(void);
#endif
