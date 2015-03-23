#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

typedef long long LL;

const LL INF = 1LL << 60;

int n;
vector<int> p;
LL dp[1024][1024][2];

void read() {
    scanf("%d", &n);
    p.resize(n + 1);
    for(int i = 0; i < n; i ++)
        scanf("%d", &p[i]);
    p[n] = 0;
}

LL calc(int le, int ri, int dir) {
    if(dp[le][ri][dir] != -1)
        return dp[le][ri][dir];

    if(le == 0 && ri == n)
        return dp[le][ri][dir] = 0;

    LL dist;
    LL ret1 = INF;
    LL ret2 = INF;

    if(ri < n) {
        if(dir) dist = p[ri + 1] - p[ri];
        else dist = p[ri + 1] - p[le];

        ret1 = (n - (ri - le)) * dist + calc(le, ri + 1, true);
    }

    if(le > 0) {
        if(!dir) dist = p[le] - p[le - 1];
        else dist = p[ri] - p[le - 1];

        ret2 = (n - (ri - le)) * dist + calc(le - 1, ri, false);
    }

    dp[le][ri][dir] = min(ret1, ret2);
    return dp[le][ri][dir];
}

void solve() {
    sort(p.begin(), p.end());
    memset(dp, -1, sizeof(dp));

    int pos = 0;
    for(int i = 0; i <= n; i ++)
        if(p[i] == 0) {
            pos = i;
            break;
        }

    cout << calc(pos, pos, 0) << endl;
}

int main()
{
    freopen("cowrun.in", "r", stdin);
    freopen("cowrun.out", "w", stdout);

    read();
    solve();

    return 0;
}
