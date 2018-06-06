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
///<��������> Default
///<����1> port δ��
///<����2> par1,2  δ��
///<����3> ThreadNum δ��
///<����ֵ>δ�� 
////////////////////////////////////////////////////////////////
float func0(int port,float par1,float par2,float par3)
{
   float res = 0;    
   return res;
}
/////////////////////////////////////////////////////////////////
///<��������> ��ȡADC��ĳ���˿ڵ�ģ���ź�����--x 
///<����1> port ָ����ȡ�Ķ˿�       1--12
///<����2> par1--a,par2--b,par3 δ��
///<����ֵ> ���ظö˿������źŵ�����ֵ y = a*x+b
////////////////////////////////////////////////////////////////
float func1(int port,float par1,float par2,float par3)
{ 
    float res;
	port = port - 1;
	ADC_onechannel(port,ADC_data);	   //��ѹֵ
    ADC_onechannel(port,ADC_data);
	AIParams[port].a = par1;		   
	AIParams[port].b = par2;
	ADC_value[port] = ADC_data[port];	  //����ֵ
	res = ADC_value[port];
 	res = (int)(res*10000)/10000.0;  
	return res;
}
/////////////////////////////////////////////////////////////////
///<��������> ��ȡRTD��ĳ���˿ڵ��¶����� 
///<����1> port ָ����ȡ�Ķ˿�       1--4
///<����2> par1,2��3 δ��
///<����ֵ> ���ظö˿�������ֵ��ӦPT1000���¶�  ������λС�� 
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
///<��������> ��ȡDI��ĳ���˿ڵ����� 0 or 1
///<����1> port ָ����ȡ�Ķ˿�       1--8
///<����2> par1,2,3 δ��
///<����ֵ> ���ظö˿�����ĵ�ƽ�ĸߵ͡��ߵ�ƽ����1���͵�ƽ����0
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
///<��������> ����ĳ��AO�˿ڵ������ѹ--x 
///<����1> port ָ����ȡ�Ķ˿�   1--8
///<����2> par1 �û��趨�Ķ˿ڵ��������--y
///<����3> par2--a
///<����4> par3--b
///<����ֵ> ���ظö˿ڵĵ�ѹ��� x = (y-b)/a
////////////////////////////////////////////////////////////////
float func4(int port,float par1,float par2,float par3)
{ 
    float res;
	port = port - 1;
	//AOParams[port].a = par2;
	//AOParams[port].b = par3;
	//if(AOAM[port] == AUTO)
	{
	   DAC_value[port] = par1;	//����ֵ
	   DAC_data[port] =  DAC_value[port];	 //��ѹֵ
	   DAC_onechannel(port,DAC_data[port]);   
	}	
	res = DAC_value[port];
	res = (int)(res*10000)/10000.0;	
	return res;
}
/////////////////////////////////////////////////////////////////
///<��������> ����ĳ��DO�˿ڵ���� (1 or 0) 
///<����1> port ָ����ȡ�Ķ˿�  1--8
///<����2> par1 �û��趨�Ĵ˶˿�����ĸߵ͵�ƽ 1-�ߵ�ƽ��0-�͵�ƽ
///<����3> par2,par3 δ�� 
///<����ֵ> ���ظö˿ڵ�ǰ�����ƽ�ĸߵ�   �ߵ�ƽ-1���͵�ƽ-0
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
///<��������>  	PID����
///<����1> port 1--4
///<����2> par1 ��ǰֵpv --����ֵ
///<����3> par2,par3 δ�� 
///<����ֵ> ��PID�����ĸ���ֵout 	--����ֵ
////////////////////////////////////////////////////////////////
float func6(int port,float par1,float par2,float par3)
{ 
    float res;
	port = port - 1;
	res = PID_Calcu(port,par1);
	return res;
}
/////////////////////////////////////////////////////////////////
///<��������>�ر����߳�--���رն�ʱ��2,3,4,5
///<����1> port ѡ��ر����ߵ��̺߳�1,2,3,4��ѡ
///<����2> par1,2��3  δ��
///<����ֵ>	δ��
////////////////////////////////////////////////////////////////
float func7(int port,float par1,float par2,float par3)
{ 
    float res=0;
	TurnOffTim(port);
	return res;
}
/////////////////////////////////////////////////////////////////
///<��������> �ӳٺ��� 
///<����1> port ѡ����ʱ�ĵ�λ 1--ms  2--s 
///<����2> par1  �趨��ʱ������  1-1000
///<����3> par2,par3  δ��
///<����ֵ>δ�� 
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
///<��������> �����̺߳���--���򿪶�ʱ��2,3,4,5 
///<����1> port ѡ������ߵ��̺߳� 1,2,3,4��ѡ
///<����2> par1  ���߳�(��ʱ��)��ɨ������
///<����3> par2,par3  δ��
///<����ֵ>	δ��
////////////////////////////////////////////////////////////////
float func9(int port,float par1,float par2,float par3)
{ 
      float res=0;
	  InitializeTimer(port,par1);
      TurnOnTim(port);
	  return res;
}
/////////////////////////////////////////////////////////////////
///<��������> ��֧���� 
///<����1> port �Ƚϵ�����       
///         1   par1>par2;
///         2   par1<par2;
///         3   par1==par2;
///         4   par3<par1<par2;
///<����2> par1 �ȽϵĻ�׼ֵ
///<����3> par2 �Ƚϵ���ֵ
///<����4> par3 �Ƚϵ���ֵ
///<����ֵ>���رȽϵĽ��  true--1  false--0
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
///<��������> ���һ��ѭ���ĺϵ� 
///<����1> port δ��
///<����2> par1,2,3  δ��
///<����ֵ>δ�� 
////////////////////////////////////////////////////////////////
float func11(int port,float par1,float par2,float par3)
{
    float res = 0;	
	return res;
}
/////////////////////////////////////////////////////////////////
///<��������> ���һ��ѭ���ķֵ�
///<����1> port δ��
///<����2> par1,2,3  δ��
///<����ֵ>δ�� 
////////////////////////////////////////////////////////////////
float func12(int port,float par1,float par2,float par3)
{
   float res = 0;  
   return res;
}
/////////////////////////////////////////////////////////////////
///<��������> ������߳���� 
///<����1> port ѡ���������ߵ��̺߳�1,2,3,4��ѡ
///<����2> par1,2,3  δ��
///<����ֵ>δ�� 
////////////////////////////////////////////////////////////////
float func13(int port,float par1,float par2,float par3)
{
    float res = 0;	
    res = SubRoutineEntry(port);	
	return res;
}
/////////////////////////////////////////////////////////////////
///<��������> ������߳��˳� ѡ���˳������ߵ��̺߳�1,2,3,4
///<����1> port 
///<����2> par1,2,3  δ��
///<����ֵ>δ�� 
////////////////////////////////////////////////////////////////
float func14(int port,float par1,float par2,float par3)
{
   float res = 0;
   SubRoutineExit(port);  
   return res;
}

