/*
PROG: money
LANG: C++
ID: mompej951
*/
#include <stdio.h>
#include <iostream>
using namespace std;

int v,n,m[32];
long long dp[16384];

int main()
{
    freopen("money.in","r",stdin);
    freopen("money.out","w",stdout);
    
    scanf("%d %d",&v,&n);
    for(int i=0;i<v;i++) scanf("%d",&m[i]);
    
    dp[0]=1;
    for(int i=0;i<v;i++)
     for(int j=0;j+m[i]<=n;j++)
      dp[j+m[i]]+=dp[j];
    /*
    for(int i=0;i<=n;i++) cout << dp[i] << " ";
    cout << endl;
    */
    cout << dp[n] << endl;
        
    return 0;
}
