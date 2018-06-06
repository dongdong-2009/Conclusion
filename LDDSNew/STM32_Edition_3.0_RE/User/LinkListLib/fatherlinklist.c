#include <stdlib.h>
#include <string.h>
#include"fatherlinklist.h"
#include "configdata.h"
#include "runtimedata.h"
#include "timer.h"

void DestroyLinkList(PNODE phead,PNODE ptail);

void ResetLinkList(void)			
{ 
   int temp,j;

   memset(RTD_value,0,sizeof(float)*4);
   memset(ADC_value,0,sizeof(float)*12);
   memset(DAC_value,0,sizeof(float)*8);
   memset(DI_data,0,sizeof(char)*8);
   memset(DO_data,0,sizeof(char)*8);
   memset(ReceivedBuffer,0,sizeof(char)*4000);
   memset(MainDataPack,0,sizeof(DATAPACK)*120);
   memset(SubDataPack,0,sizeof(DATAPACK)*60);
   memset(MainBrandNodes,0,sizeof(BNODES)*21);
   MainCnt = 0;
   SubCnt = 0;   

   for(temp=0;temp<5;temp++)
   {
      TurnOffTim(temp);
   }
   for(temp=0;temp<21;temp++)
   {
     if(MainTermlNodes[temp].phead && MainTermlNodes[temp].ptail)
     DestroyLinkList(MainTermlNodes[temp].phead,MainTermlNodes[temp].ptail);
   }
   for(temp=0;temp<7;temp++)
   {
     if(MainBlockNodes[temp].phead && MainBlockNodes[temp].ptail)
     DestroyLinkList(MainBlockNodes[temp].phead,MainBlockNodes[temp].ptail);
   }
   for(temp=0;temp<5;temp++)
   {
     for(j=0;j<21;j++)
	 {
       if(SubTermlNodes[temp][j].phead && SubTermlNodes[temp][j].ptail)
        DestroyLinkList(SubTermlNodes[temp][j].phead,SubTermlNodes[temp][j].ptail);
	 }
   }
   for(temp=0;temp<5;temp++)
   {
     for(j=0;j<7;j++)
	 {
       if(SubBlockNodes[temp][j].phead && SubBlockNodes[temp][j].ptail)
        DestroyLinkList(SubBlockNodes[temp][j].phead,SubBlockNodes[temp][j].ptail);
	 }
   }
   memset(MainTermlNodes,0,sizeof(TNODES)*21);
   memset(MainBlockNodes,0,sizeof(BLNODES)*7);
   memset(SubTermlNodes,0,sizeof(TNODES)*21*5);
   memset(SubBlockNodes,0,sizeof(BLNODES)*7*5);
   for(temp=0;temp<5;temp++)
   {
     if(SubNodes[temp].subphead && SubNodes[temp].subptail)
     DestroyLinkList(SubNodes[temp].subphead,SubNodes[temp].subptail);
   }
   memset(SubNodes,0,sizeof(SNODES)*5);
   DestroyLinkList(MainPhead,MainPtail);
   MainPhead = NULL;
   MainPtail = NULL; 
}

///<��������> �ݻ������ͷŶ�̬������ڴ�
void DestroyLinkList(PNODE phead,PNODE ptail)
{
	int i=0;
	PNODE p = phead;
	PNODE q = NULL;
   while(p!=ptail)
   {
     q = p;
	 p = p->next;
     free(q);
	 i++;
   }
   free(p);	  
}

/*
int CreateChildLink(const DATAPACK* childdatapack,PNODE phead,PNODE,ptail);
int CreateBlockLink(const DATAPACK* blockdatapack,PNODE phead,PNODE,ptail);

////////////////////////////////////////////////////////////
///<��������>�����������ݰ�������������
///<Э��˵��>������������ͷ��β�������ж�Ӧ�ķֺϽڵ�Խ�
///<����1>childdatapack ָ���������ݰ���ָ��
///<����2>phead ��������������ͷ
///<����3>ptail ��������������β
///<����4>num   �����Ľڵ���
///<����ֵ>����1����ɹ�������������0����ʧ��
////////////////////////////////////////////////////////////
int CreateChildLink(const DATAPACK* childdatapack,PNODE phead,PNODE,ptail,int num);
{
    int j = 0;
	int cnt = 0;
	PNODE p, q;
	BNODES brandnodes[10] = {0};
	if (childdatapack[cnt].fid != SBEGINNODE)
	{
		return 0;
	}
	else
	{
		p = (PNODE)malloc(sizeof(NODE));
		p->datapack = childdatapack[cnt++];
		p->pre = NULL;
		phead = p;
	}
	
	while (1)
	{
		q = (PNODE)malloc(sizeof(NODE));
		q->datapack = childdatapack[cnt++];
		q->next = NULL;
		p->next = q;
		q->pre = p;
		p = q;
			  
 	   if (p->datapack.fid == FIDSPLITNODE)
	   {
		 brandnodes[p->datapack.port].splitnode = p;
	   }
	  else if (p->datapack.fid == FIDUNITENODE)
	   {
		 brandnodes[p->datapack.port].unitenode = p;
	   }
		
  	  if (p->datapack.fid == SENDNODE)
	   {
		    ptail = p; 
			break;
	   }
    }
   num = cnt;
   for (j = 0; j < 10; j++)
   {
	 if (brandnodes[j].splitnode == NULL || brandnodes[j].unitenode== NULL)
	   continue;
	 else
	 {
	   brandnodes[j].splitnode->subnext = brandnodes[j].unitenode;
	   brandnodes[j].unitenode->subpre = brandnodes[j].splitnode;
	 }
   }
  return 1;
}

////////////////////////////////////////////////////////////
///<��������>���ݿ������ݰ����������������ؿ�������ͷ����β
///<Э��˵��>BBEGINNODE ������ʼ���λ��BENDNODE �����������λ
///<����1>blockdatapack ָ��洢�������ݰ���ָ��
///<����2>phead ������ͷ
///<����3>ptail ������β
///<����ֵ>����1����ɹ�������������0����ʧ��
////////////////////////////////////////////////////////////
int CreateBlockLink(const DATAPACK* blockdatapack,PNODE phead,PNODE,ptail);
{
    int j = 0;
	int cnt = 0;
	PNODE p, q;
	BNODES brandnodes[10] = {0};

	if (blockdatapack[cnt].fid != BBEGINNODE)
	{
		return 0;
	}
	else
	{
		p = (PNODE)malloc(sizeof(NODE));
		p->datapack = blockdatapack[cnt++];
		p->pre = NULL;
		phead = p;
	}
	
	while (1)
	{
		q = (PNODE)malloc(sizeof(NODE));
		q->datapack = blockdatapack[cnt++];
		q->next = NULL;
		p->next = q;
		q->pre = p;
		p = q;
			  
 	   if (p->datapack.fid == FIDSPLITNODE)
	   {
		 brandnodes[p->datapack.port].splitnode = p;
	   }
	  else if (p->datapack.fid == FIDUNITENODE)
	   {
		 brandnodes[p->datapack.port].unitenode = p;
	   }
		
  	  if (p->datapack.fid == BENDNODE)
	   {
		    ptail = p; 
			break;
	   }
    }

   for (j = 0; j < 10; j++)
   {
	 if (brandnodes[j].splitnode == NULL || brandnodes[j].unitenode== NULL)
	   continue;
	 else
	 {
	   brandnodes[j].splitnode->subnext = brandnodes[j].unitenode;
	   brandnodes[j].unitenode->subpre = brandnodes[j].splitnode;
	 }
   }
   return 1;
}
*/
