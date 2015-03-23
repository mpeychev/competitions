/*
  Source: usaco - 2003/2004 - nov
  Task: smrtfun
  KeyW: dp
*/
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>

#define s first
#define f second

using namespace std;

typedef pair<int, int> PII;

const int INF = -100100;

int n;
PII cow[128];
int dp[100100], cpyDp[100100];
int sum;

bool cmp(PII a, PII b)
{
    return a.s > b.s;
}

void init()
{
    scanf("%d",&n);
    for(int i = 0; i < n; i ++)
        scanf("%d %d",&cow[i].s,&cow[i].f);
    sort(cow, cow + n, cmp);

    for(int i = 1; i < 100010; i ++)
    {
        dp[i] = INF;
        cpyDp[i] = INF;
    }
}

void solve()
{
    for(int i = 0; i < n; i ++)
    {
        for(int j = max(0, -cow[i].s); j <= sum; j ++)
            if(dp[j] != INF && cpyDp[ j + cow[i].s ] < dp[j] + cow[i].f)
                cpyDp[ j + cow[i].s ] = dp[j] + cow[i].f;

        if(cow[i].s > 0) sum += cow[i].s;

        for(int j = 0; j <= sum; j ++)
            if(cpyDp[j] > dp[j])
                dp[j] = cpyDp[j];
    }

    int ans = 0;
    for(int i = 0; i <= sum; i ++)
        if(dp[i] >= 0 && ans < i + dp[i])
            ans = i + dp[i];

    printf("%d\n",ans);
}

int main()
{
    init();
    solve();

    return 0;
}
