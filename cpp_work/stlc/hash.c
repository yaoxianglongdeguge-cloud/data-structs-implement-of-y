#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//0 没来过，1 来过但能修改，2 来过且不能修改

int primes[10]={7,17,37,79,163,331,673,1361,2729,5471};

typedef struct hashcell
{

    int element;
    int last;

}cell;

typedef struct hashmap
{

    int tablesize;
    cell* cells; 
    float number;

}hashmap;

hashmap* hash_init(int tablesize);

int cell_pos(int key,int tsize);

cell* hash_find(int key,hashmap* h);

bool hash_insert(int key,hashmap* h);

bool hash_expand(hashmap* h);

bool hash_delete(int key,hashmap* h);

bool hash_shrink(hashmap* h);


hashmap* hash_init(int tablesize)
{
    if(tablesize<=0)
    {
        return NULL;
    }
    hashmap* h;
    h=(hashmap*)malloc(sizeof(hashmap));

    if(h==NULL)
    {
        return NULL;
    }

    h->tablesize=tablesize;
    h->number=0;

    h->cells=(cell*)malloc(sizeof(cell)*tablesize);

    for(int i=0;i<tablesize;i++)
    {
        h->cells[i].element=0;
        h->cells[i].last=0;
    }

    return h;
}

int cell_pos(int key,int tsize)
{
    return key%tsize;
}

cell* hash_find(int key,hashmap* h)
{
    if(h->number/h->tablesize>0.5)
    {
        hash_expand(h);
    }
    cell* p;
    int i=cell_pos(key,h->tablesize);
    p=&(h->cells[i]);
    int s=1;
    

    while(p->last!=0)
    {
        if(p->element==key)
        {
            if(p->last==2)
            {
                return p;
            }
            else if(p->last)
            {
                p=&(h->cells[(i+s*s)/h->tablesize]);
                s=s+1;
            }
        }
        else if(p->element!=key)
        {
            if(p->last==1||p->last==2)
            {
                p=&(h->cells[(i+s*s)/h->tablesize]);
                s=s+1;
            }
            else if(p->last==0)
            {
                return NULL;
            }
        }
    }

    return NULL;
}

 bool hash_insert(int key,hashmap* h)
 {
    if(h->cells==NULL||h->tablesize==0)
    {
        return false;
    }

    cell* p=hash_find(key,h);

    if(p==NULL)
    {
        int i=cell_pos(key,h->tablesize);
        int s=0;
        p=&(h->cells[i]);
        while(p->last!=0&&p->last!=1)
        {
            p=&(h->cells[((s+1)*(s+1)+i)/h->tablesize]);
            s=s+1;
        }
        p->element=key;
        p->last=2;
        h->number=h->number+1;
        return true;
    }

    return false;
 }

 bool hash_expand(hashmap* h)
 {
    if(h->cells==NULL||h->tablesize==0)
    {
        return false;
    }

    int sizem=h->tablesize;
    int count=0;
    while(count<=9&&sizem!=primes[count])
    {
        count++;
    }
    if(sizem==primes[count]&&count!=9)
    {
        sizem=primes[count+1];
    }
    else
    {
        return false;
    }
    
    hashmap* k=hash_init(sizem);

    int i=0;
    int j=0;
    while(i<h->tablesize)
    {
        if(h->cells[i].last==2)
        {
            hash_insert(h->cells[i].element,k);
        }
        i++;
    }
   
    free(h->cells);
    h->cells=k->cells;
    h->number=k->number;
    h->tablesize=k->tablesize;
    free(k);
   

    return true;


 }

 bool hash_delete(int key,hashmap* h)
 {
    if(h==NULL||h->tablesize==0)
    {
        return false;
    }

    if(h->number/h->tablesize<0.25)
    {
        hash_shrink(h);
    }

    cell* p=hash_find(key,h);

    if(p==NULL)
    {
        return true;
    }
    else
    {
        p->last=1;
        h->number--;
        return true;
    }
    return false;
 }
 
 bool hash_shrink(hashmap* h)
 {

    int sizem=0;
    int i=0;
    while(i<=9&&primes[i]!=h->tablesize)
    {
        i++;
    }

    if(primes[i]!=h->tablesize)
    {
        return false;
    }
    else
    {
        if(i==0)
        {
            return false;
        }
        else
        {
            sizem=primes[i-1];
        }

    }

    hashmap* p=hash_init(sizem);

    i=0;
    while(i<h->tablesize)
    {
        if(h->cells[i].last==2)
        {
            hash_insert(h->cells[i].element,p);
        }
        i++;
    }
    free(h->cells);
    h->cells=p->cells;
    h->number=p->number;
    h->tablesize=p->tablesize;
    free(p);

    return true;
 }



int main()
{
    hashmap* h;
    h=hash_init(7);

    hash_insert(313,h);
    hash_insert(323,h);
    hash_insert(3,h);
    hash_insert(2,h);
    hash_insert(1,h);
    hash_insert(7,h);
    hash_insert(49,h);
    hash_insert(81,h);
    hash_insert(3243,h);
    hash_insert(56,h);

    hash_delete(323,h);
    hash_delete(49,h);
    hash_delete(7,h);
    hash_delete(81,h);
    hash_delete(3243,h);
    hash_delete(90,h);
    hash_delete(1,h);
    hash_delete(2,h);
    hash_delete(3,h);

    return 0;


}





































/*
#define minsize 5

typedef struct listnode
{
    
int element;
listnode* next;

}listnode;

typedef struct hashmap
{
    
int tablesize;
listnode** thelist;

}hashmap;


hashmap* hash_init(int tablesize)
{
    
hashmap* h;
int i;
if(tablesize<minsize)
{
    return NULL;
}
    h=(hashmap*)malloc(sizeof(hashmap));
    h->tablesize=tablesize;
    
    if(h==NULL)
    {
        return NULL;
    }
    
    h->thelist=(listnode**)malloc(tablesize*sizeof(listnode*));
    
    if(h->thelist==NULL)
    {
        return NULL;
    }
    
    for(int i=0;i<tablesize;i++)
    {
        h->thelist[i]=(listnode*)malloc(sizeof(listnode));
        
        if(h->thelist[i]==NULL)
        {
            return NULL;
        }
        else
        {
            h->thelist[i]->next=NULL;
        }
    }
    return h;
    
}

hashmap* hash_find(int key,hashmap* h)
{
    listnode* p;
    listnode* l;
    l=h->thelist[hash(key,h->tablesize)];
    p=l->next;
    while(p!=NULL&&p->element!=key)
    {
        p=p->next;
    }
    return p;
}



*/
















