#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void Msort(int arr[],int val[],int left,int middle,int right);

void Mmerge(int arr[],int val[],int left,int right)
{
    if(left<right)
    {
        int middle=(left+right)/2;
        Mmerge(arr,val,left,middle);
        Mmerge(arr,val,middle+1,right);
        Msort(arr,val,left,middle,right);
    }
}

void Msort(int arr[],int val[],int left,int middle,int right)
{
    int i1=left;
    int i2=middle+1;
    int i3=left;

    while(i1<=middle&&i2<=right&&i3<=right)
    {
      
        if(arr[i1]<arr[i2])
        {
            val[i3]=arr[i1];
            i1++;
            i3++;
        }
        else if(arr[i1]>arr[i2])
        {
            val[i3]=arr[i2];
            i2++;
            i3++;
        }
        else
        {
            val[i3]=arr[i1];
            i1++;
            i3++;
            val[i3]=arr[i2];
            i2++;
            i3++;
        }
        
    }

    if(i1<middle+1)
    {
        while(i1<=middle)
        {
            val[i3]=arr[i1];
            i3++;
            i1++;
        }
    }
    else if(i2<right+1)
    {
        while(i2<=right)
        {
            val[i3]=arr[i2];
            i3++;
            i2++;
        }
    }

    int i=left;
    while(i<=right)
    {
        arr[i]=val[i];
        i++;
    }

}


int main()
{
    int arr[20]={5,3,6,8,2,1,43,86,24,9,11,12,16,64,7,8,31,32,27,100};
    int val[20];

    Mmerge(arr,val,0,19);

    return 0;



}













/*

希尔排序
int main()
{
    int arr[20]={5,3,6,8,2,1,43,86,24,9,11,12,16,64,7,8,31,32,27,100};

    int step=8;
    int j=0;
    int i=0;
    for(;step>=1;step/=2)
    {
        i=step;
                    //此时i一定是第一个起点加步长乘一，也就是每个步长对应的第二个元素，之后随着i++，会逐渐遇到对应步长的第三个第四个等（不是说
                       // 遇到第二个下一个就是同起点该步长的第三个，而是先处理其他起点的第二个），
                       //实现依次排序但是是以步长为分割
        for(;i<20;i++)
        {
            int tem=arr[i];
            for(j=i;j>=step;j-=step)
            {
               if(tem<arr[j-step])
               {
                arr[j]=arr[j-step];
               }
               else
               {
                   break;
                }
                
            }
            arr[j]=tem;
        }
    }


    return 0;
}
    */