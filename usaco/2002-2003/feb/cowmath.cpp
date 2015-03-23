#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef long long LL;

const int MAXN = 32;

int n, ma3x[MAXN][MAXN];
bool used[MAXN];
int cnt[2048];
int D;
LL ans;

void read() {
	cin >> n;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			cin >> ma3x[i][j];
}

void dfs(int cur) {
	used[cur] = true;
	for(int i = 1; i <= n; i ++)
		if(!used[i] && ma3x[cur][i] && ma3x[cur][i] % D == 0)
			dfs(i);
}

void add(int x) {
	int count[2048];
	memset(count, 0, sizeof(count));
	
	for(int i = 2; i * i <= x; i ++)
		while(x % i == 0) {
			count[i] ++;
			x /= i;
		}
	if(x > 1) count[x] ++;
	
	for(int i = 0; i <= 2000; i ++)
		cnt[i] = max(cnt[i], count[i]);
}

void solve() {
	for(int i = 2; i <= 2000; i ++) {
		memset(used, 0, sizeof(used));
		D = i;
		dfs(1);
		if(used[2]) add(i);
	}
	
	ans = 1;
	for(LL i = 2; i <= 2000; i ++)
		for(int j = 0; j < cnt[i]; j ++)
			ans *= i;
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
