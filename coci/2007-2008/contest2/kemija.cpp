#include <stdio.h>
#include <iostream>

using namespace std;

typedef long long LL;

int n;
LL a[10100], b[10100];

void read() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%lld", &b[i]);
}

void solve() {
    if(n % 3) {
        a[0] = 1;
        for(int i = 0, j = 0; j < n - 1; i = (i + 3) % n, j ++)
            a[(i + 3) % n] = a[i] - b[(i + 1) % n] + b[(i + 2) % n];

        LL sb = 0, sa = 0, x;
        for(int i = 0; i < n; i ++)
            sa += a[i], sb += b[i];
        x = (sb / 3 - sa) / n;

        for(int i = 0; i < n; i ++)
            printf("%d\n", a[i] + x);
    }
    else {
        LL mn1, mn2;

        a[0] = 1;
        mn1 = 1;
        for(int i = 0; i < n - 3; i += 3) {
            a[i + 3] = a[i] - b[i + 1] + b[i + 2];
            if(mn1 > a[i + 3]) mn1 = a[i + 3];
        }

        a[1] = 1;
        mn2 = 1;
        for(int i = 1; i < n - 2; i += 3) {
            a[i + 3] = a[i] - b[i + 1] + b[i + 2];
            if(mn2 > a[i + 3]) mn2 = a[i + 3];
        }

        for(int i = 0; i <= n - 3; i += 3)
            a[i] += (1 - mn1);

        for(int i = 1; i <= n - 2; i += 3)
            a[i] += (1 - mn2);

        a[2] = b[1] - a[0] - a[1];
        for(int i = 2; i <= n - 1; i += 3)
            a[i] = b[i - 1] - a[i - 2] - a[i - 1];

        for(int i = 0; i < n; i ++)
            printf("%lld\n", a[i]);
    }
}

int main()
{
    read();
    solve();

    return 0;
}
