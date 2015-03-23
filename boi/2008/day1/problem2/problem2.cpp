#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

const int MAXN = 1 << 8;
const int MAXK = 1 << 5;
const int INF = 1 << 30;

int n, k, p[MAXN];
int sum[MAXN];
int calc[MAXN][MAXN];
int dp[MAXN][MAXK];

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &p[i]);
}

int f(int x, int y) {
    if(dp[x][y] != -1)
        return dp[x][y];

    if(x == 1)
        return dp[x][y] = 0;

    if(!y)
        return dp[x][y] = (x - 1) * p[x] - sum[x - 1];

    int ret = INF;
    for(int i = 1; i < x; i ++)
        ret = min(ret, calc[i][x] + f(i, y - 1));

    return dp[x][y] = ret;
}

void solve() {
    for(int i = 1; i <= n; i ++)
        sum[i] = sum[i - 1] + p[i];

    for(int i = 1; i <= n; i ++)
        for(int j = i; j <= n; j ++) {
            int tmp = 0;
            for(int h = i + 1; h < j; h ++)
                if(p[h] - p[i] < p[j] - p[h]) tmp += (p[h] - p[i]);
                else tmp += (p[j] - p[h]);
            calc[i][j] = tmp;
        }

    memset(dp, -1, sizeof(dp));

    int ans = INF;
    for(int i = 1; i <= n; i ++)
        ans = min(ans, f(i, k - 1) + sum[n] - sum[i] - (n - i) * p[i]);

    printf("%d\n", ans);
}

int main()
{
    read();
    solve();

    return 0;
}
