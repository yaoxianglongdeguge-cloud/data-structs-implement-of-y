#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


typedef struct splaynode
{
    int element;
    struct splaynode* left;
    struct splaynode* right;
}splaynode;

splaynode* init(int a)
{
    splaynode* p;
    p=(splaynode*)malloc(sizeof(splaynode));
    if(p==NULL)
    {
        return NULL;
    }
    p->element=a;
    p->left=NULL;
    p->right=NULL;
    return p;
}

splaynode* leftrotate(splaynode* x)
{
    splaynode* m=x->right;
    x->right=x->right->left;
    m->left=x;
    return m;
}

splaynode* rightrotate(splaynode* x)
{
    splaynode* m=x->left;
    x->left=x->left->right;
    m->right=x;
    return m;
}


typedef splaynode* splaytree;

splaynode* splay(int item,splaytree h)
{
    splaynode* lefttree=NULL;
    splaynode* righttree=NULL;
    splaynode header1;
    header1.right=NULL;
    lefttree=&header1;
    splaynode header2;
    header2.left=NULL;
    righttree=&header2;

    while(h->element!=item)
    {
        if(item>h->element)
        {
            //要找出item节点或者和item相连的节点，这里开始节点是h
            //之后如果h右节点不存在，那说明item还没插入，而h就是插入点
            //如果存在，那继续向下，如果大于右节点，那最起码右节点应该更近，因此把h摘掉，右节点变成新的h
            //如果此时的h右节点不存在，那此时的h就是连接item节点的节点
            //如果存在，那此时需要进入右节点，并且把h摘掉
            if(h->right==NULL)
            {
                break;
            }
            if(item>h->right->element)
            {
                h=leftrotate(h);
            }
            if(h->right==NULL)
            {
                break;
            }
            //如果执行了右旋，那此时h指向的是最初的h的右节点，此时需要的是h指向自身右节点，并且摘掉h
            //如果没有执行右旋，那h指向的是最初的h，没有break，也没有右旋，说明h->right存在，并且item小于右节点
            //因此此时需要的是h指向自身右节点，并且摘掉h，我们发现，两个诉求是完全相同的。

            lefttree->right=h;     //我们假定把h挂载到lefttree的右子树上左树依然符合结构
            lefttree=h;            //lefttree指向h，之后h会指向自身的右子树，那么在逻辑上，h指向的是一棵中间树

            //而lefttree的右子树完全可以指向中间树的任意一个节点，因为中间树就是lefttree指向的原h的右子树，中间树的任何节点一定比原h小
            //因此上面的假设也成立。
            //之后就是探索原h的右子树。
            h=h->right;

            /*
            我们发现，好像只有单旋转和一字型旋转，没有z字旋转。我们先想如果全是单旋转会怎么样？
            由于单旋转并不改变树的拓扑结构，除非能组成的双旋转比较多，因此对树的平衡度影响很小，也就是说与位势函数的相关性很小，
            那么就会导致c*的界算的更松，也就是说，我们当时算均摊复杂度，用的是双旋转和一次单旋转，因此对这里未必适用，就是说全用单旋转不一定是
            logn界，所以我们避免全用单旋转。

            而这里是单旋转和一字旋转组合，而单旋转有可能下一个操作还是单旋转组合起来是个z字双旋转，也可能下一个操作是一字旋转，也就是说纯孤立的
            单旋转很少，因此可能性能略差，但工程上的优化可以接受。

            */

            

        }
        else
        {
            if(h->left==NULL)
            {
                break;
            }
            if(item>h->left->element)
            {
                h=rightrotate(h);
            }
            if(h->left==NULL)
            {
                break;
            }
            
            righttree->left=h;     
            righttree=h;     
            h=h->left;
            
        }
    }

        //之后装起来
        lefttree->right=h->left;
        righttree->left=h->right;
        h->left=header1.right;
        h->right=header2.left;

        return h;
        //由于左树的节点一定小于中间树的节点一定小于右树的结点，假如item等于h的element自然无所谓
        //但如果大于，那说明最后一步是h->right==NULL,break了，因此此时组装好之后，h->right全都来自于原右树，
        //因此全大于item，并且，h本身和h的左子树都小于item
        //因此如果把h和h的右子树拆开，分别作为新节点的左右子树，那这个新节点就可以使item 

}

splaynode* insert(int item,splaytree h)
{
    if(h==NULL)
    {
        h=init(item);
    }
    else
    {
        h=splay(item,h);
        if(h->element==item)
        {
            return h;
        }
        else
        {
            splaynode* newnode=init(item);

            if(item>h->element)
            {
                newnode->right=h->right;
                newnode->left=h;
                h->right=NULL;
                h=newnode;
            }
            else
            {
                newnode->left=h->left;
                newnode->right=h;
                h->left=NULL;
                h=newnode;
            }
        }

    }

    return h;
}

//delete的思想就是，当找到item时展开，得到根T就是item，然后要删除
//new=T->left,然后splay(item,new)，肯定是找不到的，但由于new里的元素都比item小，
//因此展开后根上是离item最近的元素，也必然是new中最大元素，右子树必然为NULL
//之后连接即可

int main()
{

    splaytree h=NULL;

    h=insert(4,h);
    h=insert(6,h);
    h=insert(8,h);
    h=insert(4,h);
    h=insert(1,h);
    h=insert(42,h);
    h=insert(66,h);
    h=insert(1000,h);
    h=insert(5,h);
    h=insert(65,h);

    return 0;
}




















