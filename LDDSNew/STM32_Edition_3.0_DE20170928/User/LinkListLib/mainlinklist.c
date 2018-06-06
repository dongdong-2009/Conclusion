#include"mainlinklist.h"

BNODES MainBrandNodes[21] = {0};  //用于主线程主链，存放分合节点
TNODES MainTermlNodes[21] = {0};  //用于主线程子链，存放子链的链头和链尾

//char   MainBlockFlags[7] = {0};   //标记使用的块号1--使用，0--未用
BLNODES MainBlockNodes[7] = {0};  //用于主线程块链，存放块链的链头和链尾

PNODE MainPhead = NULL;		      //用于主线程主链，存放主链的链头和链尾
PNODE MainPtail = NULL;	          //用于主线程主链，存放主链的链头和链尾

int MainCnt = 0;  //计数主线程节点数目
int createOneMainBlockLink(const DATAPACK* maindatapack);
int createOneMainChildLink(const DATAPACK* maindatapack);
////////////////////////////////////////////////////////////
///<功能描述>根据主线程数据包，创建主线程链表，先创建主链
///<协议说明>用port位存储UniteNode,SplitNode的配对标志
///<参数1>maindatapack 指向存储主线程数据包的指针
///<返回值>返回1代表成功建立链表。返回0代表失败
////////////////////////////////////////////////////////////
int CreateMainThreadLink(DATAPACK* maindatapack)
{
	int j;
	PNODE p, q;
	//创建主链
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
	//创建子链
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

	//检测分和节点对的数量
	//是否存在无法配对的splitnode与unitenode
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

	//创建块链
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
///<功能描述>根据主线程数据包，创建双向动态子链表
///<协议说明>创建子链，并和主线程主链中的分合节点对接
///<参数1>maindatapack 指向存储主线程子链数据包的指针
///<返回值>返回1代表成功建立链表。返回0代表失败
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
///<功能描述>根据主线程数据包，创建双向动态块链表
///<协议说明>创建块链，并把链头和链尾放在BlockNodes中
///<参数1>maindatapack 指向存储主线程块链数据包的指针
///<参数2>order  指定第几个块
///<返回值>返回1代表成功建立链表。返回0代表失败
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
///<功能描述>寻找从某个给定节点开始，成员在存在FIDStartNode的节点
///<参数1> p 给定的开始寻找节点
///<返回值> 返回找到的符合要求的节点，若返回NULL，说明存在错误
///////////////////////////////////////////////////////////////////
PNODE SearchStartNode(const PNODE p)
{
	int matchflag = p->datapack.port;
	PNODE pt = p;    														             
	while (pt->pre != NULL)
	{
		//满足：1.是合节点；2.具有与splitnode相同的标号flag
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


