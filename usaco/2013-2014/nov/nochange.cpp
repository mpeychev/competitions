#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXK = 16;
const int MAXN = 100005;

int k, n;
int coinsVal[MAXK];
int c[MAXN], ps[MAXN];
int rightEnd[MAXN][MAXK];
int sumZeroCoins[1 << MAXK];
int maxPos[1 << MAXK];

void read() {
	scanf("%d %d", &k, &n);
	
	for(int i = 0; i < k; i ++)
		scanf("%lld", &coinsVal[i]);
	
	for(int i = 1; i <= n; i ++) {
		scanf("%lld", &c[i]);
		ps[i] = ps[i - 1] + c[i];
	}
}

int getSum(int le, int ri) {
	return ps[ri] - ps[le - 1];
}

int bs(int leftEnd, int sumLimit) {
	int le = leftEnd, ri = n, mid;
	int ret = leftEnd - 1;
	while(le <= ri) {
		mid = (le + ri) >> 1;
		if(getSum(leftEnd, mid) <= sumLimit) {
			ret = mid;
			le = mid + 1;
		}
		else ri = mid - 1;
	}
	return ret;
}

void solve() {
	for(int i = 1; i <= n + 1; i ++)
		for(int j = 0; j < k; j ++)
			rightEnd[i][j] = bs(i, coinsVal[j]);
	
	for(int i = 0; i < (1 << k); i ++)
		for(int j = 0; j < k; j ++)
			if(!((i >> j) & 1))
				sumZeroCoins[i] += coinsVal[j];
	
	maxPos[0] = 1;
	for(int mask = 1; mask < (1 << k); mask ++)
		for(int i = 0; i < k; i ++)
			if((mask >> i) & 1)
				maxPos[mask] = max(maxPos[mask], rightEnd[ maxPos[mask ^ (1 << i)] ][i] + 1);
	
	int ans = -1;
	for(int mask = 0; mask < (1 << k); mask ++)
		if(maxPos[mask] == n + 1)
			ans = max(ans, sumZeroCoins[mask]);
	
	cout << ans << endl;
}

int main()
{
	freopen("nochange.in", "r", stdin);
	freopen("nochange.out", "w", stdout);
	
	read();
	solve();
	
	return 0;
}
