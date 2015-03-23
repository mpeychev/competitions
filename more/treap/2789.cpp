#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

struct node {
    int num, prior;
    int sz;
    long long sum;

    node *left, *right;
};

typedef node* pnode;

pnode even, odd;
int n, m;

pnode createNode(int x) {
    pnode ret;
    ret = new node;
    ret->num = ret->sum = x;
    ret->prior = rand();
    ret->sz = 1;
    ret->left = ret->right = NULL;
    return ret;
}

inline int getSize(pnode t) {
    if(!t) return 0;
    return t->sz;
}

inline long long getSum(pnode t) {
    if(!t) return 0;
    return t->sum;
}

inline void fix(pnode &t) {
    t->sz = getSize(t->left) + 1 + getSize(t->right);
    t->sum = getSum(t->left) + t->num + getSum(t->right);
}

void split(pnode t, pnode &le, pnode &ri, int key) {
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

void build() {
    bool fl1 = false, fl2 = false;
    int a;
    pnode ins;

    for(int i = 1; i <= n; i ++) {
        scanf("%d", &a);
        ins = createNode(a);
        if(i & 1) {
            if(!fl1) odd = createNode(a);
            else merge(odd, ins, odd);

            fl1 = true;
        }
        else {
            if(!fl2) even = createNode(a);
            else merge(even, ins, even);

            fl2 = true;
        }
    }
}

void solve() {
    int cmd, l, r, len, x, y;
    long long ans;
    pnode a1, b1, c1;
    pnode a2, b2, c2;

    for(int i = 1; i <= m; i ++) {
        scanf("%d %d %d", &cmd, &l, &r);
        len = r - l + 1;

        if(cmd == 1) {
            // odd
            if(l & 1) x = (l + 1) / 2;
            else x = (l + 2) / 2;
            y = x + (len / 2) - 1;

            split(odd, a1, c1, y);
            split(a1, a1, b1, x - 1);

            // even
            if(l & 1) x = (l + 1) / 2;
            else x = l / 2;
            y = x + (len / 2) - 1;

            split(even, a2, c2, y);
            split(a2, a2, b2, x - 1);

            merge(a1, b2, odd);
            merge(odd, c1, odd);

            merge(a2, b1, even);
            merge(even, c2, even);
        }
        else {
            ans = 0;

            // odd
            x = l;
            y = r;
            if(x % 2 == 0) x ++;
            if(y % 2 == 0) y --;

            x = (x / 2) + 1;
            y = (y / 2) + 1;

            if(x <= y) {
                split(odd, a1, c1, y);
                split(a1, a1, b1, x - 1);

                ans += getSum(b1);

                merge(a1, b1, odd);
                merge(odd, c1, odd);
            }

            // even
            x = l;
            y = r;
            if(x & 1) x ++;
            if(y & 1) y --;

            x = x / 2;
            y = y / 2;

            if(x <= y) {
                split(even, a2, c2, y);
                split(a2, a2, b2, x - 1);

                ans += getSum(b2);

                merge(a2, b2, even);
                merge(even, c2, even);
            }

            printf("%lld\n", ans);
        }
    }
}

int main()
{
    for(int i = 1; ; i ++) {
        scanf("%d %d", &n, &m);
        if(!n && !m) break;
        printf("Swapper %d:\n", i);
        build();
        solve();
        printf("\n");
    }

    return 0;
}
