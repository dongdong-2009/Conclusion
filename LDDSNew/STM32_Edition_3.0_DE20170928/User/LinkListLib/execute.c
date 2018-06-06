#include<stdio.h>
#include<stdlib.h>
#include"execute.h"
#include "usart.h"
#include"funclib.h"
#include"configdata.h"
#include"fatherlinklist.h"

#define NONSTNODE    (cursor->datapack.fid != FIDSPLITNODE ? 1:0)
#define NONUTNODE	 (cursor->datapack.fid != FIDUNITENODE ? 1:0)
#define NONSBNODE    (cursor->datapack.fid != SBEGINNODE ? 1:0)
#define NONSENODE	 (cursor->datapack.fid != SENDNODE ? 1:0)
#define NONBBNODE	 (cursor->datapack.fid != BBEGINNODE ? 1:0)
#define NONBENODE  	 (cursor->datapack.fid != BENDNODE ? 1:0)
#define NONAO        (cursor->datapack.fid != FIDAO ? 1:0)
#define NONDO		 (cursor->datapack.fid != FIDDO ? 1:0)
#define NONREGISTER  (cursor->datapack.fid != FIDREGISTER ? 1:0)
#define ISBRANCH     (cursor->pre->datapack.fid == FIDBRANCH ? 1:0)
#define ISTRUE       ((int)cursor->pre->result == 1 ? 1:0)
#define ISBLOCK      (cursor->datapack.fid == FIDBLOCK ? 1:0)
void delay_s(void);
A ConvertFIDtoFunc(int fid);
float GetParameter(const PNODE cursor,int ith);
float SearchNode(const PNODE currentcursor,const float indexnum);

/////////////////////////////////////////////////////////////////
///<��������>����˫������, ��ȡFID�Ĺ��̾��ǵ��ú����Ĺ���
///<����>�����ù�갴ִ������ͼ���̱���
///<����1>�����ͷ���
///<����2>�����β�ڵ�
///<����3>�̺߳�
///<����ֵ>�޷���ֵ
/////////////////////////////////////////////////////////////////
//void Traverse(PNODE phead,PNODE ptail,const int threadnum)
//{
//     A ff;
//	 float par1,par2,par3; //ff����������par1,par2  
//	 int fid,port;
//	 PNODE cursor;			    
//	 PNODE precursor;
//	 cursor = phead;
//	 while(cursor != NULL)
//	 {
//     //  if(ModeSel == DEBUG && NONSBNODE && NONSENODE && NONBBNODE && NONBENODE)
//	   if(1)
//	   {
//	       SentBuffer[LENGTH] = threadnum;
//		   SentBuffer[LENGTH+1] = (int)cursor->datapack.index;
//		   SentBuffer[LENGTH+2] = (int)(cursor->datapack.index*100)%100;
//           PacketHeaderGeneration(SentBuffer);
//		   UsartSendData(LENGTH+5,SentBuffer);  
//		   delay_s();
//	   }
//	   else if(ModeSel == STOP)
//	         return;
//	     
//	   par1 = GetParameter(cursor,1);
//	   par2 = GetParameter(cursor,2);
//	   par3 = GetParameter(cursor,3);
//	   fid = cursor->datapack.fid;
//	   port = cursor->datapack.port;
//	   ff = ConvertFIDtoFunc(fid);
//	   //if(PatternSel == AUTO || (NONAO && NONDO && NONREGISTER))  
//	   cursor->result = ff(port,par1,par2,par3);
//	    
//	   //�ж��Ƿ���ת�������� //�ݹ�
//	   if(ISBLOCK) 
//	   {
//	     precursor = cursor;  //��ջ
//		 if(threadnum == 0)  
//	        Traverse(MainBlockNodes[port].phead,MainBlockNodes[port].ptail,threadnum);
//		 else
//		    Traverse(SubBlockNodes[threadnum][port].phead,SubBlockNodes[threadnum][port].ptail,threadnum);
//		 cursor = precursor->next;  //��ջ
//	   }
//	   //�ж�ѭ�����������Ƿ�����ѭ��
//	   else if(!NONSTNODE)
//	   {
//	      if(ISBRANCH && ISTRUE)
//	      	  cursor = cursor->next;   //���ǰһ��������Switch����Switch�ķ���ֵΪ1��������ѭ��
//		  else
//		      cursor = cursor->subnext;	//�жϽ��Ϊ�٣���δ�����жϣ������ѭ��
//	   }
//	   else
//	   {
//           cursor = cursor->next; //�жϽ��Ϊ�棬������ִ��	  
//	   } 
//	} 
//}

