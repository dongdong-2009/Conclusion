#include"mainlinklist.h"

BNODES MainBrandNodes[21] = {0};  //�������߳���������ŷֺϽڵ�
TNODES MainTermlNodes[21] = {0};  //�������߳������������������ͷ����β

//char   MainBlockFlags[7] = {0};   //���ʹ�õĿ��1--ʹ�ã�0--δ��
BLNODES MainBlockNodes[7] = {0};  //�������߳̿�������ſ�������ͷ����β

PNODE MainPhead = NULL;		      //�������߳������������������ͷ����β
PNODE MainPtail = NULL;	          //�������߳������������������ͷ����β

int MainCnt = 0;  //�������߳̽ڵ���Ŀ
int createOneMainBlockLink(const DATAPACK* maindatapack);
int createOneMainChildLink(const DATAPACK* maindatapack);
////////////////////////////////////////////////////////////
///<��������>�������߳����ݰ����������߳������ȴ�������
///<Э��˵��>��portλ�洢UniteNode,SplitNode����Ա�־
///<����1>maindatapack ָ��洢���߳����ݰ���ָ��
///<����ֵ>����1����ɹ�������������0����ʧ��
////////////////////////////////////////////////////////////
int CreateMainThreadLink(DATAPACK* maindatapack)
{
	int j;
	PNODE p, q;
	//��������
	if (maindatapack[MainCnt].fid != FIDBEGINNODE)
	{
		return 0;
	}
	else
	{
		p = (PNODE)malloc(sizeof(NODE));
		p->datapack = maindatapack[MainCnt++];
		p->pre = NULL;
		MainPhead = p;
	}
	
	while (1)
	{
		q = (PNODE)malloc(sizeof(NODE));
		q->datapack = maindatapack[MainCnt++];
		q->next = NULL;
		p->next = q;
		q->pre = p;
		p = q;

  		if (p->datapack.fid == FIDSPLITNODE)
		{
			MainBrandNodes[p->datapack.port].splitnode = p;
		}
		else if (p->datapack.fid == FIDUNITENODE)
		{
			MainBrandNodes[p->datapack.port].unitenode = p;
		}

		if (p->datapack.fid == FIDENDNODE)
		{
			MainPtail = p;
			break;
		}
	}
	//��������
	for(j = 1; j < 21; j++)
	{
	   if (maindatapack[MainCnt].fid == SBEGINNODE)
	   {
		  if(!createOneMainChildLink(maindatapack))
			return 0;
	   }
	   else
	        break;
	}

	//���ֺͽڵ�Ե�����
	//�Ƿ�����޷���Ե�splitnode��unitenode
	for (j = 1; j < 21; j++)
	{
		if (MainBrandNodes[j].splitnode == NULL && MainBrandNodes[j].unitenode== NULL)
			continue;
		else if(MainBrandNodes[j].splitnode != NULL && MainBrandNodes[j].unitenode != NULL)
		{
		    if(MainTermlNodes[j].phead == NULL || MainTermlNodes[j].ptail == NULL)
			{
			    MainBrandNodes[j].splitnode->subnext = MainBrandNodes[j].unitenode;
	            MainBrandNodes[j].unitenode->subpre  = MainBrandNodes[j].splitnode;
			}
			else if(MainTermlNodes[j].phead != NULL && MainTermlNodes[j].ptail != NULL)
			{
		   	    MainBrandNodes[j].splitnode->subnext = MainTermlNodes[j].phead;
			    //MainTermlNodes[j].phead->pre         = MainBrandNodes[j].splitnode;
		    	//MainBrandNodes[j].unitenode->subpre  = MainTermlNodes[j].ptail;
			    MainTermlNodes[j].ptail->next        = MainBrandNodes[j].unitenode;
			} 
		}
		else 
	       return 0;
	}

	//��������
	for(j = 1;j < 7;j++)
	{
	   if (maindatapack[MainCnt].fid == BBEGINNODE)
	   {
		  if(!createOneMainBlockLink(maindatapack))
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
int createOneMainChildLink(const DATAPACK* maindatapack)
{
    int j;
	PNODE p, q;
	BNODES brandnodes[10] = {0};
	
    p = (PNODE)malloc(sizeof(NODE));
	p->datapack = maindatapack[MainCnt++];
	p->pre = NULL;
	MainTermlNodes[p->datapack.port].phead = p;
	
	while (1)
	{
		q = (PNODE)malloc(sizeof(NODE));
		q->datapack = maindatapack[MainCnt++];
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
		    MainTermlNodes[p->datapack.port].ptail = p; 
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
///<����2>order  ָ���ڼ�����
///<����ֵ>����1����ɹ�������������0����ʧ��
////////////////////////////////////////////////////////////
int createOneMainBlockLink(const DATAPACK* maindatapack)
{
    int j;
	PNODE p, q;
	BNODES brandnodes[10] = {0};
				    
	p = (PNODE)malloc(sizeof(NODE));
	p->datapack = maindatapack[MainCnt++];
	p->pre = NULL;
 	MainBlockNodes[p->datapack.port].phead = p;
	
	while (1)
	{
		q = (PNODE)malloc(sizeof(NODE));
		q->datapack = maindatapack[MainCnt++];
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
		  MainBlockNodes[p->datapack.port].ptail = p; 
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
///<��������>Ѱ�Ҵ�ĳ�������ڵ㿪ʼ����Ա�ڴ���FIDStartNode�Ľڵ�
///<����1> p �����Ŀ�ʼѰ�ҽڵ�
///<����ֵ> �����ҵ��ķ���Ҫ��Ľڵ㣬������NULL��˵�����ڴ���
///////////////////////////////////////////////////////////////////
PNODE SearchStartNode(const PNODE p)
{
	int matchflag = p->datapack.port;
	PNODE pt = p;    														             
	while (pt->pre != NULL)
	{
		//���㣺1.�ǺϽڵ㣻2.������splitnode��ͬ�ı��flag
		if (pt->datapack.fid == FIDUNITENODE && matchflag == pt->datapack.port)
		{
			return pt;
		}
		else
		{
			pt = pt->pre;
		}
	}
	return NULL;
}
*/


