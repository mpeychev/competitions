#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

struct node {
    int num, prior;
    int sz, mn;
    bool rev;

    node *left, *right;
};

typedef node* pnode;

const int INF = 1 << 30;

int n, m;
pnode treap;

pnode createNode(int x) {
    pnode ret;
    ret = new node;
    ret->num = ret->mn = x;
    ret->prior = rand();
    ret->sz = 1;
    ret->rev = false;
    ret->left = ret->right = NULL;
    return ret;
}

inline int getSz(pnode t) {
    if(!t) return 0;
    return t->sz;
}

inline int getMin(pnode t) {
    if(!t) return INF;
    return t->mn;
}

inline void fix(pnode &t) {
    t->sz = getSz(t->left) + 1 + getSz(t->right);
    t->mn = min(t->num, min(getMin(t->left), getMin(t->right)));
}

inline void push(pnode &t) {
    if(t && t->rev) {
        t->rev = false;
        swap(t->left, t->right);
        if(t->left) t->left->rev ^= true;
        if(t->right) t->right->rev ^= true;
    }
}

void split(pnode t, pnode &le, pnode &ri, int key) {
    if(!t) {
        le = ri = NULL;
        return;
    }

    push(t);

    int tmp = getSz(t->left) + 1;

    if(tmp <= key) {
        split(t->right, t->right, ri, key - tmp);
        le = t;
        fix(le);
    }
    else {
        split(t->left, le, t->left, key);
        ri = t;
        fix(ri);
    }
}

void merge(pnode le, pnode ri, pnode &t) {
    push(le);
    push(ri);

    if(!le) {
        t = ri;
        return;
    }

    if(!ri) {
        t = le;
        return;
    }

    if(le->prior < ri->prior) {
        merge(le->right, ri, le->right);
        t = le;
    }
    else {
        merge(le, ri->left, ri->left);
        t = ri;
    }

    fix(t);
}

void read() {
    scanf("%d %d", &n, &m);
}

void build() {
    int a;

    scanf("%d", &a);
    treap = createNode(a);
    for(int i = 1; i < n; i ++) {
        scanf("%d", &a);
        pnode ins;
        ins = createNode(a);
        merge(treap, ins, treap);
    }
}

void solve() {
    for(int i = 0; i < m; i ++) {
        pnode a, b, c;

        int cmd, l, r;
        scanf("%d %d %d", &cmd, &l, &r);
        if(cmd == 1) {
            split(treap, a, c, r);
            split(a, a, b, l - 1);

            b->rev ^= true;

            merge(a, b, treap);
            merge(treap, c, treap);
        }
        else {
            split(treap, a, c, r);
            split(a, a, b, l - 1);

            printf("%d\n", getMin(b));

            merge(a, b, treap);
            merge(treap, c, treap);
        }
    }
}

int main()
{
    read();
    build();
    solve();

    return 0;
}
