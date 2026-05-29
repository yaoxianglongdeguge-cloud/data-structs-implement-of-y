#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"vector.h"

typedef struct stack
{
    vector* base;
    int top;
    int size;
}stack;

void sta_null(stack* a);

bool sta_init(stack* a);

bool sta_free(stack* a);

bool sta_clear(stack* a);

bool sta_empty(stack* a);

int sta_size(stack* a);

int sta_gettop(stack* a);

void sta_push(stack* a,int e);

int sta_pop(stack* a);

void sta_trav(stack* a);

void sta_numberconver8(int a);


//置空
void sta_null(stack* a)
{
    a->base=NULL;
    a->top=0;
    a->size=0;
}

//创建栈
bool sta_init(stack* a)
{
    if(a->base==NULL)
    {
        vector* v=(vector*)malloc(sizeof(vector));
        vec_init(v);
        a->base=v;
        a->top=0;
        a->size=vec_size(v);
        return 1;
    }
    return 0;
}

//回收栈
bool sta_free(stack* a)
{
    if(a->base==NULL)
    {
        return 0;
    }
    else
    {
        vec_destroy(a->base);
        free(a->base);
        a->base=NULL;
        a->size=0;
        a->top=0;
        return 1;
    }
}

清空栈
bool sta_clear(stack* a)
{
    if(a->base==NULL)
    {
        return 0;
    }
    else
    {
        vec_clear(a->base);
        a->size=0;
        a->top=0;
        return 1;
    }
}

//判断是否为空
bool sta_empty(stack* a)
{
    if(a->base==NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//数据量
int sta_size(stack* a)
{
    return a->size;
}

//栈顶元素
int sta_gettop(stack* a)
{
    return vec_get(a->base,a->top);
}

//入栈
void sta_push(stack* a,int e)
{
    vec_insertend(a->base,e);
    a->size++;
    a->top++;
}

//弹栈
int sta_pop(stack* a)
{
    if(a->base==NULL)
    {
        return 0;
    }
    else
    {
        int m=sta_gettop(a);
        vec_deleteend(a->base);
        a->size--;
        a->top--;
        return m;
    }
}

//遍历
void sta_trav(stack* a)
{
    int m=a->top;
    while(m>=0)
    {
        printf("%d",sta_gettop(m));
        m--;
    }
}

//十进制转八进制
void sta_numberconver8(int a)
{
    stack s;
    sta_null(&s);
    sta_init(&s);
    while(a!=0)
    {
        sta_push(&s,a%8);
        a=a/8;
    }
    while(!sta_empty(&s))
    {
        printf("%d",sta_pop(&s));
    }
}


int main()
{
    stack s;
    sta_null(&s);
    sta_init(&s);

    sta_push(&s,1);
    sta_push(&s,451);
    sta_push(&s,41);
    sta_push(&s,12);

    sta_gettop(&s);
    int e=sta_pop(&s);
    sta_gettop(&s);

    sta_clear(&s);
    sta_empty(&s);

    sta_numberconver8(10);

    return 0;
}  






