//定义结构体node的同时定义了一个结构体node的变量linklist
//同时可以使用linklist来定义node的结构体变量
typedef struct node                       //结点类型定义
{
    char data;                            //结点的数据域类型
    struct node *next;                   //结点的指针域类型
} linklist;

//建立字符链函数，返回值为链表的头地址----头插法
linklist *CreatList1()
{
     char ch; linklist *head,*p;           //ch存放用户输入的字符，该字符作为新建链表结点的数据域数值，指针变量head始终指向新建链表的头结点，指针变量p指向新分配的结点
     head=NULL;                          //开始链表的头指针为空
     ch=getchar();                      //输入最后一个结点的字符值
     while(ch!='#')                     //通过输入结束标志字符结束链表的建立，结束标志字符的确定原则是不可能在字符链表中出现。
     {
         p=(linklist*)malloc(sizeof(linklist)); //在创建链表时，每增加一个结点，就动态分配一个结点空间，并用P指针变量保存其地址，各结点的空间并不一定连续
         p->data=ch;                           //将输入的字符放入新节点的数据域中
         p->next=head;
         head=p;
         ch=getchar();                         //输入下一个结点字符值
     }
     return head;
}

linklist *CreatList2()
{
    char ch;             //用于存放用户输入的字符
    linklist *head;      //head始终指向新建链表的头结点
    linklist *p;         //p始终指向新分配的结点空间
    linklist *e;        //e始终指向新建链表的尾结点

    head=NULL;         //开始链表的头尾都是空
    e=NULL;
    ch=getchar();
    while(ch!='#')
    {
        p=(linklist*)malloc(sizeof(linklist));   //动态分配结点空间
        p->data=ch;                              //将输入字符存放在新结点的数据域中
        if(head==NULL)                           //第一个结点的操作，原头指针指向空，必须改变头指针head的值，将其指向第一个结点的p
            head=p;
        else                               //当链表非空时，将原链表尾结点的指针指向新结点P
            e->next=p;
        e=p;                              //将尾结点指针保存在e中
        ch=getchar();
    }
    if(e!=NULL)                          //当链表非空时，应将尾结点的指针域置空。当链表为空时(e的值为NULL),且输入的第一个字符为结尾符时，说明未建链表，没有尾结点，不需要对指针域做置空处理
        e->next=NULL;
    
    return head;
}

//引入头结点的尾插法
//函数返回链表结点的指针类型
linklist *CreatList3()
{
    char ch;
    linklist *head,*p,*e;
    head=(linklist *)malloc(sizeof(linklist));  //建立头结点
    e=head;  //e开始时候指向头结点，以后指向尾结点
    ch=getchar();
    while(ch!='#')
    {
        p=(linklist *)malloc(sizeof(linklist));   //P指向新增结点
        p->data=ch;                              //将输入的字符出入新结点的数据域中
        e->next=p;                              //新结点插入表尾
        e=p;                                    //尾指针e指向新的表尾
        ch=getchar();
    }
    e->next=NULL;
    return head;
}


//查找运算，按序号查找：从链表的头指针开始，经过各结点的指针域，逐个结点进行搜索，直到搜索到指定序号结点为止
//Input:  para1---链表的头结点   para2---所查结点的序号
//Output: 所查结点的存储地址，如未找到，则返回空
linklist *Find1(linklist *head,int i)
{
    linklist *p, int j=1;
    p=head->next;                                 //p的初值，指向第一个结点
    while(j<i&&p->next!=NULL)
    {
        p=p->next;
        j++;
    }
    if(j==i)
        return p;
    else
        return NULL;
}

//按值查找，在链表中查找给定结点值的结点存储地址
//Input: para1---head是指向链表的头结点，para2---e是所查结点的值  para3---结点序号的指针变量，用于返回已查到结点的序号
linklist *Find2(linklist *head,char e,int *i)
{
    linklist *p;
    p->next=head;
    *i=1;          //记录查找结点的序号
    while(p!=NULL)             //搜索链表所有结点，直到最后结点为止
    {
        if(p->data!=e)
        {
            p=p->next;
            *i=*i+1;
        }
        else
            break;   //找到结点，退出循环
    }
    return  p;
}

//单链表的插入函数：指定位置插入
//Input:para1---链表的头结点，para2---插入位置，para3---所插入结点的数值
//Output:1---插入成功   0---插入不成功
int ListInsert(linklist *head,int i,char e)
{
    int j=0; //用于记录当前搜索位置
    linklist *p;  //p用于指向搜索的结点
    linklist *s;  //s用于指向插入的结点

    p=head;   //p从头结点开始搜索
    while(j<i-1&&p->next!=NULL)
    {
        p=p->next;
        j++;
    }
    if(j!=i-1)                 //搜索结束，仍未找到插入位置，说明i值不合法
        return 0
    s=(linklist *)malloc(sizeof(linklist));
    s->data=e;                  //将待插数据放入新结点的数据域中
    s->next=p->next;            //将待插结点连接其后继结点
    p->next=s;                  //将待插结点连接其前趋结点
    return 1;
}

//单链表删除程序：删除指定位置的结点运算
//Input:para1---链表的头结点，para2---删除结点的位置
//Output: 1---删除成功，0---删除失败
int LinkDelete(linklist *head, int i)     //删除第i个结点
{
    int j=0;    //计数器J用于记录当前搜索位置
    linklist *p;
    linklist *s;
    p=head;
    while(j<i-1&&p->next!=NULL)
    {
        p=p->next;
        j++;
    }
    if(j!=i-1||p->next=NULL)
        return 0;
    s=p->next;           //s指向删除的结点
    p->next=s->next;         //删除结点
    free(s);                   //释放删除结点的空间
    return 1;   
}