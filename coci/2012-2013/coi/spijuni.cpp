#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

struct el {
    int a, b, c;

    el() {}
    el(int _a, int _b, int _c): a(_a), b(_b), c(_c) {}
};

int n, sz;
el g[1024 * 1024];
int rt[1024];
int ans;

void build() {
    int x;

    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++) {
            scanf("%d", &x);
            if(i < j) g[sz ++] = el(i, j, x);
        }

    for(int i = 1; i <= n; i ++) {
        scanf("%d", &x);
        g[sz ++] = el(0, i, x);
    }
}

bool cmp(el x, el y) {
    return x.c < y.c;
}

int root(int v) {
    int ret = v, up;
    while(rt[ret] != ret) ret = rt[ret];
    while(v != ret) {
        up = rt[v];
        rt[v] = ret;
        v = up;
    }
    return ret;
}

void solve() {
    sort(g, g + sz, cmp);

    for(int i = 0; i <= n; i ++)
        rt[i] = i;

    for(int i = 0; i < sz; i ++) {
        int r1 = root(g[i].a);
        int r2 = root(g[i].b);
        if(r1 != r2) {
            ans += g[i].c;
            rt[r1] = r2;
        }
    }

    cout << ans << endl;
}

int main()
{
    build();
    solve();

    return 0;
}
