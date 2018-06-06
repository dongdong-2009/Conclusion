#include "mcp3208.h"

void ADCRcc_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC| RCC_APB2Periph_AFIO,ENABLE); 
}
void ADCGPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void mcp3208_Configuration(void)
{
    ADCRcc_Configuration();
	ADCGPIO_Configuration();
}
u16 mcp3208_chanOne(u8 channel)
{
   u8 i;
   u16 data;

    
   GPIO_WriteBit(GPIOC, mcp3208_cs1, Bit_SET);	//cs=0
   GPIO_WriteBit(GPIOC, mcp3208_Din1, Bit_RESET); //din=1
   GPIO_WriteBit(GPIOC, mcp3208_clk1,Bit_SET); //clk=0
   delay_ms(1);
   GPIO_WriteBit(GPIOC, mcp3208_clk1,Bit_RESET); //   
   delay_ms(1);
   GPIO_WriteBit(GPIOC, mcp3208_Din1, Bit_RESET); //din=1
   GPIO_WriteBit(GPIOC, mcp3208_clk1,Bit_SET);
   delay_ms(1);
   GPIO_WriteBit(GPIOC, mcp3208_clk1,Bit_RESET);
   delay_ms(1);
   for(i=0;i<3;i++)
   {
	   if((channel&(1<<(2-i)))!=0)
	       GPIO_WriteBit(GPIOC, mcp3208_Din1, Bit_RESET);
	   else
	       GPIO_WriteBit(GPIOC, mcp3208_Din1, Bit_SET);
	   GPIO_WriteBit(GPIOC, mcp3208_clk1, Bit_SET);
	   delay_ms(1);
	   GPIO_WriteBit(GPIOC, mcp3208_clk1,Bit_RESET);
	   delay_ms(1);
   }
   GPIO_WriteBit(GPIOC, mcp3208_clk1, Bit_SET);
   delay_ms(1);  
   GPIO_WriteBit(GPIOC, mcp3208_clk1,Bit_RESET);
   delay_ms(1);
   
   GPIO_WriteBit(GPIOC, mcp3208_clk1, Bit_SET);
   delay_ms(1);
   data=GPIO_ReadInputDataBit(GPIOC, mcp3208_Dout1);
   GPIO_WriteBit(GPIOC, mcp3208_clk1,Bit_RESET); 
   delay_ms(1); 	   
   for(i=0;i<12;i++)
   {
       
	   GPIO_WriteBit(GPIOC, mcp3208_clk1, Bit_SET);	
       delay_ms(1);	         
	   data|=(GPIO_ReadInputDataBit(GPIOC, mcp3208_Dout1)<<(11-i)); 
	   GPIO_WriteBit(GPIOC, mcp3208_clk1, Bit_RESET); 
       delay_ms(1);	   
   }
   GPIO_WriteBit(GPIOC, mcp3208_cs1, Bit_RESET);
   delay_ms(1);
   return data;
}
u16 mcp3208_chanTwo(u8 channel)
{
   u8 i;
   u16 data;
    
   GPIO_WriteBit(GPIOA, mcp3208_cs2, Bit_SET);	//cs=0
   GPIO_WriteBit(GPIOA, mcp3208_Din2, Bit_RESET); //din=1
   GPIO_WriteBit(GPIOA, mcp3208_clk2,Bit_SET); //clk=0
   delay_ms(1);
   GPIO_WriteBit(GPIOA, mcp3208_clk2,Bit_RESET); //   
   delay_ms(1);
   GPIO_WriteBit(GPIOA, mcp3208_Din2, Bit_RESET); //din=1
   GPIO_WriteBit(GPIOA, mcp3208_clk2,Bit_SET);
   delay_ms(1);
   GPIO_WriteBit(GPIOA, mcp3208_clk2,Bit_RESET);
   delay_ms(1);
   for(i=0;i<3;i++)
   {
	   if((channel&(1<<(2-i)))!=0)
	       GPIO_WriteBit(GPIOA, mcp3208_Din2, Bit_RESET);
	   else
	       GPIO_WriteBit(GPIOA, mcp3208_Din2, Bit_SET);
	   GPIO_WriteBit(GPIOA, mcp3208_clk2, Bit_SET);
	   delay_ms(1);
	   GPIO_WriteBit(GPIOA, mcp3208_clk2,Bit_RESET);
	   delay_ms(1);
   }
   GPIO_WriteBit(GPIOA, mcp3208_clk2, Bit_SET);
   delay_ms(1);  
   GPIO_WriteBit(GPIOA, mcp3208_clk2,Bit_RESET);
   delay_ms(1);
   
   GPIO_WriteBit(GPIOA, mcp3208_clk2, Bit_SET);
   delay_ms(1);
   data=GPIO_ReadInputDataBit(GPIOA, mcp3208_Dout2);
   GPIO_WriteBit(GPIOA, mcp3208_clk2,Bit_RESET); 
   delay_ms(1); 	   
   for(i=0;i<12;i++)
   {
       
	   GPIO_WriteBit(GPIOA, mcp3208_clk2, Bit_SET);	
       delay_ms(1);	         
	   data|=(GPIO_ReadInputDataBit(GPIOA, mcp3208_Dout2)<<(11-i)); 
	   GPIO_WriteBit(GPIOA, mcp3208_clk2, Bit_RESET); 
       delay_ms(1);	   
   }
   GPIO_WriteBit(GPIOA, mcp3208_cs2, Bit_RESET);
   delay_ms(1);
   return data;
}

