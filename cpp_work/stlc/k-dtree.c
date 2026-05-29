#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// 1 x 2 y

typedef struct kdnode
{
    int x;
    int y;

    struct kdnode* right;
    struct kdnode* left;

}kdnode;

static int count=0;

typedef kdnode* kdtree;

kdnode* init(int x,int y)
{
    kdnode* k=(kdnode*)malloc(sizeof(kdnode));
    k->left=NULL;
    k->right=NULL;
    k->x=x;
    k->y=y;

    return k;
}

kdnode* insert(kdtree k,int x,int y,int level)
{
    if(k==NULL)
    {
        kdnode* p=init(x,y);

        return p;
    }

    if(k->x==x&&k->y==y)
    {
        return k;
    }

    if(level==1)
    {
        if(x>k->x)
        {
            k->right=insert(k->right,x,y,2);
        }
        else if(x<k->x)
        {
            k->left=insert(k->left,x,y,2);
        }
    }
    else if(level==2)
    {
        if(y>k->y)
        {
            k->right=insert(k->right,x,y,1);
        }
        else if(y<k->y)
        {
            k->left=insert(k->left,x,y,1);
        }
    }

    return k;
}

void printrange(int low[],int high[],kdtree k,int level,kdnode val[])
{
    if(k==NULL)
    {
        return ;
    }
    if(k->x>=low[0]&&k->x<=high[0]&&k->y>=low[1]&&k->y<=high[1])
    {
        val[count]=*k;
        count++;
    }

    if(level==1)
    {
        if(low[0]<=k->x)
        {
            printrange(low,high,k->left,2,val);
        }
        if(high[0]>=k->x)
        {
            printrange(low,high,k->right,2,val);
        }

    }

     if(level==2)
    {
        if(low[1]<=k->y)
        {
            printrange(low,high,k->left,1,val);
        }
        if(high[1]>=k->y)
        {
            printrange(low,high,k->right,1,val);
        }

    }
}
/*虽然每一层并不是同时验证两个元素，但是查找逻辑实际上是遍历的，也就是说，只要发现左子树
有可能存在，就一定会去看看，右子树同理。但是，还要经过x或y的判断，或许两个都判断一下可能会更好的二分
但现在这样也已经足够了。
那么理论上，全部用x检查好像也行，因为运行逻辑是去除掉那些绝对不可行的，而对于可能行的是一定会查看的。
那一定会查看所有x在范围内的节点。理论上，如果x范围远比y更宽，这样的策略可能会更好
但我还没学到*/


int main()
{

    kdtree k=NULL;
    k=init(20,1);
    insert(k,12,1243,1);
    insert(k,32,3,1);
    insert(k,124,4,1);
    insert(k,52,453,1);
    insert(k,12,90,1);

    insert(k,342,12,1);
    insert(k,2,63,1);
    insert(k,1,443,1);
    insert(k,1442,43,1);

    int low[2];
    int high[2];
    kdnode val[30];

    low[0]=1;
    low[1]=10;

    high[0]=200;
    high[1]=1000;
    

    printrange(low,high,k,1,val);



    return 0;
}








