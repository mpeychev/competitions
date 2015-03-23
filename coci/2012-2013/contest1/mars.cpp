#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef long long LL;
const LL INF = 1LL << 60;

struct Segment {
    int left, right;

    Segment() {}
    Segment(int _left, int _right): left(_left), right(_right) {}
};

const int MAXN = 1 << 9;

inline void swap(int &x, int &y) {
    x ^= y ^= x ^= y;
}

inline LL min(LL x, LL y) {
    if(x < y) return x;
    return y;
}

int n, k;
int ma3x[MAXN][MAXN];

int cache[MAXN][MAXN];
Segment seg[2 * MAXN];

LL dp[MAXN][MAXN], best[MAXN][MAXN];

void read() {
    scanf("%d", &k);
    n = 1 << k;
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
            scanf("%d", &ma3x[i][j]);
}

inline int lca(int x, int y) {
    if(x > y) swap(x,y);
    if(cache[x][y]) return cache[x][y];
    int _x = x, _y = y;
    x += n, y += n;
    while(x != y)
        x >>= 1, y >>= 1;
    return cache[_x][_y] = x;
}

void init(int idx, int le, int ri) {
    seg[idx] = Segment(le, ri);

    if(le == ri) return;

    int mid = (le + ri) >> 1;
    init(2 * idx, le, mid);
    init(2 * idx + 1, mid + 1, ri);
}

inline bool inside(int leaf, int idx) {
    return (seg[idx].left <= leaf && leaf <= seg[idx].right);
}

LL calcDp(int le, int ri);
LL calcBest(int a, int ri);

LL calcBest(int a, int ri) {
    if(best[a][ri] != -1)
        return best[a][ri];

    int v = lca(a, ri);
    v = 4 * v + 2;

    if(inside(ri, v)) v ++;

    LL ret = INF;
    for(int b = seg[v].left; b <= seg[v].right; b ++)
        ret = min(ret, ma3x[a][b] + calcDp(b, ri));

    return best[a][ri] = ret;
}

LL calcDp(int le, int ri) {
    if(le > ri) swap(le, ri);

    if(dp[le][ri] != -1)
        return dp[le][ri];

    if(le == ri) return dp[le][ri] = 0;
    if(le % 2 == 0 && le + 1 == ri) return dp[le][ri] = ma3x[le][ri];

    int v = lca(le, ri);
    v <<= 2;
    if(inside(le, v)) v ++;

    LL ret = INF;
    for(int a = seg[v].left; a <= seg[v].right; a ++)
        ret = min(ret, calcDp(le, a) + calcBest(a, ri));

    return dp[le][ri] = ret;
}

void solve() {
    init(1, 0, n - 1);
    memset(dp, -1, sizeof(dp));
    memset(best, -1, sizeof(best));

    LL ans = INF;
    for(int i = 0; i < (n >> 1); i ++)
        for(int j = (n >> 1); j < n; j ++)
            ans = min(ans, calcDp(i, j));

    cout << ans << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