u16 mcp3208_adc(u8 port)
{      

    if(port<8)
	{
	   return mcp3208_chanOne(port);    		 
	}
	else
	{
	   return mcp3208_chanTwo(port); 		 
	}
   
}


float readSenor(u8 port,float range)
{
   u16 AD_value;
   float AD_data;

   AD_value=mcp3208_adc(port);   
   AD_data=((float)AD_value/4096)*range;

   if((port==11)||(port==10))
   {
      AD_data+=1.0;
   }
   return AD_data;
} 
//float chanvalue12(float volt)
//{
//    float value; 
//    value=(volt*48+1000)*1.0833;
////    value=value+POWER_PT;
////    value=value/0.74948/POWER_PT;
////    value=(value-1)*2998.4875;
////    value+=7;
//    return value;        
//}
//float chanvalue13(float volt)
//{
//    float value;
//    value=(volt*48+1000)*1.0837;
////    value=value+POWER_PT;
////    value=value/0.75026/POWER_PT;
////    value=(value-1)*291.0075395.701;
////	value+=7;
//    return value;        
//}
//float chanvalue14(float volt)
//{
//    float value;
//    value=(volt*48+1000)*1.0823;
////    value=value+POWER_PT;
////    value=value/0.74987/POWER_PT;
////    value=(value-1)*2995.1976;
//    return value;        
//}
//float chanvalue15(float volt)
//{
//    float value;
//    value=(volt*48+1000)*1.0823;
////    value=value+POWER_PT;
////    value=value/0.7496/POWER_PT;
////    value=(value-1)*3000;
////	value+=7;
//    return value;        
//}
float chanvalue12(float volt)
{
    float value; 
    value=(volt*48+1000)*1.00759956;
//    value=value+POWER_PT;
//    value=value/0.74948/POWER_PT;
//    value=(value-1)*2998.4875;
//    value+=7;
    return value;        
}
float chanvalue13(float volt)
{
    float value;
    value=(volt*48+1000)*0.883912676;
//    value=value+POWER_PT;
//    value=value/0.75026/POWER_PT;
//    value=(value-1)*291.0075395.701;
//	value+=7;
    return value;        
}
float chanvalue14(float volt)
{
    float value;
    value=(volt*48+1000)*1.00653327;
//    value=value+POWER_PT;
//    value=value/0.74987/POWER_PT;
//    value=(value-1)*2995.1976;
    return value;        
}
float chanvalue15(float volt)
{
    float value;
    value=(volt*48+1000)*1.0030896597;
//    value=value+POWER_PT;
//    value=value/0.7496/POWER_PT;
//    value=(value-1)*3000;
//	value+=7;
    return value;        
}
float readTemp(u8 port)
{
    double A=3.9083e-3;
    double B=-5.775e-7;  
       
    u8 i;
    u16 AD_value;
    float AD_data,res;
    float T0,TR;

    AD_value=mcp3208_adc(port);
    AD_data=((float)AD_value/4096)*5.0; 
    switch(port)
    {
        case 12:res=chanvalue12(AD_data);break;
        case 13:res=chanvalue13(AD_data);break;
        case 14:res=chanvalue14(AD_data);break;
        case 15:res=chanvalue15(AD_data);break;
        default:break;         
    }
    T0=(res/1000-1)/A;

    for(i=0;i<50;i++)
        {
            TR=T0+(res-1000*(1+A*T0+B*T0*T0))/(1000*(A+2*B*T0));
            if(fabs(TR-T0)<0.001) break;
            else T0=TR;
        } 		
    return TR;
    
}

void APortCIn(float aarr[16],float range[12])
{
    u8 i;     
    for(i=0;i<12;i++)
    {          
        aarr[i]=readSenor(i,range[i]);
    }
    for(i=12;i<16;i++)
    {
        aarr[i]=readTemp(i);
    }
}
float APortIn(u8 port, float range)
{
    
    float analog;


    if(port<12)
        analog=readSenor(port,range); 
    else
        analog=readTemp(port);
    
    return analog;
}
 




