#include"funclib.h"
#include "adc.h"
#include "rtd.h"
#include "dac.h" 		   			 
#include "pid.h"
#include "lookuptable.h"
#include "timer.h"
#include "digital_io.h"
#include "diyfunc.h"
#include "runtimedata.h"

A FuncArray[]={func0, func1,func2,func3,func4,func5,func6,func7, func8, func9, func10,func11,func12,func13,func14,
             // Default AI    ARI   DI   AO     DO    PID Closesub Delay Opensub Switch Unite Split  Entry	Exit
               func15,func16,func17,func18, func19,  func20, func21, func22, func23};
            // Begin  End	LUT   Register BasicMath Diyfunc Block    AOall   DOall


/////////////////////////////////////////////////////////////////
///<功能描述> Default
///<参数1> port 未用
///<参数2> par1,2  未用
///<参数3> ThreadNum 未用
///<返回值>未用 
////////////////////////////////////////////////////////////////
float func0(int port,float par1,float par2,float par3)
{
   float res = 0;    
   return res;
}
/////////////////////////////////////////////////////////////////
///<功能描述> 读取ADC的某个端口的模拟信号输入--x 
///<参数1> port 指定读取的端口       1--12
///<参数2> par1--a,par2--b,par3 未用
///<返回值> 返回该端口输入信号的物理值 y = a*x+b
////////////////////////////////////////////////////////////////
float func1(int port,float par1,float par2,float par3)
{ 
    float res;
	port = port - 1;
	ADC_onechannel(port,ADC_data);	   //电压值
    ADC_onechannel(port,ADC_data);
	AIParams[port].a = par1;		   
	AIParams[port].b = par2;
	ADC_value[port] = ADC_data[port];	  //物理值
	res = ADC_value[port];
 	res = (int)(res*10000)/10000.0;  
	return res;
}
/////////////////////////////////////////////////////////////////
///<功能描述> 读取RTD的某个端口的温度输入 
///<参数1> port 指定读取的端口       1--4
///<参数2> par1,2，3 未用
///<返回值> 返回该端口输入阻值对应PT1000的温度  保留两位小数 
////////////////////////////////////////////////////////////////
float func2(int port,float par1,float par2,float par3)
{ 
    float res;
	port = port - 1;
	RTD_onechannel(port,RTD_value);
	res = RTD_value[port];
	res = (int)(res*10000)/10000.0;	
	return res;
}
/////////////////////////////////////////////////////////////////
///<功能描述> 读取DI的某个端口的输入 0 or 1
///<参数1> port 指定读取的端口       1--8
///<参数2> par1,2,3 未用
///<返回值> 返回该端口输入的电平的高低。高电平返回1，低电平返回0
////////////////////////////////////////////////////////////////
float func3(int port,float par1,float par2,float par3)
{ 
    int res;
    port = port - 1; 
	DI_onechannel(port,DI_data);
	res = (int)DI_data[port];
	return (float)res;
}
/////////////////////////////////////////////////////////////////
///<功能描述> 设置某个AO端口的输出电压--x 
///<参数1> port 指定读取的端口   1--8
///<参数2> par1 用户设定的端口的物理输出--y
///<参数3> par2--a
///<参数4> par3--b
///<返回值> 返回该端口的电压输出 x = (y-b)/a
////////////////////////////////////////////////////////////////
float func4(int port,float par1,float par2,float par3)
{ 
    float res;
	port = port - 1;
	//AOParams[port].a = par2;
	//AOParams[port].b = par3;
	//if(AOAM[port] == AUTO)
	{
	   DAC_value[port] = par1;	//物理值
	   DAC_data[port] =  DAC_value[port];	 //电压值
	   DAC_onechannel(port,DAC_data[port]);   
	}	
	res = DAC_value[port];
	res = (int)(res*10000)/10000.0;	
	return res;
}
/////////////////////////////////////////////////////////////////
///<功能描述> 设置某个DO端口的输出 (1 or 0) 
///<参数1> port 指定读取的端口  1--8
///<参数2> par1 用户设定的此端口输出的高低电平 1-高电平，0-低电平
///<参数3> par2,par3 未用 
///<返回值> 返回该端口当前输出电平的高低   高电平-1，低电平-0
////////////////////////////////////////////////////////////////
float func5(int port,float par1,float par2,float par3)
{ 
    int res;
	port = port - 1;
	DO_onechannel(port,(int)par1);
	DO_data[port] = (int)par1;
	res = (int)par1;
	return (float)res;
}
/////////////////////////////////////////////////////////////////
///<功能描述>  	PID函数
///<参数1> port 1--4
///<参数2> par1 当前值pv --物理值
///<参数3> par2,par3 未用 
///<返回值> 经PID计算后的给定值out 	--物理值
////////////////////////////////////////////////////////////////
float func6(int port,float par1,float par2,float par3)
{ 
    float res;
	port = port - 1;
	res = PID_Calcu(port,par1);
	return res;
}
/////////////////////////////////////////////////////////////////
///<功能描述>关闭子线程--即关闭定时器2,3,4,5
///<参数1> port 选择关闭子线的线程号1,2,3,4可选
///<参数2> par1,2，3  未用
///<返回值>	未用
////////////////////////////////////////////////////////////////
float func7(int port,float par1,float par2,float par3)
{ 
    float res=0;
	TurnOffTim(port);
	return res;
}
/////////////////////////////////////////////////////////////////
///<功能描述> 延迟函数 
///<参数1> port 选择延时的单位 1--ms  2--s 
///<参数2> par1  设定延时的数字  1-1000
///<参数3> par2,par3  未用
///<返回值>未用 
////////////////////////////////////////////////////////////////
float func8(int port,float par1,float par2,float par3)
{ 
    float res;
	unsigned long count = 0;
	if(port == 1)
	{
	  count = (unsigned long)par1*8000;
	  if(count>0)
	    while(count--);
	}
	else if(port == 2)
	{
	  count = (unsigned long)par1*8000*1000;
	  if(count>0)
	     while(count--);
	}	
	return res;
}
/////////////////////////////////////////////////////////////////
///<功能描述> 打开子线程函数--即打开定时器2,3,4,5 
///<参数1> port 选择打开子线的线程号 1,2,3,4可选
///<参数2> par1  子线程(定时器)的扫描周期
///<参数3> par2,par3  未用
///<返回值>	未用
////////////////////////////////////////////////////////////////
float func9(int port,float par1,float par2,float par3)
{ 
      float res=0;
	  InitializeTimer(port,par1);
      TurnOnTim(port);
	  return res;
}
/////////////////////////////////////////////////////////////////
///<功能描述> 分支函数 
///<参数1> port 比较的类型       
///         1   par1>par2;
///         2   par1<par2;
///         3   par1==par2;
///         4   par3<par1<par2;
///<参数2> par1 比较的基准值
///<参数3> par2 比较的右值
///<参数4> par3 比较的左值
///<返回值>返回比较的结果  true--1  false--0
////////////////////////////////////////////////////////////////
float func10(int port,float par1,float par2,float par3)  
{ 
    float res = 0;
	float benchMark = par1;
	float rightValue = par2;
	float leftValue = par3;
	switch(port)
	{
	   case 1:	if(benchMark > rightValue) res = 1;break;
	   case 2:	if(benchMark < rightValue) res = 1;break;
	   case 3:	if(benchMark == rightValue) res = 1;break;
	   case 4:	if(benchMark > leftValue && benchMark < rightValue) res = 1;break;	   
	}
	return res;
}
/////////////////////////////////////////////////////////////////
///<功能描述> 标记一个循环的合点 
///<参数1> port 未用
///<参数2> par1,2,3  未用
///<返回值>未用 
////////////////////////////////////////////////////////////////
float func11(int port,float par1,float par2,float par3)
{
    float res = 0;	
	return res;
}
/////////////////////////////////////////////////////////////////
///<功能描述> 标记一个循环的分点
///<参数1> port 未用
///<参数2> par1,2,3  未用
///<返回值>未用 
////////////////////////////////////////////////////////////////
float func12(int port,float par1,float par2,float par3)
{
   float res = 0;  
   return res;
}
/////////////////////////////////////////////////////////////////
///<功能描述> 标记子线程入口 
///<参数1> port 选择进入的子线的线程号1,2,3,4可选
///<参数2> par1,2,3  未用
///<返回值>未用 
////////////////////////////////////////////////////////////////
float func13(int port,float par1,float par2,float par3)
{
    float res = 0;	
    res = SubRoutineEntry(port);	
	return res;
}
/////////////////////////////////////////////////////////////////
///<功能描述> 标记子线程退出 选择退出的子线的线程号1,2,3,4
///<参数1> port 
///<参数2> par1,2,3  未用
///<返回值>未用 
////////////////////////////////////////////////////////////////
float func14(int port,float par1,float par2,float par3)
{
   float res = 0;
   SubRoutineExit(port);  
   return res;
}

