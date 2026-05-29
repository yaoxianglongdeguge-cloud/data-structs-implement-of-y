#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


typedef struct binonode
{
    int element;
    struct binonode* left;
    struct binonode* next;

}binonode;

typedef struct binoarr
{
    int currentsize;
    binonode** arr;
}binoarr;

binoarr* arr_init()
{
    binoarr* p;
    p=(binoarr*)malloc(sizeof(binoarr));

    p->arr=(binonode**)malloc(sizeof(binonode*)*11);
    int i=0;
    while(i<11)
    {
        p->arr[i]=NULL;
        i++;
    }
    p->currentsize=0;

    return p;
}

binonode* node_init(int e)
{
    
    binonode* o=NULL;
    o=(binonode*)malloc(sizeof(binonode));
    o->element=e;
    o->left=NULL;
    o->next=NULL;
    return o;
}

bool bino_merge(binoarr* a1,binoarr*a2)
{
    if(a1==NULL||a2==NULL)
    {
        return false;
    }
    int i=0;
    binonode* carry=NULL;

    while(i<11)
    {
        if(a1->arr[i]==NULL)
        {
            if(a2->arr[i]==NULL)
            {
                if(carry!=NULL)
                {
                    a1->arr[i]=carry;
                    carry=NULL;
                }
            }
            else
            {
                if(carry==NULL)
                {
                    a1->arr[i]=a2->arr[i];
                    a2->arr[i]=NULL;
                }
                else
                {
                    if(a2->arr[i]->element>carry->element)
                    {
                        a2->arr[i]->next=carry->left;
                        carry->left=a2->arr[i];
                        a2->arr[i]=NULL;
                    }
                    else
                    {
                        carry->next=a2->arr[i]->left;
                        a2->arr[i]->left=carry;
                        carry=a2->arr[i];
                        a2->arr[i]=NULL;
                    }
                }
            }
        }
        else
        {
            if(a2->arr[i]==NULL)
            {
                if(carry!=NULL)
                {
                    if(a1->arr[i]->element>carry->element)
                    {
                        a1->arr[i]->next=carry->left;
                        carry->left=a1->arr[i];
                        a1->arr[i]=carry;
                        carry=a1->arr[i];
                        a1->arr[i]=NULL;
                        
                    }
                    else
                    {
                        carry->next=a1->arr[i]->left;
                        a1->arr[i]->left=carry;
                        carry=a1->arr[i];
                        a1->arr[i]=NULL;
                        
                    }
                }
            }
            else
            {
                if(carry==NULL)
                {
                    if(a1->arr[i]->element>a2->arr[i]->element)
                    {
                        carry=a2->arr[i];
                        a1->arr[i]->next=a2->arr[i]->left;
                        a2->arr[i]->left=a1->arr[i];
                        a1->arr[i]=NULL;
                        a2->arr[i]=NULL;
                    }
                    else
                    {
                        carry=a1->arr[i];
                        a2->arr[i]->next=a1->arr[i]->left;
                        a1->arr[i]->left=a2->arr[i];
                        a2->arr[i]=NULL;
                        a1->arr[i]=NULL;
                    }
                }
                else
                {
                    binonode* o=carry;
                    if(a1->arr[i]->element>a2->arr[i]->element)
                    {
                        carry=a2->arr[i];
                        a1->arr[i]->next=a2->arr[i]->left;
                        a2->arr[i]->left=a1->arr[i];
                        a1->arr[i]=o;
                        a2->arr[i]=NULL;
                    }
                    else
                    {
                        carry=a1->arr[i];
                        a2->arr[i]->next=a1->arr[i]->left;
                        a1->arr[i]->left=a2->arr[i];
                        a1->arr[i]=o;
                        a2->arr[i]=NULL;
                    }
                }
            }
        }
        i++;
    }

    a1->currentsize=a1->currentsize+a2->currentsize;
    int j=0;
    int u=0;
    while(j<11)
    {
        if(a2->arr[j]!=NULL)
        {
            u=1;
        }
        j++;
    }
    if(u==0)
    {
        free(a2->arr);
        free(a2);
    }
    else
    {
        return false;
    }
    return true;
}

bool bino_insert(binoarr* a,int e)
{
    binonode* o=node_init(e);
    binoarr* arr=arr_init();
    arr->currentsize=1;
    arr->arr[0]=o;

    bino_merge(a,arr);
    return true;
}




int main()
{

    binoarr* a1=arr_init();
    bino_insert(a1,1);
    bino_insert(a1,13);
    bino_insert(a1,15);
    bino_insert(a1,17);
    bino_insert(a1,2);
    bino_insert(a1,3);
    bino_insert(a1,7);
    bino_insert(a1,32);
    bino_insert(a1,50);

    binoarr* a2=arr_init();
    bino_insert(a2,10);
    bino_insert(a2,13);
    bino_insert(a2,15);
    bino_insert(a2,7);
    bino_insert(a2,5);
    bino_insert(a2,4);
    bino_insert(a2,74);
    bino_insert(a2,132);
    bino_insert(a2,530);
    
    bino_merge(a1,a2);


    return 0;
}












