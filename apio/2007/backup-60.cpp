#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef long long LL;

const int MAXN = 100100;
const LL INF = 1LL << 60;

int n, k;
LL s[MAXN];
LL dp[2][MAXN];

void read() {
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i ++)
		scanf("%lld", &s[i]);
}

void solve() {
	for(int iter = 1; iter <= k; iter ++) {
		dp[iter & 1][2 * iter - 1] = INF;
		for(int i = 2 * iter; i <= n; i ++)
			dp[iter & 1][i] = min(s[i] - s[i - 1] + dp[(iter - 1) & 1][i - 2], dp[iter & 1][i - 1]);
	}
	cout << dp[k & 1][n] << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
