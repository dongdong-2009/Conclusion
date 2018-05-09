#include "sys.h"

//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}

//�ر������ж�
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}

//���������ж�
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}

//����ջ����ַ
//addr:ջ����ַ
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
