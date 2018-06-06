#include "deh.h"

u8 dehStart(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8])
{
    float deLiq,dewflow,detemp;
    float detime=0;

    deLiq=APortIn(DELIQCHAN,arin[DELIQCHAN]);

    if(deLiq>=DELIQMAX)
    {
        //π ’œ
        return 1;
    }
    if(deLiq<=DELIQMIN)
    {
        //π ’œ
        return 2;
    }
    APortOut(DECPUMPCHAN,DECPUMPDEF,arout[DECPUMPCHAN]);

    delay_s(8); 
    dewflow=APortIn(DEWFLOWCHAN,arin[DEWFLOWCHAN]);

    if(dewflow<DEWFLOWMIN)
    {
        //π ’œ
        return 3;
    }
    
    //ø™¿‰‘¥£ª
    do
    {        
        detemp=APortIn(DESTEMPCHAN,0);
        delay_s(5);
        detime++;
        if(detime>(int)(DEWTIM/5))
        {
            //±®æØ
            return 4;
        }
            
    }while(detemp>DESTEMPMAX);
    APortOut(DEFANCHAN,DEFANDEF,arout[DEFANCHAN]); 


    return 0;
}



u8 dehStop(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8])
{
    float deLiq,dewflow,detemp;
    float detime=0;

    deLiq=APortIn(DELIQCHAN,arin[DELIQCHAN]);
    if(deLiq>=DELIQMAX)
    {
        //π ’œ
        return 1;
    }
    if(deLiq<=DELIQMIN)
    {
        //π ’œ
        return 2;
    }
    APortOut(DECPUMPCHAN,DECPUMPDEF,arout[DECPUMPCHAN]);

    delay_s(8); 
    dewflow=APortIn(DEWFLOWCHAN,arin[DEWFLOWCHAN]);

    if(dewflow<DEWFLOWMIN)
    {
        //π ’œ
        return 3;
    }
    
    //ø™¿‰‘¥£ª
    do
    {        
        detemp=APortIn(DESTEMPCHAN,0);
        delay_s(5);
        detime++;
        if(detime>(int)(DEWTIM/5))
        {
            //±®æØ
            return 4;
        }
            
    }while(detemp>DESTEMPMAX);
    APortOut(DEFANCHAN,DEFANDEF,arout[DEFANCHAN]); 


    return 0;
}








