#include "heatpump_ctrl.h"


void EEV_initial(void)
{  
    u8 i;

    DPortOut(EEVSTART,0);
    DPortOut(DIRECTION,0);

    for(i=0;i<250;i++)
    {
        DPortOut(OUTPULSE,1); 
        delay_ms(2);
        DPortOut(OUTPULSE,0); 
        delay_ms(2); 
    }
    DPortOut(EEVSTART,1);

} 
void EEV_Ajust(u8 eevStep,u8 direction)
{ 
    u8 i;

    DPortOut(EEVSTART,0);
    DPortOut(DIRECTION,direction);
    for(i=0;i<eevStep;i++)
    {
        DPortOut(OUTPULSE,1); 
        delay_ms(2);
        DPortOut(OUTPULSE,0); 
        delay_ms(2); 
    }
    DPortOut(EEVSTART,1);
} 
void EEV_close()
{ 
    u8 i;

    DPortOut(EEVSTART,0);
    DPortOut(DIRECTION,1);

    for(i=0;i<250;i++)
    {
        DPortOut(OUTPULSE,1); 
        delay_ms(2);
        DPortOut(OUTPULSE,0); 
        delay_ms(2); 
    }
    DPortOut(EEVSTART,1);
}




