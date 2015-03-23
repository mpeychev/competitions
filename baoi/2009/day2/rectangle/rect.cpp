#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

#define pb push_back

using namespace std;

typedef long long LL;

struct pii
{
    int x, y;
};

struct vec
{
    LL x1, y1;
    LL x, y;
    LL a, b;

    vec() {}
    vec(LL _x1, LL _y1, LL _x, LL _y, LL _a, LL _b): x1(_x1), y1(_y1), x(_x), y(_y), a(_a), b(_b) {}
};

struct ox
{
    LL x, y, len;

    ox() {}
    ox(LL _x, LL _y, LL _len): x(_x), y(_y), len(_len) {}
};

const int MAXN = 1515;
const int INF = (1 << 30);
const int OXC = -100000000;

int n;
pii p[MAXN];
vector< vec > v;
vector< ox > u;

bool cmpPII(pii a, pii b)
{
    if(a.x < b.x) return true;
    if(a.x > b.x) return false;
    return a.y < b.y;
}

bool cmpOX(ox a, ox b)
{
    if(a.len < b.len) return true;
    if(a.len > b.len) return false;
    if(a.x < b.x) return true;
    if(a.x > b.x) return false;
    return a.y < b.y;
}

bool cmpVEC(vec a, vec b)
{
    if(a.x < b.x) return true;
    if(a.x > b.x) return false;
    if(a.y < b.y) return true;
    if(a.y > b.y) return false;
    if(a.a * b.b < b.a * a.b) return true;
    if(a.a * b.b > b.a * a.b) return false;
    return a.x1 < b.x1;
}

bool equal(vec a, vec b)
{
    if(a.x != b.x) return false;
    if(a.y != b.y) return false;
    if(a.a * b.b != b.a * a.b) return false;
    return true;
}

void init()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%d %d", &p[i].x, &p[i].y);
    sort(p, p + n, cmpPII);
}

LL solveU()
{
    if(u.size() < 2) return 0;

    LL ret = 0;

    u.pb(ox(0, 0, INF));
    sort(u.begin(), u.end(), cmpOX);

    ox tmp = u[0];
    for(int i = 1; i < u.size(); i ++)
        if(u[i].len != tmp.len || u[i].x != tmp.x)
        {
            LL s = (u[i - 1].y - tmp.y) * tmp.len;
            if(s > ret) ret = s;
            tmp = u[i];
        }

    return ret;
}

LL findS(vec a, vec b)
{
    LL xl, yl;
    LL xr, yr;

    xl = a.x1;
    yl = a.y1 + a.y;

    xr = b.x1 + b.x;
    yr = b.y1;

    LL ret = (xr - xl) * (yr - yl) + a.x * a.y;

    LL g = yr - a.y1;
    LL f = b.x1 - xl;

    return ret - g * f;
}

LL solveV()
{
    if(v.size() < 2) return 0;

    LL ret = 0, s;

    sort(v.begin(), v.end(), cmpVEC);

    vec tmp = v[0];
    for(int i = 1; i < v.size(); i ++)
        if(!equal(tmp, v[i]))
        {
            s = findS(tmp, v[i - 1]);
            if(s > ret) ret = s;
            tmp = v[i];
        }

    s = findS(tmp, v[ v.size() - 1 ]);
    if(s > ret) ret = s;

    return ret;
}

void solve()
{
    for(int i = 0; i < n; i ++)
        for(int j = i + 1; j < n; j ++)
            if(p[i].y == p[j].y) u.pb(ox(p[i].x, p[i].y, p[j].x - p[i].x));
            else if(p[i].x != p[j].x)
            {
                LL x, y;
                x = p[j].x - p[i].x;
                y = p[j].y - p[i].y;

                if(y < 0)
                {
                    LL x1 = p[i].x;
                    LL a = p[i].y - OXC;

                    v.pb(vec(p[i].x, p[i].y, x, y, x1 * x + a * y, x));
                }
            }

    LL res1, res2;
    res1 = solveU();
    res2 = solveV();

    if(res1 > res2) cout << res1 << endl;
    else cout << res2 << endl;
}

int main()
{
    init();
    solve();

    return 0;
}
