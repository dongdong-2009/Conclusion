#include "UI.h"
#include <string.h>
//#include "config.h"

void PAGE0(void)
{
	LCD_Fill(0,0,479,30,0X8430);//BSTAR
	LCD_Fill(0,30,30,242,0X8430);

	LCD_Fill(449,30,479,242,0X8430);//BSTAR
	LCD_Fill(0,242,479,281,0X8430);//function
	
	showzifustr(5,5,"BSTAR",0xB723,0X8430);
	showzifustr(10,247,"ON",0xB723,0X8430);
	showzifustr(400,247,"OFF",0xB723,0X8430);


}


void PAGE1(int PvRH,int PvTe,int SvTe,int PvCO2,int SvCO2)
{
	char ss[6];
	LCD_Main_Clear(0xffff);

	LCD_Fill(160,30,330,60,0xB5B6);//
	LCD_Fill(330,30,479,60,0x94b2);//

	LCD_Fill(0,30,160,120,0x5ACB);//Hum
	LCD_Fill(0,121,160,180,0x7BCF);//AF
	LCD_Fill(0,181,160,241,0x94B2);//Tem
	
	showzifustr(170,40,"PV",0xffff,0xB5B6);
	showzifustr(340,40,"Unit",0xffff,0x94b2);
	
	showzifustr(340,90,"$C",0,0xffff);
	showzifustr(340,150,"ppm",0,0xffff);
	showzifustr(340,210,"%",0,0xffff);	
	
	showzifustr(30,90,"TEMP:",0xffff,0x5ACB);
	showzifustr(30,150,"CO2",0xffff,0x7BCF);
	showzifustr(30,210,"RH",0xffff,0x94B2);

 	showzifustr(127,247,"CONFIG",0xB723,0X8430);  //dehumidifier
//	showzifustr(250,247,"    ",0xffff,0x7497);	
 //	showzifustr(244,247,"UNOCCUP",0xB723,0X8430);  //dehumidifier
//	showzifustr(250,247,"    ",0xffff,0x7497);
	
	inttostrA(PvTe,ss);
	showzifustr(160,90,ss,0,0xffff);
	inttostrA(PvCO2,ss);
	showzifustr(160,150,ss,0,0xffff);
	inttostrA(PvRH,ss);
	showzifustr(160,210,ss,0,0xffff);

}
 
void PAGE2(int SvTe,int SvCO2)
{
	char ss[6];
	LCD_Main_Clear(0xffff);
	
	showzifustr(120,247,"  BACK  ",0xB723,0X8430);
	showzifustr(242,247,"  SAVE  ",0xB723,0X8430);
	
	LCD_Fill(0,30,242,60,0x5ACB);//H
	LCD_Fill(242,30,479,60,0xB5B6);//AF
	

	showzifustr(80,35,"TEMP",0xffff,0x5ACB);
    showzifustr(141,35,"$C",0xffff,0x5ACB);
	showzifustr(320,35,"CON",0xffff,0xB5B6);
	showzifustr(380,35,"PPM",0xffff,0xB5B6);

	showzifustr(40,140,"<",0xB723,0xffff);
	showzifustr(200,140,">",0x7BCF,0xffff);
	showzifustr(280,140,"<",0xB723,0xffff);
	showzifustr(440,140,">",0x7BCF,0xffff);

	
	inttostrA(SvTe,ss);
	showzifustr(80,140,ss,0,0xffff);
	inttostrA(SvCO2,ss);
	showzifustr(320,140,ss,0,0xffff);

}

