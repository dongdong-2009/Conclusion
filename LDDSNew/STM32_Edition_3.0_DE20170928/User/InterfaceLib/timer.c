#include <stdio.h>
#include<stdlib.h>
#include "stm32f10x.h"
#include "usart.h"

/*********************************************************************************************************
** Functoin name:       Time_Configuration
** Descriptions:        初始化TIM1
                        包括 时钟、TIM1工作方式配置
** input paraments:     无
** output paraments:    无    
** Returned values:     无
*********************************************************************************************************/
void InitializeTimer(int n,float time)
{   
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TypeDef* TIMx;
	TIM_DeInit(TIMx);    

	switch(++n)
	{  case 1: TIMx = TIM1; RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE); break;
	   case 2: TIMx = TIM2;	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	break;
	   case 3: TIMx = TIM3;	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	break;
	   case 4: TIMx = TIM4;	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);	break;        
	   case 5: TIMx = TIM5;	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);	break;
	}
                   					          // 复位TIM5定时器 
	TIM_TimeBaseStructure.TIM_Period = (int)(2000 * time);            // 每T5秒更新一次子程序 T5<30
	TIM_TimeBaseStructure.TIM_Prescaler = (36000-1);                  // 分频36000       
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;           // 时钟分频  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;       // 计数方向向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                  // 重复计数  
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIMx, TIM_FLAG_Update); 
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);                      //使能TIM2中断源 
	TIM_Cmd(TIMx, DISABLE); 
}
/*********************************************************************************************************
** Functoin name:       TimeOn/Off Timx
** Descriptions:        打开或关闭TIMx
                        
** input paraments:     无
** output paraments:    无    
** Returned values:     无
*********************************************************************************************************/
void TurnOnTim(int x)
{
   int i = x + 1;
   switch(i)
   {
      case 1:	TIM_Cmd(TIM1, ENABLE);break;     //TIM1 开启
	  case 2:	TIM_Cmd(TIM2, ENABLE);break;     //TIM2 开启
	  case 3:	TIM_Cmd(TIM3, ENABLE);break;     //TIM3 开启
	  case 4:	TIM_Cmd(TIM4, ENABLE);break;     //TIM4 开启
	  case 5:	TIM_Cmd(TIM5, ENABLE);break;     //TIM5 开启
   } 
}
void TurnOffTim(int x)
{
  int i = x + 1;
  switch(i)
   {
      case 1:	TIM_Cmd(TIM1, DISABLE);break;   //TIM1 关闭
	  case 2:	TIM_Cmd(TIM2, DISABLE);break;     //TIM2 关闭
	  case 3:	TIM_Cmd(TIM3, DISABLE);break;     //TIM3 关闭
	  case 4:	TIM_Cmd(TIM4, DISABLE);break;     //TIM4 关闭
	  case 5:	TIM_Cmd(TIM5, DISABLE);break;     //TIM5 关闭
   } 
}

///*********************************************************************************************************
//** Functoin name:       Timx中断退出函数
//** Descriptions:        清中断标志位，允许再次进入中断
//                        
//** input paraments:     x 要退出的子线程号
//** output paraments:    无    
//** Returned values:     无
//*********************************************************************************************************/
//void SubRoutineExit(int x)
//{ 
//   int i = x + 1; 
//   switch(i)
//   {
//      case 1:	TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);break;     //TIM1 清中断
//	  case 2:	TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);break;     //TIM2 清中断
//	  case 3:	TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);break;     //TIM3 清中断
//	  case 4:	TIM_ClearITPendingBit(TIM4, TIM_FLAG_Update);break;     //TIM4 清中断
//	  case 5:	TIM_ClearITPendingBit(TIM5, TIM_FLAG_Update);break;     //TIM5 清中断
//   } 
//}
///*********************************************************************************************************
//** Functoin name:       Timx中断入口函数
//** Descriptions:        判断中断标志位是否溢出中断
//                        
//** input paraments:     x 要进入的子线程号 
//** output paraments:    无    
//** Returned values:     如果成功进入子线程，则返回1，否则返回0
//*********************************************************************************************************/
//int SubRoutineEntry(int x)
//{ 
//   int i = x + 1; 
//   switch(i)
//   {
//      case 1:	if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  return 1;   //TIM1 中断溢出
//	  case 2:	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  return 1;   //TIM2 中断溢出
//	  case 3:	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  return 1;   //TIM3 中断溢出
//	  case 4:	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  return 1;   //TIM4 中断溢出
//	  case 5:	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  return 1;   //TIM5 中断溢出
//   }  
//   return 0;
//}
//





