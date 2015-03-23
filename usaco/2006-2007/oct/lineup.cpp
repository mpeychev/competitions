/*
  Source: usaco - 2006/2007 - oct
  Task: lineup
  KeyW: simple dp
*/
#include <stdio.h>
#include <iostream>

using namespace std;

int n;
int a[5010], dp[5010];
int ans;

int main()
{
    scanf("%d",&n);
    for(int i = 1; i <= n; i ++)
        scanf("%d",&a[i]);

    for(int i = 1; i <= n; i ++)
        for(int j = 0; j < i; j ++)
            if(a[i] > a[j] && dp[i] < dp[j] + 1)
                dp[i] = dp[j] + 1;

    for(int i = 1; i <= n; i ++)
        if(ans < dp[i])
            ans = dp[i];
    printf("%d\n",ans);

    return 0;
}
