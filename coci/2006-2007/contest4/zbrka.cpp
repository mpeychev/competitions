#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXC = 10100;
const int MOD = 1000000007;

int n, c;
int dp[MAXC], sum[MAXC];

void read() {
    cin >> n >> c;
}

inline int getSum(int le, int ri) {
    if(!le) return sum[ri];
    int ret = sum[ri] - sum[le - 1];
    if(ret < 0) ret += MOD;
    return ret;
}

void solve() {
    dp[0] = 1;
    for(int i = 2; i <= n; i ++) {
        memset(sum, 0, sizeof(sum));
        sum[0] = dp[0];
        for(int j = 1; j <= c; j ++) {
            sum[j] = sum[j - 1] + dp[j];
            if(sum[j] >= MOD) sum[j] -= MOD;
        }

        dp[0] = 1;
        for(int j = 1; j <= c; j ++)
            dp[j] = getSum(j - min(i - 1, j), j);
    }

    cout << dp[c] << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
