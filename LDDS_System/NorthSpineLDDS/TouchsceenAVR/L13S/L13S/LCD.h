

#define   LCD_RS_H	  PORTG|= 1<<0
#define   LCD_RS_L    PORTG &= ~(1<<0)

#define   LCD_WR_H    PORTG |= 1<<1
#define   LCD_WR_L    PORTG &= ~(1<<1)

#define   LCD_RD_H     PORTG |= 1<<2
#define   LCD_RD_L     PORTG &= ~(1<<2)

#define   LCD_CS_H     PORTD |= 1<<0
#define   LCD_CS_L     PORTD&= ~(1<<0)

#define   LCD_REST_H    PORTG |= 1<<4
#define   LCD_REST_L    PORTG &= ~(1<<4)

#define   LCD_BG_H	  PORTG|= 1<<3
#define   LCD_BG_L    PORTG &= ~(1<<3)

/**************************
       数据输出口
**************************/
#define DATAH  PORTC
#define DATAL  PORTA

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

void LCD_Writ_Bus(char VH,char VL) ;
void LCD_WR_DATA(int da);
void LCD_WR_REG(int da);
void LCD_WR_REG_DATA(int reg,int da);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void Lcd_Init(void);
void LCD_Clear(unsigned int Color);
void LCD_Fill(unsigned int xsta,unsigned int ysta,unsigned int xend,unsigned int yend,unsigned int color);
void showzifu(unsigned int x,unsigned int y,char val,unsigned int dcolor,unsigned int bgcolor);
void showzifustr(unsigned int x,unsigned int y,char *str,unsigned int dcolor,unsigned int bgcolor); 
void inttostr(int dd,char *str);
void inttostrA(int dd,char *str);
void inttostrC(int dd,char *str);
//void showzifustrA(unsigned int x,unsigned int y,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);
void LCD_DrawRectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void showlogo(unsigned int x,unsigned int y,char val,unsigned int dcolor,unsigned int bgcolor);
void showlogostr(unsigned int x,unsigned int y,char *str,unsigned int dcolor,unsigned int bgcolor);