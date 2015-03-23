/*
  Source: ioi-2001-day 1
  Task: mobiles
  KeyW: bit
*/
#include <stdio.h>
#include <iostream>

using namespace std;

const int MAXS = 1024 + 10;

int s;
int m[MAXS][MAXS];
int code;
int x,y,a;
int l,b,r,t;

void update()
{
    while(x<=s)
    {
        int index=y;
        while(index<=s)
        {
            m[x][index]+=a;
            index+=(index & -index);
        }
        x+=(x & -x);
    }
}

int sum(int xx,int yy)
{
    int ret=0;
    while(xx)
    {
        int index=yy;
        while(index)
        {
            ret+=m[xx][index];
            index-=(index & -index);
        }
        xx-=(xx & -xx);
    }
    return ret;
}

int main()
{
    for( ; ; )
    {
        scanf("%d",&code);
        switch(code)
        {
            case 0:
                scanf("%d",&s);
                break;

            case 1:
                scanf("%d %d %d",&x,&y,&a);
                x++; y++;
                update();
                break;

            case 2:
                scanf("%d %d %d %d",&l,&b,&r,&t);
                l++; b++; r++; t++;
                printf("%d\n",sum(r,t)-sum(r,b-1)-sum(l-1,t)+sum(l-1,b-1));
                fflush(stdout);
                break;

            case 3:
                return 0;
        }
    }
}
