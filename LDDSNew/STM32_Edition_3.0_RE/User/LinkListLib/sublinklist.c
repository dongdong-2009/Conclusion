#include"sublinklist.h"

BNODES SubBrandNodes[5][21] = {0};  //�������̵߳���������ŷֺϽڵ�
TNODES SubTermlNodes[5][21] = {0};  //�������̵߳������������������ͷ����β

//char   SubBlockFlags[5][7] = {0};   //���ʹ�õĿ��1--ʹ�ã�0--δ��
BLNODES SubBlockNodes[5][7] = {0};  //�������̵߳Ŀ�������ſ�������ͷ����β
	
int SubCnt = 0;                     //�������̵߳Ľڵ���
SNODES SubNodes[5] = {0};	        //�洢���̵߳�ͷβ�ڵ�

int creatOneSubThreadLink(DATAPACK* subdatapack);
int createOneSubChildLink(const DATAPACK* subdatapack,const int threadNum);
int createOneSubBlockLink(const DATAPACK* subdatapack,const int threadNum);
////////////////////////////////////////////////////////////
///<��������>�����������߳�
///<����1>subdatapack �洢���߳����ݰ���ָ��
///<����ֵ>����1����ɹ�������������0����ʧ��
////////////////////////////////////////////////////////////
int CreateSubThreadLinks(DATAPACK* subdatapack)
{
   int temp = 0;
   int j;
   for(j=0;j<5;j++)
   {
      //�жϵ�һ���ڵ��Ƿ�����ڽڵ�
      if(subdatapack[SubCnt].fid == FIDENTRYNODE)
      {
        temp = creatOneSubThreadLink(subdatapack);
	    if(temp == 0)
	     return 0;
	  }
	  else
	    break;
   }

   for(j=0;j<5;j++)
   {
      if(((int)SubNodes[j].subphead | (int)SubNodes[j].subptail != 0) && ((int)SubNodes[j].subphead & (int)SubNodes[j].subptail == 0))
	  return 0;
   }
   return 1;
}  
////////////////////////////////////////////////////////////
///<��������>����һ�����߳���
///<Э��˵��1>���̵߳ĵ�һ���ڵ����ұ��������߳���ڽڵ�entrynode
///<Э��˵��2>���̵߳����һ���ڵ����ұ��������߳��˳��ڵ�exitnode
///<Э��˵��3>��portλ�洢splitnode,unitenode����Ա�־λ
///<����1>subdatapack �洢���߳����ݰ���ָ��
///<����ֵ>����1����ɹ�������������0����ʧ��
////////////////////////////////////////////////////////////
int creatOneSubThreadLink(DATAPACK* subdatapack)
{
   int j,threadNum;
   PNODE p,q;

   p = (PNODE)malloc(sizeof(NODE));
   p->datapack = subdatapack[SubCnt++]; 
   p->pre = NULL;
   p->next = NULL;
   SubNodes[p->datapack.port].subphead = p;	  //port �洢�̺߳�
   threadNum = p->datapack.port;

   while (1)
   {
	   q = (PNODE)malloc(sizeof(NODE));
	   q->datapack = subdatapack[SubCnt++];
	   q->next = NULL;
	   p->next = q;
	   q->pre = p;
	   p = q;
	
	 	if (p->datapack.fid == FIDSPLITNODE)
		{
			SubBrandNodes[threadNum][p->datapack.port].splitnode = p;
		}
		else if (p->datapack.fid == FIDUNITENODE)
		{
			SubBrandNodes[threadNum][p->datapack.port].unitenode = p;
		}
	
		if (p->datapack.fid == FIDEXITNODE)
		{
			SubNodes[p->datapack.port].subptail = p;
			if(p->datapack.port != threadNum)
			   return 0;
		    else
			   break;
		}
	}
	//��������
	for(j = 1; j < 21; j++)
	{
	   if (subdatapack[SubCnt].fid == SBEGINNODE)
	   {
		  if(!createOneSubChildLink(subdatapack,threadNum))
			return 0;
	  }
	   else
	        break;
	}

	//���ֺͽڵ�Ե�����
	//�Ƿ�����޷���Ե�splitnode��unitenode
	for (j = 1; j < 21; j++)
	{
		if (SubBrandNodes[threadNum][j].splitnode == NULL && SubBrandNodes[threadNum][j].unitenode == NULL)
			continue;
		else if(SubBrandNodes[threadNum][j].splitnode != NULL && SubBrandNodes[threadNum][j].unitenode != NULL)
		{
		    if(SubTermlNodes[threadNum][j].phead == NULL || SubTermlNodes[threadNum][j].ptail == NULL)
			{
			    SubBrandNodes[threadNum][j].splitnode->subnext = SubBrandNodes[threadNum][j].unitenode;
	            SubBrandNodes[threadNum][j].unitenode->subpre  = SubBrandNodes[threadNum][j].splitnode;
			}
			else if(SubTermlNodes[threadNum][j].phead != NULL && SubTermlNodes[threadNum][j].ptail != NULL)
			{
		   	   SubBrandNodes[threadNum][j].splitnode->subnext = SubTermlNodes[threadNum][j].phead;
			   //SubTermlNodes[threadNum][j].phead->pre         = SubBrandNodes[threadNum][j].splitnode;
			   //SubBrandNodes[threadNum][j].unitenode->subpre  = SubTermlNodes[threadNum][j].ptail;
			   SubTermlNodes[threadNum][j].ptail->next        = SubBrandNodes[threadNum][j].unitenode;
			} 
		}
		else 
	       return 0;
	}

	//��������
	for(j = 1;j < 7;j++)
	{
	   if (subdatapack[SubCnt].fid == BBEGINNODE)
	   {
		  if(!createOneSubBlockLink(subdatapack,threadNum))
		    return 0;  
	   }
	   else
	      break;	  
	}
	return 1;
}

