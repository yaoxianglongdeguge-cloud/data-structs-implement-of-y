#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define CAPACITY 10
#define ADDCAPA 10

typedef struct vector
{
int *arr;
int size;
int capacity;
}vector;

//创建默认大小的表
bool vec_init(vector *a)
{
a->arr=(int*)malloc(CAPACITY *sizeof(int));
if(a->arr!=NULL)
{
    a->capacity=CAPACITY;
    a->size=0;
    return 1;
}
else
{
    return 0;
}

}

//创建特定大小的表
bool vec_inittwo(vector *a,int b,int size)
{
a->arr=(int*)malloc(b *sizeof(int));
if(a->arr!=NULL)
{
    a->capacity=b;
    a->size=size;

    return 1;
}
else
{
    return 0;
}

}

//回收表
bool vec_destroy(vector *a)
{
    if(a->arr!=NULL)
    {
        free(a->arr);
        a->arr=NULL;
        return 1;
    }
    else
    { return 0;}
}

//清空为默认表
bool vec_clear(vector *a)
{
    if(a->arr!=NULL)
    {
        vec_destroy(a);
        vec_init(a);
        return 1;
    }
    else
    {
        return 1;
    }
}

//判断表是否为空
bool vec_empty(vector *a)
{
    if(a->arr==NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//表内数据量
int vec_size(vector *a)
{
    if(a->arr!=NULL)
    {
        return a->size;
    }
    else
    {
        return 0;
    }
}

//表容量
int vec_capacity(vector *a)
{
    if(a->arr!=NULL)
    {
        return a->capacity;
    }
    else
    {
        return 0;
    }
}

//返回i位置数据
int vec_get(vector *a,int i)
{
    return a->arr[i-1];
}

//返回表内与b符合函数oper的第一个数据
int vec_locate(vector *a,int b,bool (*oper)(int m,int n))
{
     if(a->arr!=NULL)
    {
    for(int k=0;k<a->size;k++)
    {
        if(oper(a->arr[k],b))
        {
            return k;
    }
    }
     }
return -1;

}

//相等判断函数
bool vec_equal(int a,int b)
{
    if(a==b)
    { return 1; }
    else
    { return 0; }
}

//返回b位置数据前一个数据
int vec_pre(vector *a,int b)
{
    int m=0;
     if(a->arr!=NULL)
    {
    int n=vec_locate(a,b,vec_equal);
    if(n>1&&n<vec_size(a))
    {
        m=a->arr[n-1];
    }
    }
  return m;
}

//返回b位置数据后一个数据
int vec_next(vector *a,int b)
{
    int m=0;
    if(a->arr!=NULL)
    {

        int n=vec_locate(a,b,vec_equal);
        if(n>0&&n<vec_size(a)-1)
        {
            m=a->arr[n+1];
        }
    }
  return m;
}

//表扩容
void vec_expand(vector *a)
{
    struct vector p1;
    vec_inittwo(&p1,a->capacity+ADDCAPA,vec_size(a));
    for(int k=0;k<vec_size(a);k++)
    {
        p1.arr[k]=a->arr[k];
    }
    free(a->arr);
    a->arr=p1.arr;
    a->capacity=p1.capacity;
    a->size=p1.size;

}

bool vec_narrow(vector* a)
{
    if(vec_capacity(a)>10)
    {
    struct vector p1;
    vec_inittwo(&p1,vec_capacity(a)-ADDCAPA,vec_size(a));
    for(int k=0;k<vec_size(a);k++)
    {
        p1.arr[k]=a->arr[k];
    }
    free(a->arr);
    a->arr=p1.arr;
    a->capacity=p1.capacity;
    a->size=p1.size;

    }
    return 0;
}


//表尾端插入
bool vec_insertend(vector *a,int b)
{
  
    if(a->arr!=NULL)
    {

        if(vec_size(a)>=vec_capacity(a))
        {
            vec_expand(a); 
        }
        
        
        a->arr[vec_size(a)]=b;
        a->size++;
        return 1;
    }
    else
    {
        return 0;
    }
   
}

//表尾端删除
bool vec_deleteend(vector *a)
{
  
    if(a->arr!=NULL)
    {
        a->arr[vec_size(a)]=0;
        a->size--;
        return 1;
    }
    else
    {
        return 0;
    }
   
}

//表特定位置插入
bool vec_insert(vector *a,int i,int b)
{
    if(i<1||i>vec_size(a)+1)
    {
        return 0;
    }
    if(vec_size(a)>=vec_capacity(a))
    {
        vec_expand(a); 
    }
     for(int k=vec_size(a)-1;k>=i-1;k--)
        {
            a->arr[k+1]=a->arr[k];
        }
        a->arr[i-1]=b;
        a->size++;
        return 1;
   
}

//表特定位置删除
bool vec_delete(vector *a,int i)
{
    if(i<1||i>vec_size(a))
    {
        return 0;
    }

     for(int k=i-1;k<vec_size(a)-1;k++)
        {
            a->arr[k]=a->arr[k+1];
        }
        a->size--;
        return 1;
   
}

//遍历表
void vec_visit(vector*a)
{
    if(a->arr!=NULL)
    {

        for(int l=0;l<vec_size(a);l++)
        {
            printf("%d",a->arr[l]);
        }
    }
    
}



//例题函数

//表合并
void vec_merge(vector *p1,vector *p2)
{
    int length=vec_capacity(p1)+vec_capacity(p2);
    while(vec_capacity(p1)<=length)
    {
        vec_expand(p1);
    }
    for(int i=0;i<vec_size(p2);i++)
    {
        int m=vec_get(p2,i+1);
        if(vec_locate(p1,m,vec_equal)==-1)
        {
            vec_insertend(p1,m);
        }
    }


}

//表按小到大顺序混合    
void vec_mixture(vector *p1,vector *p2,vector *p3)
{
    int length=vec_capacity(p1)+vec_capacity(p2);
    while(vec_capacity(p3)<=length)
    {
        vec_expand(p3);
    }
    int i=0;
    int j=0;
   while(i<vec_size(p1)&&j<vec_size(p2))
   {
    if(p1->arr[i]>p2->arr[j])
    {
        vec_insertend(p3,p2->arr[j]);
        j++;
    }
    else if(p1->arr[i]<p2->arr[j])
    {
        vec_insertend(p3,p1->arr[i]);
        i++;
    }
    else
    {
        vec_insertend(p3,p2->arr[j]);
        i++;
        j++;
    }


   }
 

   if(i!=vec_size(p1))
   {
    for(;i<vec_size(p1);i++)
    {
        vec_insertend(p3,p1->arr[i]);
    }
   }

     if(j!=vec_size(p2))
   {
    for(;j<vec_size(p2);j++)
    {
        vec_insertend(p3,p2->arr[j]);
    }
   }


}

int main()
{
    /*
    struct vector p1;
    init(&p1);
    visit(&p1);
    insertend(&p1,1);
    insertend(&p1,12);
    insertend(&p1,4);
    insert(&p1,2,5);
    insertend(&p1,123);

    deleteend(&p1);
    delete(&p1,2);

    int y1=get(&p1,2);
    int y2=pre(&p1,4);
    int y3=next(&p1,4);

    int u1=size(&p1);
    int u2=capacity(&p1);

    clear(&p1);

    struct vector p1;
    init(&p1);
    insertend(&p1,1);
    insertend(&p1,12);
    insertend(&p1,55);
    insertend(&p1,66);
    insertend(&p1,73);
    insertend(&p1,123);
    insertend(&p1,415);
    insertend(&p1,1644);


     struct vector p2;
    init(&p2);
    insertend(&p2,1);
    insertend(&p2,11);
    insertend(&p2,55);
    insertend(&p2,332);
    insertend(&p2,1000);

    struct vector p3;
    init(&p3);
    mixture(&p1,&p2,&p3);
    //merge(&p1,&p2);
    for(int i=0;i<size(&p3);i++)
    {
        printf("%d",p3.arr[i]);
    }*/


   








    return 0;
}