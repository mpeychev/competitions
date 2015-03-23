#include <stdio.h>
#include <iostream>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;
typedef long long LL;

const int MAXN = 1 << 16;
const LL INF = 1LL << 60;

int n;
PII p[MAXN];
PII data[MAXN];
int sz;
LL dp[MAXN];

void read() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%d %d", &p[i].x, &p[i].y);
}

inline LL min(LL a, LL b) {
    if(a < b) return a;
    return b;
}

void solve() {
    sort(p, p + n);

    data[sz ++] = p[0];
    for(int i = 1; i < n; i ++) {
        while(sz >= 1 && data[sz - 1].y <= p[i].y)
            sz --;
        data[sz ++] = p[i];
    }

    for(int i = sz; i >= 1; i --)
        data[i] = data[i - 1];

    dp[0] = 0;
    for(int i = 1; i <= sz; i ++) {
        dp[i] = INF;
        for(int j = 1; j <= i; j ++)
            dp[i] = min(dp[i], (LL)data[i].x * (LL)data[j].y + dp[j - 1]);
    }

    printf("%lld\n", dp[sz]);
}

int main()
{
    read();
    solve();

    return 0;
}
