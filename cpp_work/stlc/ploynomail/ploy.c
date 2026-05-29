
#include"list.h"

typedef struct polynomial
{
struct terms* head;
struct terms* tail;
int max;
int length;
}poly;

typedef struct terms
{
int expn;
float coef;
struct terms* next;
}terms;

bool poly_null(poly* p)
{
    p->head=NULL;
    p->tail=NULL;
    p->max=0;
    p->length=0;
    return 1;
}

bool poly_init(poly* p,int n,terms t[])
{
    if(p->head==NULL)
    {
        p->head=(terms*)malloc(sizeof(terms));
        p->tail=(terms*)malloc(sizeof(terms));
        p->head->next=NULL;
        int i=0;
        terms* o;
        o=p->head;
        while(i<n)
        {
            terms* k=(terms*)malloc(sizeof(terms));
            k->coef=t[i].coef;
            k->expn=t[i].expn;
            k->next=p->tail;
            o->next=k;
            o=o->next;
            p->length++;
            i++;
        }
        p->max=t[0].expn;
        return 1;
    }
    return 0;
}

int poly_length(poly* p)
{
    return p->length;
}

int poly_max(poly* p)
{
    return p->max;
}

bool poly_print(poly* p)
{
    if(p->head!=NULL&&p->length!=0)
    {
        int i=0;
        terms* o=p->head->next;
        while(i<p->length)
        {
            printf("(%d,%d)",o->expn,o->coef);
            o=o->next;
            i++;
        }
    }
    return 0;
}

poly poly_add(poly* p1,poly* p2)
{
    poly p3;
    poly_null(&p3);
    int k=p1->length+p2->length;

    terms t[k];

    terms* o1=p1->head->next;
    terms* o2=p2->head->next;
    int i=0;
    while(o1!=p1->tail&&o2!=p2->tail)
    {
        if(o1->expn>o2->expn)
        {
            t[i].expn=o1->expn;
            t[i].coef=o1->coef;
            o1=o1->next;
            i++;
        }
        else if(o1->expn<o2->expn)
        {
            t[i].expn=o2->expn;
            t[i].coef=o2->coef;
            o2=o2->next;
            i++;
        }
        else
        {
            if(o1->coef+o2->coef!=0)
            {
                t[i].expn=o1->expn;
                t[i].coef=o1->coef+o2->coef;
                o1=o1->next;
                o2=o2->next;
                i++;
            }
            else
            {
                o1=o1->next;
                o2=o2->next;
            }
        }
    }

    if(o1!=p1->tail)
    {
        while(o1!=p1->tail)
        {
            t[i].expn=o1->expn;
            t[i].coef=o1->coef;
            o1=o1->next;
            i++;
        }
    }
    else if(o2!=p2->tail)
    {
        t[i].expn=o2->expn;
        t[i].coef=o2->coef;
        o2=o2->next;
        i++;
    }
    poly_init(&p3,i,t);

    return p3;
}

poly poly_substract(poly* p1,poly* p2)
{
    poly p3;
    poly_null(&p3);
    int k=0;
    if(p1->max>=p2->max)
    {
      k=p1->max+2;
    }
    else
    {
      k=p2->max+2;
    }
      terms t[k];

    terms* o1=p1->head->next;
    terms* o2=p2->head->next;
    int i=0;
    while(o1!=p1->tail&&o2!=p2->tail)
    {
        if(o1->expn>o2->expn)
        {
            t[i].expn=o1->expn;
            t[i].coef=o1->coef;
            o1=o1->next;
            i++;
        }
        else if(o1->expn<o2->expn)
        {
            t[i].expn=o2->expn;
            t[i].coef=0-o2->coef;
            o2=o2->next;
            i++;
        }
        else
        {
            if(o1->coef-o2->coef!=0)
            {
                t[i].expn=o1->expn;
                t[i].coef=o1->coef-o2->coef;
                o1=o1->next;
                o2=o2->next;
                i++;
            }
            else
            {
                o1=o1->next;
                o2=o2->next;
            }
        }
    }

    if(o1!=p1->tail)
    {
        while(o1!=p1->tail)
        {
            t[i].expn=o1->expn;
            t[i].coef=o1->coef;
            o1=o1->next;
            i++;
        }
    }
    else if(o2!=p2->tail)
    {
        t[i].expn=o2->expn;
        t[i].coef=0-o2->coef;
        o2=o2->next;
        i++;
    }
    poly_init(&p3,i+1,t);

    return p3;
}
    
poly poly_terms_mutiply(terms* t1,terms* t2)
{
    terms t[1];
    poly p;
    poly_null(&p);
    t[0].expn=t1->expn+t2->expn;
    t[0].coef=t1->coef*t2->coef;
    poly_init(&p,1,t);
    return p;
}

poly poly_mutiply(poly* p1,poly* p2)
{
    poly p3;
    poly_null(&p3);
    terms u[1];
    u[0].expn=0;
    u[0].coef=0;
    poly_init(&p3,1,u);
    poly p4;
    poly_null(&p4);
    terms* o1=p1->head->next;
    while(o1!=p1->tail)
    {
        terms* o2=p2->head->next;
        while(o2!=p2->tail)
        {
            p4=poly_terms_mutiply(o1,o2);
            poly p5=poly_add(&p3,&p4);
            p3=p5;
            o2=o2->next;
        }
            o1=o1->next;
    }
    return p3;
}




int main()
{
    terms t1[5];
    t1[0].expn=8;
    t1[0].coef=3.4;

    t1[1].expn=7;
    t1[1].coef=2.4;

    t1[2].expn=4;
    t1[2].coef=2.4;

    t1[3].expn=3;
    t1[3].coef=1.2;

    t1[4].expn=0;
    t1[4].coef=7;


    terms t2[4];
    t2[0].expn=6;
    t2[0].coef=3.4;

    t2[1].expn=4;
    t2[1].coef=2.4;

    t2[2].expn=2;
    t2[2].coef=1;

    t2[3].expn=0;
    t2[3].coef=1.2;

    poly p1;
    poly_null(&p1);
    poly_init(&p1,5,t1);
    poly_print(&p1);

    poly p2;
    poly_null(&p2);
    poly_init(&p2,4,t2);
    poly_print(&p2);

    poly p3=poly_add(&p1,&p2);
    poly p4=poly_substract(&p1,&p2);
    poly p5=poly_mutiply(&p1,&p2);






    return 0;
}

















