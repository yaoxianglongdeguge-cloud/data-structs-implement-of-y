#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


typedef struct heapnode
{

    struct heapnode* left;
    struct heapnode* right;
    int element;
    int zero;

}heapnode;

heapnode* heap_merge(heapnode* h1,heapnode* h2);

heapnode* heap_merge1(heapnode* h1,heapnode* h2);

heapnode* heap_init(int k)
{
    heapnode* p;
    p=(heapnode*)malloc(sizeof(heapnode));


    p->element=k;
    p->left=NULL;
    p->right=NULL;
    p->zero=0;

    return p;
}

heapnode* heap_merge(heapnode* h1,heapnode* h2)
{
    if(h1==NULL)
    {
        return h2;
    }

    if(h2==NULL)
    {
        return h1;
    }

    if(h1->element<h2->element)
    {
        return heap_merge1(h1,h2);
    }
    else
    {
        return heap_merge1(h2,h1);
    }

}

heapnode* heap_merge1(heapnode* h1,heapnode* h2)
{
    if(h1->left==NULL)
    {
        h1->left=h2;
    }
    else
    {
        h1->right=heap_merge(h1->right,h2);
        if(h1->left->zero<h1->right->zero)
        {
            heapnode* m=h1->right;
            h1->right=h1->left;
            h1->left=m;
        }
        h1->zero=h1->right->zero+1;

    }

    return h1;

}

heapnode* heap_insert(heapnode* h,int k[])
{
    int i=0;
    while(i<9)
    {
        heapnode* m=heap_init(k[i]);
        h=heap_merge(h,m); 
        i++;
    }
    return h;
}


int main()
{
    int k1[10]={3,5,7,2,1,32,14,15,16,17};
    heapnode* p1=heap_init(1);
    p1=heap_insert(p1,k1);

    int k2[10]={31,55,72,3,4,5,9,34,61,17};
    heapnode* p2=heap_init(2);
    p2=heap_insert(p2,k2);

    heapnode* p3=heap_merge(p1,p2);

    return 0;

    
    


}