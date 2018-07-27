#ifndef __UI_H
#define __UI_H		



void PAGE0(void);
void PAGE1(int PvT,int PvH,int SvH,int PvAF,int SvAF);
void PAGE2(int SvH,int SvAF);


extern void LCD_Main_Clear(unsigned int Color);
extern void LCD_Fill(unsigned int xsta,unsigned int ysta,unsigned int xend,unsigned int yend,unsigned int color);
extern void showzifu(unsigned int x,unsigned int y,char val,unsigned int dcolor,unsigned int bgcolor);
extern void showzifustr(unsigned int x,unsigned int y,char *str,unsigned int dcolor,unsigned int bgcolor); 
extern void inttostr(int dd,char *str);
extern void inttostrA(int dd,char *str);
extern void inttostrB(int dd,char *str);
extern void inttostrC(int dd,char *str);
//void showzifustrA(unsigned int x,unsigned int y,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);
extern void LCD_DrawRectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
extern void showlogo(unsigned int x,unsigned int y,char val,unsigned int dcolor,unsigned int bgcolor);
extern void showlogostr(unsigned int x,unsigned int y,char *str,unsigned int dcolor,unsigned int bgcolor);
#endif 

