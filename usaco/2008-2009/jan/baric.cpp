#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef long long LL;

const int MAXN = 1 << 7;
const LL INF = 1LL << 60;

int n, e;
LL m[MAXN];
LL a[MAXN], b[MAXN], c[MAXN][MAXN];
LL dp[MAXN][MAXN];

void read() {
	cin >> n >> e;
	for(int i = 1; i <= n; i ++)
		cin >> m[i];
}

LL abss(LL x) {
	if(x < 0) return -x;
	return x;
}

LL calc(int pos, int count) {
	LL &ret = dp[pos][count];
	
	if(ret != -1)
		return ret;
	
	if(!count) {
		ret = a[pos];
		return ret;
	}
	
	ret = INF;
	for(int i = count; i < pos; i ++) {
		LL tmp;
		
		if(pos == n + 1) tmp = b[i] + calc(i, count - 1);
		else tmp = c[i][pos] + calc(i, count - 1);
		
		ret = min(ret, tmp);
	}
	
	return ret;
}

void solve() {
	for(int i = 2; i <= n; i ++)
		for(int j = 1; j < i; j ++)
			a[i] += 2 * abss(m[j] - m[i]);
	
	for(int i = n - 1; i >= 1; i --)
		for(int j = n; j > i; j --)
			b[i] += 2 * abss(m[j] - m[i]);
	
	for(int le = 1; le < n; le ++)
		for(int ri = le + 2; ri <= n; ri ++)
			for(int i = le + 1; i < ri; i ++)
				c[le][ri] += abss(2 * m[i] - m[le] - m[ri]);
	
	memset(dp, -1, sizeof(dp));
	
	for(int i = 1; i <= n; i ++) {
		LL tmp = calc(n + 1, i);
		if(tmp <= e) {
			cout << i << " " << tmp << endl;
			return;
		}
	}
}

int main()
{
	read();
	solve();

    return 0;
}
