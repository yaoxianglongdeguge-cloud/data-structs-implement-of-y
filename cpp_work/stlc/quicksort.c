#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


//事实上快排只需要保证从某个位置开始，两边分别大于等于枢纽，小于等于枢纽，也就是说等于枢纽的或者枢纽本身
//在哪是无所谓的，但问题是我们最后要确定分割位置，这个就依赖指针最后指向位置
//如果只是少量的等于枢纽元的元素，那最后指针指向位置基本取决于元素的相对枢纽的大小位置
//而这一般是可以接近平分的（只要枢纽的大小选的好）
//但如果有大量的连续的等于枢纽元元素，如果指针不停止，就会出现一个指针先走，然后一下子走很远
//另一个指针再走，但很快就交错了，导致指针指向位置两边极不平衡
//而如果两个指针停一下进行一下交换，就可以保持接近的频率移动，最后接近中间位置。

void qswap(int arr[],int i,int j)
{
    int p=arr[i];
    arr[i]=arr[j];
    arr[j]=p;
}

int median(int arr[],int left,int right)
{
    int center=(right+left)/2;

    if(arr[left]>arr[center])
    {
        qswap(arr,left,center);
    }
     if(arr[left]>arr[right])
    {
        qswap(arr,left,right);
    }
     if(arr[center]>arr[right])
    {
        qswap(arr,center,right);
    }

    qswap(arr,center,right-1);
    return arr[right-1];
}



void Qsort(int arr[],int left,int right)
{ 
    int i=left;
    int j=right-1;
    
    if(left+2<=right)
    {
        int povit=median(arr,left,right);
        while(true)
        {
            while(arr[++i]<povit){}
            while(arr[--j]>povit){}
            if(i<j)
            {
                qswap(arr,i,j);
            }
            else
        {
            break;
        }

        }
        qswap(arr,i,right-1);

        Qsort(arr,left,i-1);
        Qsort(arr,i+1,right);

    }
    else if(left+1==right)
    {
     if(arr[left]>arr[right])
     {
        qswap(arr,left,right);
     }
    }

    
}


int main()
{
    int arr[20]={5,3,6,8,2,1,43,86,24,9,11,12,16,64,7,8,31,32,27,100};


    Qsort(arr,0,19);
    return 0;
}










