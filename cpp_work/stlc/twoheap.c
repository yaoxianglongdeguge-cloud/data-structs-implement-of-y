#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MIN 0

typedef struct heap
{
    int capacity;
    int size;
    int* elements;
}heap;

heap* heap_init(int maxelement)
{
    heap* h;
    h=(heap*)malloc(sizeof(heap));

    if(h==NULL)
    {
        return NULL;
    }

    h->elements=(int*)malloc(sizeof(int)*maxelement);
    if(h->elements==NULL)
    {
        return NULL;
    }

    h->size=0;
    h->capacity=maxelement;
    h->elements[0]=MIN;

    return h;
}

bool heap_insert(heap* h,int e)
{
    if(h==NULL||h->elements==NULL)
    {
        return false;
    }

    h->elements[h->size+1]=e;

    int pos=h->size+1;

    while(pos>0)
    {
        if(e<h->elements[pos/2])
        {
            int k=h->elements[pos/2];
            h->elements[pos/2]=e;
            h->elements[pos]=k;

            pos=pos/2;
        }
        else
        {
            break;
        }

    }

    h->size++;
    return true;

}

bool heap_deletemin(heap* h)
{
    if(h==NULL||h->elements==NULL)
    {
        return false;
    }
    int minment=h->elements[1];
    int lastment=h->elements[h->size];
    h->size--;
    int pos=1;
    int child=pos;

    while(pos*2<=h->size)
    {
        child=pos*2;
        if(child!=h->size&&h->elements[child]>h->elements[child+1])
        {
            child++;
        }

        if(lastment>h->elements[child])
        {
            h->elements[pos]=h->elements[child];
        }
        else
        {
            break;
        }
        pos=child;

    }

    h->elements[pos]=lastment;
    return minment;
}

void heap_sort(heap* h)
{
    int i=h->size;
    int tem=0;
    while(i>=1)
    {
        tem=h->elements[1];
        heap_deletemin(h);
        h->elements[i]=tem;
        i--;

    }
}

//其实insert和deletemin都是先把一个插入，然后过滤，deletemin就是先删除最顶上的
//然后，把最后一个元素放到最顶上，然后下滤，也就是说单点改变堆总是可以通过上滤下滤维持结构特性

int main()
{
    heap* h=heap_init(20);

    heap_insert(h,2);
    heap_insert(h,5);
    heap_insert(h,1);
    heap_insert(h,6);
    heap_insert(h,7);
    heap_insert(h,3);
    heap_insert(h,4);

    heap_insert(h,8);
    heap_insert(h,9);

    heap_insert(h,10);
    
    heap_insert(h,12);
    heap_insert(h,13);
    heap_insert(h,11);

    heap_insert(h,14);
    
    heap_insert(h,15);
    heap_insert(h,16);

     
    heap_sort(h);

    return 0;







}












