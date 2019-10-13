#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
//线性表的双向链表存储结构
typedef struct lnode
{
    int data;
    struct lnode *prior;
    struct lnode *next;
}Lnode ,* linklist;
//线性表的单向链表存储结构（用于建立加和减的链表）
typedef struct node
{
    int data;
    struct node *prior;
    struct node *next;
}Node , * LinkList;

int len=0;//定义全局变量，记录第三个链表的长度。

void build(linklist head);//建立链表，把数1，数2存入链表。
void plus(linklist head1,linklist head2);//加法运算
void minus(linklist head1,linklist head2);//减法运算
void print(linklist head);//把结果打印出来

int main()
{
    char operate;
    linklist head1,head2;
    head1=(linklist)malloc(sizeof(Lnode));
    head1->next=NULL;
    head2=(linklist)malloc(sizeof(Lnode));
    head2->next=NULL;//定义两个空链表，用于存储两个长整数
    printf("输入第一个数:\n");
    build(head1);
    printf("请输入运算符：+ or - :\n");
    scanf("%c",&operate);
    if((operate!='+')&&(operate!='-'))//检测运算符正确不正确
    {
        printf("运算符错误！");
    }
    else
    {
        getchar();
        printf("请输入第二个数：\n");
        build(head2);
        printf("\n");
        print(head1);
        printf("\n%c\n",operate);
        print(head2);
        printf("\n=\n");
    }
    if(operate=='+')
    {
        plus(head1,head2);
    }
    if(operate=='-')
    {
        minus(head1,head2);//减法完成
    }

    return 0;
}

void build(linklist head)
{
    char temp;
    linklist p;
    head->data=0;
    while((temp=getchar())!= '\n')
    {
        if((temp<'0')||(temp>'9'))//用ASCll码来检测长整数是不是含有其他字符。
        {
            printf("输入的数据含有无法识别字符！");
            exit(0);
        }
        p=(linklist)malloc(sizeof(Lnode));
        p->data=temp-48;
        if(head->data==0)//因为存储两个长整数的链表是双向循环链表，添加第一节点时有点特殊；head->data里面存着节点数量。
        {
            head->next=p;
            head->prior=p;
            p->prior=head;
            p->next=head;
        }
        else//头插法逆序存储在链表中
        {
            p->prior=head->next->prior;
            p->next=head->next;
            p->next->prior=p;
            head->next=p;
        }
        head->data=head->data+1;
    }
}

void plus(linklist head1,linklist head2)
{
    int a=0;//a记录着进位。
    linklist rear1=head1->next;
    linklist rear2=head2->next;
    LinkList head3,p,pre;
    head3=(LinkList)malloc(sizeof(Node));
    head3->next=NULL;
    pre=head3;
    while((rear1!=head1)&&(rear2!=head2))//因为是循环链表，所以遍历到头结点的前一个正好遍历完整。此处是把较短的链表加载完。
    {
        p=(LinkList)malloc(sizeof(Node));
        p->data=(rear1->data+rear2->data+a)%10;
        a=(rear1->data+rear2->data+a)/10;//进位
        rear1=rear1->next;
        rear2=rear2->next;
        if(len==0)//因为head3链表不是循环链表，添加第一个结点时特殊，因为head3->next=NULL,所以不能p->prior=head3->next->prior。
        {
            head3->next=p;
            p->prior=head3;
            p->next=NULL;

        }
        else
        {
            p->prior=head3->next->prior;
            p->next=head3->next;
            p->next->prior=p;
            head3->next=p;
        }
        len++;
    }
    while((head1->data>head2->data)&&(rear1!=head1))//若整数1比整数2长，则把数1剩下长度的数计算存到链表3中
    {
        p=(LinkList)malloc(sizeof(Node));
        p->data=(rear1->data+a)%10;
        a=(rear1->data+a)/10;
        rear1=rear1->next;
        p->prior=head3->next->prior;
        p->next=head3->next;
        p->next->prior=p;
        head3->next=p;
    }
    while((head2->data>head1->data)&&(rear2!=head2))//若整数2比整数1长，则把数2剩下长度的数计算存到链表3中
    {
        p=(LinkList)malloc(sizeof(Node));
        p->data=(rear2->data+a)%10;
        a=(rear2->data+a)/10;
        rear2=rear2->next;
        p->prior=head3->next->prior;
        p->next=head3->next;
        p->next->prior=p;
        head3->next=p;
    }
    if(a>0)
    {
        p=(LinkList)malloc(sizeof(Node));
        p->data=a;
        p->prior=head3->next->prior;
        p->next=head3->next;
        p->next->prior=p;
        head3->next=p;
    }
    pre=head3->next;
    while(pre)
    {
        printf("%d",pre->data);
        pre=pre->next;
    }
}

