/*
PROG: kimbits
LANG: C++
ID: mompej951
*/

#include <stdio.h>
#include <iostream>

using namespace std;

typedef long long ll;

ll n,l,pos;
ll f[32][32];
ll dp[32][32];

void Pascal()
{
    f[0][0]=1;
    f[1][0]=1; f[1][1]=1;
    for(int i=2;i<=n;i++)
    {
        f[i][0]=1;
        for(int j=1;j<=i;j++) f[i][j]=f[i-1][j]+f[i-1][j-1];
    }
}

void init()
{
    cin >> n >> l >> pos;
    
    Pascal();
    dp[0][0]=1;
    dp[1][0]=1; dp[1][1]=2;
    for(int i=2;i<=n;i++)
    {
        dp[i][0]=1;
        for(int j=1;j<=i;j++) dp[i][j]=dp[i][j-1]+f[i][j];
    }
}

void solve()
{
    if(dp[n][l]==pos)
    {
        for(int i=0;i<l;i++) printf("1");
        for(int i=l;i<n;i++) printf("0");
        printf("\n");
        return;
    }
    
    for(int i=1;i<=n;i++)
    {
        if(l>n-i) l=n-i;
        if(pos>dp[n-i][l]) { printf("1"); pos-=dp[n-i][l]; l--; }
        else printf("0");
    }
    printf("\n");
}

int main()
{
    freopen("kimbits.in","r",stdin);
    freopen("kimbits.out","w",stdout);
    
    init();
    solve();
    
    return 0;
}
