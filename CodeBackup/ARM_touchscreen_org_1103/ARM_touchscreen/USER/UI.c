#include "UI.h"
#include <string.h>
#include "LCD.h"
void PAGE0(void)
{
	LCD_Fill(0,0,479,45,0X01CF);//BSTAR
	LCD_Fill(0,235,479,281,0X01CF);//function
	
	LCD_Fill(238,0,242,479,0X01CF);//
	LCD_Fill(242,138,479,142,0X01CF);//

	showzifustr(10,8,"AIR T&D",0xB723,0X01CF,1);
	showzifustr(10,247,"ON",0xFFFF,0X01CF,1);
	showzifustr(410,247,"OFF",0xFFFF,0X01CF,1);

}

unsigned char PAGE1(int PvRH,int PvTe,int PvCO2)
{
	char ss[6];	
	unsigned char i=0;			    
	LCD_Main_Clear(BLUEBG);

	LCD_Fill(238,45,242,281,0X01CF);//
	LCD_Fill(242,45,243,235,0xB723);//

	LCD_Fill(242,138,479,142,0X01CF);//
	LCD_Fill(242,142,479,143,0xB723);//

	LCD_Fill(242,235,380,281,0X01CF);//

	LCD_Fill(0,234,479,235,0xB723);//
	LCD_Fill(0,45,479,46,0xB723);//


	showzifustr(20,60,"Temperature:",0x0000,BLUEBG,1);
    showzifustr(262,60,"RH:",0x0000,BLUEBG,1);
	showzifustr(262,158,"CO#:",0x0000,BLUEBG,1);

 	showzifustr(127,247,"CONFIG",0xFFFF,0X01CF,1);  //dehumidifier
	
	inttostrA(PvTe,ss);
	showzifustr(10,120,ss,0,BLUEBG,2);
	showzifustr(200,120,"$C",0,BLUEBG,1);

	inttostr(PvCO2,ss);
	showzifustr(302,188,ss,0,BLUEBG,1);
	showzifustr(370,188,"ppm",0,BLUEBG,1);

	inttostrA(PvRH,ss);
	showzifustr(302,90,ss,0,BLUEBG,1);
    showzifustr(370,90,"%",0,BLUEBG,1);
    
	i=1;
	return i;
}
 
unsigned char PAGE2(int SvTe,int SvCO2)
{
	char ss[6];
	unsigned char i=0;	
	LCD_Main_Clear(BLUEBG);
	
	showzifustr(120,247,"  BACK  ",0xffff,0X01CF,1);
	showzifustr(242,247,"  SAVE  ",0xffff,0X01CF,1);

	LCD_Fill(238,0,242,479,0X01CF);//
    LCD_Fill(242,45,243,235,0xB723);//
   	LCD_Fill(0,234,479,235,0xB723);//
	LCD_Fill(0,45,479,46,0xB723);//


	showzifustr(20,60,"Temperature $C",0x0000,BLUEBG,1);
    showzifustr(272,60,"  CO# ppm",0x0000,BLUEBG,1);

	showzifustr(15,140,"<",0xB723,BLUEBG,1);
	showzifustr(200,140,">",0x7BCF,BLUEBG,1);
	showzifustr(260,140,"<",0xB723,BLUEBG,1);
	showzifustr(450,140,">",0x7BCF,BLUEBG,1);

	inttostrA(SvTe,ss);
	showzifustr(10,120,ss,0,BLUEBG,2);
	inttostr(SvCO2,ss);
	showzifustr(252,120,ss,0,BLUEBG,2);

	i=1;
	return i;

}