////////////////////////////////////////////////////////////////
///<��������>����fid���ҵ���Ӧ�ĺ���ָ��
///<����> fid ��λ�����͵�fid
///<����ֵ> A�ͺ���ָ�� 
///////////////////////////////////////////////////////////////
A ConvertFIDtoFunc(int fid)
{
	A a = NULL;
	switch(fid)
	{
	    case 0x01: a = FuncArray[1];break;
	    case 0x02: a = FuncArray[2];break;
		case 0x03: a = FuncArray[3];break;
		case 0x04: a = FuncArray[4];break;
		case 0x05: a = FuncArray[5];break;
	    case 0x06: a = FuncArray[6];break;
	    case 0x07: a = FuncArray[7];break;
	    case 0x08: a = FuncArray[8];break;
		case 0x09: a = FuncArray[9];break;
	    case 0x0a: a = FuncArray[10];break;
		case 0x0b: a = FuncArray[11];break;
		case 0x0c: a = FuncArray[12];break;
		case 0x0d: a = FuncArray[13];break;
		case 0x0e: a = FuncArray[14];break;
		case 0x0f: a = FuncArray[15];break;
		case 0x10: a = FuncArray[16];break;
		case 0x11: a = FuncArray[17];break;
		case 0x12: a = FuncArray[18];break;
		case 0x13: a = FuncArray[19];break;
		case 0x14: a = FuncArray[20];break;
		case 0x15: a = FuncArray[21];break;
		default :  a = FuncArray[0];break;
	}
	return a;
}

////////////////////////////////////////////////////////////////
///<��������>����ú����Ĳ��� 
///<����> ith ָ�����ĸ����� 1th or 2th
///<����> currentcursor ��ǰ�ڵ�
///<����ֵ>  ���ҵ�����ָ���ڵ㺯����ִ�н������û�У�����-1
///////////////////////////////////////////////////////////////
float GetParameter(const PNODE cursor,int ith)
{
  float par;
  float index;
  int isRef;

  if(ith == 1)
  {
     isRef = cursor->datapack.flag1;	 
	 index = cursor->datapack.par1;
     if(isRef == 1)  par = SearchNode(cursor,index);
	 else  par = index;
  }
  else if(ith == 2)
  {
     isRef = cursor->datapack.flag2;
	 index = cursor->datapack.par2;
     if(isRef == 1) par = SearchNode(cursor,index);
	 else par = index;
  }
  else if(ith == 3)
  {
     isRef = cursor->datapack.flag3;	 
	 index = cursor->datapack.par3;
     if(isRef == 1)  par = SearchNode(cursor,index);
	 else  par = index; 
  }
  return par;
}

////////////////////////////////////////////////////////////////
///<��������>Ѱ��ָ��index�Ľڵ㣬�����ظýڵ�ĺ���ִ�н��
///<����> indexnum ָ���ı�֧����������	(Ŀǰ��֧�ֱ����ڵ�����)
///<����> currentcursor ��ǰ�ڵ�
///<����ֵ>  ���ҵ�����ָ���ڵ㺯����ִ�н������û�У�����-1
///////////////////////////////////////////////////////////////
 float SearchNode(const PNODE currentcursor,const float indexnum)
{
     float index = 0;
   	 PNODE p = currentcursor ->pre;
	 while(p->datapack.fid != FIDBEGINNODE || p->datapack.fid != FIDENTRYNODE)
	 {
	     //index = p->datapack.indexint + p->datapack.indexdec/100.0;
		 index = p->datapack.index;
	   	 if(index == indexnum)
		    return p->result;
		 else
		   p = p->pre;
	 }
	 while(p->datapack.fid != FIDENDNODE || p->datapack.fid != FIDEXITNODE)
	 {
	    //index = p->datapack.indexint + p->datapack.indexdec/100.0;
		index = p->datapack.index;
	   	 if(index == indexnum)
		    return p->result;
		 else
		   p = p->next;
	 }
	 return -1;
}


////////////////////////////////////////////////////////////////
///<��������>Debugģʽ���ӳ�ִ��
///<����>  NULL
///<����ֵ>  NULL
///////////////////////////////////////////////////////////////
void delay_s(void)
{
    unsigned int i;
	unsigned int j;
 
	 for(i=0;i<1000;i++)
		for(j=0;j<5000;j++);
}


