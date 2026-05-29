/*首先需要明确几点，
1.
一个结点到另一个节点的路径只有一条。比如m到p，p的父节点到p只有一条路径，以此类推到m只有一条路径到p。

如果插入节点涂成黑色，那假设插到p上，原本经由p到NULL的路径，有一条多了黑节点，其他的不变，因此不行。当然如果全面
调整树的结构和颜色或许可以（我不确定），但那样太大动干戈了。

*/

/*
证明红黑树向下过程，红黑树性质成立。
首先，向下的路径是通过比较关键字。
向下过程，遇到两种情况会进行操作，一个是p结点的两个儿子都是红色的，反转颜色，二是，反转导致的连续红色，进行旋转。至于有没有其他的情况，我们再看。
一开始我们有一棵红黑树，符合性质，之后开始向下，遇到p结点，两个儿子是红色，那么反转颜色。
如果p的父节点是黑色，那么对于性质三，p和他的父节点不冲突，p和儿子不冲突，儿子都是黑色，那和孙子也不冲突，
那么性质三成立，性质四，任意结点到p的父节点的路径黑数没变，之后到p两个儿子的黑数没变，那么再延伸也不变
因此成立。
如果父结点是红色的，性质三不成立，由于叔结点必然不是红色的，否则第一次颜色反转应该是p的祖父节点，因此，对p的父节点和p的祖父节点进行旋转
旋转涉及的点有p，p的父节点，p的叔节点，p的祖父结点，旋转之后。
首先性质三，p结点及其子树本身没有冲突，也没有改变颜色，因此内部依旧没有冲突，p的兄弟，p的叔，p的祖父的兄弟，父节点均如此。
剩下的就是p的父节点和p的祖父节点，最后改变后，没有冲突。

对于性质四，首先到p祖父节点处的黑数旋转后依然没变，其次，路径出路必然要经过p的两个孩子，p的兄弟，p的叔，而这些节点内部没有改变，因此看的
仅仅是从祖父位置（除了自身）到那几个结点（除了他们自身）经过的路径上黑数改变，没变，因此成立。

*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


// 1 red  0 black

typedef struct redblacktreenode
{
    int elem;
    struct redblacktreenode* left;
    struct redblacktreenode* right;
    int color;
}rbnode;

static rbnode* x;//本节点
static rbnode* p;//父节点
static rbnode* gp;//祖父节点
static rbnode* ggp;//曾祖节点

typedef rbnode* rbtree;

void leftonerotate(rbnode* x)
{
    rbnode* r=p->right;
    p->right=gp;
    gp->left=r;
    
    p->color=0;
    gp->color=1;

    if(x->elem>ggp->elem)//要确定旋转后祖父位置连在曾祖哪里
    {
        ggp->right=p;
    }
    else
    {
        ggp->left=p;
    }
    
}

void rightonerotate(rbnode* x)
{
    rbnode* r=p->left;
    p->left=gp;
    gp->right=r;
    
    p->color=0;
    gp->color=1;
    

    if(x->elem>ggp->elem)//要确定旋转后祖父位置连在曾祖哪里
    {
        ggp->right=p;
    }
    else
    {
        ggp->left=p;
    }
    
}

void lefttworotate(rbnode* x)
{
    
        p->right=x->left;
        gp->left=x->right;
        x->right=gp;
        x->left=p;

        x->color=0;
        p->color=1;
        gp->color=1;
    if(x->elem>ggp->elem)
    {
      ggp->right=x;
    }
    else
    {
        ggp->left=x;
    }
}

void righttworotate(rbnode* x)
{
    
        p->left=x->right;
        gp->right=x->left;
        x->right=p;
        x->left=gp;

        x->color=0;
        p->color=1;
        gp->color=1;
    if(x->elem>ggp->elem)
    {
      ggp->right=x;
    }
    else
    {
        ggp->left=x;
    }
}



rbnode* init(int elem,int color)
{
    rbnode* r=(rbnode*)malloc(sizeof(rbnode));
    if(r==NULL)
    {
        return NULL;
    }
    r->left=NULL;
    r->right=NULL;
    r->color=color;
    r->elem=elem;

    return r;
}

void rbdown(rbtree t)
{
    x->color=1;
    if(x->right!=NULL&&x->left!=NULL)
    {
        x->right->color=0;
        x->left->color=0;
    }

    if(p->color==1)
    {
        if(p->elem<gp->elem)
        {
            if(x->elem<p->elem)
            {
                leftonerotate(x);
                gp=ggp;//把四辈节点的顺序顺下去
            }
            else
            {
                lefttworotate(x);
                gp=ggp;
                p=x;
            }
        }
        else
        {
            if(x->elem>p->elem)
            {
                rightonerotate(x);
                gp=ggp;
            }
            if(x->elem<p->elem)
            {
                righttworotate(x);
                gp=ggp;
                p=x;
            }
        }
    }

    t->right->color=0;//t为一个哨兵节点，这样就防止了当遇到需要颜色反转的时候，ggp和gp重合的问题。
}

rbtree insert(rbtree t,int item)
{
    ggp=t; gp=t; p=t; x=t;

    while(x!=NULL)
    {
        ggp=gp; gp=p; p=x;//顺序不能乱

        if(item==x->elem)
        {
            return t;
        }
        else if(item>x->elem)
        {
            x=x->right;
        }
        else
        {
            x=x->left;
        }

        if(x==NULL)
        {
            break;
        }
        
        if(x->right!=NULL&&x->left!=NULL)
        {
            if(x->right->color==1&&x->left->color==1)
            {
                rbdown(t);
            }
        }
    }

    x=init(item,1);

    if(item>p->elem)
    {
        p->right=x;
    }
    else
    {
        p->left=x;
    }

    rbdown(t);

    return t;

}

int main()
{
    rbtree t=init(-10000000,0);
    t->right=init(4,0);

    insert(t,23);
    insert(t,3);
    insert(t,5);
    insert(t,5);
    insert(t,53);
    insert(t,43);
    insert(t,235);
    insert(t,123);
    insert(t,1);
    insert(t,0);
    insert(t,9123);
    insert(t,24);
    insert(t,6);
    insert(t,77);
    insert(t,51);
    insert(t,533);
    insert(t,45);
    insert(t,95);
    insert(t,1232);
    insert(t,11);
    insert(t,10);
    insert(t,86);


    return 0;

}











