#ifndef  _FATHERLINKLIST_H
#define  _FATHERLINKLIST_H
//////////////////////////////////////////////////////////////////////////////////////////
///<��������>����ڵ����ͣ���Ϊmainlinklist��sublinklist�������ļ��ĸ��ļ�
/////////////////////////////////////////////////////////////////////////////////////////
#include<stdlib.h>
#include<stdio.h>
#include"configdata.h"

typedef struct _node
{
 	DATAPACK datapack;	          //�洢��˽ڵ�󶨵ĺ����Լ��ú����Ĳ���
	float result;				 //�洢�������ú�ķ���ֵ
	struct _node *next;	        //�洢Node�ĺ���
	struct _node *pre;	 	   //�洢Node��ǰ�ڵ�
	struct _node *subnext;    //������SplitNode���洢�߼��Ӻ��㣬����תʱӦ�ô洢���Ǹ��ڵ�
	struct _node *subpre;     //������UniteNode���洢�߼���ǰ��㣬����֧����Ļع�ڵ�
}NODE,*PNODE;

typedef struct _branchnodesparing
{
	PNODE splitnode;        //����洢�����зֺϽڵ�ԵĽṹ��
	PNODE unitenode;
}BRANCHNODES,BNODES;

typedef struct _terminalnodes
{
	PNODE phead;            //����洢������ͷβ�ڵ�ԵĽṹ��
	PNODE ptail;
}TERMINALNODES,TNODES;

typedef struct _blocknodes
{
	PNODE phead;            //����洢������ͷβ�ڵ�ԵĽṹ��
	PNODE ptail;
}BLOCKNODES,BLNODES;      

typedef struct _subthreadnodes
{						   //����洢���߳�����ͷβ�ڵ�Ľṹ��
  PNODE subphead;
  PNODE subptail;
}SNODES,SUBTHREADNODES;

extern BNODES MainBrandNodes[21];
extern TNODES MainTermlNodes[21];
extern BLNODES MainBlockNodes[7];
//extern char  MainBlockFlags[7];
extern PNODE MainPhead;	                   //��flowchart��ͷ���
extern PNODE MainPtail;		              //��flowchart��β�ڵ�
extern int MainCnt;

extern BNODES SubBrandNodes[5][21];
extern TNODES SubTermlNodes[5][21];
//extern char   SubBlockFlags[5][7];
extern BLNODES SubBlockNodes[5][7];
extern SNODES SubNodes[5];
extern int SubCnt;
void ResetLinkList(void);
#endif /*FATHERLINKLIST_H*/

