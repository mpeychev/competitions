/*
  Source: usaco - 2005/2006
  Task: trt
  KeyW: dp
*/
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

int n;
int v[2048];
int dp[2048][2048];

void read()
{
    scanf("%d",&n);
    for(int i = 0; i < n; i ++)
        scanf("%d",&v[i]);
}

int f(int l, int r)
{
    if(dp[l][r] != -1) return dp[l][r];
    if(l > r) return 0;
    if(l == r) return v[l] * n;

    dp[l][r] = max(v[l] * (n - r + l) + f(l + 1, r), v[r] * (n - r + l) + f(l, r - 1));
    return dp[l][r];
}

int main()
{
    read();
    memset(dp, -1, sizeof(dp));
    printf("%d\n",f(0, n - 1));

    return 0;
}
