#include <stdio.h>
#include <iostream>

using namespace std;

const int MAXN = 1 << 18;

struct node {
    bool begin, end;
    int len;
    int left, right, ans;

    node() {}
    node(bool _b, bool _e, int _len, int _le, int _ri, int _a):
        begin(_b), end(_e), len(_len), left(_le), right(_ri), ans(_a) {}
};

int n, q, x;
node tree[2 * MAXN];
int lvs;

void read() {
    scanf("%d %d", &n, &q);
}

node merge(node le, node ri) {
    if(!ri.len)
        return le;

    node ret;

    ret.begin = le.begin;
    ret.end = ri.end;
    ret.len = le.len + ri.len;

    ret.left = le.left;
    if(le.left == le.len && le.end != ri.begin) ret.left += ri.left;

    ret.right = ri.right;
    if(ri.right == ri.len && le.end != ri.begin) ret.right += le.right;

    ret.ans = max(le.ans, ri.ans);
    if(le.end != ri.begin) ret.ans = max(ret.ans, le.right + ri.left);

    return ret;
}

void init(int idx) {
    if(idx >= lvs) return;
    init(idx << 1);
    init((idx << 1) + 1);
    tree[idx] = merge(tree[idx << 1], tree[(idx << 1) + 1]);
}

void update(int idx) {
    tree[idx].begin ^= 1;
    tree[idx].end ^= 1;
    idx >>= 1;
    while(idx) {
        tree[idx] = merge(tree[(idx << 1)], tree[(idx << 1) + 1]);
        idx >>= 1;
    }
}

void solve() {
    lvs = 1;
    while(lvs < n) lvs <<= 1;

    for(int i = 0; i < n; i ++)
        tree[lvs + i] = node(0, 0, 1, 1, 1, 1);
    for(int i = n; i < lvs; i ++)
        tree[lvs + i] = node(0, 0, 0, 0, 0, 0);

    init(1);

    for(int i = 0; i < q; i ++) {
        scanf("%d", &x);
        x --;
        update(x + lvs);
        printf("%d\n", tree[1].ans);
    }
}

int main()
{
    read();
    solve();

    return 0;
}
