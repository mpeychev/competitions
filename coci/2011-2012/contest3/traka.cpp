#include <stdio.h>
#include <iostream>
#include <math.h>
#include <algorithm>

#define mp make_pair
#define a first
#define b second

using namespace std;

typedef long long LL;
typedef pair<LL, LL> Line;

const int MAXN = 1 << 17;
const LL INF = (LL)-1e9;
const double eps = 1e-9;

int n, m;
int t[MAXN], f[MAXN];
int s[MAXN];
Line l[MAXN], st[MAXN];
int sz;
LL sol;

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &t[i]);
    for(int i = 1; i <= m; i ++)
        scanf("%d", &f[i]);
}

bool cmp(Line f, Line g) {
    return f.a * INF + f.b > g.a * INF + g.b;
}

LL bs(LL x, LL y) {
    int lo = 0, hi = sz - 1, mid;
    while(lo < hi) {
        mid = (lo + hi) >> 1;
        if(st[mid].a * x + st[mid].b * y > st[mid + 1].a * x + st[mid + 1].b * y) hi = mid;
        else lo = mid + 1;
    }
    return st[lo].a * x + st[lo].b * y;
}

void solve() {
    for(int i = 1; i <= n; i ++)
        s[i] = s[i - 1] + t[i];
    for(int i = 0; i < n; i ++)
        l[i] = mp(s[i + 1], -s[i]);

    sort(l, l + n, cmp);

    st[sz ++] = l[0];
    for(int i = 1; i < n; i ++) {
        while(sz > 1) {
            double x1 = (double)(l[i].b - st[sz - 1].b) / (double)(st[sz - 1].a - l[i].a);
            double x2 = (double)(st[sz - 1].b - st[sz - 2].b) / (double)(st[sz - 2].a - st[sz - 1].a);
            if(x2 - x1 > eps) sz --;
            else break;
        }
        st[sz ++] = l[i];
    }

    for(int i = 2; i <= m; i ++)
        sol += bs(f[i - 1], f[i]);

    for(int i = 1; i <= n; i ++)
        sol += (LL)t[i] * (LL)f[m];

    printf("%lld\n", sol);
}

int main()
{
    read();
    solve();

    return 0;
}
