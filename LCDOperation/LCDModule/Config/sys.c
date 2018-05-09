#include "sys.h"

//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}

//关闭所有中断
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}

//开启所有中断
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}

//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

void delay_us(u32 nus)
{
   u32 temp;
   SysTick->LOAD=9*nus;
   SysTick->VAL=0x00;
   SysTick->CTRL=0x01;
   do
   {
     temp=SysTick->CTRL;
   }while((temp&0x01)&&(!(temp&(1<<16))));
   SysTick->CTRL=0x00;
   SysTick->VAL=0x00;
}

void delay_ms(u16 nms)
{
   u32 temp;
   SysTick->LOAD=9000*nms;
   SysTick->VAL=0x00;
   SysTick->CTRL=0x01;
   do
   {                                                                                                                                             
     temp=SysTick->CTRL;
   }while((temp&0x01)&&(!(temp&(1<<16))));
   SysTick->CTRL=0x00;
   SysTick->VAL=0x00;
}

void delay_s(u8 ns)
{
   u16 i;
   for(i=0;i<ns*10;i++)
   {
      delay_ms(100);
   }
}
