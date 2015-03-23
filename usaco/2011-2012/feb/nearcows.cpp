#include <iostream>
#include <stdio.h>
#include <vector>

#define pb push_back

using namespace std;

const int MAXN = 100100;
const int MAXK = 21;

int n, k;
vector<int> g[MAXN];
int parent[MAXN];
int sumDown[MAXN][MAXK];

void read() {
	int a, b;
	
	scanf("%d %d", &n, &k);
	for(int i = 1; i < n; i ++) {
		scanf("%d %d", &a, &b);
		g[a].pb(b);
		g[b].pb(a);
	}
	
	for(int i = 1; i <= n; i ++)
		scanf("%d", &sumDown[i][0]);
}

void dfs(int cur) {
	for(int i = 0; i < g[cur].size(); i ++)
		if(!parent[ g[cur][i] ]) {
			parent[ g[cur][i] ] = cur;
			dfs(g[cur][i]);
			
			for(int j = 1; j <= k; j ++)
				sumDown[cur][j] += sumDown[ g[cur][i] ][j - 1];
		}
}

void calc(int curNode) {
	int ans = 0;
	for(int i = 0; i <= k; i ++)
		ans += sumDown[curNode][i];
	
	int prevNode = curNode;
	curNode = parent[curNode];
	for(int stepsUp = 1; stepsUp <= k && curNode != -1; stepsUp ++) {
		ans += sumDown[curNode][0];
		for(int i = 1; i + stepsUp <= k; i ++)
			ans += (sumDown[curNode][i] - sumDown[prevNode][i - 1]);
		prevNode = curNode;
		curNode = parent[curNode];
	}
	
	printf("%d\n", ans);
}

void solve() {
	parent[1] = -1;
	dfs(1);
	
	for(int i = 1; i <= n; i ++)
		calc(i);
}

int main()
{
	read();
	solve();

    return 0;
}
