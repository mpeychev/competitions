#include <stdio.h>
#include <iostream>

using namespace std;

double k, p[100100], s;
int n;

void read() {
    scanf("%lf", &k);
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%lf", &p[i]);
}

void solve() {
    for(int i = 0;  i < n - 1; i ++) {
        if(p[i + 1] - s > p[i] + k) {
            p[i + 1] -= s;
            double add = (p[i + 1] - p[i] - k) / 2;
            s += add;
            p[i + 1] -= add;
        }
        else p[i + 1] = min(p[i + 1] + s, p[i] + k);
    }

    printf("%.5lf\n", s);
}

int main()
{
    read();
    solve();

    return 0;
}