/////////////////////////////////////////////////////////////////
///<��������> ���߳̿�ʼ����
///<����1> port  δ��
///<����2> par1,2,3   δ��
///<����ֵ>δ�� 
////////////////////////////////////////////////////////////////
float func15(int port,float par1,float par2,float par3)
{
   float res = 0; 
   return res;
}
/////////////////////////////////////////////////////////////////
///<��������> ���߳̽�������
///<����1> port  δ��
///<����2> par1,2,3  δ�� 
///<����ֵ>δ�� 
////////////////////////////////////////////////////////////////
float func16(int port,float par1,float par2,float par3)
{
   float res = 0; 
   return res;
}
/////////////////////////////////////////////////////////////////
///<��������>  LUT����
///<����1> port δ��
///<����2> par1 row scale
///<����3> par2 column scale
///<����4> par3 δ��
///<����ֵ> ��PID�����ĸ���ֵout 
////////////////////////////////////////////////////////////////
float func17(int port,float par1,float par2,float par3)
{ 
    float res = 0;
	res = LookupTable(par1,par2);
	return res;
}

/////////////////////////////////////////////////////////////////
///<��������>  Register����
///<����1> port ѡ��Ĵ����ı�� 1-8
///<����2> par1 R/W, R--1�� W--0
///<����3> par2 Ҫд��ļĴ�����ֵ
///<����4> par3 δ��
///<����ֵ> ���ص�ǰ�Ĵ�����ֵ 
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
///<��������>  BasicMath����
///<����1> port ѡ�����������
///          1   par1 + par2,
///          2   par1 - par2,
///          3   par1 * par2,
///          4   par1 / par2,
///          5   par1 % par2,
///          6   par1 | par2,
///          7   par1 & par2,
///          8   par1 || par2,
///          9   par1 && par2
///<����2> par1 �������
///<����3> par2 �Ҳ�����
///<����4> par3 δ��
///<����ֵ> ���������� 
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
///<��������>DIYAlgorithm����
///<����1> port δ��
///<����2> par1  DiyFunc�ĵ�һ��������user defines it��
///<����3> par2  DiyFunc�ĵڶ���������user defines it��
///<����3> par3	 DiyFunc�ĵ���������
///<����ֵ> ����DiyFunc�ķ���ֵ
////////////////////////////////////////////////////////////////
float func20(int port,float par1,float par2,float par3)     
{
   	float res = 0;
  	res = DiyFunc(par1,par2,par3);
	return res;
}

/////////////////////////////////////////////////////////////////
///<��������>Block�麯��
///<����1> port  δ��
///<����2> par1  δ��
///<����3> par2  δ��
///<����3> par3	 δ��
///<����ֵ> δ��
////////////////////////////////////////////////////////////////
float func21(int port,float par1,float par2,float par3)     
{
   	float res = 0; 	
	return res;
}
/////////////////////////////////////////////////////////////////
///<��������>AOall����,һ���Գ�ʼ������AO�˿�
///<����1> port  δ��
///<����2> par1  ��ʼ������  AO1toAO8 = 1�� AO8toAO1 = 2
///<����3> par2  ʱ����(s) 0,1,2...n
///<����3> par3	 ��ʼ��ֵ (v)
///<����ֵ> δ��
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
	      DAC_value[i] = par3;	//����ֵ
	      DAC_data[i] = par3;	 //��ѹֵ
	      DAC_onechannel(i,DAC_data[i]); 
		  func8(2,par2,0,0);
	   } 
	}
	else
	{
	   for(i=7;i>=0;i--)
	   {
	      AOAM[i] = AUTO; 	
	      DAC_value[i] = par3;	//����ֵ
	      DAC_data[i] = par3;	 //��ѹֵ
	      DAC_onechannel(i,DAC_data[i]);
		  func8(2,par2,0,0);   
	   } 
	}
	return res;
}

/////////////////////////////////////////////////////////////////
///<��������>DOall����,һ���Գ�ʼ������DO�˿�
///<����1> port  δ��
///<����2> par1  ��ʼ������  DO1toDO8 = 1�� DO8toDO1 = 2
///<����3> par2  ʱ����(s) 0,1,2...n
///<����3> par3	 ��ʼ��ֵ (v) 0,1
///<����ֵ> δ��
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
