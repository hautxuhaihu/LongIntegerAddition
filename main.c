#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
//���Ա��˫������洢�ṹ
typedef struct lnode
{
    int data;
    struct lnode *prior;
    struct lnode *next;
}Lnode ,* linklist;
//���Ա�ĵ�������洢�ṹ�����ڽ����Ӻͼ�������
typedef struct node
{
    int data;
    struct node *prior;
    struct node *next;
}Node , * LinkList;

int len=0;//����ȫ�ֱ�������¼����������ĳ��ȡ�

void build(linklist head);//������������1����2��������
void plus(linklist head1,linklist head2);//�ӷ�����
void minus(linklist head1,linklist head2);//��������
void print(linklist head);//�ѽ����ӡ����

int main()
{
    char operate;
    linklist head1,head2;
    head1=(linklist)malloc(sizeof(Lnode));
    head1->next=NULL;
    head2=(linklist)malloc(sizeof(Lnode));
    head2->next=NULL;//�����������������ڴ洢����������
    printf("�����һ����:\n");
    build(head1);
    printf("�������������+ or - :\n");
    scanf("%c",&operate);
    if((operate!='+')&&(operate!='-'))//����������ȷ����ȷ
    {
        printf("���������");
    }
    else
    {
        getchar();
        printf("������ڶ�������\n");
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
        minus(head1,head2);//�������
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
        if((temp<'0')||(temp>'9'))//��ASCll������ⳤ�����ǲ��Ǻ��������ַ���
        {
            printf("��������ݺ����޷�ʶ���ַ���");
            exit(0);
        }
        p=(linklist)malloc(sizeof(Lnode));
        p->data=temp-48;
        if(head->data==0)//��Ϊ�洢������������������˫��ѭ��������ӵ�һ�ڵ�ʱ�е����⣻head->data������Žڵ�������
        {
            head->next=p;
            head->prior=p;
            p->prior=head;
            p->next=head;
        }
        else//ͷ�巨����洢��������
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
    int a=0;//a��¼�Ž�λ��
    linklist rear1=head1->next;
    linklist rear2=head2->next;
    LinkList head3,p,pre;
    head3=(LinkList)malloc(sizeof(Node));
    head3->next=NULL;
    pre=head3;
    while((rear1!=head1)&&(rear2!=head2))//��Ϊ��ѭ���������Ա�����ͷ����ǰһ�����ñ����������˴��ǰѽ϶̵���������ꡣ
    {
        p=(LinkList)malloc(sizeof(Node));
        p->data=(rear1->data+rear2->data+a)%10;
        a=(rear1->data+rear2->data+a)/10;//��λ
        rear1=rear1->next;
        rear2=rear2->next;
        if(len==0)//��Ϊhead3������ѭ��������ӵ�һ�����ʱ���⣬��Ϊhead3->next=NULL,���Բ���p->prior=head3->next->prior��
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
    while((head1->data>head2->data)&&(rear1!=head1))//������1������2���������1ʣ�³��ȵ�������浽����3��
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
    while((head2->data>head1->data)&&(rear2!=head2))//������2������1���������2ʣ�³��ȵ�������浽����3��
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
    if(head1->data>head2->data)//������1������2��
    {
        while(rear2!=head2)
        {
            p=(LinkList)malloc(sizeof(Node));
            p->data=rear1->data-rear2->data-a;
            if(p->data<0)//p->data<0�����Ӧ��rear1->dataС��rear2->data.
            {
                p->data=p->data+10;//��ǰ���һλ
                a=1;
            }
            else
            {
                a=0;
            }
            rear1=rear1->next;
            rear2=rear2->next;
            if(len==0)//��Ϊhead3������ѭ��������ӵ�һ�����ʱ���⣬��Ϊhead3->next=NULL,���Բ���p->prior=head3->next->prior��
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
        while(rear1!=head1&&rear2==head2)//������1������2���������1ʣ�³��ȵ�������浽����3��
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

    if(head2->data>head1->data)//��2����1��
    {
        printf("-");//���������
        while(rear1!=head1)
        {
            p=(LinkList)malloc(sizeof(Node));
            p->data=rear2->data-rear1->data-a;
            if(p->data<0)//p->data<0�����Ӧ��rear2->dataС��rear1->data.
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
            if(len==0)//��Ϊhead3������ѭ��������ӵ�һ�����ʱ���⣬��Ϊhead3->next=NULL,���Բ���p->prior=head3->next->prior��
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

    if(head1->data==head2->data)//��ӵ���������һ������
    {
        q1=head1->prior;//��Ϊ��������������洢�����������Ǵ�ͷ������
        q2=head2->prior;
        while(((q1->data)==(q2->data))&&q1!=head1)//������������������������ȫһ����������㡣
        {
            q1=q1->prior;
            q2=q2->prior;
            if(q1==head1)
                printf("0");
        }
        if((q1->data)>(q2->data))//���������1������2
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
        if((q1->data)<(q2->data))//���������1С����2
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
    while(pre->data==0)//�����㷨������,���������00001,00002������ʽ������Ӧ��ȥ����
    {
        pre=pre->next;
    }
    while(pre)
    {
        printf("%d",pre->data);
        pre=pre->next;
    }
}

void print(linklist head)//����1����2���뵽��Ļ�ϡ�
{
    linklist q;
    q=head->prior;
    while(q!=head)
    {
        printf("%d",q->data);
        q=q->prior;
    }
}



