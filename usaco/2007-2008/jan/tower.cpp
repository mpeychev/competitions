/*
  Source: usaco - 2007/2008 - jan
  Task: tower
  KeyW: dp in tree
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>

#define pb push_back

using namespace std;

const int MAXN = 10000 + 10;

int n;
int a, b;
vector<int> g[MAXN];
int dp[MAXN][2][2];

void read()
{
    scanf("%d", &n);
    for(int i = 1; i < n; i ++)
    {
        scanf("%d %d", &a, &b);
        g[a].pb(b);
        g[b].pb(a);
    }
}

int dfs(int cur, int prev, bool flCur, bool flPrev)
{
    if(dp[cur][flCur][flPrev] != -1) return dp[cur][flCur][flPrev];

    int ret;

    if(flCur || (!flCur && flPrev))
    {
        ret = flCur;

        for(int i = 0; i < g[cur].size(); i ++)
            if(g[cur][i] != prev)
                ret += min(dfs(g[cur][i], cur, 0, flCur), dfs(g[cur][i], cur, 1, flCur));

        dp[cur][flCur][flPrev] = ret;
        return ret;
    }

    vector<int> tower0;
    vector<int> tower1;

    int sumOpt = 0;
    bool goOpt = false;

    for(int i = 0; i < g[cur].size(); i ++)
        if(g[cur][i] != prev)
        {
            int t0 = dfs(g[cur][i], cur, 0, 0);
            int t1 = dfs(g[cur][i], cur, 1, 0);

            tower0.pb(t0);
            tower1.pb(t1);

            if(t1 <= t0)
            {
                goOpt = true;
                sumOpt += t1;
            }
            else sumOpt += t0;
        }

    if(!tower0.size())
    {
        dp[cur][flCur][flPrev] = MAXN;
        return MAXN;
    }

    if(goOpt)
    {
        dp[cur][flCur][flPrev] = sumOpt;
        return sumOpt;
    }

    ret = MAXN;
    for(int i = 0; i < tower0.size(); i ++)
        ret = min(ret, sumOpt - tower0[i] + tower1[i]);

    dp[cur][flCur][flPrev] = ret;
    return ret;
}

int main()
{
    read();
    memset(dp, -1, sizeof(dp));
    printf("%d\n", min(dfs(1, 0, 0, 0), dfs(1, 0, 1, 0)));

    return 0;
}
