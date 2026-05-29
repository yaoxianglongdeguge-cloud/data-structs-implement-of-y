#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node
{
    struct node* next;
    int site;
}node;

typedef struct listnode
{
    node* next;
    int num;
    int low;

}listnode;

int min(int a,int b)
{
    if(a>=b)
    {
        return b;
    }
    else
    {
        return a;
    }
    return 0;
}


listnode* init(int a)
{
    listnode* p=(listnode*)malloc((a+1)*sizeof(listnode));

    p[0].num=a;
    p[0].low=0;
    p[0].next=NULL;
    for(int i=1;i<=a;i++)
    {
        p[i].num=0;
        p[i].low=0;
        p[i].next=NULL;
    }
    
    return p;
    
}

void insert(listnode* p,int a,int b)
{
    node* m=p[a].next;
    node* o=p[b].next;
    
    if(p[a].next==NULL)
    {
        node* l=(node*)malloc(sizeof(node));
        l->next=NULL;
        l->site=b;
        p[a].next=l;
    }
    
    
    
    
    if(p[b].next==NULL)
    {
        node* l=(node*)malloc(sizeof(node));
        l->next=NULL;
        l->site=a;
        p[b].next=l;
    }


    if(o!=NULL)
    {

        while(o->next!=NULL)
        {
            if(o->site==a)
            {
                return;
            }
            o=o->next;
        }
    }
    
    if(m!=NULL)
    {   
        while(m->next!=NULL)
        {
            if(m->site==b)
            {
                return;
            }
            m=m->next;
        }
        
    }

    if(m!=NULL)
    {
        node* l=(node*)malloc(sizeof(node));
        l->next=NULL;
        l->site=b;
        m->next=l;
    }

     if(o!=NULL)
    {
        node* l=(node*)malloc(sizeof(node));
        l->next=NULL;
        l->site=a;
        o->next=l;
    }

}

void findart(listnode*p,int a,int* counter,bool visit[],int parent[])
{
    (*counter)++;

    p[a].num=*counter;
    visit[a]=true;
    p[a].low=p[a].num;

    node* m=p[a].next;

    while(m!=NULL)
    {

        if(visit[m->site]!=true)
        {
            parent[m->site]=a;
            findart(p,m->site,counter,visit,parent);
            p[a].low=min(p[m->site].low,p[a].low);
        }

        else
        {
            if(parent[a]!=m->site)
            {
                p[a].low=min(p[a].low,p[m->site].num);
            }
        }

        m=m->next;

    }



}//num和low的标识顺序恰好相反，因此这两个进程可以合并起来，当展开的时候就是num，收回就是low，
 //因此当num的终止，也就是孩子为null或者追溯到祖先的时候，low就开始标识工作
 //两个进程刚好一去一回，因此可以嵌合在一个例程.或者说它们都需要先展开到一个点结束.

 


int main()
{
    listnode* p=init(7);
    insert(p,1,2);
     insert(p,1,4);
      insert(p,3,2);
       insert(p,4,3);
        insert(p,4,5);
         insert(p,4,6);
         insert(p,3,7);
          insert(p,1,4);


bool visit[8];
int i=0;
while(i<=7)
{
    visit[i]=false;
    i++;
}
int parent[8];
i=0;
while(i<=7)
{
    parent[i]=0;
    i++;
}
int counter=0;

findart(p,2,&counter,visit,parent);
         return 0;

}












