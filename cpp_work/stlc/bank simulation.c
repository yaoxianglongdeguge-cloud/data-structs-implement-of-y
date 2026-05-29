#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct event
{
    int occurtime;
    int kind;
}event;


typedef struct custom
{
    int arrivaltime;
    int duration;
}custom;

typedef struct eventnode
{
    event* eve;
    struct eventnode* next;
}eventnode;


typedef struct eventlist
{
    eventnode* head;
    eventnode* tail;

}eventlist; 

typedef struct cusnode
{
    custom* cus;
    struct cusnode* next;
}cusnode;


typedef struct cuslist
{
    cusnode* head;
    cusnode* tail;

}cuslist; 

cuslist Q[3];


void eve_init(eventlist* e)
{
    e->head=NULL;
    e->tail=NULL;
    e->head=(eventnode*)malloc(sizeof(eventnode));
    e->head->eve=(event*)malloc(sizeof(event));
    e->head->eve->kind=-2;
    e->head->eve->occurtime=-1;
    e->head->next=NULL;
    e->tail=e->head;
  
}

void cus_init(cuslist* e)
{
    e->head=NULL;
    e->tail=NULL;
    e->head=(cusnode*)malloc(sizeof(cusnode));
    e->head->cus=NULL;
    e->head->next=NULL;
    e->tail=e->head;
}

bool cmp(event a,event b)
{
    if(a.occurtime-b.occurtime>0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void eve_insert(eventlist* a,int time,int kind,bool(*cmp)(event,event))
{
    eventnode* o=(eventnode*)malloc(sizeof(eventnode));
    o->eve=(event*)malloc(sizeof(event));
    o->eve->kind=kind;
    o->eve->occurtime=time;
    o->next=NULL;
    eventnode* p=a->head;
    while(p!=NULL)
    {
        if(p->next!=NULL&&cmp(*o->eve,*p->eve)==1&&cmp(*p->next->eve,*o->eve)==1)
        {
            eventnode* m=p->next;
            p->next=o;
            o->next=m;
            break;
        }
        else if(p->next==NULL)
        {
            p->next=o;
            a->tail=o;
            p=NULL;
        }
        else
        {
            p=p->next;
        }

    }
}

void cus_insert(cuslist* a,int time,int duration)
{
    cusnode* o=(cusnode*)malloc(sizeof(cusnode));
    o->cus=(custom*)malloc(sizeof(custom));
    o->cus->duration=duration;
    o->cus->arrivaltime=time;
    cusnode* p=a->tail;
    p->next=o;
    a->tail=o;
}

eventnode eve_delete(eventlist* a)
{
    eventnode q;
    if(a->head->next!=NULL)
    {
        if(a->head->next->next!=NULL)
        {
            eventnode* o=a->head;
            eventnode* p=o->next;
            q=*p;
            o->next=p->next;
            free(p->eve);
            free(p);

        }
        else
        {
           q=*a->tail;
           free(a->tail->eve);
           free(a->tail);
           a->tail=a->head;
           a->head->next=NULL;
        }
        
    }
    return q;

}

cusnode cus_delete(cuslist* a)
{
    cusnode q;
    q.cus=NULL;
    q.next=NULL;
    if(a->head->next!=NULL)
    {
        if(a->head->next->next!=NULL)
        {
            cusnode* o=a->head;
            cusnode* p=o->next;
            q=*p;
            o->next=p->next;
            free(p->cus);
            free(p);
        }
        else
        {
           q=*a->tail;
           free(a->tail->cus);
           free(a->tail);
           a->tail=a->head;
           a->head->next=NULL;
        }
        
    }
    return q;

}

void cus_random(int *duration,int *interval)
{
    *duration=rand()%(15-6+1)+6;
    *interval=rand()%(7-0+1)+0;
}

int shortest(cuslist Q[])
{
    int j;
    int minlen=20000000;
    cusnode* p;
    for(int i=0;i<3;i++)
    {
        p=Q[i].head;
        int count=0;
        while(p!=NULL)
        {
            p=p->next;
            count++;
        }
        if(count<minlen)
        {
            j=i;
            minlen=count;
        }
    }
    return j;
}

void openday(eventlist* ev,int *totaltime,int *cusnum)
{
  totaltime=0;
  cusnum=0;
  eve_init(ev);
  eve_insert(ev,0,-1,cmp);
  for(int i=0;i<3;i++)
  {
   cus_init(&Q[i]);
  }
}

void cusarrival(eventlist* e,event ev)
{
    int duration=0;
    int interval=0;
    int daytime=0;
    custom c;
    cus_random(&duration,&interval);
    daytime=ev.occurtime+interval;
    if(daytime<240)
    {
        eve_insert(e,ev.occurtime+interval,-1,cmp);
    }
    int s=shortest(Q);
    cus_insert(&Q[s],ev.occurtime,duration);
    if(Q[s].head->next==Q[s].tail)
    {
        eve_insert(e,ev.occurtime+duration,s,cmp);
    }

}

void cusleave(eventlist* e,event ev,int* custtime)
{
    int time=ev.occurtime;
    int kind=ev.kind;
    cusnode* p=Q[ev.kind].head->next;
    *custtime=*custtime+time-p->cus->arrivaltime;
    p=p->next;
    cus_delete(&Q[ev.kind]);
    if(p!=NULL)
    {
        eve_insert(e,time+p->cus->duration,kind,cmp);
    }
    

}

int main()
{
    eventlist ev;
    eve_init(&ev);

    int totaltime;
    int cusnum;
    openday(&ev,&totaltime,&cusnum);
    eventnode* p=ev.head->next;

    while(p!=NULL)
    {
        if(ev.head->next!=NULL)
        {
            
            p=ev.head->next;
            if(p->eve->kind==-1)
            {
                event e;
                e.kind=p->eve->kind;
                e.occurtime=p->eve->occurtime;
                eve_delete(&ev);
                cusarrival(&ev,e);
                cusnum++;
            }
        else
        {
            event e;
            e.kind=p->eve->kind;
            e.occurtime=p->eve->occurtime;
            eve_delete(&ev);
            cusleave(&ev,e,&totaltime);
        }
        }
        else
        {
            break;
        }
    }
    
    
    return 0;
    
}






