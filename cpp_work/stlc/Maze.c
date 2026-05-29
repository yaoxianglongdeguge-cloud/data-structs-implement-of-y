#include"stack.h"

typedef struct position
{
int r;
int c;
}position;

typedef struct maze
{
    char arr[10][10];
    int row;
    int col;
}maze;

typedef struct block
{
position pos;
int next;
}block;


block blockarr[20];


bool maze_init(maze * m)
{

    m->col=10;
    m->row=10;

}

void pos_push(maze* m,position p,int i,stack* s)
{
    int e=(p.r)*10+p.c;
    sta_push(s,e);
    blockarr[e].next=i;
    blockarr[e].pos.c=p.c;
    blockarr[e].pos.r=p.r;
    m->arr[p.r][p.c]='*';
}

block pos_pop(maze* m,stack* s)
{
    int b=sta_pop(s);
    block t=blockarr[b];
    return t;
}

bool open(maze* m,position p,int dir)
{
     if(dir==1)
     {
        if(m->arr[p.r-1][p.c]==' ')
        {
            return true;
        }
        else
        {
            return false;
        }
     }
     else  if(dir==2)
     {
        if(m->arr[p.r][p.c+1]==' ')
        {
            return true;
        }
        else
        {
            return false;
        }
     }
      else  if(dir==3)
     {
        if(m->arr[p.r+1][p.c]==' ')
        {
            return true;
        }
        else
        {
            return false;
        }
     }
      else  if(dir==4)
     {
        if(m->arr[p.r][p.c-1]==' ')
        {
            return true;
        }
        else
        {
            return false;
        }
     }
}

void footprint(maze*m,position p)
{
    m->arr[p.r][p.c]='*';
}

void markprint(maze* m,position p)
{
    m->arr[p.r][p.c]='!';
}

position nextpos(maze* m,position p,int dir,stack* s)
{
    position newpos;
switch (dir)
{
case 1:
    newpos.r=p.r-1;
    newpos.c=p.c;
    pos_push(m,p,1,s);
    break;
case 2:
    newpos.r=p.r;
    newpos.c=p.c+1;
    pos_push(m,p,2,s);
    break;
case 3:
    newpos.r=p.r+1;
    newpos.c=p.c;
    pos_push(m,p,3,s);
    break;
case 4:
    newpos.r=p.r;
    newpos.c=p.c-1;
    pos_push(m,p,4,s);
    break;
}
return newpos;
}

int main()
{

maze m;
maze_init(&m);


    for(int a=0;a<10;a++)
    {
        for(int b=0;b<10;b++)
        {
            m.arr[a][b]=' ';
        }
    }

m.arr[0][0]='#';
m.arr[0][1]='#';
m.arr[0][2]='#';
m.arr[0][3]='#';
m.arr[0][4]='#';
m.arr[0][5]='#';
m.arr[0][6]='#';
m.arr[0][7]='#';
m.arr[0][8]='#';
m.arr[0][9]='#';
m.arr[1][0]='#';
m.arr[2][0]='#';
m.arr[3][0]='#';
m.arr[4][0]='#';
m.arr[5][0]='#';
m.arr[6][0]='#';
m.arr[7][0]='#';
m.arr[8][0]='#';
m.arr[9][0]='#';
m.arr[9][1]='#';
m.arr[9][2]='#';
m.arr[9][3]='#';
m.arr[9][4]='#';
m.arr[9][5]='#';
m.arr[9][6]='#';
m.arr[9][7]='#';
m.arr[9][8]='#';
m.arr[9][9]='#';
m.arr[2][9]='#';
m.arr[3][9]='#';
m.arr[4][9]='#';
m.arr[5][9]='#';
m.arr[6][9]='#';
m.arr[7][9]='#';
m.arr[8][9]='#';

m.arr[1][3]='#';
m.arr[1][7]='#';
m.arr[2][3]='#';
m.arr[2][7]='#';

m.arr[3][5]='#';
m.arr[3][6]='#';

m.arr[4][2]='#';
m.arr[4][3]='#';
m.arr[4][4]='#';

m.arr[5][4]='#';

m.arr[6][2]='#';
m.arr[6][6]='#';
m.arr[8][1]='#';


m.arr[7][2]='#';
m.arr[7][3]='#';
m.arr[7][4]='#';
m.arr[7][7]='#';
m.arr[7][6]='#';


stack s;
sta_null(&s);
sta_init(&s);
position pos;
pos.r=1;
pos.c=1;

int len=0;

while(pos.c!=8||pos.r!=8)
{
   
    if(open(&m,pos,1)==true)
    {
        nextpos(&m,pos,1,&s);
        pos.r--;
        len++;
    }
    else if(open(&m,pos,2)==true)
    {
        nextpos(&m,pos,2,&s);
        pos.c++;
        len++;
    }
    else if(open(&m,pos,3)==true)
    {
        nextpos(&m,pos,3,&s);
        pos.r++;
        len++;
    }
    else if(open(&m,pos,4)==true)
    {
        nextpos(&m,pos,4,&s);
        pos.c--;
        len++;
    }
    else
    {
        markprint(&m,pos);
        pos=pos_pop(&m,&s).pos;
        len--;

    }
}
















free(blockarr);

return 0;






}
















