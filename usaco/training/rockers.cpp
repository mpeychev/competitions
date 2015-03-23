/*
PROG: rockers
LANG: C++
ID: mompej951
*/

#include <stdio.h>
#include <iostream>

using namespace std;

int n,t,m;
int a[32];

int num;
int sol;

void read()
{
    scanf("%d %d %d",&n,&t,&m);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
}

void rec(int song,int disk,int sum)
{
    if(num>sol) sol=num;
    if(song==n) return;
    if(disk==m) return;
    rec(song+1,disk,sum);
    if(a[song]+sum<=t)
    {
        num++;
        rec(song+1,disk,sum+a[song]);
        num--;
    }
    if(a[song]<=t)
    {
        num++;
        if(disk!=m-1) rec(song+1,disk+1,a[song]);
        num--;
    }
}

int main()
{
    freopen("rockers.in","r",stdin);
    freopen("rockers.out","w",stdout);
    
    read();
    rec(0,0,0);
    printf("%d\n",sol);
    
    return 0;
}
