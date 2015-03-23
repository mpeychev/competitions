#include <stdio.h>
#include <iostream>

using namespace std;

typedef long long LL;

const int MAXN = 1 << 17;
const LL INF = 10000000000000LL;

int n, m;
int t[MAXN], f[MAXN];
LL event[MAXN];

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &t[i]);
    for(int i = 1; i <= m; i ++)
        scanf("%d", &f[i]);
}

inline LL max(LL x, LL y) {
    if(x < y) return y;
    return x;
}

LL findDelta(int carIdx) {
    LL tmp = event[2];
    LL ret = 0;
    for(int i = 2; i <= n; i ++) {
        tmp += t[i - 1] * f[carIdx];
        ret = max(ret, event[i + 1] - tmp);
    }
    return ret;
}

void solve() {
    event[1] = 0;
    for(int i = 2; i <= n + 1; i ++)
        event[i] = event[i - 1] + t[i - 1] * f[1];

    for(int i = 2; i <= m; i ++) {
        LL delta = findDelta(i);
        event[1] = event[2] + delta;
        for(int j = 2; j <= n + 1; j ++)
            event[j] = event[j - 1] + t[j - 1] * f[i];
    }

    printf("%lld\n", event[n + 1]);
}

int main()
{
    read();
    solve();

    return 0;
}
