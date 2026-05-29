#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"stack.h"

#define Opsize 7

char Opset[Opsize]={'+','-','*','/','(',')','#'};

char prior[7][7]={
    {'>','>','<','<','<','>','>'},
    {'>','>','<','<','<','>','>'},
    {'>','>','>','>','<','>','>'},
    {'>','>','>','>','<','>','>'},
    {'<','<','<','<','<','=',' '},
    {'<','<','<','<',' ','>','>'},
    {'<','<','<','<','<',' ','='}

};

int operate(int a,char thet,int b)
{
    int c=0;
    if(thet=='+')
    {
        c=a+b;
    }
    else if(thet=='-')
    {
        c=a-b;
    }
    else if(thet=='*')
    {
        c=a*b;
    }
    else if(thet=='/')
    {
        c=a/b;
    }
    return c;
}

bool innopset(char c)
{
    for(int i=0;i<Opsize;i++)
    {
        if(c==Opset[i])
        {
            return true;
        }
    }
    return false;
}

int oporder(char op)
{
    
      for(int i=0;i<Opsize;i++)
    {
        if(op==Opset[i])
        {
            return i;
        }
    }
    return -1;
}

char precede(char a,char b)
{
    return prior[oporder(a)][oporder(b)];
}

int calculate(char expr[])
{
    stack s1;//符号栈
    sta_null(&s1);
    sta_init(&s1);
    sta_push(&s1,'#');
    stack s2;//数字栈
    sta_null(&s2);
    sta_init(&s2);

    int count=0;
    char c=expr[0];
    while(c!='#'||sta_gettop(&s1)!='#')
    {
        c=expr[count];
        if(innopset(c)==false)
        {
            sta_push(&s2,c-'0');
            count++;
        }
        else
        {
            if(precede(sta_gettop(&s1),c)=='<')
            {
                sta_push(&s1,c);
                count++;
            }
            else if(precede(sta_gettop(&s1),c)=='>')
            {
                int a=sta_pop(&s2);
                int b=sta_pop(&s2);
                int d=operate(b,sta_gettop(&s1),a);
                sta_push(&s2,d);
                sta_pop(&s1);
            }
            else if(precede(sta_gettop(&s1),c)=='=')
            {
                sta_pop(&s1);
                count++;
            }
        }
    }
    return sta_gettop(&s2);


    
    
}


int main()
{
    char expr[18]={'1','+','3','*','9','/','(','0','+','7','*','2',')','+','3','/','1','#'};
    int d=calculate(expr);

        return 0;
}





