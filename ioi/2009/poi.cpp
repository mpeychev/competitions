/*
  Source: ioi - 2009
  Task: poi
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct
{
    int tasks,num,res;
} participant;

int n,t,p,tmp;
participant m[2048];
int points[2048];
bool g[2048][2048];

void init()
{
    scanf("%d %d %d",&n,&t,&p);
    for(int i=1;i<=n;i++)
    {
        tmp=0;
        for(int j=1;j<=t;j++)
        {
            scanf("%d",&g[i][j]);
            if(g[i][j]==0) points[j]++;
            else tmp++;
        }
        m[i].tasks=tmp;
        m[i].num=i;
    }
    
    for(int i=1;i<=n;i++)
     for(int j=1;j<=t;j++)
      m[i].res+=g[i][j]*points[j];
}

bool cmp(participant a,participant b)
{
    if(a.res>b.res) return true;
    if(a.res<b.res) return false;
    if(a.tasks>b.tasks) return true;
    if(a.tasks<b.tasks) return false;
    if(a.num<b.num) return true;
    return false;
}

void solve()
{
    sort(m+1,m+n+1,cmp);
    for(int i=1;i<=n;i++)
     if(m[i].num==p)
     {
            printf("%d %d\n",m[i].res,i);
            break;
     }
}

int main()
{
    init();
    solve();

    return 0;
}
