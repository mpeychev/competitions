#include <stdio.h>

int n;
double dp[1 << 20], ma3x[32][32];
bool used[1 << 20];

double max(double a, double b) {
    if(a - b > 0.0) return a;
    return b;
}

void read() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++) {
            scanf("%lf", &ma3x[i][j]);
            ma3x[i][j] /= 100.0;
        }
}

double get(int mask) {
    if(used[mask])
        return dp[mask];

    int bits = -1;
    for(int i = 0; i < n; i ++)
        bits += ((mask >> i) & 1);

    double ret = -1.0;
    for(int i = 0; i < n; i ++)
        if((mask >> i) & 1)
            ret = max(ret, ma3x[bits][i] * get(mask - (1 << i)));

    used[mask] = 1;
    dp[mask] = ret;
    return ret;
}

void solve() {
    used[0] = 1;
    dp[0] = 1.0;
    printf("%.12lf\n", 100 * get((1 << n) - 1));
}

int main()
{
    read();
    solve();

    return 0;
}
