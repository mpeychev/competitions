/*
PROG: inflate
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

struct task
{
    int score;
    int time;
};

int n,m;
task a[1<<14];
long long dp[1<<14];

bool cmp(task a, task b)
{
    if(a.time<b.time) return true;
    return false;
}

int main()
{
    freopen("inflate.in","r",stdin);
    freopen("inflate.out","w",stdout);
    scanf("%d %d",&m,&n);
    for(int i=0;i<n;i++) scanf("%d %d",&a[i].score,&a[i].time);
    
    long long sol=-1;
    sort(a,a+n,cmp);
    for(int i=1;i<=m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i-a[j].time<0) break;
            if(dp[i]<dp[i-a[j].time]+a[j].score) dp[i]=dp[i-a[j].time]+a[j].score;
        }
        if(sol<dp[i]) sol=dp[i];
    }
    
    printf("%lld\n",sol);
    
    return 0;
}
