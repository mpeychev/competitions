#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string.h>

using namespace std;

typedef long long LL;

int n, s[16], k;
LL dp[1 << 16][16];

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i ++)
        scanf("%d", &s[i]);
}

LL get(int mask, int idx) {
    if(dp[mask][idx] != -1)
        return dp[mask][idx];

    if(__builtin_popcount(mask) == n)
        return dp[mask][idx] = 1LL;

    LL ret = 0;
    for(int i = 0; i < n; i ++)
        if(!((mask >> i) & 1) && fabs(s[i] - s[idx]) > k)
            ret += get(mask | (1 << i), i);

    return dp[mask][idx] = ret;
}

void solve() {
    memset(dp, -1, sizeof(dp));
    LL ans = 0;
    for(int i = 0; i < n; i ++)
        ans += get(1 << i, i);
    printf("%lld\n", ans);
}

int main()
{
    read();
    solve();

    return 0;
}
