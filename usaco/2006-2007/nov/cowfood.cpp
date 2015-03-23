/*
  Source: usaco - 2006/2007 - nov
  Task: cowfood
  KeyW: dp + bit mask
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>

#define pb push_back

using namespace std;

const int MOD = 100000000;

int m, n;
int grid[16][16];
int sum[16];

vector< int > r[16];
vector< int > t[16][500];

int dp[150][500], cpyDp[150][500];
int ans;

inline int get(int mask, int pos) { return (mask >> pos) & 1; }

inline int cnt(int mask)
{
    int ret = 0;
    while(mask)
    {
        ret += (mask & 1);
        mask >>= 1;
    }
    return ret;
}

void read()
{
    scanf("%d %d", &m, &n);
    for(int i = 0; i < m; i ++)
    {
        if(i) sum[i] = sum[i - 1];
        for(int j = 0; j < n; j ++)
        {
            scanf("%d", &grid[i][j]);
            sum[i] += grid[i][j];
        }
    }
}

bool checkRow(int row, int mask)
{
    for(int i = 0; i < n; i ++)
    {
        if(get(mask, i) && !grid[row][i]) return false;
        if(i && get(mask, i) && get(mask, i - 1)) return false;
    }
    return true;
}

bool valid(int mask1, int mask2)
{
    for(int i = 0; i < n; i ++)
        if(get(mask1, i) && get(mask2, i))
            return false;
    return true;
}

void init()
{
    for(int i = 0; i < m; i ++)
        for(int j = 0; j < (1 << n); j ++)
            if(checkRow(i, j))
                r[i].pb(j);

    for(int i = 1; i < m; i ++)
        for(int j = 0; j < r[i].size(); j ++)
            for(int k = 0; k < r[i - 1].size(); k ++)
                if(valid(r[i][j], r[i - 1][k]))
                    t[i][j].pb(k);
}

void solve()
{
    for(int i = 0; i < r[0].size(); i ++)
    {
        dp[cnt(r[0][i])][i] = 1;
        ans ++;
    }

    for(int i = 1; i < m; i ++)
    {
        memcpy(cpyDp, dp, sizeof(dp));
        memset(dp, 0, sizeof(dp));

        for(int j = 0; j <= sum[i]; j ++)
            for(int k = 0; k < r[i].size(); k ++)
                if(j - cnt(r[i][k]) >= 0)
                    for(int h = 0; h < t[i][k].size(); h ++)
                        dp[j][k] = (dp[j][k] + cpyDp[j - cnt(r[i][k])][ t[i][k][h] ]) % MOD;

        for(int j = 1; j <= sum[i]; j ++)
            for(int k = 1; k < r[i].size(); k ++)
                ans = (ans + dp[j][k]) % MOD;
    }

    printf("%d\n",ans);
}

int main()
{
    read();
    init();
    solve();

    return 0;
}
