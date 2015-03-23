#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

const int MAXN = 1 << 9;

int k, n;
int p[32];
int ma3x[MAXN][MAXN];
int ans = (int)1e9;
int stMax[MAXN][16], stMin[MAXN][16];

void read() {
    scanf("%d", &k);
    n = 1 << k;
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
            scanf("%d", &ma3x[i][j]);
}

int calc() {
    int ret = 0;
    for(int i = 0; i < n - 1; i ++)
        ret += ma3x[ p[i] ][ p[i + 1] ];
    return ret;
}

inline int max(int a, int b) {
    if(a < b) return b;
    return a;
}

inline int min(int a, int b) {
    if(a < b) return a;
    return b;
}

bool check() {
    for(int i = 0; i < n; i ++)
        stMax[i][0] = stMin[i][0] = p[i];

    for(int i = 1; i < k; i ++) {
        int period = 1 << i;
        for(int j = 0; j <= n - period; j += period) {
            stMax[j][i] = max(stMax[j][i - 1], stMax[ j + (period >> 1) ][i - 1]);
            stMin[j][i] = min(stMin[j][i - 1], stMin[ j + (period >> 1) ][i - 1]);
        }
    }

    for(int i = 1; i < k; i ++) {
        int period = 1 << i;
        for(int j = 0; j <= n - period; j += period)
            if(stMax[j][i] - stMin[j][i] + 1 != period)
                return false;
    }

    return true;
}

void solve() {
    for(int i = 0; i < n; i ++)
        p[i] = i;

    do
    {
        int tmp = calc();
        if(tmp < ans && check()) ans = tmp;
    }
    while(next_permutation(p, p + n));

    printf("%d\n", ans);
}

int main()
{
    read();
    solve();

    return 0;
}
