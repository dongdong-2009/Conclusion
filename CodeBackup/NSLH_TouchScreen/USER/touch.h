#ifndef __TOUCH_H
#define __TOUCH_H
#include "stm32f10_timer.h"
#include "LCD.h"

#define TP_PRES_DOWN 0x80  //����������	  
#define TP_CATH_PRES 0x40  //�а��������� 

//�봥����оƬ��������	   
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
void TP_Write_Byte(u8 num);						//�����оƬд��һ������
u16 TP_Read_AD(u8 CMD);							//��ȡADת��ֵ
u16 TP_Read_XOY(u8 xy);							//���˲��������ȡ(X/Y)
u8 TP_Read_XY(u16 *x,u16 *y);					//˫�����ȡ(X+Y)
u8 TP_Read_XY2(u16 *x,u16 *y);					//����ǿ�˲���˫���������ȡ
//void TP_Drow_Touch_Point(u16 x,u16 y,u16 color);//��һ������У׼��
//void TP_Draw_Big_Point(u16 x,u16 y,u16 color);	//��һ�����
//u8 TP_Scan(u8 tp);								//ɨ��
void TP_Save_Adjdata(void);						//����У׼����
//u8 TP_Get_Adjdata(void);						//��ȡУ׼����
void TP_Adjust(void);							//������У׼
void TP_Init(void);								//��ʼ��
																 
void TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac);//��ʾУ׼��Ϣ
#endif  
