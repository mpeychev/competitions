#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

typedef long long LL;

const int MAXN = 1 << 18;

struct el {
    int idx;
    LL dist;
    short int qtype;

    el() {}
    el(int _idx, LL _dist, short int _qtype): idx(_idx), dist(_dist), qtype(_qtype) {}
};

int n, t[MAXN];
vector<int> nxt[MAXN];
vector< el > events;
int vec[MAXN], sz;
LL l, d[MAXN], up[MAXN];
int ans[MAXN], tree[MAXN];

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

bool cmp(el a, el b) {
    if(a.dist < b.dist) return true;
    if(a.dist > b.dist) return false;
    return a.qtype < b.qtype;
}

void add(int idx) {
    while(idx <= n) {
        tree[idx] ++;
        idx += (idx & -idx);
    }
}

int get(int idx) {
    int ret = 0;
    while(idx) {
        ret += tree[idx];
        idx -= (idx & -idx);
    }
    return ret;
}

void solve() {
    sz = 1;
    dfs(1);

    for(int i = 1; i <= n; i ++) {
        events.pb(el(i, d[ vec[i] ], 0));
        events.pb(el(i, d[ vec[i] ] + l, 1));
    }

    sort(events.begin(), events.end(), cmp);

    for(int i = 0; i < events.size(); i ++)
        if(!events[i].qtype) add(events[i].idx);
        else ans[ vec[ events[i].idx ] ] = get(events[i].idx + t[ vec[ events[i].idx ] ] - 1) - get(events[i].idx - 1);

    for(int i = 1; i <= n; i ++)
        printf("%d\n", ans[i]);
}

int main()
{
    freopen("runaway.in", "r", stdin);
    freopen("runaway.out", "w", stdout);

    read();
    solve();

    return 0;
}
