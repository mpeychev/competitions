/// Local testing - Segmentation fault (core dumped)
/// http://www.spoj.com/problems/GRASSPLA/ - accepted

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>

#define pb push_back

using namespace std;

const int MAXN = 100100;
const int MAX_LOG = 17;

struct chain {
    int up, sz;
    vector< int > bit;

    void add(int x, bool isNew);

    void initBit() {
        bit.resize(sz + 1);
    }

    int getSum(int idx) {
        idx ++;

        int ret = 0;
        while(idx) {
            ret += bit[idx];
            idx -= (idx & -idx);
        }

        return ret;
    }

    void update(int idx, int val) {
        idx ++;

        int lim = sz;
        while(idx <= lim) {
            bit[idx] += val;
            idx += (idx & -idx);
        }
    }
};

int n, m;
vector< int > g[MAXN];
int level[MAXN], p[MAXN][MAX_LOG];
int tsz[MAXN];
bool heavy[MAXN];

vector< chain > vec;
int inChain[MAXN];
int posInChain[MAXN];

int cnt[MAXN];

void read() {
    int a, b;

    scanf("%d %d", &n, &m);
    for(int i = 1; i < n; i ++) {
        scanf("%d %d", &a, &b);
        g[a].pb(b);
        g[b].pb(a);
    }
}

void chain::add(int x, bool isNew) {
    if(isNew) {
        posInChain[x] = 0;
        sz = 1;
        up = x;
    }
    else {
        posInChain[x] = sz;
        sz ++;
    }
}

chain createChain(int x) {
    chain ret;
    ret.add(x, true);
    return ret;
}

void dfs(int u) {
    tsz[u] = 1;
    for(int i = 0; i < g[u].size(); i ++) {
        int v = g[u][i];
        if(level[v] == -1) {
            level[v] = level[u] + 1;
            p[v][0] = u;
            dfs(v);
            tsz[u] += tsz[v];
        }
    }

    for(int i = 0; i < g[u].size(); i ++) {
        int v = g[u][i];
        if(v != p[u][0] && 2 * tsz[v] > tsz[u] - 1)
            heavy[v] = true;
    }
}

void dfs2(int u) {
    for(int i = 0; i < g[u].size(); i ++) {
        int v = g[u][i];
        if(v != p[u][0]) {
            if(heavy[v]) {
                if(heavy[u]) {
                    inChain[v] = inChain[u];
                    vec[ inChain[u] ].add(v, false);
                }
                else {
                    inChain[v] = vec.size();
                    vec.pb(createChain(v));
                }
            }

            dfs2(v);
        }
    }
}

int lca(int u, int v) {
    if(level[u] > level[v])
        u ^= v ^= u ^= v;

    for(int i = MAX_LOG - 1; i >= 0; i --)
        if(p[v][i] != -1 && level[ p[v][i] ] >= level[u])
            v = p[v][i];

    if(u == v) return u;

    for(int i = MAX_LOG - 1; i >= 0; i --)
        if(p[u][i] != p[v][i])
            u = p[u][i], v = p[v][i];

    return p[u][0];
}

void init() {
    memset(level, -1, sizeof(level));
    memset(p, -1, sizeof(p));
    memset(inChain, -1, sizeof(inChain));

    level[1] = 0;
    heavy[1] = true;
    inChain[1] = 0;
    vec.pb(createChain(1));

    dfs(1);
    dfs2(1);

    for(int i = 0; i < vec.size(); i ++)
        vec[i].initBit();

    for(int i = 1; i < MAX_LOG; i ++)
        for(int j = 1; j <= n; j ++)
            if(p[j][i - 1] != -1)
                p[j][i] = p[ p[j][i - 1] ][i - 1];
}

void answer(int u, int v) {
    if(level[u] > level[v])
        u ^= v ^= u ^= v;

    if(inChain[v] == -1) {
        printf("%d\n", cnt[v]);
        return;
    }

    int ans = vec[ inChain[v] ].getSum(posInChain[v]);

    printf("%d\n", ans);
}

void goUp(int tmp, int lim) {
    while(tmp != lim) {
        if(inChain[tmp] == -1) {
            cnt[tmp] ++;
            tmp = p[tmp][0];
            continue;
        }

        int chainIdx = inChain[tmp];

        if(inChain[tmp] != inChain[lim]) {
            vec[chainIdx].update(0, 1);
            vec[chainIdx].update(posInChain[tmp] + 1, -1);
            tmp = vec[chainIdx].up;
            tmp = p[tmp][0];
            continue;
        }

        vec[chainIdx].update(posInChain[lim] + 1, 1);
        vec[chainIdx].update(posInChain[tmp] + 1, -1);
        break;
    }
}

void plant(int u, int v) {
    int ver = lca(u, v);
    goUp(u, ver);
    goUp(v, ver);
}

void solve() {
    scanf("\n");

    char cmd;
    int a, b;

    for(int i = 0; i < m; i ++) {
        scanf("%c %d %d\n", &cmd, &a, &b);
        if(cmd == 'P') plant(a, b);
        else answer(a, b);
    }
}

int main()
{
    read();
    init();
    solve();

    return 0;
}
