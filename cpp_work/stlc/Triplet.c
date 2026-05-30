#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Triplet{
int *arr;
};


void balance(struct Triplet *a)
{
    if(a->arr[0]>a->arr[1])
    {
        int e=a->arr[1];
        a->arr[1]=a->arr[0];
        a->arr[0]=e;
    }

      if(a->arr[0]>a->arr[2])
    {
        int e=a->arr[2];
        a->arr[2]=a->arr[0];
        a->arr[0]=e;
    }

      if(a->arr[1]>a->arr[2])
    {
        int e=a->arr[2];
        a->arr[2]=a->arr[1];
        a->arr[1]=e;

    }

}

void init(struct Triplet *a,int e1,int e2,int e3)
{
    a->arr= (int*)malloc(3 *sizeof(int));
  
    a->arr[0]=e1;
   a->arr[1]=e2;
    a->arr[2]=e3;
    balance(a);
}

void destroy(struct Triplet *a)
{
    free(a->arr);
    a->arr=NULL;
}

bool ifempty(struct Triplet *a)
{
    return (a->arr==NULL);
}

int get(struct Triplet *a,int i)
{
    int m=0;
    if(i>0&&i<4&&ifempty(a)!=true)
    {
        m=a->arr[i-1];
    }
   
    return m;
}

void put(struct Triplet *a,int i,int e)
{
    if(ifempty(a)!=true&&i>0&&i<4)
    {
        a->arr[i-1]=e;
    }

}

bool isacending(struct Triplet *a)
{
    if(a->arr[2]>=a->arr[1]&&a->arr[1]>a->arr[0])
    {
        return true;
    }
    else
    {
        return false;
    }
}

int max(struct Triplet *a)
{
    if(ifempty(a)!=true)
    {

        if(isacending(a)==true)
        {
            return a->arr[2];
        }
        else
        {
            balance(a);
            return max(a);
        }
    }
    else
    {
        return 0;
    }
}







int main(){

    struct Triplet p1;
    init(&p1,3,2,1);


}
