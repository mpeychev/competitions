/*
PROG: game1
LANG: C++
ID: mompej951
*/

#include <stdio.h>
#include <iostream>

using namespace std;

int n;
int m[128],sum[128];
int dp[128][128];

void init()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&m[i]);
        sum[i]=sum[i-1]+m[i];
    }
}

int f(int x,int y)
{
    if(dp[x][y]) return dp[x][y];
    if(x+1==y)
    {
        if(m[x]>m[y]) return m[x];
        return m[y];
    }
    
    int l=m[x]+sum[y]-sum[x]-f(x+1,y);
    int r=m[y]+sum[y-1]-sum[x-1]-f(x,y-1);
    
    if(l>r) dp[x][y]=l;
    else dp[x][y]=r;
    
    return dp[x][y];
}

void solve()
{
    int first=f(1,n);
    int second=sum[n]-first;
    printf("%d %d\n",first,second);
}

int main()
{
    freopen("game1.in","r",stdin);
    freopen("game1.out","w",stdout);
    
    init();
    solve();
    
    return 0;
}
