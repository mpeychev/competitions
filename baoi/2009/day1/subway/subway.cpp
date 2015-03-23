#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100100;
const double eps = 1e-9;

int m, n;
int x[MAXN];
char dir;
double a[MAXN], dist;

void init()
{
    scanf("%d %d", &m, &n);
    for(int i = 0; i < n; i ++)
        scanf("%d %c\n", &x[i], &dir);
    sort(x, x + n);
}

void solve()
{
    for(int i = 1; i < n; i += 2)
        x[i] = 2 * m - x[i];
    sort(x, x + n);

    a[0] = x[0];
    dist = 2 * (double)m / (double)n;
    for(int i = 1; i < n; i ++)
        a[i] = a[i - 1] + dist;

    double mn, mx;
    mn = mx = (double)x[0] - a[0];
    for(int i = 1; i < n; i ++)
    {
        double tmp = (double)x[i] - a[i];
        if(mn - tmp > eps) mn = tmp;
        if(tmp - mx > eps) mx = tmp;
    }

    printf("%.6lf\n", (mx - mn) / 2);
}

int main()
{
    init();
    solve();

    return 0;
}
