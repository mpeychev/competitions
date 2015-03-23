#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

struct item {
    int num, prior, sz;
    item *left, *right;
};

typedef item* pitem;

pitem treap;
int n, m;

pitem createItem(int x) {
    pitem ret;
    ret = new item;
    ret->num = x;
    ret->sz = 1;
    ret->prior = rand() | (rand() << 15);
    ret->left = NULL;
    ret->right = NULL;
    return ret;
}

inline int getSize(pitem t) {
    if(!t) return 0;
    return t->sz;
}

inline void fix(pitem &t) {
    t->sz = getSize(t->left) + 1 + getSize(t->right);
}

void split(pitem t, pitem &le, pitem &ri, int key) {
    if(!t) {
        le = ri = NULL;
        return;
    }

    int tmp = getSize(t->left) + 1;
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

void merge(pitem le, pitem ri, pitem &t) {
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
        fix(t);
    }
    else {
        merge(le, ri->left, ri->left);
        t = ri;
        fix(t);
    }
}

void write(pitem t) {
    if(!t) return;
    write(t->left);
    printf("%d ", t->num);
    write(t->right);
}

int main()
{
    scanf("%d %d", &n, &m);

    treap = createItem(1);
    for(int i = 2; i <= n; i ++) {
        pitem ins;
        ins = createItem(i);
        merge(treap, ins, treap);
    }

    for(int i = 0; i < m; i ++) {
        int l, r;
        scanf("%d %d", &l, &r);

        pitem a, b, c;
        split(treap, a, c, r);
        split(a, a, b, l - 1);

        merge(b, a, treap);
        merge(treap, c, treap);
    }

    write(treap);
    printf("\n");

    return 0;
}
