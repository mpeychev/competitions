/*
  Source: usaco - 2006/2007 - nov
  Task: plank
  KeyW:
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

typedef long long LL;

const int MAXN = 1024;
const LL INF = 1LL << 60;

int n;
int m[MAXN];
int sum[MAXN];
LL dp[MAXN][MAXN];
int idx[MAXN][MAXN];

void init()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &m[i]);

    sort(m + 1, m + n + 1);

    for(int i = 1; i <= n; i ++)
        sum[i] = sum[i - 1] + m[i];

    for(int i = 1; i <= n; i ++)
        cout << m[i] << " ";
    cout << endl;

    for(int i = 1; i <= n; i ++)
        cout << sum[i] << " ";
    cout << endl;

    memset(dp, -1, sizeof(dp));
    memset(idx, -1, sizeof(idx));
}

LL f(int l, int r)
{
    if(l == r) return 0;
    if(l + 1 == r) return m[l] + m[r];
    if(dp[l][r] != -1) return dp[l][r];

    LL ret = INF;
    int id = -1;

    for(int i = l + 1; i < r; i ++)
    {
        LL tmp = sum[r] - sum[l - 1] + f(l, i) + f(i + 1, r);
        if(ret > tmp)
        {
            ret = tmp;
            id = i;
        }
    }

    dp[l][r] = ret;
    idx[l][r] = id;
    //cout << l << " " << r << " " << id << " " << sum[id] - sum[l - 1] << " " << sum[r] - sum[id] << endl;
    return ret;
}

int main()
{
    init();
    cout << f(1, n) << endl;

    for(int i = 1; i <= n; i ++) cout << dp[1][i] << " ";
    cout << endl;
    cout << endl;

    for(int i = 1; i <= n; i ++)
    {
        for(int j = 1; j <= n; j ++) cout << idx[i][j] << " ";
        cout << endl;
    }

    return 0;
}
