#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 100100;

int n, x[MAXN], y[MAXN];
long long cntX[MAXN], cntY[MAXN];
long long ans;

void read() {
	scanf("%d", &n);
	for(int i = 0; i < n; i ++) {
		scanf("%d %d", &x[i], &y[i]);
		cntX[ x[i] ] ++;
		cntY[ y[i] ] ++;
	}
}

void solve() {
	for(int i = 0; i < n; i ++)
		ans += (cntX[ x[i] ] - 1) * (cntY[ y[i] ] - 1);
	cout << ans << endl;
}

int main()
{
	read();
	solve();
	
	return 0;
}
