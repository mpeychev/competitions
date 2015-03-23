#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

struct node {
    int num, prior;
    int sz, mn;
    node *left, *right;
};

typedef node* pnode;

const int INF = 1 << 30;

pnode createNode(int x) {
    pnode ret;
    ret = new node;
    ret->num = ret->mn = x;
    ret->prior = rand();
    ret->sz = 1;
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

void split(pnode t, pnode &le, pnode &ri, int key) {
    if(!t) {
        le = ri = NULL;
        return;
    }

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

void write(pnode t) {
    if(!t) return;
    write(t->left);
    printf("(%d %d) ", t->num, t->prior);
    write(t->right);
}

int main()
{
    int n, a, b;
    char cmd;
    pnode treap;

    treap = new node;

    scanf("%d\n", &n);

    scanf("%c %d %d\n", &cmd, &a, &b);
    treap = createNode(b);

    for(int i = 1; i < n; i ++) {
        scanf("%c %d %d\n", &cmd, &a, &b);
        
        pnode le, ri, ins;
        if(cmd == '+') {
            ins = createNode(b);

            split(treap, le, ri, a);

            merge(le, ins, treap);
            merge(treap, ri, treap);
        }
        else {
            split(treap, le, ri, b);
            split(le, le, ins, a - 1);

            printf("%d\n", getMin(ins));

            merge(le, ins, treap);
            merge(treap, ri, treap);
        }
    }

    return 0;
}
