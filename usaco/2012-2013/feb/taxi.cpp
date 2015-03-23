#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

typedef long long LL;

const int MAXN = 100100;

int n;
LL m, a[MAXN], b[MAXN];
LL ans;

inline LL myAbs(LL x) {
    if(x < 0) return -x;
    return x;
}

void read() {
    scanf("%d %lld", &n, &m);
    for(int i = 0; i < n; i ++) {
        scanf("%lld %lld", &a[i], &b[i]);
        ans += myAbs(a[i] - b[i]);
    }
}

void solve() {
    b[n] = 0;
    a[n] = m;

    n ++;

    sort(a, a + n);
    sort(b, b + n);

    for(int i = 0; i < n; i ++)
        ans += abs(a[i] - b[i]);

    printf("%lld\n", ans);
}

int main()
{
    freopen("taxi.in", "r", stdin);
    freopen("taxi.out", "w", stdout);

    read();
    solve();

    return 0;
}
