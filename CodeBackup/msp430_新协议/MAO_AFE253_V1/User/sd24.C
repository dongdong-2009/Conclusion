
#include "device.h"
#include "type_def.h"
#include "sd24.h"
#include "math.h"
#include "Utilities.h"

#define NUM  30

int  sd24_rawdata[3];
int  sd24_calibrator[3] = {0};
char conversion_done = 0;
//int g_bySecFlag; // 采样一般标志，为了提高上传频率。

#define SD24CONF0_FUDGE     0x70
#define SD24CONF1_FUDGE     0xF8    //0x38

//====================================================================
void InitAnalogFrontEnd(void)
{   
    SD24CTL = SD24SSEL_1  /* Clock is SMCLK */
        | SD24DIV_3   /* Divide by 4 => ADC clock: 1MHz */
            | SD24REFON;  /* Use internal reference */
    //SD24CTL |= SD24OVIE;
    soft_delay1ms(1000);  //Delay for 1.2V ref startup
    SD24CCTL0 |= SD24GRP+SD24DF+SD24OSR_256;              // Group with CH1
    SD24CCTL1 |= SD24GRP+SD24DF+SD24OSR_256;              // Group with CH2
    SD24CCTL2 |= SD24SNGL + SD24DF+SD24OSR_256;               // Enable interrupt   &&&  // Single Mode
    SD24INCTL0 |= SD24INCH_7 + SD24GAIN_1;
    SD24INCTL1 |= SD24INCH_7 + SD24GAIN_1;
    SD24INCTL2 |= SD24INCH_7 + SD24GAIN_1;
  
#if defined(SD24CONF0_FUDGE)
    SD24CONF0 = SD24CONF0_FUDGE;                
#endif
#if defined(SD24CONF1_FUDGE)
    SD24CONF1 = SD24CONF1_FUDGE;
#endif
    //master of the group conversion
    SD24CCTL2|=SD24SC;
    while(!(SD24CCTL2&SD24IFG));
    sd24_calibrator[0] += (int)SD24MEM0;
    sd24_calibrator[1] += (int)SD24MEM1;
    sd24_calibrator[2] += (int)SD24MEM2;
    for(int i=0; i<3; i++)
    sd24_calibrator[i] = 0; 
   

    for(int i=0;i<NUM;i++)
    {
        SD24CCTL2|=SD24SC;                    //for Single conversion, each SD24SC setting for each conversion start
        while(!(SD24CCTL2&SD24IFG));
        sd24_calibrator[0] += (int)SD24MEM0;
        sd24_calibrator[1] += (int)SD24MEM1;
        sd24_calibrator[2] += (int)SD24MEM2;
    }
    SD24CCTL2 &= ~SD24SC;
    SD24CCTL1 &= ~SD24SC;
    SD24CCTL0 &= ~SD24SC;
    
    for(int i=0;i<3;i++)
    sd24_calibrator[i] =  sd24_calibrator[i] / NUM;
    
    SD24CCTL0 = SD24GRP+SD24DF+SD24OSR_256;              // Group with CH1
    SD24CCTL1 = SD24GRP+SD24DF+SD24OSR_256;              // Group with CH2
    SD24CCTL2 = SD24IE+SD24DF+SD24OSR_256;               // Enable interrupt    &&&   //Continuous Mode
    SD24INCTL0 = SD24INCH_0 + SD24GAIN_1;
    SD24INCTL1 = SD24INCH_0 + SD24GAIN_1;
    SD24INCTL2 = SD24INCH_0 + SD24GAIN_1;
} // 模拟前端初始化函数结束

void start_sd24(void)
{
    SD24CCTL2 &= ~SD24IFG;
    SD24CCTL1 &= ~SD24IFG;
    SD24CCTL0 &= ~SD24IFG;
    SD24CCTL2 |= SD24SC;
}

void stop_sd24(void)
{
    SD24CCTL2 &= ~SD24SC;
}


#pragma vector=SD24_VECTOR
__interrupt void SD24ISR(void)
{
    switch (__even_in_range(SD24IV, 8))
    {
        
    case 2:  break;                  // SD24MEM Overflow 
    case 4:  break;                 // SD24MEM0 IFG 
    case 6:  break;                // SD24MEM1 IFG  
    case 8:                        // SD24MEM2 IFG  
        {
            sd24_rawdata[0] = (int)SD24MEM0;
            sd24_rawdata[1] = (int)SD24MEM1;
            sd24_rawdata[2] = (int)SD24MEM2;
            conversion_done = 1;
            break;
        }
    }
}

