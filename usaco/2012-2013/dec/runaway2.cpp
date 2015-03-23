#include <iostream>
#include <stdio.h>
#include <vector>

#define pb push_back

using namespace std;

typedef long long LL;

const int MAXN = 1 << 18;
const LL INF = 1LL << 62;

int n, t[MAXN];
vector<int> nxt[MAXN];
vector<LL> tree[2 * MAXN];
int vec[MAXN], sz;
LL l, d[MAXN], up[MAXN];
int lvs;
int ans[MAXN];

void read() {
    int father;

    scanf("%d %lld", &n, &l);
    for(int i = 2; i <= n; i ++) {
        scanf("%d %lld", &father, &up[i]);
        nxt[father].pb(i);
    }
}

void dfs(int cur) {
    vec[sz ++] = cur;
    t[cur] ++;
    for(int i = 0; i < nxt[cur].size(); i ++) {
        d[ nxt[cur][i] ] = d[cur] + up[ nxt[cur][i] ];
        dfs(nxt[cur][i]);
        t[cur] += t[ nxt[cur][i] ];
    }
}

void init(int idx) {
    if(idx >= lvs) return;

    init(2 * idx);
    init(2 * idx + 1);

    int x = 0, y = 0;
    int leIdx = 2 * idx, riIdx = 2 * idx + 1;
    while(x < tree[leIdx].size() || y < tree[riIdx].size()) {
        LL val1 = INF;
        LL val2 = INF;

        if(x < tree[leIdx].size()) val1 = tree[leIdx][x];
        if(y < tree[riIdx].size()) val2 = tree[riIdx][y];

        if(val1 <= val2) tree[idx].pb(tree[leIdx][x ++]);
        else tree[idx].pb(tree[riIdx][y ++]);
    }
}

int get(int idx, int ri, LL lim) {
    if(ri == tree[idx].size() - 1) {
        int left = 0, right = tree[idx].size() - 1, mid;
        int ret = 0;
        while(left <= right) {
            mid = (left + right) >> 1;
            if(tree[idx][mid] <= lim) {
                ret = mid + 1;
                left = mid + 1;
            }
            else right = mid - 1;
        }
        return ret;
    }

    int len = tree[2 * idx].size();
    if(ri < len) return get(2 * idx, ri, lim);

    return get(2 * idx, len - 1, lim) + get(2 * idx + 1, ri - len, lim);
}

int calc(int le, int ri, LL lim) {
    if(!le) return get(1, ri, lim);
    return get(1, ri, lim) - get(1, le - 1, lim);
}

void solve() {
    dfs(1);

    lvs = 1;
    while(lvs < n) lvs <<= 1;

    for(int i = 0; i < n; i ++)
        tree[i + lvs].pb(d[ vec[i] ]);

    init(1);

    for(int i = 0; i < sz; i ++)
        ans[ vec[i] ] = calc(i, i + t[ vec[i] ] - 1, d[ vec[i] ] + l);

    for(int i = 1; i <= n; i ++)
        printf("%d\n", ans[i]);
}

int main()
{
    read();
    solve();

    return 0;
}
