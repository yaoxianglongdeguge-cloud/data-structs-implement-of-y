#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


typedef struct treenode
{
    int tdata;
    struct treenode* left;
    struct treenode* right;
}treenode;

bool tree_makeempty(treenode* t)
{
    if(t==NULL)
    {
        return false;
    }
    if(t->left==NULL&&t->right==NULL)
    {
        return false;
    }

    tree_makeempty(t->left);
    tree_makeempty(t->right);
    free(t);
    t->left=NULL;
    t->right=NULL;
    return true;
}

treenode* tree_find(treenode* t,int target)
{
    if(t->tdata==target)
    {
        return t;
    }
    if(t==NULL)
    {
        return NULL;
    }
    
    if(tree_find(t->left,target)!=NULL)
    {
        return tree_find(t->left,target);
    }
    else if(tree_find(t->right,target)!=NULL)
    {
        return tree_find(t->right,target);
    }

    return NULL;
}

treenode* tree_findmin(treenode* t)
{
    if(t==NULL)
    {
        return NULL;
    }
    if(tree_findmin(t->left)==NULL)
    {
        return t;
    }
    else
    {
        return tree_findmin(t->left);
    }
}

treenode* tree_findmax(treenode* t)
{
    if(t==NULL)
    {
        return NULL;
    }
    if(tree_findmax(t->right)==NULL)
    {
        return t;
    }
    else
    {
        return tree_findmax(t->right);
    }
}

treenode* tree_insert(treenode* t,int target)
{
    if(t==NULL)
    {
        treenode* s=(treenode*)malloc(sizeof(treenode));
        s->tdata=target;
        s->left=NULL;
        s->right=NULL;
        return s;
    }
    if(target<t->tdata)
    {
        t->left=tree_insert(t->left,target);
    }
    else if(target>t->tdata)
    {
        t->right=tree_insert(t->right,target);
    }
    return t;
}

treenode* tree_delete(treenode* t,int target)
{
    if(t==NULL)
    {
        return NULL;
    }

    if(target>t->tdata)
    {
        t->right=tree_delete(t->right,target);
    }
    else if(target<t->tdata)
    {
        t->left=tree_delete(t->left,target);
    }
    else
    {
        if(t->left!=NULL&&t->right!=NULL)
        {
            treenode* p=tree_findmin(t->right);
            t->tdata=p->tdata;
            t->right=tree_delete(t->right,p->tdata);
        }
        else if(t->left==NULL&&t->right==NULL)
        {
            free(t);
            return NULL;
        }
        else if(t->left==NULL&&t->right!=NULL)
        {
            treenode* p=t;
            t=t->right;
            free(p);
        }
         else if(t->left!=NULL&&t->right==NULL)
        {
            treenode* p=t;
            t=t->left;
            free(p);
        }
        

        
            
    }


    return t;

}



int main()
{
    treenode node;
    node.tdata=10;
    node.left=NULL;
    node.right=NULL;
    int arr[10]={4,3,6,2,8,23,9,123,1,77};
    int i=0;
    while(i<10)
    {
        tree_insert(&node,arr[i]);
        i++;
    }

    treenode* m1=tree_findmin(&node);
    treenode* m2=tree_findmax(&node);
    tree_delete(&node,9);
    tree_makeempty(&node);
    


    return 0;
}




