/////////////////////////////////////////////////////////////////
///<功能描述> 主线程开始函数
///<参数1> port  未用
///<参数2> par1,2,3   未用
///<返回值>未用 
////////////////////////////////////////////////////////////////
float func15(int port,float par1,float par2,float par3)
{
   float res = 0; 
   return res;
}
/////////////////////////////////////////////////////////////////
///<功能描述> 主线程结束函数
///<参数1> port  未用
///<参数2> par1,2,3  未用 
///<返回值>未用 
////////////////////////////////////////////////////////////////
float func16(int port,float par1,float par2,float par3)
{
   float res = 0; 
   return res;
}
/////////////////////////////////////////////////////////////////
///<功能描述>  LUT函数
///<参数1> port 未用
///<参数2> par1 row scale
///<参数3> par2 column scale
///<参数4> par3 未用
///<返回值> 经PID计算后的给定值out 
////////////////////////////////////////////////////////////////
float func17(int port,float par1,float par2,float par3)
{ 
    float res = 0;
	res = LookupTable(par1,par2);
	return res;
}

/////////////////////////////////////////////////////////////////
///<功能描述>  Register函数
///<参数1> port 选择寄存器的编号 1-8
///<参数2> par1 R/W, R--1， W--0
///<参数3> par2 要写入的寄存器的值
///<参数4> par3 未用
///<返回值> 返回当前寄存器的值 
////////////////////////////////////////////////////////////////
float func18(int port,float par1,float par2,float par3)     
{
   float res = 0;
   port = port - 1;
   if(REGAM[port] == AUTO)
   {
       if((int)par1 == 0)
          Registers[port] = par2;
   }
   res = Registers[port];
   return res;
}
/////////////////////////////////////////////////////////////////
///<功能描述>  BasicMath函数
///<参数1> port 选择运算操作符
///          1   par1 + par2,
///          2   par1 - par2,
///          3   par1 * par2,
///          4   par1 / par2,
///          5   par1 % par2,
///          6   par1 | par2,
///          7   par1 & par2,
///          8   par1 || par2,
///          9   par1 && par2
///<参数2> par1 左操作数
///<参数3> par2 右操作数
///<参数4> par3 未用
///<返回值> 返回运算结果 
////////////////////////////////////////////////////////////////
float func19(int port,float par1,float par2,float par3)     
{
   float res = 0;
   switch(port)
   {
      case 1: res = par1 + par2;break;
	  case 2: res = par1 - par2;break;
	  case 3: res = par1 * par2;break;
	  case 4: res = par1 / par2;break;
	  case 5: res = (int)par1 % (int)par2;break;
	  case 6: res = (int)par1 | (int)par2;break;
	  case 7: res = (int)par1 & (int)par2;break;
	  case 8: res = (int)par1 ||(int)par2;break;
	  case 9: res = (int)par1 &&(int)par2;break;
   }
   return res;
}

