#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXP = 305;
const int INF = 1 << 20;

int m, p;
int a[MAXP], b[MAXP];
int dp[MAXP][MAXP];

void read() {
	scanf("%d %d", &m, &p);
	for(int i = 1; i <= p; i ++) {
		scanf("%d %d", &a[i], &b[i]);
		a[i] += a[i - 1];
		b[i] += b[i - 1];
	}
}

int go(int idx1, int idx2) {
	int &ret = dp[idx1][idx2];
	
	if(ret != -1)
		return ret;
	
	if(idx2 == p + 1) {
		dp[idx1][idx2] = 1;
		return dp[idx1][idx2];
	}
	
	ret = INF;
	
	if(idx1 != idx2) ret = 1 + go(idx2, idx2);	/// Just wait one month
	
	for(int k = idx2; k <= p; k ++) {
		if((b[idx2 - 1] - b[idx1 - 1]) + (a[k] - a[idx2 - 1]) > m) break;
		if(b[k] - b[idx2 - 1] > m) break;
		ret = min(ret, 1 + go(idx2, k + 1));
	}
	
	return ret;
}

void solve() {
	memset(dp, -1, sizeof(dp));
	cout << go(1, 1) + 1 << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
