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

unsigned char PAGEpw(void)
{
	char ss[6];	
	unsigned char i=0;			    
	LCD_Main_Clear(BLUEBG);

//	LCD_Fill(238,45,242,281,0X01CF);//
//	LCD_Fill(242,45,243,235,0xB723);//

//	LCD_Fill(242,138,479,142,0X01CF);//
//	LCD_Fill(242,142,479,143,0xB723);//

//	LCD_Fill(242,235,380,281,0X01CF);//

	LCD_Fill(0,234,479,235,0xB723);//
	LCD_Fill(0,45,479,46,0xB723);  //

	
	LCD_Fill(60,60,100,100,0xB723);  // button 1
	LCD_Fill(60,120,100,160,0xB723);  //button 2
	LCD_Fill(60,180,100,220,0xB723);  //button 3
	
	LCD_Fill(120,60,160,100,0xB723);  // button 4
	LCD_Fill(120,120,160,160,0xB723);  //button 5
	LCD_Fill(120,180,160,220,0xB723);  //button 6
	
	LCD_Fill(180,60,220,100,0xB723);  // button 7
	LCD_Fill(180,120,220,160,0xB723);  //button 8
	LCD_Fill(180,180,220,220,0xB723);  //button 9
	
  LCD_Fill(240,60,280,100,0xB723);  // button *
	LCD_Fill(240,120,280,160,0xB723);  //button 0
	LCD_Fill(240,180,280,220,0xB723);  //button #
	
	
			
	LCD_Fill(340,60,420,120,0xB723);  //  button enter
  LCD_Fill(340,150,420,210,0xB723);  //   button back
	

											


	showzifustr(70,70,"1",0x0000,0xB723,1);
  showzifustr(70,130,"2",0x0000,0xB723,1);
	showzifustr(70,190,"3",0x0000,0xB723,1);
	
	showzifustr(130,70,"4",0x0000,0xB723,1);
  showzifustr(130,130,"5",0x0000,0xB723,1);
	showzifustr(130,190,"6",0x0000,0xB723,1);

  showzifustr(190,70,"7",0x0000,0xB723,1);
  showzifustr(190,130,"8",0x0000,0xB723,1);
	showzifustr(190,190,"9",0x0000,0xB723,1);  
	
	showzifustr(250,70,"*",0x0000,0xB723,1);
  showzifustr(250,130,"0",0x0000,0xB723,1);
	showzifustr(250,190,"#",0x0000,0xB723,1);
	
	
	showzifustr(360,80,"Enter",0x0000,0xB723,1);
	showzifustr(360,210,"Return",0x0000,0xB723,1);
	
	
	i=4;
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