/////////////////////////////////////////////////////////////////
///<功能描述>DIYAlgorithm函数
///<参数1> port 未用
///<参数2> par1  DiyFunc的第一个参数（user defines it）
///<参数3> par2  DiyFunc的第二个参数（user defines it）
///<参数3> par3	 DiyFunc的第三个参数
///<返回值> 返回DiyFunc的返回值
////////////////////////////////////////////////////////////////
float func20(int port,float par1,float par2,float par3)     
{
   	float res = 0;
  	res = DiyFunc(par1,par2,par3);
	return res;
}

/////////////////////////////////////////////////////////////////
///<功能描述>Block块函数
///<参数1> port  未用
///<参数2> par1  未用
///<参数3> par2  未用
///<参数3> par3	 未用
///<返回值> 未用
////////////////////////////////////////////////////////////////
float func21(int port,float par1,float par2,float par3)     
{
   	float res = 0; 	
	return res;
}
/////////////////////////////////////////////////////////////////
///<功能描述>AOall函数,一次性初始化所有AO端口
///<参数1> port  未用
///<参数2> par1  初始化方向  AO1toAO8 = 1， AO8toAO1 = 2
///<参数3> par2  时间间隔(s) 0,1,2...n
///<参数3> par3	 初始化值 (v)
///<返回值> 未用
////////////////////////////////////////////////////////////////
float func22(int port,float par1,float par2,float par3)     
{
   	float res = par3; 
	int i;
	if(par1 == 1)
	{
	    for(i=0;i<8;i++)
	   {
	      AOAM[i] = AUTO; 	
	      DAC_value[i] = par3;	//物理值
	      DAC_data[i] = par3;	 //电压值
	      DAC_onechannel(i,DAC_data[i]); 
		  func8(2,par2,0,0);
	   } 
	}
	else
	{
	   for(i=7;i>=0;i--)
	   {
	      AOAM[i] = AUTO; 	
	      DAC_value[i] = par3;	//物理值
	      DAC_data[i] = par3;	 //电压值
	      DAC_onechannel(i,DAC_data[i]);
		  func8(2,par2,0,0);   
	   } 
	}
	return res;
}

/////////////////////////////////////////////////////////////////
///<功能描述>DOall函数,一次性初始化所有DO端口
///<参数1> port  未用
///<参数2> par1  初始化方向  DO1toDO8 = 1， DO8toDO1 = 2
///<参数3> par2  时间间隔(s) 0,1,2...n
///<参数3> par3	 初始化值 (v) 0,1
///<返回值> 未用
////////////////////////////////////////////////////////////////
float func23(int port,float par1,float par2,float par3)     
{
   	float res = par3; 
	int i;
	if(par1 == 1)
	{
	    for(i=0;i<8;i++)
	   {	
	      DO_onechannel(i,(int)par3);
	      DO_data[i] = (int)par3;
		  func8(2,par2,0,0);
	   } 
	}
	else
	{
	  for(i=7;i>=0;i--)
	   {
	      DO_onechannel(i,(int)par3);
	      DO_data[i] = (int)par3;
		  func8(2,par2,0,0);
	   } 
	}
	return res;
}
