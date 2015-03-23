#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <queue>

#define pb push_back

using namespace std;

const int MAXN = 256;
const int INF = 1 << 25;

struct el {
	int to, rd, prv;
	
	el() {}
	el(int _to, int _rd, int _prv): to(_to), rd(_rd), prv(_prv) {}
};

int k, c, m, n;
int ma3x[MAXN][MAXN];
vector<int> vec;

int source, sink;
int idx[MAXN], cpy[MAXN], level[MAXN];
el g[1 << 14];
int sz;

void read() {
	scanf("%d %d %d", &k, &c, &m);
	
	n = k + c;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			scanf("%d", &ma3x[i][j]);
}

void add(int a, int b, int c) {
	g[sz] = el(b, c, idx[a]);
	idx[a] = sz ++;
	
	g[sz] = el(a, 0, idx[b]);
	idx[b] = sz ++;
}

bool bfs() {
	memset(level, -1, sizeof(level));
	queue<int> q;
	
	q.push(sink);
	level[sink] = 0;
	while(!q.empty()) {
		int tmp = q.front();
		q.pop();
		
		if(tmp == source) return true;
		
		for(int i = idx[tmp]; i != -1; i = g[i].prv) {
			int nxt = g[i].to;
			if(level[nxt] == -1 && g[i ^ 1].rd) {
				level[nxt] = level[tmp] + 1;
				q.push(nxt);
			}
		}
	}
	return (level[source] != -1);
}

int dfs(int cur, int flow) {
	if(cur == sink)
		return flow;
	
	for(int &i = cpy[cur]; i != -1; i = g[i].prv) {
		int nxt = g[i].to;
		if(level[cur] - 1 == level[nxt] && g[i].rd) {
			int fl = dfs(nxt, min(flow, g[i].rd));
			if(fl) {
				g[i].rd -= fl;
				g[i ^ 1].rd += fl;
				return fl;
			}
		}
	}
	
	level[cur] = -42;
	return 0;
}

bool check(int lim) {
	/// Build
	memset(idx, -1, sizeof(idx));
	sz = 0;
	
	source = n;
	sink = n + 1;
	
	for(int i = 0; i < k; i ++)
		add(source, i, m);
	
	for(int i = k; i < n; i ++)
		add(i, sink, 1);
	
	for(int i = 0; i < k; i ++)
		for(int j = k; j < n; j ++)
			if(ma3x[i][j] <= lim)
				add(i, j, 1);
	
	/// Dinitz
	int maxFlow = 0, flow;
	while(bfs()) {
		memcpy(cpy, idx, sizeof(idx));
		while((flow = dfs(source, INF)) != 0)
			maxFlow += flow;
	}
	
	return (maxFlow == c);
}

void solve() {
	/// Floyd-Warshall
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			if(!ma3x[i][j] && i != j)
				ma3x[i][j] = INF;
	
	for(int h = 0; h < n; h ++)
		for(int i = 0; i < n; i ++)
			for(int j = 0; j < n; j ++)
				if(ma3x[i][h] + ma3x[h][j] < ma3x[i][j])
					ma3x[i][j] = ma3x[i][h] + ma3x[h][j];
	
	/// Binary search
	for(int i = 0; i < k; i ++)
		for(int j = k; j < n; j ++)
			vec.pb(ma3x[i][j]);
	
	sort(vec.begin(), vec.end());
	
	int le = 0, ri = (int)vec.size() - 1, mid;
	int ans = INF;
	
	while(le <= ri) {
		mid = (le + ri) >> 1;
		if(check(vec[mid])) {
			ans = vec[mid];
			ri = mid - 1;
		}
		else le = mid + 1;
	}
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
