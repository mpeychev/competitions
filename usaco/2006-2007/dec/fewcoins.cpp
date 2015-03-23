#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 1 << 7;
const int INF = 1 << 25;

int n, t, d, ans;
int v[MAXN], c[MAXN];
int dp1[30005], dp2[30005][105];

void read() {
    scanf("%d %d", &n, &t);
    for(int i = 0; i < n; i ++)
        scanf("%d", &v[i]);
    for(int i = 0; i < n; i ++)
        scanf("%d", &c[i]);
}

int gcd(int a, int b) {
    while(b) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int calc(int x, int y) {
    if(dp2[x][y] != -1)
        return dp2[x][y];

    if(!x) return dp2[x][y] = 0;

    if(!y) {
        if(x % v[y] != 0 || x / v[y] > c[y]) return dp2[x][y] = INF;
        return dp2[x][y] = x / v[y];
    }

    int ret = INF;
    for(int i = 0; i <= c[y] && i * v[y] <= x; i ++)
        ret = min(ret, i + calc(x - i * v[y], y - 1));

    return dp2[x][y] = ret;
}

void solve() {
    d = v[0];
    for(int i = 1; i < n; i ++)
        d = gcd(d, v[i]);

    if(t % d != 0) {
        printf("-1\n");
        return;
    }

    for(int i = 1; i <= 10000; i ++)
        dp1[i] = INF;

    for(int i = 0; i < n; i ++) {
        for(int j = 0; j + v[i] <= 10000; j ++)
            dp1[ j + v[i] ] = min(dp1[ j + v[i] ], dp1[j] + 1);
    }

    memset(dp2, -1, sizeof(dp2));

    ans = INF;
    for(int i = t; i <= t + 250; i ++) {
        int b1 = calc(i, n - 1);
        int b2 = dp1[i - t];
        if(b1 < INF && b2 < INF && b1 + b2 < ans) ans = b1 + b2;
    }

    cout << ans << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
