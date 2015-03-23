#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 1515;

int n, ma3x[MAXN][MAXN];
int dp[MAXN][MAXN];

void read() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            scanf("%d", &ma3x[i][j]);
}

int calc(int le, int ri) {
    int &ret = dp[le][ri];

    if(ret != -1)
        return ret;

    int nxt = max(le, ri) + 1;
    if(nxt == n + 1) {
        ret = 0;
        return ret;
    }

    ret = min(ma3x[nxt][le] + calc(nxt, ri), ma3x[ri][nxt] + calc(le, nxt));
    return ret;
}

void solve() {
    memset(dp, -1, sizeof(dp));
    cout << calc(1, 1) << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
