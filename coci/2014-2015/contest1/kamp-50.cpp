#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>

#define pb push_back
#define mp make_pair

using namespace std;

typedef long long LL;
typedef pair<int, LL> PIL;

const int MAXN = 2020;
const int MAX_LOG = 13;

int n, k;
vector< PIL > g[MAXN];
int teams[MAXN];

int level[MAXN];
int p[MAXN][16];
int dist[MAXN];

int timeIn[MAXN];
int br;

void read() {
	int a, b;
	LL c;
	
	scanf("%d %d", &n, &k);
	for(int i = 1; i < n; i ++) {
		scanf("%d %d %lld", &a, &b, &c);
		g[a].pb(mp(b, c));
		g[b].pb(mp(a, c));
	}
	
	for(int i = 0; i < k; i ++)
		scanf("%d", &teams[i]);
}

void dfs(int cur) {
	br ++;
	timeIn[cur] = br;
	
	for(int i = 0; i < g[cur].size(); i ++)
		if(level[ g[cur][i].first ] == -1) {
			level[ g[cur][i].first ] = level[cur] + 1;
			p[ g[cur][i].first ][0] = cur;
			dist[ g[cur][i].first ] = dist[cur] + g[cur][i].second;
			dfs(g[cur][i].first);
		}
}

int lca(int u, int v) {
	if(level[u] > level[v])
		swap(u, v);
	
	for(int i = MAX_LOG; i >= 0; i --)
		if(p[v][i] != -1 && level[ p[v][i] ] >= level[u])
			v = p[v][i];
	
	if(u == v) return u;
	
	for(int i = MAX_LOG; i >= 0; i --)
		if(p[v][i] != p[u][i])
			v = p[v][i], u = p[u][i];
	
	return p[v][0];
}

bool cmp(int x, int y) {
	return timeIn[x] < timeIn[y];
}

LL getDist(int a, int b) {
	return dist[a] + dist[b] - 2 * dist[ lca(a, b) ];
}

void go(int root) {
	memset(level, -1, sizeof(level));
	memset(p, -1, sizeof(p));
	memset(dist, 0, sizeof(dist));
	memset(timeIn, 0, sizeof(timeIn));
	br = 0;
	
	level[root] = 0;
	dfs(root);
	
	for(int j = 1; j <= MAX_LOG; j ++)
		for(int i = 1; i <= n; i ++)
			if(p[i][j - 1] != -1)
				p[i][j] = p[ p[i][j - 1] ][j - 1];
	
	sort(teams, teams + k, cmp);
	
	LL ret = 0;
	ret = getDist(root, teams[0]);
	for(int i = 0; i < k - 1; i ++)
		ret += getDist(teams[i], teams[i + 1]);
	ret += getDist(root, teams[k - 1]);
	
	LL mx = -1;
	for(int i = 0; i < k; i ++)
		mx = max(mx, getDist(root, teams[i]));
	
	cout << ret - mx << endl;
}

void solve() {
	for(int i = 1; i <= n; i ++)
		go(i);
}

int main()
{
	read();
	solve();

    return 0;
}