void minus(linklist head1,linklist head2)
{
    int a=0;
    linklist q1,q2;
    linklist rear1=head1->next;
    linklist rear2=head2->next;
    LinkList head3,p,pre;
    head3=(LinkList)malloc(sizeof(Node));
    head3->next=NULL;
    pre=head3;
    if(head1->data>head2->data)//若整数1比整数2长
    {
        while(rear2!=head2)
        {
            p=(LinkList)malloc(sizeof(Node));
            p->data=rear1->data-rear2->data-a;
            if(p->data<0)//p->data<0代表对应的rear1->data小于rear2->data.
            {
                p->data=p->data+10;//从前面借一位
                a=1;
            }
            else
            {
                a=0;
            }
            rear1=rear1->next;
            rear2=rear2->next;
            if(len==0)//因为head3链表不是循环链表，添加第一个结点时特殊，因为head3->next=NULL,所以不能p->prior=head3->next->prior。
            {
                head3->next=p;
                p->prior=head3;
                p->next=NULL;
            }
            else
            {
                p->prior=head3->next->prior;
                p->next=head3->next;
                p->next->prior=p;
                head3->next=p;
            }
            len++;
        }
        while(rear1!=head1&&rear2==head2)//若整数1比整数2长，则把数1剩下长度的数计算存到链表3中
        {
            p=(LinkList)malloc(sizeof(Node));
            p->data=rear1->data-a;
            if(p->data<0)
            {
                p->data=p->data+10;
                a=1;
            }
            else
            {
                a=0;
            }
            rear1=rear1->next;
            p->prior=head3->next->prior;
            p->next=head3->next;
            p->next->prior=p;
            head3->next=p;
        }
    }

    if(head2->data>head1->data)//数2比数1长
    {
        printf("-");//先输出负号
        while(rear1!=head1)
        {
            p=(LinkList)malloc(sizeof(Node));
            p->data=rear2->data-rear1->data-a;
            if(p->data<0)//p->data<0代表对应的rear2->data小于rear1->data.
            {
                p->data=p->data+10;
                a=1;
            }
            else
            {
                a=0;
            }
            rear2=rear2->next;
            rear1=rear1->next;
            if(len==0)//因为head3链表不是循环链表，添加第一个结点时特殊，因为head3->next=NULL,所以不能p->prior=head3->next->prior。
            {
                head3->next=p;
                p->prior=head3;
                p->next=NULL;
            }
            else
            {
                p->prior=head3->next->prior;
                p->next=head3->next;
                p->next->prior=p;
                head3->next=p;
            }
            len++;
        }
        while(rear2!=head2&&rear1==head1)
        {
            p=(LinkList)malloc(sizeof(Node));
            p->data=rear2->data-a;
            if(p->data<0)
            {
                p->data=p->data+10;
                a=1;
            }
            else
            {
                a=0;
            }
            rear2=rear2->next;
            p->prior=head3->next->prior;
            p->next=head3->next;
            p->next->prior=p;
            head3->next=p;
        }
    }

    if(head1->data==head2->data)//最复杂的是两个数一样长。
    {
        q1=head1->prior;//因为两个整数是逆序存储，所以这样是从头遍历。
        q2=head2->prior;
        while(((q1->data)==(q2->data))&&q1!=head1)//遍历检查两个长整数，如果完全一样，则输出零。
        {
            q1=q1->prior;
            q2=q2->prior;
            if(q1==head1)
                printf("0");
        }
        if((q1->data)>(q2->data))//如果发现数1大于数2
        {
            while(rear1!=head1)
            {
                p=(LinkList)malloc(sizeof(Node));
                p->data=rear1->data-rear2->data-a;
                if(p->data<0)
                {
                    p->data=p->data+10;
                    a=1;
                }
                else
                {
                    a=0;
                }
                rear1=rear1->next;
                rear2=rear2->next;
                if(len==0)
                {
                    head3->next=p;
                    p->prior=head3;
                    p->next=NULL;
                }
                else
                {
                    p->prior=head3->next->prior;
                    p->next=head3->next;
                    p->next->prior=p;
                    head3->next=p;
                }
                len++;
            }
        }
        if((q1->data)<(q2->data))//如果发现数1小于数2
        {

            while(rear1!=head1)
            {
                p=(LinkList)malloc(sizeof(Node));
                p->data=rear2->data-rear1->data-a;
                if(p->data<0)
                {
                    p->data=p->data+10;
                    a=1;
                }
                else
                {
                    a=0;
                }
                rear1=rear1->next;
                rear2=rear2->next;
                if(len==0)
                {
                    head3->next=p;
                    p->prior=head3;
                    p->next=NULL;
                }
                else
                {
                    p->prior=head3->next->prior;
                    p->next=head3->next;
                    p->next->prior=p;
                    head3->next=p;
                }
                len++;
            }
            printf("-");
        }
    }
    pre=head3->next;
    while(pre->data==0)//由于算法的问题,结果可能是00001,00002这种形式，所以应该去掉。
    {
        pre=pre->next;
    }
    while(pre)
    {
        printf("%d",pre->data);
        pre=pre->next;
    }
}

void print(linklist head)//把数1，数2输入到屏幕上。
{
    linklist q;
    q=head->prior;
    while(q!=head)
    {
        printf("%d",q->data);
        q=q->prior;
    }
}



