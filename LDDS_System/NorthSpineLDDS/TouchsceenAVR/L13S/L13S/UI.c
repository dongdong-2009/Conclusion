#include "UI.h"
#include <string.h>
#include "config.h"

void UI(void)
{
	char ss[6];
 	LCD_BG_H;
	LCD_Clear(0xffff);
	LCD_Fill(0,0,259,150,0x3b35);
	LCD_Fill(260,0,479,150,0x32b2);
	LCD_Fill(0,151,319,281,0xffff);
	LCD_Fill(320,151,479,281,0x012C);
	showzifustr(15,25,"Temperature",0xffff,0x3b35);
	showzifustr(192,80,"$C",0xffff,0x3b35);
	showzifustr(285,25,"Humidity",0xffff,0x32b2);
	showzifustr(427,80,"%",0xffff,0x32b2);
	showzifustr(15,156,"Setting",0x3b35,0xffff);
	inttostrC(25,ss);
	showzifustr(180,220,ss,0,0xffff);
	showzifustr(145,220,"<",0x8410,0xffff);
	showzifustr(280,220,">",0x32b2,0xffff);
	showzifustr(355,198,"ON",0x8410,0x012C);
	showzifustr(410,198,"OFF",0xffff,0x012C);
//	showlogostr(340,198,"01234",0xffff,0x012C);
}
