#include  <stdio.h>

//存储一个顺序表，必须确定一组地址连续的空间（空间的大小为max X L）以及线性表的长度n

#define maxsize 1024        //线性表中可能的最大的节点数
typedef struct
{
    int data[maxsize];     //int型，则节点所占的空间大小L为2个字节
    int last;              //结点是data[0]，其下标值为0，其位置是1
} sequenlist               //线性表最后一个结点的下标值，即线性表的长度n=last+1

//顺序表插入操作
int Insert(sequenlist *L,int x,int i)
{
    int j;
    if(L->last>=maxsize-1)
    {
        printf("空间溢出");
        retrun 0;
    }
    else if(i<1||i>L->last+2)
    {
        printf("插入位置非法");
        return 0;
    }
    else
    {
        for(j=L->last;j>=i-1;j--)
            L->data[j+1]=L->data[j];
        L->data[i-1]=x;
        L->last=L->last+1;
    }
    return 1;
}

//顺序表删除操作
int Delete(sequenlist *L,int i)
{
    int j;
    if(i<1||i>L->last+1)
    {
        printf("删除位置非法");
        return 0;
    }
    else
    {
        for(j=i;j<=L->last;j++)
            L->data[j-1]=L->data[j];
        L->last=L->last-1;
    }
return 1;
}

main()
{
    sequenlist *L;
    int i, ch,n;
    while(1)
    {
        printf("\n 请选择：");
        printf("\n (1) 输入顺序表")；
        printf("\n (2) 插入数据");
        printf("\n (3) 删除数据");
        printf("\n (4) 结束\n");

        ch=getchar();    //取得按键结果

        switch(ch)
        {
            case 1:
                printf("\n 请输入顺序表中数据个数 n= ");    //输入数据个数
                scanf("%d", &n);
                printf("\n");
                L=(sequenlist *)malloc(sizeof(sequenlist));
                for(i=0;i<n;i++)
                {
                    printf("\n 请输入第 %d 个整型数据的值:",i+1);
                    scanf("%d",&L->data[i];)
                }
                L->last=n-1;
                printf("\n 输入的顺序表数据为：");
                for(i=0;i<=L->last;i++)
                    printf("%d", L->data[i]);
                printf("\n");
                break;
            
            case 2:
                printf("\n 请输入插入顺序表中的数据");
                scanf("%d",&n);
                printf("\n 请输入插入顺序表中的位置");
                scanf("%d",&i);
                printf("\n");
                if(Insert(L,n,i))
                    {
                        printf("\n 插入后的数据顺序表为:");
                        for(i=0;i<L->last;i++)
                            printf("%d",L->data[i]);
                        printf("\n");
                    }
                break;

            case 3:
                printf("\n 请输入删除数据的位置");
                scanf("%d",&i);
                printf("\n");
                if(Delete(L,i))
                    {
                        printf("\n 删除后的数据顺序表为:");
                        for(i=0;i<L->last;i++)
                            printf("%d",L->data[i]);
                        printf("\n");
                    }
                break;

            case 4:
                return;    //程序结束
        }
    }
    
}