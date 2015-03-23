#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>

#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 20100;

struct el {
	int a, b, c;
	
	el() {}
	el(int _a, int _b, int _c): a(_a), b(_b), c(_c) {}
};

int n, m, k;
vector< PII > edges[2];

int rt[MAXN];

vector<int> t1[MAXN];
int compNumber[MAXN];
int compCount;

vector< PII > edges0;

vector< el > ans;

void read() {
	int a, b, c;
	
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 0; i < m; i ++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[c].pb(mp(a, b));
	}
}

int findRoot(int u) {
	int ret = u;
	while(rt[ret] != ret)
		ret = rt[ret];
	
	while(u != ret) {
		int up = rt[u];
		rt[u] = ret;
		u = up;
	}
	
	return ret;
}

void dfs(int cur) {
	compNumber[cur] = compCount;
	for(int i = 0; i < (int)t1[cur].size(); i ++)
		if(compNumber[ t1[cur][i] ] == -1)
			dfs(t1[cur][i]);
}

void solve() {
	if((int)edges[0].size() < k) {
		printf("no solution\n");
		return;
	}
	
	/// Build 1-tree
	for(int i = 0; i <= n; i ++)
		rt[i] = i;
	
	for(int i = 0; i < (int)edges[1].size(); i ++) {
		int r1 = findRoot(edges[1][i].first);
		int r2 = findRoot(edges[1][i].second);
		
		if(r1 != r2) {
			t1[ edges[1][i].first ].pb( edges[1][i].second );
			t1[ edges[1][i].second ].pb(edges[1][i].first);
			rt[r1] = r2;
		}
	}
	
	memset(compNumber, -1, sizeof(compNumber));
	for(int i = 1; i <= n; i ++)
		if(compNumber[i] == -1) {
			dfs(i);
			compCount ++;
		}
	
	if(compCount - 1 > k) {
		printf("no solution\n");
		return;
	}
	
	/// Merge components
	for(int i = 0; i < compCount; i ++)
		rt[i] = i;
	
	for(int i = 0; i < (int)edges[0].size(); i ++) {
		int r1 = findRoot(compNumber[ edges[0][i].first ]);
		int r2 = findRoot(compNumber[ edges[0][i].second ]);
		
		if(r1 != r2) {
			edges0.pb(edges[0][i]);
			k --;
			compCount --;
			rt[r1] = r2;
		}
	}
	
	if(compCount > 1) {
		printf("no solution\n");
		return;
	}
	
	/// Go back to global solution
	int global = n;
	for(int i = 1; i <= n; i ++)
		rt[i] = i;
	
	for(int i = 0; i < (int)edges0.size(); i ++) {
		ans.pb(el(edges0[i].first, edges0[i].second, 0));
		int r1 = findRoot(edges0[i].first);
		int r2 = findRoot(edges0[i].second);
		
		if(r1 != r2) {
			global --;
			rt[r1] = r2;
		}
	}
	
	for(int i = 0; i < (int)edges[0].size() && k > 0; i ++) {
		int r1 = findRoot(edges[0][i].first);
		int r2 = findRoot(edges[0][i].second);
		
		if(r1 != r2) {
			ans.pb(el(edges[0][i].first, edges[0][i].second, 0));
			global --;
			k --;
			rt[r1] = r2;
		}
	}
	
	if(k > 0) {
		printf("no solution\n");
		return;
	}
	
	for(int i = 0; i < (int)edges[1].size(); i ++) {
		int r1 = findRoot(edges[1][i].first);
		int r2 = findRoot(edges[1][i].second);
		
		if(r1 != r2) {
			ans.pb(el(edges[1][i].first, edges[1][i].second, 1));
			global --;
			rt[r1] = r2;
		}
	}
	
	if(global > 1) {
		printf("no solution\n");
		return;
	}
	
	for(int i = 0; i < ans.size(); i ++)
		printf("%d %d %d\n", ans[i].a, ans[i].b, ans[i].c);
}

int main()
{
	read();
	solve();

    return 0;
}
