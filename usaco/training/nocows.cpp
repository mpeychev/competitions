/*
PROG: nocows
LANG: C++
ID: mompej951
*/
#include <iostream>

#define MOD 9901
using namespace std;

int n,k;
short int dp[201][201][101],c[201][201];

void init()
{
    c[0][0]=1;
    c[1][0]=1; c[1][1]=1;
    for(int i=2;i<=n;i++)
    {
        c[i][0]=1;
        for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
    }
}

int f(int x,int sum,int lvl)
{
    if(lvl==1)
    {
        if(x==1 && sum==n) dp[x][sum][lvl]=1;
        else dp[x][sum][lvl]=0;
    }
    if(lvl==2)
    {
        if(x==2 && sum==n-1) dp[x][sum][lvl]=1;
        else dp[x][sum][lvl]=0;
    }
    if(dp[x][sum][lvl]!=-1) return dp[x][sum][lvl];
    dp[x][sum][lvl]=0;
    for(int i=2;i<=n-sum;i+=2) dp[x][sum][lvl]=(dp[x][sum][lvl]+f(i,sum+i,lvl-1)*c[i][x/2])%MOD;
    return dp[x][sum][lvl];
}

int main()
{
    freopen("nocows.in","r",stdin);
    freopen("nocows.out","w",stdout);
    cin >> n >> k;
    for(int i=0;i<=n;i++)
     for(int j=0;j<=n;j++)
      for(int p=0;p<=k;p++)
       dp[i][j][p]=-1;
    init();
    int sol=0;
    for(int i=2;i<=n;i+=2) sol=(sol+f(i,i,k))%MOD;
    
    cout << sol << endl;
    
    return 0;
}
