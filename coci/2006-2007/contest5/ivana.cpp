#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 1 << 7;

int n, a[MAXN];
int dp[MAXN][MAXN];
int ans;

void read() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) {
        scanf("%d", &a[i]);
        a[i] %= 2;
    }
}

inline int nextPos(int x) {
    if(x == n - 1) return 0;
    return x + 1;
}

inline int prevPos(int x) {
    if(x == 0) return n - 1;
    return x - 1;
}

int f(int le, int ri) {
    if(dp[le][ri] != -1)
        return dp[le][ri];

    if(le == ri)
        return dp[le][ri] = a[le];

    return dp[le][ri] = max(a[le] - f(nextPos(le), ri), a[ri] - f(le, prevPos(ri)));
}

void solve() {
    if(n == 1) {
        cout << a[0] << endl;
        return;
    }

    memset(dp, -1, sizeof(dp));

    for(int i = 0; i < n; i ++)
        if(a[i] - f(nextPos(i), prevPos(i)) > 0)
            ans ++;

    cout << ans << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
