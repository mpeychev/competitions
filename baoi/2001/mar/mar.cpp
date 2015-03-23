/*
  Source: baoi - 2001
  Task: Mars Maps
  KeyW: interval tree
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = (1 << 14);
const int MAXY = (1 << 16);

struct side
{
    int x, y1, y2;
    int type;

    side() {}
    side(int _x, int _y1, int _y2, int _type): x(_x), y1(_y1), y2(_y2), type(_type) {}
};

struct node
{
    int cnt, cover;
};

int n, mxy, lvs;
side m[2 * MAXN];
node tree[MAXY];

bool cmp(side a, side b)
{
    return a.x < b.x;
}

void init()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
    {
        int x1, y1;
        int x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        m[2 * i] = side(x1, y1, y2, 1);
        m[2 * i + 1] = side(x2, y1, y2, -1);

        if(mxy < y2) mxy = y2;
    }
    sort(m, m + 2 * n, cmp);

    lvs = 1;
    while(lvs <= mxy) lvs <<= 1;
}

void update(int idx, int lint, int rint, int l, int r, int add)
{
    if(r < lint || rint < l) return;
    if(l <= lint && rint <= r) tree[idx].cnt += add;
    else
    {
        int mid = (lint + rint) >> 1;
        update(2 * idx, lint, mid, l, r, add);
        update(2 * idx + 1, mid + 1, rint, l, r, add);
    }

    if(tree[idx].cnt) tree[idx].cover = rint - lint + 1;
    else
    {
        int t = 0;
        if(2 * idx < 2 * lvs) t += tree[2 * idx].cover;
        if(2 * idx + 1 < 2 * lvs) t += tree[2 * idx + 1].cover;
        tree[idx].cover = t;
    }
}

void solve()
{
    int ans = 0;
    update(1, 0, lvs - 1, m[0].y1, m[0].y2 - 1, m[0].type);
    for(int i = 1; i < 2 * n; i ++)
    {
        ans += (m[i].x - m[i - 1].x) * tree[1].cover;
        update(1, 0, lvs - 1, m[i].y1, m[i].y2 - 1, m[i].type);
    }

    printf("%d\n", ans);
}

int main()
{
    init();
    solve();

    return 0;
}
