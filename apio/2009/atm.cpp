#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>

#define pb push_back

using namespace std;

const int MAXN = 500500;
const int MAXM = 500500;

int n, m;
vector< int > g[MAXN];
vector< int > gPrim[MAXN];
int cash[MAXN];
int start;
int p;
int pubs[MAXN];

int list[MAXN];
int sz;
bool used[MAXN];

int color[MAXN];
int sumCash[MAXN];
int compCount;

bool validEnd[MAXN];

vector< int > compG[MAXN];

vector<int> seq;
int dp[MAXN];

void read() {
	int a, b;
	
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i ++) {
		scanf("%d %d", &a, &b);
		g[a].pb(b);
		gPrim[b].pb(a);
	}
	
	for(int i = 1; i <= n; i ++)
		scanf("%d", &cash[i]);
	
	scanf("%d %d", &start, &p);
	for(int i = 0; i < p; i ++)
		scanf("%d", &pubs[i]);
}

void dfs1(int cur) {
	used[cur] = true;
	for(int i = 0; i < (int)g[cur].size(); i ++)
		if(!used[ g[cur][i] ])
			dfs1(g[cur][i]);
	list[sz ++] = cur;
}

void dfs2(int cur) {
	color[cur] = compCount;
	for(int i = 0; i < (int)gPrim[cur].size(); i ++)
		if(color[ gPrim[cur][i] ] == -1)
			dfs2(gPrim[cur][i]);
}

void dfs3(int cur) {
	used[cur] = true;
	for(int i = 0; i < (int)compG[cur].size(); i ++)
		if(!used[ compG[cur][i] ])
			dfs3(compG[cur][i]);
	seq.pb(cur);
}

void solve() {
	for(int i = 1; i <= n; i ++)
		if(!used[i])
			dfs1(i);
	
	memset(color, -1, sizeof(color));
	for(int i = sz - 1; i >= 0; i --)
		if(color[ list[i] ] == -1) {
			dfs2(list[i]);
			compCount ++;
		}
	
	for(int i = 1; i <= n; i ++)
		sumCash[ color[i] ] += cash[i];
	
	for(int i = 0; i < p; i ++)
		validEnd[ color[ pubs[i] ] ] = true;
	
	for(int i = 1; i <= n; i ++)
		for(int j = 0; j < (int)g[i].size(); j ++)
			if(color[i] != color[ g[i][j] ])
				compG[ color[i] ].pb(color[ g[i][j] ]);
	
	memset(used, 0, sizeof(used));
	for(int i = 0; i < compCount; i ++)
		if(!used[i])
			dfs3(i);
	
	for(int i = 0; i < (int)seq.size(); i ++) {
		int cur = seq[i];
		
		if(validEnd[cur]) dp[cur] = sumCash[cur];
		else dp[cur] = -1;
		
		for(int j = 0; j < (int)compG[cur].size(); j ++) {
			int nxt = compG[cur][j];
			
			if(dp[nxt] == -1) continue;
			if(dp[nxt] + sumCash[cur] > dp[cur])
				dp[cur] = dp[nxt] + sumCash[cur];
		}
	}
	
	cout << dp[ color[start] ] << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
