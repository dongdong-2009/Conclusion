#ifndef  _FATHERLINKLIST_H
#define  _FATHERLINKLIST_H
//////////////////////////////////////////////////////////////////////////////////////////
///<功能描述>定义节点类型，作为mainlinklist和sublinklist两个子文件的父文件
/////////////////////////////////////////////////////////////////////////////////////////
#include<stdlib.h>
#include<stdio.h>
#include"configdata.h"

typedef struct _node
{
 	DATAPACK datapack;	          //存储与此节点绑定的函数以及该函数的参数
	float result;				 //存储函数调用后的返回值
	struct _node *next;	        //存储Node的后结点
	struct _node *pre;	 	   //存储Node的前节点
	struct _node *subnext;    //仅用于SplitNode，存储逻辑子后结点，即跳转时应该存储的那个节点
	struct _node *subpre;     //仅用于UniteNode，存储逻辑子前结点，即分支链表的回归节点
}NODE,*PNODE;

typedef struct _branchnodesparing
{
	PNODE splitnode;        //定义存储主链中分合节点对的结构体
	PNODE unitenode;
}BRANCHNODES,BNODES;

typedef struct _terminalnodes
{
	PNODE phead;            //定义存储子链的头尾节点对的结构体
	PNODE ptail;
}TERMINALNODES,TNODES;

typedef struct _blocknodes
{
	PNODE phead;            //定义存储块链的头尾节点对的结构体
	PNODE ptail;
}BLOCKNODES,BLNODES;      

typedef struct _subthreadnodes
{						   //定义存储子线程主链头尾节点的结构体
  PNODE subphead;
  PNODE subptail;
}SNODES,SUBTHREADNODES;

extern BNODES MainBrandNodes[21];
extern TNODES MainTermlNodes[21];
extern BLNODES MainBlockNodes[7];
//extern char  MainBlockFlags[7];
extern PNODE MainPhead;	                   //主flowchart的头结点
extern PNODE MainPtail;		              //主flowchart的尾节点
extern int MainCnt;

extern BNODES SubBrandNodes[5][21];
extern TNODES SubTermlNodes[5][21];
//extern char   SubBlockFlags[5][7];
extern BLNODES SubBlockNodes[5][7];
extern SNODES SubNodes[5];
extern int SubCnt;
void ResetLinkList(void);
#endif /*FATHERLINKLIST_H*/

