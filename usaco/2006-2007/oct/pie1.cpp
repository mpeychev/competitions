/*
  Source: usaco - 2006/2007 - oct
  Task: pie1
  KeyW: dp
*/
#include <stdio.h>
#include <iostream>

using namespace std;

int r, c;
int a[128][128];
int dp[128][128];

int main()
{
    scanf("%d %d",&r,&c);
    for(int i = 1; i <= r; i ++)
        for(int j = 1; j <= c; j ++)
            scanf("%d",&a[i][j]);

    dp[1][1] = a[1][1];
    for(int j = 2; j <= c; j ++)
        for(int i = 1; i <= r; i ++)
        {
            if(dp[i - 1][j - 1]) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + a[i][j]);
            if(dp[i][j - 1]) dp[i][j] = max(dp[i][j], dp[i][j - 1] + a[i][j]);
            if(dp[i + 1][j - 1]) dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + a[i][j]);
        }

    printf("%d\n",dp[r][c]);

    return 0;
}
