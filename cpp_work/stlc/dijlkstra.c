#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node
{
    struct node* next;
    int weigh;
    int site;
}node;

typedef struct listnode
{
    node* next;
    bool known;
    int dist;
    int path;

}listnode;

listnode* init(int a)
{
    listnode* arr=(listnode*)malloc(sizeof(listnode)*a+1);
    arr->known=false;
    arr->next=NULL;
    for(int i=0;i<=a;i++)
    {
        arr[i].dist=100000000;
    }
    arr->path=0;
    arr[0].dist=a;

    return arr;
}

void insert(listnode* l,int a,int b,int w)
{
    node* n=l[a].next;
    if(n==NULL)
    {
      n=(node*)malloc(sizeof(node));
      n->site=b;
      n->next=NULL;
      n->weigh=w;
      l[a].next=n;

      return;
    }
    while(n->next!=NULL)
    {
        n=n->next;
    }
    n->next=(node*)malloc(sizeof(node));
    n->next->site=b;
    n->next->next=NULL;
    n->next->weigh=w;
}


void diljkstra(listnode* l,int a)
{
    l[a].dist=0;
    l[a].known=true;
    l[a].path=a;
    int vet=a;
    node* n=l[a].next;

    while(true)
    {
        n=l[vet].next;
        while(n!=NULL)
        {
            int m=n->site;
            if(l[m].dist>l[vet].dist+n->weigh)
            {
                l[m].dist=l[vet].dist+n->weigh;
                l[m].path=vet;
            } 
            n=n->next;
            
        }
        int count=1000;
        int m=vet;
        
        for(int i=1;i<=l[0].dist;i++)
        {
            if(l[i].known==0&&l[i].dist<count)
            {
                count=l[i].dist;
                vet=i;
            }
        }
        if(m==vet)
        {
            break;
        }
        l[vet].known=true;

    }
    }
    
    int main()
{
    listnode* l=init(7);
    insert(l,1,2,2);
    insert(l,1,4,1);
    insert(l,2,4,3);
    insert(l,2,5,10);
    insert(l,3,1,4);
    insert(l,3,6,5);
    insert(l,4,3,2);
    insert(l,4,5,2);
    insert(l,4,6,8);
    insert(l,4,7,4);
    insert(l,5,7,6);
    insert(l,7,6,1);

    diljkstra(l,1);


    return 0;



}















