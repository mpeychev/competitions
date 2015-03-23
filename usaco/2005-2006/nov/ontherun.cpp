#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

typedef long long LL;

int n, l, p[1 << 10];
bool used[1 << 20];
LL dp[1005][1005][2];

void read() {
    scanf("%d %d", &n, &l);
    for(int i = 0; i < n; i ++) {
        scanf("%d", &p[i]);
        used[ p[i] ] = true;
    }
}

LL go(int le, int ri, bool pos) {
    if(dp[le][ri][pos] != -1)
        return dp[le][ri][pos];

    if(le == 0 && ri == n - 1)
        return dp[le][ri][pos] = 0;

    LL ret = 1LL << 62;
    if(!pos) {
        if(le > 0) ret = min(ret, (n - ri + le - 1) * (p[le] - p[le - 1]) + go(le - 1, ri, 0));
        if(ri != n - 1) ret = min(ret, (n - ri + le - 1) * (p[ri + 1] - p[le]) + go(le, ri + 1, 1));
    }
    else {
        if(le > 0) ret = min(ret, (n - ri + le - 1) * (p[ri] - p[le - 1]) + go(le - 1, ri, 0));
        if(ri != n - 1) ret = min(ret, (n - ri + le - 1) * (p[ri + 1] - p[ri]) + go(le, ri + 1, 1));
    }

    return dp[le][ri][pos] = ret;
}

void solve() {
    if(!used[l]) p[n ++] = l;
    sort(p, p + n);

    int idx;
    for(int i = 0; i < n; i ++)
        if(p[i] == l) {
            idx = i;
            break;
        }

    memset(dp, -1, sizeof(dp));
    cout << go(idx, idx, 0) << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
