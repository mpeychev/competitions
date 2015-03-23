/*
PROG: subset
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

int n;
int s;
long long dp[512][64];

long long rec(int sum,int last)
{
     if(sum>s) return 0;
     if(dp[sum][last]!=-1) return dp[sum][last];
     if(sum==s) return 1;
     dp[sum][last]=0;
     for(int i=last+1;i<=n;i++) dp[sum][last]+=rec(sum+i,i);
     return dp[sum][last];
}

int main()
{
    freopen("subset.in","r",stdin);
    freopen("subset.out","w",stdout);
    
    scanf("%d",&n);
    s=((n+1)*n)/2;
    if(s&1) { printf("0\n"); return 0; }
    
    s/=2;
    memset(dp,-1,sizeof(dp));
    printf("%lld\n",rec(0,0)/2);
    
    return 0;
}
