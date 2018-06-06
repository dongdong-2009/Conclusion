#ifndef _CONFIGDATA_H
#define _CONFIGDATA_H
#include<stdlib.h>
#include"protocol.h"

#define FIDAI        0x01        //AI�ڵ�����к� 
#define FIDRI        0x02        //RI�ڵ�����к�
#define FIDDI        0x03        //DI�ڵ�����к� 
#define FIDAO        0x04	     //AO�ڵ�����к�
#define FIDDO        0x05        //DO�ڵ�����к�
#define FIDPID       0x06       //PID�ڵ�����к�
#define FIDCLOSESUB  0x07       //CloseSub�ڵ�����к�
#define FIDDELAY     0x08       //Delay�ڵ�����к�
#define FIDOPENSUB   0x09       //OpenSub�ڵ�����к�
#define FIDBRANCH    0x0a       //��֧�ڵ�����к�
#define FIDUNITENODE 0x0b      //ѭ���Ͻڵ�����к�
#define FIDSPLITNODE 0x0c	    //ѭ���ֽڵ�����к�
#define FIDENTRYNODE 0x0d	   //���߳���ڽڵ�����к�
#define FIDEXITNODE  0x0e	   //���߳��˳��ڵ�����к�		  
#define FIDBEGINNODE 0x0f      //�����Ŀ�ʼ�ڵ�
#define FIDENDNODE   0x10      //�����Ľ����ڵ�
#define FIDLUT       0x11      //LUT
#define FIDREGISTER	 0x12      //Register
#define FIDMATH		 0x13	   //BasicMath�ڵ����к�
#define FIDDIY		 0x14	   //DIY�����Ľڵ����к�
#define FIDBLOCK     0x15      //BLOCK�麯���ڵ����к�

#define BBEGINNODE   0xaa     //������ʼ��־λ
#define BENDNODE	 0xbb     //����������־λ
#define SBEGINNODE   0xcc     //�����Ŀ�ʼ��־λ
#define SENDNODE     0xdd     //����������־λ

#define NUM 20              //ÿ�����ݰ����������ݸ���
#define MAINBOXMAX 120	  //���߳�������ɺ������������������ͷ�����120
#define SUBBOXMAX  60	  //���߳�������ɺ��������������������߳���)60
///////////////////////////////////////////////////////////////////////
/*
typedef struct _datapack
{
	char fid;	           //the ID of the function called 
	char port;              // the port of the function chosen
	char flag1;			   //the status flag of type of parameter1
	char flag2;            // the status flag of type of parameter2 
	char flag3;            // the status flag of type of parameter3 
	char par1inth;		  //integer bit of parameter1 
	char par1intl;
    char par1dech;		  //decimal bit of parameter1 
	char par1decl;
	char par2inth;		  //integer bit of parameter2 
	char par2intl;
    char par2dech;		  //decimal bit of parameter2 
	char par2decl;	
	char par3inth;		  //integer bit of parameter3
	char par3intl;
    char par3dech;		  //decimal bit of parameter3
	char par3decl;
	char indexint;	       //integer bit of index of function assigned in upper machine
	char indexdec;         //decimal bit of index of function assigned in upper machine 
	char reserved;
}DATAPACK;
*/
///////////////////////////////////////////////////////////////////////////////////////////
typedef struct _datapack
{
   char fid;
   char port;
   char flag1;
   char flag2;
   char flag3;
   float par1;
   float par2;
   float par3;
   float index;
}DATAPACK;
extern DATAPACK MainDataPack[MAINBOXMAX];     //the storage of each data packet in main routine 
extern DATAPACK SubDataPack[SUBBOXMAX];       //the storage of each data packet in subroutines 

int DataAnalysis(char* receivebuffer,DATAPACK* maindatapack, DATAPACK* subdatapack);

#endif /*CONFIGDATA_H*/

