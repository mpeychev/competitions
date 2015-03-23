/*
  Source: usaco - 2005/2006 - oct - gold
  Task: flight
  KeyW: greedy + interval tree
*/
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

struct group {
    int s, e, m;
};

struct node {
    int whole, down;
};

int k, n, c;
group tmp;
vector< group > p[2];
int lvs;
node t[1 << 15];

void init() {
    scanf("%d %d %d", &k, &n, &c);
    for(int i = 0; i < k; i ++) {
        scanf("%d %d %d", &tmp.s, &tmp.e, &tmp.m);
        tmp.s --;
        tmp.e --;
        if(tmp.s < tmp.e) p[0].pb(tmp);
        else {
            tmp.s ^= tmp.e ^= tmp.s ^= tmp.e;
            p[1].pb(tmp);
        }
    }

    lvs = 1;
    while(lvs < n) lvs <<= 1;
}

bool cmp(group a, group b) {
    if(a.e < b.e) return true;
    if(a.e > b.e) return false;
    if(a.s < b.s) return true;
    return false;
}

void update(int idx, int le, int ri, int a, int b, int val) {
    if(ri < a || b < le)
        return;

    if(a <= le && ri <= b) {
        t[idx].whole += val;
        return;
    }

    int mid = (le + ri) >> 1;
    update(idx << 1, le, mid, a, b, val);
    update((idx << 1) + 1, mid + 1, ri, a, b, val);

    t[idx].down = max(t[idx << 1].down + t[idx << 1].whole,
                      t[(idx << 1) + 1].down + t[(idx << 1) + 1].whole);
}

int get(int idx, int le, int ri, int a, int b, int sum) {
    if(ri < a || b < le) return 0;

    if(a <= le && ri <= b)
        return sum + t[idx].whole + t[idx].down;

    int left, right;
    int mid = (le + ri) >> 1;
    left = get(idx << 1, le, mid, a, b, sum + t[idx].whole);
    right = get((idx << 1) + 1, mid + 1, ri, a, b, sum + t[idx].whole);

    return max(left, right);
}

int calc(int dir) {
    sort(p[dir].begin(), p[dir].end(), cmp);
    for(int i = 1; i < 2 * lvs; i ++) {
        t[i].whole = 0;
        t[i].down = 0;
    }
    int ret = 0;
    for(int i = 0; i < p[dir].size(); i ++) {
        int f = get(1, 0, lvs - 1, p[dir][i].s, p[dir][i].e, 0);

        int add = min(p[dir][i].m, c - f);
        ret += add;
        update(1, 0, lvs - 1, p[dir][i].s, p[dir][i].e - 1, add);
    }
    return ret;
}

int main()
{
    init();
    printf("%d\n", calc(0) + calc(1));

    return 0;
}
