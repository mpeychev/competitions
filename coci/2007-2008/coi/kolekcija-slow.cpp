#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

const int MAXM = 300300;

int n, k, m;
int p[MAXM];
int dp[MAXM];

void read() {
	scanf("%d %d", &n, &k);
	scanf("%d", &m);
	for(int i = 0; i < m; i ++)
		scanf("%d", &p[i]);
}

int go(int i) {
	int &ret = dp[i];
	
	if(ret != -1)
		return ret;
	
	if(i == m) {
		ret = 0;
		return ret;
	}
	
	int start = m;
	for(int j = i + 1; j < m; j ++)
		if(p[i] + k <= p[j]) {
			start = j;
			break;
		}
	
	ret = k + go(start);
	for(int j = start; j < m; j ++) {
		int tmp = p[j] - p[i] + 1 + go(j + 1);
		if(ret > tmp) ret = tmp;
	}
	
	return ret;
}

void solve() {
	sort(p, p + m);
	
	if(p[m - 1] - p[0] + 1 <= k) {
		cout << k << endl;
		return;
	}
	
	memset(dp, -1, sizeof(dp));
	cout << go(0) << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
