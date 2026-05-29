#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>



#define MAX 254

typedef char* sstr;


sstr str_alloc(int len)
{
    sstr s;
    if(len<=MAX)
    {   
        s=(sstr)malloc((len+2)*sizeof(char));
    }
    else
    {
        s=(sstr)malloc(256*sizeof(char));
    }
    s[0]=len;
    return s;
}

bool str_init(sstr *s,char* p)
{
    if(p==NULL||*s!=NULL)
    {
        return false;
    }
    else
    {
        int plen=0;
        int i=0;
        while(p[i]!='\0')
        {
            plen++;
            i++;
        }
        *s=str_alloc(plen);
        i=1;
        while(p[i-1]!='\0'&&i<=s[0])
        {
            (*s)[i]=p[i-1];
            i++;
        }
        (*s)[(*s)[0]+1]='\0';
        return true;
    }
    return false;
}

bool str_free(sstr *s)
{
    if(s==NULL)
    {
        return false;
    }
    else
    {
        free(*s);
        s=NULL;
        return true;
    }
    return false;
}

sstr str_sub(sstr *s,int pos,int len)
{
    if(s==NULL||len+pos-1>s[0]||pos>s[0])
    {
        return NULL;
    }
    else
    {
        int i=pos;
        sstr d;
        d=NULL;
        d=str_alloc(len);
        int j=1;
        while(j<len+1)
        {
            d[j]=(*s)[i];
            i++;
            j++;
        }
        return d;
    }
    return NULL;
}

bool str_range(sstr *s,int a,int b)
{
    if((*s)==NULL||a>(*s)[0]||b>(*s)[0])
    {
        return false;
    }
    else
    {
        sstr m=str_sub(s,a,(b-a+1));
        str_free(s);
        *s=m;
        return true;
    }
    return false;
}

sstr str_concate(sstr s1,sstr s2)
{
    sstr t;
    t=NULL;
    int mlen=s1[0]+s2[0];

    t=str_alloc(mlen);
    int i=1;
    int j=1;
    while(j<=MAX&&j<=mlen&&i<=s1[0])
    {
        t[j]=s1[i];
        i++;
        j++;
    }
    i=1;
    while(j<=MAX&&j<=mlen&&i<=s2[0])
    {
        t[j]=s2[i];
        i++;
        j++;
    }
    
  

    return t;
}

void str_get_next(sstr* s,int* next)
{
    int i=1;
    int j=0;
    next[0]=0;
    next[1]=0;
    while(i<=(*s)[0])
    {
        if(j==0||(*s)[i]==(*s)[j])
        {
            i++;
            j++;
            next[i]=j;
        }
        else
        {
            j=next[j];
        }
    }
}

int str_index_KMP(sstr* s,sstr* p,int pos)
{
    if(*s==NULL||*p==NULL||pos<1||pos>s[0])
    {
        return 0;
    }
    int i=pos;int j=0;
    int  next[(*p)[0]];
    str_get_next(p,next);
    while(i<=(*s)[0]&&j<=(*p)[0])
    {
        if(j==0||(*s)[i]==(*p)[j])
        {
            i++;
            j++;
        }
        else
        {
            j=next[j];
        }
    }
    if(j>(*p)[0])
    {
        return i-(*p)[0];
    } 
  
   
        return 0;
    
    
}





int main()
{
    sstr s;
    s=NULL;
    sstr i;
    i=NULL;
    char* p="adcbbbdadcbdddcbcbcdaa";
    char* k="cbcda";
    str_init(&i,k);
    str_init(&s,p);

    sstr l=str_concate(s,i);
    
    int m=str_index_KMP(&s,&i,2);

    str_range(&s,2,6);
    return 0;
}








































//kmp算法，为什么母串不用回溯，因为，比如原本母串到了i，然后回溯到p，那我们要求模式串也回溯，由k到m，那如果要匹配，m到k，一定与p到i
//匹配，否则，m还要移动，但最终要匹配，反正最后i的移动和k的移动一定要使这两段配上，否则说明，模式串和母串根本无法匹配，然后，匹配上之后
//就会发现，m到k与p到i，之前已经有过匹配了（不包含i），也就是说，模式串到j之前有两个子段甚至多个是相同的，其中一个是后缀，那直接把其他相同子段
//拉过来，i就没有必要回溯了，因为此时i回溯比较的一定是匹配的。而且那个相同的子段一定是前缀，就是说一段前缀和一段后缀相同，否则那一段子段后面匹配上之后
//前面匹配不上。这好像不是充分必要的条件。
//根本上就是只要找到最大的匹配前后缀，把前缀拉过来匹配，既然后缀已经匹配上了（因为这段字串都是匹配好的），那就没必要回溯再匹配一遍了。
//而且由于你这个是最大的，如果想用更大的前缀匹配，必然是匹配不上的。而如果用更小的，那会缺少可能性，因为原本如果最大的那个没配上也会用小的，不应该直接用。



















