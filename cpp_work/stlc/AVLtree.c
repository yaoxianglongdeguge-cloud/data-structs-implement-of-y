#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


int maxs(int a,int b) 
{
    if(a>=b)
    {
        return a;
    }
    else
    {
        return b;
    }
    return 0;
}

typedef struct avlnode
{
 int tdata;
 struct avlnode* left;
 struct avlnode* right;
 int height; 
}avlnode;

int height(avlnode* a)
{
    if(a!=NULL)
    {
        return a->height;
    }
    else
    {
        return 0;
    }
}

void rotateright(avlnode** a)
{ 
    if (*a == NULL || (*a)->left == NULL) return;
        avlnode* p=*a;
        *a=(*a)->left;
        avlnode* o=(*a)->right;
        (*a)->right=p;
        p->left=o;
        p->height=maxs(height(p->left),height(p->right))+1;
        (*a)->height=maxs(height(p),height((*a)->left))+1;
}
void rotateleft(avlnode** a)
{
    if (*a == NULL || (*a)->right  == NULL) return;
    avlnode* p=*a;
    *a=(*a)->right;
    avlnode* o=(*a)->left;
    (*a)->left=p;
    p->right=o;
    p->height=maxs(height(p->left),height(p->right))+1;
    (*a)->height=maxs(height(p),height((*a)->right))+1;
}
void rotateleftright(avlnode** a)
{
    if (a == NULL || *a == NULL || (*a)->left == NULL) return;
    rotateleft(&((*a)->left));
    rotateright(a);
}
void rotaterightleft(avlnode** a)
{
    if (a == NULL || *a == NULL || (*a)->right == NULL) return;
    rotateright(&((*a)->right));
    rotateleft(a);
}

avlnode* avl_insert(avlnode** a,int target)
{
    if(*a==NULL)
    {
        (*a)=(avlnode*)malloc(sizeof(avlnode));
        (*a)->tdata=target;
        (*a)->right=NULL;
        (*a)->left=NULL;
        (*a)->height=1;
    }
    else if(target>(*a)->tdata)
    {
        (*a)->right=avl_insert(&((*a)->right),target);
        if(height((*a)->right)-height((*a)->left)==2)
        {
            if(target>(*a)->right->tdata)
            {
                rotateleft(a);
            }
            else if(target<(*a)->right->tdata)
            {
                rotaterightleft(a);
            }
        }
    }
    else if(target<(*a)->tdata)
    {
    (*a)->left=avl_insert(&((*a)->left),target);
    if(height((*a)->right)-height((*a)->left)==-2)
    {
        if(target<(*a)->left->tdata)
        {
            rotateright(a);
        }
        else if(target>(*a)->left->tdata)
        {
            rotateleftright(a);
        }
    }
        
    }
        
    (*a)->height=maxs(height((*a)->right),height((*a)->left))+1;
     return *a;
}

int main()
{
    avlnode* a;
    a->height=0;
    a->left=NULL;
    a->right=NULL;
    a->tdata=5;

    avl_insert(&a,1);
    avl_insert(&a,14);
    avl_insert(&a,51);
    avl_insert(&a,2);
    avl_insert(&a,3);

    avl_insert(&a,4);
    avl_insert(&a,6);
    avl_insert(&a,8);
    
    avl_insert(&a,19);

    avl_insert(&a,5);
    avl_insert(&a,32);
    

    avl_insert(&a,21);
    avl_insert(&a,22);
    avl_insert(&a,25);
    avl_insert(&a,28);

    avl_insert(&a,30);

    avl_insert(&a,122);
    avl_insert(&a,121);

    avl_insert(&a,40);
    avl_insert(&a,90);

    return 0;
}