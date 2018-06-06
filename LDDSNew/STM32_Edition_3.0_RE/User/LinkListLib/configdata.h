#ifndef _CONFIGDATA_H
#define _CONFIGDATA_H
#include<stdlib.h>
#include"protocol.h"

#define FIDAI        0x01        //AI节点的序列号 
#define FIDRI        0x02        //RI节点的序列号
#define FIDDI        0x03        //DI节点的序列号 
#define FIDAO        0x04	     //AO节点的序列号
#define FIDDO        0x05        //DO节点的序列号
#define FIDPID       0x06       //PID节点的序列号
#define FIDCLOSESUB  0x07       //CloseSub节点的序列号
#define FIDDELAY     0x08       //Delay节点的序列号
#define FIDOPENSUB   0x09       //OpenSub节点的序列号
#define FIDBRANCH    0x0a       //分支节点的序列号
#define FIDUNITENODE 0x0b      //循环合节点的序列号
#define FIDSPLITNODE 0x0c	    //循环分节点的序列号
#define FIDENTRYNODE 0x0d	   //子线程入口节点的序列号
#define FIDEXITNODE  0x0e	   //子线程退出节点的序列号		  
#define FIDBEGINNODE 0x0f      //主链的开始节点
#define FIDENDNODE   0x10      //主链的结束节点
#define FIDLUT       0x11      //LUT
#define FIDREGISTER	 0x12      //Register
#define FIDMATH		 0x13	   //BasicMath节点序列号
#define FIDDIY		 0x14	   //DIY函数的节点序列号
#define FIDBLOCK     0x15      //BLOCK块函数节点序列号

#define BBEGINNODE   0xaa     //块链开始标志位
#define BENDNODE	 0xbb     //块链结束标志位
#define SBEGINNODE   0xcc     //子链的开始标志位
#define SENDNODE     0xdd     //子链结束标志位

#define NUM 20              //每个数据包包含的数据个数
#define MAINBOXMAX 120	  //主线程最多容纳函数框数（包括主链和分链）120
#define SUBBOXMAX  60	  //子线程最多容纳函数框数（包括所有子线程链)60
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

