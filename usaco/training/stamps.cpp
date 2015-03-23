/*
PROG: stamps
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
using namespace std;

int n,k;
int m[64],mx;
int dp[2000010];

int main()
{
    freopen("stamps.in","r",stdin);
    freopen("stamps.out","w",stdout);
    scanf("%d %d",&k,&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&m[i]);
        if(m[i]>mx) mx=m[i];
    }
    mx*=k;
    
    dp[0]=1;
    for(int i=1;i<=mx+1;i++)
    {
        int mn=250;
        for(int j=0;j<n;j++) if(i-m[j]>=0 && dp[i-m[j]]<=k && dp[i-m[j]]<mn) mn=dp[i-m[j]];
        if(mn==250) { cout << i-1 << endl; break; }
        dp[i]=mn+1;
    }
    
    return 0;
}
