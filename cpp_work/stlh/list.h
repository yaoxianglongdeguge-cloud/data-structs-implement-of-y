#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


typedef struct Node
{
int data;
struct Node* pre;
struct Node* next;
}Node;

typedef struct List
{
Node* head;
Node* tail;
int size;
}List;

//函数声明
Node* lis_makenode(int d);

bool lis_freenode(Node* p); 

bool lis_init(List* L);

bool lis_freelist(List* L);

bool lis_clear(List* L);

Node* lis_locate(List* L, int i);

Node* lis_locpre(List* L, int i);

Node* lis_locnext(List* L, int i);

Node* lis_lochead(List* L);

Node* lis_loctail(List* L);

int lis_size(List* L);    

int lis_get(List* L, int i);

bool lis_insertend(List* L, int d);

bool lis_insert(List* L, int i, int d);

Node* lis_delete(List* L, int i);

bool lis_deleteend(List* L);

bool lis_change(List* L, int i, int e);

void lis_null(List* L);



//函数定义
//生成结点
Node* lis_makenode(int d)
{
Node*p=(Node*)malloc(sizeof(Node));
p->data=d;
p->pre=NULL;
p->next=NULL;
return p;
}

//回收结点
bool lis_freenode(Node* p)
{
    if(p!=NULL)
    {
        free(p);
        p=NULL;
        return 1;
    }
    return 0;
}

//初始化链表指针
void lis_null(List* L)
{
    L->head=NULL;
    L->tail=NULL;
    L->size=0;
}

//创建链表
bool lis_init(List* L)
{
if((L->head==NULL)&&(L->tail==NULL))
{
    L->head=(Node *)malloc(sizeof(Node));
    L->tail=(Node *)malloc(sizeof(Node));
    L->head->pre=L->tail;
    L->head->next=NULL;
    L->tail->next=L->head;
    L->tail->pre=NULL;
    L->size=0;
    return 1;
}
return 0;

}

//回收链表
bool lis_freelist(List* L)
{

    if(L->head!=NULL)
    {
        int i=0;
        Node* p=L->head->next;
        int m=lis_size(L);
        while(i<=m)
        {

            free(L->head);
            L->head=p;
            p=p->next;
            i++;
        }
        free(L->tail);
        L->tail=NULL;
        return 1;
    }
}

//清空链表
bool lis_clear(List* L)
{
    if(L->head!=NULL)
    {
    int m=lis_size(L);
    int i=1;
    while(i<=m)
    {
        lis_deleteend(L);
        i++;
    }
    return 1;
    }
    return 0;

}

//i位置结点
Node* lis_locate(List* L,int i)
{
    Node* p = NULL;
    int j=1;
    p=L->head;
    while(j<=i)
    {
        p=p->next;
        j++;
    }
    return p;
}

//i位置前结点
Node* lis_locpre(List* L,int i)
{
    Node* p=NULL;
    if(L->head!=NULL&&i>1&&i<=L->size)
    {
        p=lis_locate(L,i-1);
    }
    return p;
}

//i位置后结点
Node* lis_locnext(List* L,int i)
{
    Node* p=NULL;
    if(L->head!=NULL&&i>=1&&i<L->size)
    {
        p=lis_locate(L,i+1);
    }
    return p;
}

//头结点
Node* lis_lochead(List* L)
{
    return L->head;
}

//尾结点
Node* lis_loctail(List* L)
{
    return L->tail;
}

//链表长度
int lis_size(List* L)
{
    return L->size;
}

//i位置结点数据
int lis_get(List* L,int i)
{
    int m=0;
    m=lis_locate(L,i)->data;
    return m;
}

//链表i位置插入
bool lis_insert(List* L,int i,int d)
{
    if(L->head!=NULL&&i<=L->size&&i>0)
    {
        Node* m=lis_makenode(d);
        Node* p1=lis_locate(L,i-1);
        Node* p2=p1->next;
        p1->next=m;
        m->pre=p1;
        m->next=p2;
        p2->pre=m;
        L->size++;
        return 1;
        
    }
    return 0;
}

//尾端插入
bool lis_insertend(List* L,int d)
{
    if(L->head!=NULL)
    {
    if(L->tail->pre==NULL&&L->head->next==NULL)
    {
        Node* p=lis_makenode(d);
        p->next=L->tail;
        p->pre=L->head;
        L->tail->pre=p;
        L->head->next=p;
        L->size++;
    }
    else
    {
        Node* p = lis_makenode(d);
        Node* m=L->tail->pre;
        p->next=L->tail;
        L->tail->pre=p;
        p->pre=m;
        m->next=p;
        L->size++;

    }
    return 1;
    }
    return 0;
}

//删除i处结点
Node* lis_delete(List* L,int i)
{
    Node* p3=NULL;
    if(L->head!=NULL&&i>0&&i<=L->size)
    {
        Node* p1=lis_locate(L,i-1);
        Node* p2=p1->next->next;
        lis_freenode(p1->next);
        p1->next=NULL;
        p1->next=p2;
        p2->pre=p1;
        L->size--;
        p3=p2;
        
    }
   return p3;
}

//尾端删除
bool lis_deleteend(List* L)
{
    if(L->tail!=NULL&&L->size>0)
    {
        Node* p=L->tail->pre->pre;
        lis_freenode(L->tail->pre);
        p->next=L->tail;
        L->tail->pre=p;
        L->size--;
        return 1;
    }
    return 0;
}

//改变i位置元素数据
bool lis_change(List* L,int i,int e)
{
    if(L->head!=NULL)
    {
        Node* p=lis_locate(L,i);
        p->data=e;
        return 1;
    }
    return 0;
}

//小到大顺序合并链表
void lis_merge(List* La,List* Lb,List* Lc)
{

    Node* pa=La->head->next;
    Node* pb=Lb->head->next;
    if(La->head!=NULL&&Lb!=NULL)
    {
        while((pa!=La->tail)&&(pb!=Lb->tail))
        {
            if(pa->data>pb->data)
        {
            lis_insertend(Lc,pb->data);
            pb=pb->next;
        }
        else if(pa->data<pb->data)
        {
            lis_insertend(Lc,pa->data);
            pa=pa->next;
        }
        else
        {
            lis_insertend(Lc,pa->data);
            pa=pa->next;
            pb=pb->next;
        }
        }
    
        if(pa!=La->tail)
        {
            while(pa->next!=La->tail)
            {
                lis_insertend(Lc,pa->data);
                pa=pa->next;
            }
        }
         if(pb!=Lb->tail)
        {
            while(pb!=Lb->tail)
            {
                lis_insertend(Lc,pb->data);
                pb=pb->next;
            }
        }
    
   
    }
   
}

