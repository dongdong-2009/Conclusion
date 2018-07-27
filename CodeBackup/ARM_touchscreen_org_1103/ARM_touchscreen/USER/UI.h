#ifndef __UI_H
#define __UI_H		

void PAGE0(void);
unsigned char PAGE1(int PvT,int PvH,int PvAF);
unsigned char PAGE2(int SvH,int SvAF);
extern void LCD_Main_Clear(unsigned int Color);
extern void LCD_Fill(unsigned int xsta,unsigned int ysta,unsigned int xend,unsigned int yend,unsigned int color);
extern void showzifu(unsigned int x,unsigned int y,char val,unsigned int dcolor,unsigned int bgcolor);
extern void showzifularge(unsigned int x,unsigned int y,char val,unsigned int dcolor,unsigned int bgcolor);
extern void showzifustr(unsigned int x,unsigned int y,char *str,unsigned int dcolor,unsigned int bgcolor,unsigned char size); 
extern void inttostr(int dd,char *str);
extern void inttostrA(int dd,char *str);
extern void inttostrB(int dd,char *str);
extern void inttostrC(int dd,char *str);
#endif 

