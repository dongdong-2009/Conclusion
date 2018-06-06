#include"sublinklist.h"

BNODES SubBrandNodes[5][21] = {0};  //用于子线程的主链，存放分合节点
TNODES SubTermlNodes[5][21] = {0};  //用于子线程的子链，存放子链的链头和链尾

//char   SubBlockFlags[5][7] = {0};   //标记使用的块号1--使用，0--未用
BLNODES SubBlockNodes[5][7] = {0};  //用于子线程的块链，存放块链的链头和链尾
	
int SubCnt = 0;                     //计数子线程的节点数
SNODES SubNodes[5] = {0};	        //存储子线程的头尾节点

int creatOneSubThreadLink(DATAPACK* subdatapack);
int createOneSubChildLink(const DATAPACK* subdatapack,const int threadNum);
int createOneSubBlockLink(const DATAPACK* subdatapack,const int threadNum);
////////////////////////////////////////////////////////////
///<功能描述>创建所有子线程
///<参数1>subdatapack 存储子线程数据包的指针
///<返回值>返回1代表成功建立链表。返回0代表失败
////////////////////////////////////////////////////////////
int CreateSubThreadLinks(DATAPACK* subdatapack)
{
   int temp = 0;
   int j;
   for(j=0;j<5;j++)
   {
      //判断第一个节点是否是入口节点
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
///<功能描述>创建一个子线程链
///<协议说明1>子线程的第一个节点是且必须是子线程入口节点entrynode
///<协议说明2>子线程的最后一个节点是且必须是子线程退出节点exitnode
///<协议说明3>用port位存储splitnode,unitenode的配对标志位
///<参数1>subdatapack 存储子线程数据包的指针
///<返回值>返回1代表成功建立链表。返回0代表失败
////////////////////////////////////////////////////////////
int creatOneSubThreadLink(DATAPACK* subdatapack)
{
   int j,threadNum;
   PNODE p,q;

   p = (PNODE)malloc(sizeof(NODE));
   p->datapack = subdatapack[SubCnt++]; 
   p->pre = NULL;
   p->next = NULL;
   SubNodes[p->datapack.port].subphead = p;	  //port 存储线程号
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
	//创建子链
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

	//检测分和节点对的数量
	//是否存在无法配对的splitnode与unitenode
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

	//创建块链
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
///<功能描述>根据子线程数据包，创建双向动态子链表
///<协议说明>创建子链，并和子线程主链中的分合节点对接
///<参数1>maindatapack 指向存储主线程子链数据包的指针
///<返回值>返回1代表成功建立链表。返回0代表失败
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
///<功能描述>根据主线程数据包，创建双向动态块链表
///<协议说明>创建块链，并把链头和链尾放在BlockNodes中
///<参数1>maindatapack 指向存储主线程块链数据包的指针
///<返回值>返回1代表成功建立链表。返回0代表失败
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
///<功能描述>向下寻找与SplitNode节点配对的UniteNode节点
///<参数1> p 给定的开始寻找节点
///<参数2> direction 寻找的方向 1 -- upward ; 0 -- downward ;
///<返回值> 返回目标unitenode的指针
///////////////////////////////////////////////////////////////////
PNODE SearchUniteNode(const PNODE p,const int direction)
{
   int matchflag = p->datapack.port;
   PNODE pt = p;    //pt 临时指针
   while(pt->pre != NULL)
   {
     //满足：1.是合节点；2.且flag相等
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
