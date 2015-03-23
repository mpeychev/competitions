#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define pb push_back

using namespace std;

const int MAXN = 1 << 15;
const int MAXL = 1 << 5;

int n, tlen, pos;
char s[MAXN][MAXL];
char t[MAXL];
int vec[MAXN];
vector< int > tree[2 * MAXN];
int lvs;

void read() {
    scanf("%d\n", &n);
    for(int i = 0; i < n; i ++)
        scanf("%s", &s[i]);
}

bool cmp(int a, int b) {
    return strcmp(s[a], s[b]) < 0;
}

void go(int idx) {
    if(idx >= lvs) return;

    int leftChild = (idx << 1), rightChild = (idx << 1) + 1;

    go(leftChild);
    go(rightChild);

    int i = 0, j = 0;
    while(i < tree[leftChild].size() || j < tree[rightChild].size()) {
        if(i == tree[leftChild].size()) {
            tree[idx].pb(tree[rightChild][j ++]);
            continue;
        }
        if(j == tree[rightChild].size()) {
            tree[idx].pb(tree[leftChild][i ++]);
            continue;
        }
        if(tree[leftChild][i] < tree[rightChild][j]) tree[idx].pb(tree[leftChild][i ++]);
        else tree[idx].pb(tree[rightChild][j ++]);
    }
}

void init() {
    for(int i = 0; i < n; i ++)
        vec[i] = i;

    sort(vec, vec + n, cmp);

    lvs = 1;
    while(lvs < n) lvs <<= 1;

    for(int i = 0; i < n; i ++)
        tree[i + lvs].pb(vec[i]);

    go(1);
}

int findWord() {
    int le = 0, ri = n - 1, mid;
    while(le <= ri) {
        mid = (le + ri) >> 1;
        int value = strcmp(s[ vec[mid] ], t);
        if(value == 0) return vec[mid];
        if(value < 0) le = mid + 1;
        else ri = mid - 1;
    }
    return -1;
}

void calc1() {
    int i, le = 0, ri = n - 1;
    long long ans = 0;

    for(i = 0; i < tlen && le <= ri; i ++) {
        ans += (ri - le + 1);

        if(s[ vec[le] ][i] > t[i]) break;
        if(s[ vec[ri] ][i] < t[i]) break;

        short int fl1 = 0, fl2 = 0;

        if(s[ vec[le] ][i] != t[i]) {
            fl1 = 1;
            for(int k = 16; k >= 0; k --)
                if(le + (1 << k) <= ri && s[ vec[ le + (1 << k) ] ][i] < t[i])
                    le += (1 << k);
        }

        if(s[ vec[ri] ][i] != t[i]) {
            fl2 = 1;
            for(int k = 16; k >= 0; k --)
                if(ri - (1 << k) >= le && s[ vec[ ri - (1 << k) ] ][i] > t[i])
                    ri -= (1 << k);
        }

        le += fl1;
        ri -= fl2;
    }

    if(i == tlen && le <= ri) ans += (ri - le + 1);

    printf("%lld\n", ans);
}

int get(int idx, int le, int ri, int a, int b) {

//    cout << idx << " : " << le << " " << ri << " || " << a << " " << b << endl;

    if(ri < a || b < le) return 0;

    if(a <= le && ri <= b) {
        int bsLe = 0, bsRi = tree[idx].size() - 1, mid;
        int ret = -1;
        while(bsLe <= bsRi) {
            mid = (bsLe + bsRi) >> 1;
            if(tree[idx][mid] <= pos) {
                ret = mid;
                bsLe = mid + 1;
            }
            else bsRi = mid - 1;
        }
        return ret + 1;
    }

    int MID = (le + ri) >> 1;

    return get(idx << 1, le, MID, a, b) + get((idx << 1) + 1, MID + 1, ri, a, b);
}

void calc2() {
    int i, le = 0, ri = n - 1;
    long long ans = 0;

    for(i = 0; i < tlen && le <= ri; i ++) {
//        cout << "start get " << le << " " << ri << endl;
        ans += get(1, 0, lvs - 1, le, ri);
//        cout << "end get\n";

        if(s[ vec[le] ][i] > t[i]) break;
        if(s[ vec[ri] ][i] < t[i]) break;

        short int fl1 = 0, fl2 = 0;

        if(s[ vec[le] ][i] != t[i]) {
            fl1 = 1;
            for(int k = 16; k >= 0; k --)
                if(le + (1 << k) <= ri && s[ vec[ le + (1 << k) ] ][i] < t[i])
                    le += (1 << k);
        }

        if(s[ vec[ri] ][i] != t[i]) {
            fl2 = 1;
            for(int k = 16; k >= 0; k --)
                if(ri - (1 << k) >= le && s[ vec[ ri - (1 << k) ] ][i] > t[i])
                    ri -= (1 << k);
        }

        le += fl1;
        ri -= fl2;

//        cout << t[i] << ": " << le << " " << ri << endl;
    }

    if(i == tlen && le <= ri) ans += get(1, 0, lvs - 1, le, ri);

    printf("%lld\n", ans);
}

void solve() {
    int q;
    scanf("%d\n", &q);
    for( ; q; q --) {
        scanf("%s", &t);
        tlen = strlen(t);

        pos = findWord();

        if(pos == -1) calc1();
        else calc2();
    }
}

int main()
{
    read();
    init();
    solve();

    return 0;
}
