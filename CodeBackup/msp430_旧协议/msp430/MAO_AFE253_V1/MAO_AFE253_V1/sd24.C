

#include "device.h"
#include "type_def.h"
#include "sd24.h"
#include "math.h"
#include "Utilities.h"

int sd24_sample_0, sd24_sample_1, sd24_sample_2;
unsigned int sample_count;//log_sample_count;
unsigned long long ch0_accum,ch1_accum,ch2_accum;
int ch0_short, ch1_short, ch2_short;
unsigned long long _ch0_accum = 0, _ch1_accum = 0, _ch2_accum = 0;
long* Mul_result = (long *) 0x13a;
U8 g_byNewValue;
U8 g_bySecFlag; // 采样一般标志，为了提高上传频率。

#define SD24CONF0_FUDGE     0x70
#define SD24CONF1_FUDGE     0xF8    //0x38

//====================================================================
void InitAnalogFrontEnd(void)
{   
    SD24CTL = SD24SSEL_1  /* Clock is SMCLK */
        | SD24DIV_3   /* Divide by 4 => ADC clock: 1MHz */
            | SD24REFON;  /* Use internal reference */
    //SD24CTL |= SD24OVIE;
    soft_delay1ms(500);  //Delay for 1.2V ref startup
    SD24CCTL0 |= SD24GRP+SD24DF+SD24OSR_256;              // Group with CH1
    SD24CCTL1 |= SD24GRP+SD24DF+SD24OSR_256;              // Group with CH2
    SD24CCTL2 |= SD24SNGL + SD24DF+SD24OSR_256;               // Enable interrupt
    SD24INCTL0 |= SD24INCH_7 + SD24GAIN_1;
    SD24INCTL1 |= SD24INCH_7 + SD24GAIN_1;
    SD24INCTL2 |= SD24INCH_7 + SD24GAIN_1;
    
#if defined(SD24CONF0_FUDGE)
    SD24CONF0 = SD24CONF0_FUDGE;                /* Tweaks recommended by Freising */
#endif
#if defined(SD24CONF1_FUDGE)
    SD24CONF1 = SD24CONF1_FUDGE;
#endif
    //master of the group conversion
    SD24CCTL2|=SD24SC;
    while(!(SD24CCTL2&SD24IFG));
    ch0_short += (int)SD24MEM0;
    ch1_short += (int)SD24MEM1;
    ch2_short += (int)SD24MEM2;
    
    ch0_short = ch1_short = ch2_short = 0;
    for(int i=0; i<82;i++)
    {
        SD24CCTL2|=SD24SC;
        while(!(SD24CCTL2&SD24IFG));
        ch0_short += (int)SD24MEM0;
        ch1_short += (int)SD24MEM1;
        ch2_short += (int)SD24MEM2;
    }
    SD24CCTL2 &= ~SD24SC;
    SD24CCTL1 &= ~SD24SC;
    SD24CCTL0 &= ~SD24SC;
    ch0_short = ch0_short/82;
    ch1_short = ch1_short/82;
    ch2_short = ch2_short/82;
    
    SD24CCTL0 = SD24GRP+SD24DF+SD24OSR_256;              // Group with CH1
    SD24CCTL1 = SD24GRP+SD24DF+SD24OSR_256;              // Group with CH2
    SD24CCTL2 = SD24IE+SD24DF+SD24OSR_256;               // Enable interrupt
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
        
    case 2:                                   // SD24MEM Overflow
        {
            __no_operation();
        }break;
    case 4:                                   // SD24MEM0 IFG
        break;
    case 6:                                   // SD24MEM1 IFG
        break;
    case 8:                                   // SD24MEM2 IFG  
        {
            sd24_sample_0 = (int)SD24MEM0;
            sd24_sample_1 = (int)SD24MEM1;
            sd24_sample_2 = (int)SD24MEM2;
            g_byNewValue = 1;
        }break;
    }
}

