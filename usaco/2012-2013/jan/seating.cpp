#include <iostream>
#include <stdio.h>

using namespace std;

struct node {
    int begin, end, mx;

    node() {}
    node(int _begin, int _end, int _mx): begin(_begin), end(_end), mx(_mx) {}
};

int n, m, lvs;
node tree[1 << 21];
short int st[1 << 21];

void read() {
    scanf("%d %d\n", &n, &m);
}

inline void printTree() {
    for(int i = 1; i < 2 * lvs; i ++) {
        printf("%d: ", i);
        cout << tree[i].begin << " " << tree[i].end << " " << tree[i].mx << " | " << st[i] << endl;
    }
}

inline int max(int a, int b) {
    if(a < b) return b;
    return a;
}

node merge(node left, node right, int len) {
    node ret;
    len >>= 1;

    ret.begin = left.begin;
    if(ret.begin == len) ret.begin += right.begin;

    ret.end = right.end;
    if(ret.end == len) ret.end += left.end;

    ret.mx = max(left.mx, right.mx);
    ret.mx = max(ret.mx, left.end + right.begin);

    return ret;
}

void initTree(int idx, int le, int ri) {
    if(le == ri) {
        if(le < n) tree[idx] = node(1, 1, 1);
        else {
            tree[idx] = node(0, 0, 0);
            st[idx] = 1;
        }

        return;
    }

    int mid = (le + ri) >> 1;

    initTree(idx << 1, le, mid);
    initTree((idx << 1) + 1, mid + 1, ri);

    tree[idx] = merge(tree[idx << 1], tree[(idx << 1) + 1], ri - le + 1);

    if(st[idx << 1] != st[(idx << 1) + 1]) st[idx] = -1;
    else st[idx] = st[idx << 1];
}

void init() {
    lvs = 1;
    while(lvs < n) lvs <<= 1;

    initTree(1, 0, lvs - 1);
}

inline void push(int idx, short int val, int len) {
    len >>= 1;

    st[idx] = val;
    if(!val) tree[idx] = node(len, len, len);
    else tree[idx] = node(0, 0, 0);
}

void update(int idx, int le, int ri, int a, int b, short int val) {
    if(ri < a || b < le)
        return;

    if(a <= le && ri <= b) {
        st[idx] = val;

        if(!val) tree[idx] = node(ri - le + 1, ri - le + 1, ri - le + 1);
        else tree[idx] = node(0, 0, 0);

        return;
    }

    if(st[idx] != -1) {
        push(2 * idx, st[idx], ri - le + 1);
        push(2 * idx + 1, st[idx], ri - le + 1);
        st[idx] = -1;
    }

    int mid = (le + ri) >> 1;

    update(idx << 1, le, mid, a, b, val);
    update((idx << 1) + 1, mid + 1, ri, a, b, val);

    tree[idx] = merge(tree[idx << 1], tree[(idx << 1) + 1], ri - le + 1);

    if(st[idx << 1] != st[(idx << 1) + 1]) st[idx] = -1;
    else st[idx] = st[idx << 1];
}

int findPos(int idx, int le, int ri, int p) {
    if(st[idx] != -1) {
        push(2 * idx, st[idx], ri - le + 1);
        push(2 * idx + 1, st[idx], ri - le + 1);
        st[idx] = -1;
        tree[idx] = merge(tree[idx << 1], tree[(idx << 1) + 1], ri - le + 1);
    }

    if(tree[idx].mx < p)
        return -1;

    if(tree[idx].begin >= p)
        return le;

    int mid = (le + ri) >> 1;

    int getLeft = findPos(idx << 1, le, mid, p);
    if(getLeft != -1) return getLeft;

    if(tree[idx << 1].end + tree[(idx << 1) + 1].begin >= p)
        return mid - tree[idx << 1].end + 1;

    return findPos((idx << 1) + 1, mid + 1, ri, p);
}

void solve() {
    int ans = 0;

    char cmd;
    int p, a, b;

    for(int i = 0; i < m; i ++) {
        scanf("%c", &cmd);
        if(cmd == 'A') {
            scanf("%d\n", &p);
            a = findPos(1, 0, lvs - 1, p);
            if(a != -1) {
//                cout << "ok\n";
                update(1, 0, lvs - 1, a, a + p - 1, 1);
            }
            else {
//                cout << "fail\n";
                ans ++;
            }
        }
        else {
            scanf("%d %d\n", &a, &b);
            a --;
            b --;
            update(1, 0, lvs - 1, a, b, 0);
        }
    }

    cout << ans << endl;
}

int main()
{
    freopen("seating.in", "r", stdin);
    freopen("seating.out", "w", stdout);

    read();
    init();
    solve();

    return 0;
}
