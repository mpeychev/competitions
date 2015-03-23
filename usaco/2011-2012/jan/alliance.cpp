#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>

#define pb push_back

using namespace std;

typedef long long LL;

const int MAXN = 100100;
const LL MOD = 1000000007LL;

struct Edge {
	int to, prv;
	bool passed;
	
	Edge() {}
	Edge(int _to, int _prv, bool _passed): to(_to), prv(_prv), passed(_passed) {}
};

int n, m;

int idx[MAXN];
Edge g[2 * MAXN];
int sz;

LL ret = 1;
bool used[MAXN];
bool cyc;

vector<int> t[MAXN];
LL dp[MAXN];

void add(int a, int b) {
	g[sz] = Edge(b, idx[a], false);
	idx[a] = sz ++;
	
	g[sz] = Edge(a, idx[b], false);
	idx[b] = sz ++;
}

void read() {
	int a, b;
	memset(idx, -1, sizeof(idx));
	
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i ++) {
		scanf("%d %d", &a, &b);
		add(a, b);
	}
}

void dfs(int cur) {
	used[cur] = true;
	for(int i = idx[cur]; i != -1; i = g[i].prv)
		if(!g[i].passed) {
			g[i].passed = true;
			g[i ^ 1].passed = true;
			
			if(!used[ g[i].to ]) {
				t[cur].pb(g[i].to);
				dfs(g[i].to);
			}
			else cyc = true;
		}
}

LL go(int node, bool fl) {
	if(!fl) return 1;
	
	LL &ret = dp[node];
	
	if(ret != -1)
		return ret;
	
	ret = 1;
	for(int i = 0; i < (int)t[node].size(); i ++) {
		ret += go(t[node][i], true);
		if(ret >= MOD) ret -= MOD;
	}
	
	return ret;
}

void solve() {
	memset(dp, -1, sizeof(dp));
	
	for(int i = 1; i <= n; i ++)
		if(!used[i]) {
			cyc = false;
			dfs(i);
			
			if(cyc) {
				ret = ret << 1;
				if(ret >= MOD) ret -= MOD;
			}
			else {
				ret *= go(i, true);
				if(ret >= MOD) ret %= MOD;
			}
		}
	
	cout << ret << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
