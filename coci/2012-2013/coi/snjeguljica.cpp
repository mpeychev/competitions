#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 262144;

struct node {
    int minVal, maxVal;

    node() {}
    node(int _minVal, int _maxVal): minVal(_minVal), maxVal(_maxVal) {}
};

int n, m, lvs;
int vec[MAXN];
node tree[2 * MAXN];

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i ++) {
        scanf("%d", &vec[i]);
        vec[i] --;
    }
}

inline int min(int x, int y) {
    if(x < y) return x;
    return y;
}

inline int max(int x, int y) {
    if(x < y) return y;
    return x;
}

node merge(node le, node ri) {
    return node(min(le.minVal, ri.minVal), max(le.maxVal, ri.maxVal));
}

void init(int idx) {
    if(idx >= lvs) return;

    init(idx << 1);
    init((idx << 1) + 1);

    tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
}

void update(int idx1, int idx2) {
    idx1 >>= 1, idx2 >>= 1;
    while(idx1 && idx2) {
        tree[idx1] = merge(tree[2 * idx1], tree[2 * idx1 + 1]);
        if(idx2 != idx1) tree[idx2] = merge(tree[2 * idx2], tree[2 * idx2 + 1]);
        idx1 >>= 1, idx2 >>= 1;
    }
}

node rmq(int idx, int le, int ri, int a, int b) {
    if(a <= le && ri <= b)
        return tree[idx];

    if(b < le || ri < a)
        return node(MAXN, -1);

    int mid = (le + ri) >> 1;
    node r1 = rmq(2 * idx, le, mid, a, b);
    node r2 = rmq(2 * idx + 1, mid + 1, ri, a, b);
    return merge(r1, r2);
}

void printTree() {
    for(int i = 1; i < 2 * lvs; i ++)
        printf("%d: %d %d\n", i, tree[i].minVal, tree[i].maxVal);
}

void solve() {
    lvs = 1;
    while(lvs < n) lvs <<= 1;

    for(int i = 0; i < n; i ++)
        tree[ lvs + vec[i] ] = node(i, i);
    for(int i = n; i < lvs; i ++)
        tree[ lvs + i ] = node(MAXN, -1);

    init(1);

    short int cmd;
    int x, y;
    for( ; m; m --) {
        scanf("%d %d %d", &cmd, &x, &y);
        x --, y --;
        if(cmd == 1) {
            swap(vec[x], vec[y]);
            tree[ lvs + vec[x] ] = node(x, x);
            tree[ lvs + vec[y] ] = node(y, y);
            update(lvs + vec[x], lvs + vec[y]);
        }
        else {
            node cur = rmq(1, 0, lvs - 1, x, y);
            if(cur.maxVal - cur.minVal == y - x) printf("YES\n");
            else printf("NO\n");
        }
    }
}

int main()
{
    read();
    solve();

    return 0;
}
