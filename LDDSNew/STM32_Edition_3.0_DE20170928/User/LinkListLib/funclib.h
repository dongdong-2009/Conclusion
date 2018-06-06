#ifndef _FUNCLIB_H
#define _FUNCLIB_H
#include<stdio.h>
#include<stdlib.h>
//#define FuncNum 25 

///////////////////////////////////////////////////////////////////////////////
///<��������> ����ָ�뺯���������ͣ������������п⺯���Ĺ��е�ǩ��
///<�β�1> port �˿ں�, ѡ��˺������ĸ��˿ڻ���
///<�β�2> par  ����λ�������û����������Ҫ��Ӧ��ֵ
///<�β�3> ThreadNum �̺߳ţ����ô˺������̵߳��̺߳�
//////////////////////////////////////////////////////////////////////////////
typedef float (*A)(int,float,float,float);

float func0(int port,float par1,float par2,float par3);      // Default
float func1(int port,float par1,float par2,float par3);        // AI
float func2(int port,float par1,float par2,float par3);        // ARI
float func3(int port,float par1,float par2,float par3);        // DI
float func4(int port,float par1,float par2,float par3);        // AO
float func5(int port,float par1,float par2,float par3);        // DO
float func6(int port,float par1,float par2,float par3);   	    //PID
float func7(int port,float par1,float par2,float par3);		   // Close SUB
float func8(int port,float par1,float par2,float par3);        //delay
float func9(int port,float par1,float par2,float par3);		 //OPEN SUB
float func10(int port,float par1,float par2,float par3);        // Branch
float func11(int port,float par1,float par2,float par3);        // StartNode
float func12(int port,float par1,float par2,float par3);       // EndNode  
float func13(int port,float par1,float par2,float par3);       // EntryNode
float func14(int port,float par1,float par2,float par3);       // ExitNode
float func15(int port,float par1,float par2,float par3);       // Begin
float func16(int port,float par1,float par2,float par3);      // Ene
float func17(int port,float par1,float par2,float par3);      //LUT	
float func18(int port,float par1,float par2,float par3);      //Register
float func19(int port,float par1,float par2,float par3);      //	BasicMath
float func20(int port,float par1,float par2,float par3);      //	DIYAlgorithm
float func21(int port,float par1,float par2,float par3);      // Block
float func22(int port,float par1,float par2,float par3);      //  AO_ALL
float func23(int port,float par1,float par2,float par3);      // DO_ALL
extern  A FuncArray[];

#endif /*_FUNCLIB_H*/


