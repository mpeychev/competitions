/*
  Source: usaco - 2001/2002 - feb
  Task: roads
  KeyW: dp in tree
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>

#define pb push_back

using namespace std;

const int MAXN = 150 + 10;
const int nondef = -1;
const int NoTree = 424242;

int n, p;
int a, b;
int prev[MAXN], down[MAXN];
vector<int> g[MAXN];
int dp[MAXN][MAXN][MAXN];

void compute(int back, int cur)
{
    prev[cur] = back;
    for(int i = 0; i < g[cur].size(); i ++)
        if(g[cur][i] != back)
            compute(cur, g[cur][i]);

    down[cur] = 1;
    for(int i = 0; i < g[cur].size(); i ++)
        if(g[cur][i] != back)
            down[cur] += down[ g[cur][i] ];
}

void init()
{
    scanf("%d %d", &n, &p);
    for(int i = 1; i < n; i ++)
    {
        scanf("%d %d", &a, &b);
        g[a].pb(b);
        g[b].pb(a);
    }

    compute(-1, 1);
}

int calc(int root, int sz, int le)
{
    if(le >= g[root].size())
    {
        if(sz) return NoTree;
        return 0;
    }

    if(!sz)
    {
        int cnt = 0;
        for(int i = le; i < g[root].size(); i ++)
            if(g[root][i] != prev[root])
                cnt ++;
        return cnt;
    }

    if(dp[root][sz][le] != nondef) return dp[root][sz][le];
    if(g[root][le] == prev[root])
    {
        dp[root][sz][le] = calc(root, sz, le + 1);
        return dp[root][sz][le];
    }

    int sum = 0;
    for(int i = le; i < g[root].size(); i ++)
        if(g[root][i] != prev[root])
            sum += down[ g[root][i] ];

    if(sum < sz)
    {
        dp[root][sz][le] = NoTree;
        return dp[root][sz][le];
    }

    if(sum == sz)
    {
        dp[root][sz][le] = 0;
        return dp[root][sz][le];
    }

    if(sum == sz - 1)
    {
        dp[root][sz][le] = 1;
        return dp[root][sz][le];
    }

    int ret = NoTree;
    ret = 1 + calc(root, sz, le + 1);

    for(int t = 1; t <= sz; t ++)
    {
        int tmp = calc(g[root][le], t - 1, 0) + calc(root, sz - t, le + 1);
        if(tmp < ret) ret = tmp;
    }

    dp[root][sz][le] = ret;
    return ret;
}

void solve()
{
    memset(dp, nondef, sizeof(dp));

    int ans = NoTree;
    for(int i = 1; i <= n; i ++)
    {
        int tmp = (i != 1) + calc(i, p - 1, 0);
        if(tmp < ans) ans = tmp;
    }
    printf("%d\n", ans);
}

int main()
{
    init();
    solve();

    return 0;
}