////////////////////////////////////////////////////////////
///<��������>�������߳����ݰ�������˫��̬������
///<Э��˵��>�����������������߳������еķֺϽڵ�Խ�
///<����1>maindatapack ָ��洢���߳��������ݰ���ָ��
///<����ֵ>����1����ɹ�������������0����ʧ��
////////////////////////////////////////////////////////////
int createOneSubChildLink(const DATAPACK* subdatapack,const int threadNum)
{
    int j;
	PNODE p, q;
	BNODES brandnodes[10] = {0};
	
	p = (PNODE)malloc(sizeof(NODE));
	p->datapack = subdatapack[SubCnt++];
	p->pre = NULL;
	SubTermlNodes[threadNum][p->datapack.port].phead = p;
	
	while (1)
	{
		q = (PNODE)malloc(sizeof(NODE));
		q->datapack = subdatapack[SubCnt++];
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
		    SubTermlNodes[threadNum][p->datapack.port].ptail = p; 
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

////////////////////////////////////////////////////////////
///<��������>�������߳����ݰ�������˫��̬������
///<Э��˵��>����������������ͷ����β����BlockNodes��
///<����1>maindatapack ָ��洢���߳̿������ݰ���ָ��
///<����ֵ>����1����ɹ�������������0����ʧ��
////////////////////////////////////////////////////////////
int createOneSubBlockLink(const DATAPACK* subdatapack,const int threadNum)
{
    int j;
	PNODE p, q;
	BNODES brandnodes[10] = {0};

	p = (PNODE)malloc(sizeof(NODE));
	p->datapack = subdatapack[SubCnt++];
	p->pre = NULL;
	SubBlockNodes[threadNum][p->datapack.port].phead = p;
	
	while (1)
	{
		q = (PNODE)malloc(sizeof(NODE));
		q->datapack = subdatapack[SubCnt++];
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
		    SubBlockNodes[threadNum][p->datapack.port].ptail = p; 
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

/*

////////////////////////////////////////////////////////////////////
///<��������>����Ѱ����SplitNode�ڵ���Ե�UniteNode�ڵ�
///<����1> p �����Ŀ�ʼѰ�ҽڵ�
///<����2> direction Ѱ�ҵķ��� 1 -- upward ; 0 -- downward ;
///<����ֵ> ����Ŀ��unitenode��ָ��
///////////////////////////////////////////////////////////////////
PNODE SearchUniteNode(const PNODE p,const int direction)
{
   int matchflag = p->datapack.port;
   PNODE pt = p;    //pt ��ʱָ��
   while(pt->pre != NULL)
   {
     //���㣺1.�ǺϽڵ㣻2.��flag���
     if(pt->datapack.fid == FIDUNITENODE && matchflag == pt->datapack.port)
	 {
        return pt;
	 }
	 else
	 {
	    if(direction)
		   pt = pt->pre;
		else
           pt = pt->next;
	 }
   }
    return NULL;
}
*/
