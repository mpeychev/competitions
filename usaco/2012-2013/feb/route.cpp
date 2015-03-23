#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

typedef long long LL;

struct edge {
    int a, b;
};

int n, m, r;
LL valLeft[40100], valRight[40100];
LL nxtLeft[40100], nxtRight[40100];
edge e[100100];
LL ans;

void read() {
    scanf("%d %d %d", &n, &m, &r);
    for(int i = 1; i <= n; i ++) {
        scanf("%lld", &valLeft[i]);
        if(ans < valLeft[i]) ans = valLeft[i];
    }
    for(int i = 1; i <= m; i ++) {
        scanf("%lld", &valRight[i]);
        if(ans < valRight[i]) ans = valRight[i];
    }
    for(int i = 0; i < r; i ++)
        scanf("%d %d", &e[i].a, &e[i].b);
}

bool cmp(edge x, edge y) {
    if(x.a > y.a) return true;
    if(x.a < y.a) return false;
    return x.b > y.b;
}

void solve() {
    sort(e, e + r, cmp);

    memset(nxtLeft, -1, sizeof(nxtLeft));
    memset(nxtRight, -1, sizeof(nxtRight));

    for(int i = 0; i < r; i ++) {
        LL x, y;

        if(nxtRight[ e[i].b ] == -1) x = valLeft[ e[i].a ] + valRight[ e[i].b ];
        else x = valLeft[ e[i].a ] + nxtRight[ e[i].b ];

        if(nxtLeft[ e[i].a ] == -1) y = valLeft[ e[i].a ] + valRight[ e[i].b ];
        else y = nxtLeft[ e[i].a ] + valRight[ e[i].b ];

        if(nxtLeft[ e[i].a ] < x) nxtLeft[ e[i].a ] = x;
        if(nxtRight[ e[i].b ] < y) nxtRight[ e[i].b ] = y;

        if(ans < x) ans = x;
        if(ans < y) ans = y;
    }

    cout << ans << endl;
}

int main()
{
    freopen("route.in", "r", stdin);
    freopen("route.out", "w", stdout);

    read();
    solve();

    return 0;
}
