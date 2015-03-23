#include <stdio.h>
#include <iostream>

using namespace std;

const int MAXN = 100010;
const int MOD = 1000000007;

int n;
long long a[MAXN],b[MAXN];
long long dp[MAXN][4];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<n;i++)
        scanf("%d",&b[i]);
    
    dp[1][0] = a[1];
    dp[1][2] = b[1];
    for(int i=2;i<=n;i++)
    {
        dp[i][0] = (( (dp[i-1][0] + dp[i-1][1] + dp[i-1][2]) % MOD ) * a[i]) % MOD;
        if(b[i-1] > 0)
            dp[i][1] = ( (( (dp[i-1][0] + dp[i-1][1]) % MOD ) * b[i-1]) % MOD + (dp[i-1][2] * (b[i-1]-1)) % MOD ) % MOD;
        dp[i][2] = (( (dp[i-1][0] + dp[i-1][1] + dp[i-1][2]) % MOD ) * b[i]) % MOD;
    }
    
    cout << (dp[n][0] + dp[n][1] + dp[n][2]) % MOD << endl;
    
    return 0;
}
