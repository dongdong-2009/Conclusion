#ifndef __IO_H
#define __IO_H
#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "timer.h"	

//bitband operation, GPIO control like 51
//details refer to CM3È¨ÍþÖ¸ÄÏ Chap5 pp87-92

//Macro for IO operations
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//IO mapping
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 

//IO operation for one bit, n MUST be less than 16
#define PA_out(n)   BIT_ADDR(GPIOA_ODR_Addr,n) 
#define PA_in(n)    BIT_ADDR(GPIOA_IDR_Addr,n) 

#define PB_out(n)   BIT_ADDR(GPIOB_ODR_Addr,n) 
#define PB_in(n)    BIT_ADDR(GPIOB_IDR_Addr,n) 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n) 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n) 

#define PD_out(n)   BIT_ADDR(GPIOD_ODR_Addr,n) 
#define PD_in(n)    BIT_ADDR(GPIOD_IDR_Addr,n) 

#define PE_out(n)   BIT_ADDR(GPIOE_ODR_Addr,n) 
#define PE_in(n)    BIT_ADDR(GPIOE_IDR_Addr,n) 

#define PF_out(n)   BIT_ADDR(GPIOF_ODR_Addr,n) 
#define PF_in(n)    BIT_ADDR(GPIOF_IDR_Addr,n) 

#define PG_out(n)   BIT_ADDR(GPIOG_ODR_Addr,n) 
#define PG_in(n)    BIT_ADDR(GPIOG_IDR_Addr,n) 

void IO_OutPushPull_Init(GPIO_TypeDef *GPIOx, u8 GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed); //Output Push-pull mode
void IO_InPullUp_Init(GPIO_TypeDef *GPIOx, u8 GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed); //Input pull-up mode
void IO_Interrupt_Init(GPIO_TypeDef *GPIOx, u8 GPIO_Pin, EXTITrigger_TypeDef EXTI_Trigger, u8 PrePrior, u8 SubPrior);

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

//__ASM functions
void WFI_SET(void);	//wait for interrupt
void INTX_DISABLE(void); // disable all interrupts
void INTX_ENABLE(void); // enable all interrupts
void MSR_MSP(u32 addr); // set stack address

#endif
