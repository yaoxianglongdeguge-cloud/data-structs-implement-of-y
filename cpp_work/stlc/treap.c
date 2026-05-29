#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

static int mleftrotate=0;
static int mrightrotate=0;
static int minsert=0;

static int val[10];

static int count=0;


typedef struct treapnode
{
    int elem;
    int prior;
    struct treapnode* right;
    struct treapnode* left;

}trnode;



trnode* init(int elem)
{
    trnode* t=(trnode*)malloc(sizeof(trnode));
    t->left=NULL;
    t->right=NULL;
    t->prior=val[count];
    count++;
    t->elem=elem;

    return t;

}

trnode* leftrotate(trnode* t)
{
    trnode* tr;
    tr=t->left;
    t->left=tr->right;
    tr->right=t;
    if(t->left!=NULL&&t->prior>t->left->prior)
    {
        tr->right=leftrotate(t);
    }
    mleftrotate++;

    return tr;
}

trnode* rightrotate(trnode* t)
{
    trnode* tr;
    tr=t->right;
    t->right=tr->left;
    tr->left=t;
    if(t->right!=NULL&&t->prior>t->right->prior)
    {
        tr->left=rightrotate(t);
    }
    mrightrotate++;

    return tr;
}


trnode* insert(trnode* t,int elem)
{
    if(t==NULL)
    {
        t=init(elem);
        return t;
    }
    if(t->elem==elem)
    {
        return t;
    }
    else if(t->elem>elem)
    {
        t->left=insert(t->left,elem);
        if(t->prior>t->left->prior)
        {
            t=leftrotate(t);
        }
    }
    else if(t->elem<elem)
    {
        t->right=insert(t->right,elem);
        if(t->prior>t->right->prior)
        {
            t=rightrotate(t);
        }
    }
    minsert++;

    return t;
}

trnode* tr_remove(trnode* t,int elem)
{
    if(elem>t->elem)
    {
        t->right=tr_remove(t->right,elem);
    }
    else if(elem<t->elem)
    {
        t->left=tr_remove(t->left,elem);
    }
    else
    {
        if(t->left==NULL)
        {
            trnode* m=t->right;
            free(t);
            return m;
        }
        else if(t->right==NULL)
        {
            trnode* m=t->left;
            free(t);
            return m;
        }

        if(t->left->prior<t->right->prior)
        {
            t=leftrotate(t);
        }
        else
        {
            t=rightrotate(t);
        }

        t=tr_remove(t,elem);

       
    }

    return t;
}


int main()
{
    val[0]=47634;
    val[1]=51305;
    val[2]=88044;
    val[3]=3347;
    val[4]=3347;
    val[5]=26067;
    val[6]=97804;
    val[7]=97804;
    val[8]=105690;
    val[9]=16062;
    val[10]=1;
    val[11]=47634;
    trnode* t=init(55);
    t=insert(t,4);
    t=insert(t,24);
    t=insert(t,5);
    t=insert(t,90);
    t=insert(t,77);
    t=insert(t,422);
    t=insert(t,4111);
    t=insert(t,44);
    t=insert(t,46);
    t=insert(t,74);
    t=insert(t,4);

    t=tr_remove(t,4);
    t=tr_remove(t,422);
    t=tr_remove(t,90);



    return 0;

}

