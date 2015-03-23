#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

typedef long long LL;

const int MAXM = 128;
const int MAXK = 512;

int n, m, k;
int cnt[MAXM];
LL dp[MAXM][MAXK];

LL F(LL N, LL K) {
	if(N == 0)
		return 0;
	
	if(K == 0)
		return ((1 + N) * N) / 2;
	
	if(N == 1)
		return 1;
	
	if(N <= K + 1)
		return N;
	
	LL last = N / (K + 1);
	return (K + 1) * (((1 + last) * last) / 2) + (N - last * (K + 1)) * (last + 1);
}

void read() {
	int x;
	
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 0; i < n; i ++) {
		scanf("%d", &x);
		cnt[x] ++;
	}
}

LL go(int curM, int leftK) {
	LL &ret = dp[curM][leftK];
	
	if(ret != -1)
		return ret;
	
	if(curM == m) {
		ret = F(cnt[curM], leftK);
		return ret;
	}
	
	ret = 1LL << 62;
	for(int i = 0; i <= leftK; i ++) {
		LL tmp = F(cnt[curM], i) + go(curM + 1, leftK - i);
		if(ret > tmp) ret = tmp;
	}
	
	return ret;
}

void solve() {
	memset(dp, -1, sizeof(dp));
	cout << go(1, k) << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
