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
Node* lis_makenode(int d)
{
Node*p=(Node*)malloc(sizeof(Node));
p->data=d;
p->pre=NULL;
p->next=NULL;
return p;
}

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

void lis_null(List* L)
{
    L->head=NULL;
    L->tail=NULL;
    L->size=0;
}

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

Node* lis_locpre(List* L,int i)
{
    Node* p=NULL;
    if(L->head!=NULL&&i>1&&i<=L->size)
    {
        p=lis_locate(L,i-1);
    }
    return p;
}

Node* lis_locnext(List* L,int i)
{
    Node* p=NULL;
    if(L->head!=NULL&&i>=1&&i<L->size)
    {
        p=lis_locate(L,i+1);
    }
    return p;
}

Node* lis_lochead(List* L)
{
    return L->head;
}

Node* lis_loctail(List* L)
{
    return L->tail;
}

int lis_size(List* L)
{
    return L->size;
}

int lis_get(List* L,int i)
{
    int m=0;
    m=lis_locate(L,i)->data;
    return m;
}

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


int main()
{
    /*
    List p;
    lis_null(&p);
    lis_init(&p);
    lis_insertend(&p,1);
    lis_insertend(&p,11);
    lis_insertend(&p,123);
    lis_insertend(&p,41);
    lis_insertend(&p,31);

    lis_insert(&p,2,8);
    lis_change(&p,2,5);
    lis_deleteend(&p);
    lis_insertend(&p,41);
    lis_insertend(&p,31);
    lis_delete(&p,3);
    int m=lis_get(&p,3);

    lis_clear(&p);
    lis_freelist(&p);*/

      List p1;
    lis_null(&p1);
    lis_init(&p1);
    lis_insertend(&p1,1);
    lis_insertend(&p1,11);
    lis_insertend(&p1,43);
    lis_insertend(&p1,122);
    lis_insertend(&p1,2314);

      List p2;
    lis_null(&p2);
    lis_init(&p2);
    lis_insertend(&p2,1);
    lis_insertend(&p2,31);
    lis_insertend(&p2,42);
    lis_insertend(&p2,111);
    lis_insertend(&p2,122);
    lis_insertend(&p2,133);
    lis_insertend(&p2,2314);
    lis_insertend(&p2,12233);
    lis_insertend(&p2,231423);

    List p3;
    lis_null(&p3);
    lis_init(&p3);
    lis_merge(&p1,&p2,&p3);


  



return 0;
}
