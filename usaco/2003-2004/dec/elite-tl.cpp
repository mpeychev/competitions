/*
  Source: usaco - 2003/2004 - dec
  Task: elite
  KeyW: maths; dp
*/
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

int n, s;
int dp[2][10200][128];
int ans;

int sumSqr(int x)
{
    return (x * (x + 1) * (2 * x + 1)) / 6;
}

int main()
{
    scanf("%d %d",&n,&s);
    if(sumSqr(n) >= s)
    {
        printf("0\n");
        return 0;
    }

    dp[0][0][0] = 1;
    for(int i = 1; i <= n; i ++)
    {
        memset(dp[i & 1], 0, sizeof(dp[i & 1]));
        for(int k = sumSqr(i); k < s; k ++)
            for(int j = 1; j * j <= k; j ++)
                for(int h = 0; h < j; h ++)
                    dp[i & 1][k][j] += dp[!(i & 1)][k - j * j][h];
    }

    for(int i = 0; i < s; i ++)
        for(int j = 0; j * j < i; j ++)
            ans += dp[n & 1][i][j];

    printf("%d\n",ans);

    return 0;
}
