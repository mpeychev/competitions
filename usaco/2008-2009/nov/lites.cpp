#include <stdio.h>
#include <iostream>

using namespace std;

struct node {
    bool fl;
    int full, empty;
};

int n, m;
node t[1 << 18];
int lvs;

void initTree(int idx, int le, int ri) {
    t[idx].fl = false;
    t[idx].full = 0;
    t[idx].empty = ri - le + 1;

    if(le != ri) {
        int mid = (le + ri) >> 1;
        initTree(idx << 1, le, mid);
        initTree((idx << 1) + 1, mid + 1, ri);
    }
}

void init() {
    scanf("%d %d", &n, &m);

    lvs = 1;
    while(lvs < n) lvs <<= 1;

    initTree(1, 0, lvs - 1);
}

node merge(node left, node right, bool xr) {
    node ret;
    ret.fl = xr;
    ret.empty = left.empty + right.empty;
    ret.full = left.full + right.full;
    return ret;
}

void update(int idx, int le, int ri, int a, int b) {
    if(ri < a || b < le)
        return;

    if(a <= le && ri <= b) {
        t[idx].fl ^= 1;
        return;
    }

    int mid = (le + ri) >> 1;
    update(idx << 1, le, mid, a, b);
    update((idx << 1) + 1, mid + 1, ri, a, b);

    node left = t[idx << 1];
    node right = t[(idx << 1) + 1];

    if(t[idx << 1].fl)
        swap(left.full, left.empty);
    if(t[(idx << 1) + 1].fl)
        swap(right.full, right.empty);

    t[idx] = merge(left, right, t[idx].fl);
}

int query(int idx, int le, int ri, int a, int b, bool xr) {
    if(ri < a || b < le)
        return 0;

    if(a <= le && ri <= b) {
        if(t[idx].fl ^ xr) return t[idx].empty;
        return t[idx].full;
    }

    int mid = (le + ri) >> 1;
    return query(idx << 1, le, mid, a, b, xr ^ t[idx].fl) +
            query((idx << 1) + 1, mid + 1, ri, a, b, xr ^ t[idx].fl);
}

void solve() {
    int cmd, a, b;
    for(int i = 0; i < m; i ++) {
        scanf("%d %d %d", &cmd, &a, &b);
        a --; b --;
        if(!cmd) update(1, 0, lvs - 1, a, b);
        else printf("%d\n", query(1, 0, lvs - 1, a, b, false));
    }
}

int main()
{
    init();
    solve();

    return 0;
}
