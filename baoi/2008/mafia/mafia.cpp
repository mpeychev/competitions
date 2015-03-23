#include <iostream>
#include <stdio.h>
#include <queue>
#include <string.h>
#include <vector>

#define pb push_back

using namespace std;

typedef long long LL;

const LL INF = 1LL << 42;

struct el {
	int to;
	LL rd;
	int prv;
	bool type;
	
	el() {}
	el(int _to, LL _rd, int _prv, bool _type): to(_to), rd(_rd), prv(_prv), type(_type) {}
};

int n, m;
int a, b;
LL cost[256];

int source, sink;
int idx[512], cpy[512], sz;
el g[1 << 17];
int level[512];

vector< int > ans;

void read() {
	scanf("%d %d", &n, &m);
	scanf("%d %d", &a, &b);
	for(int i = 1; i <= n; i ++)
		scanf("%lld", &cost[i]);
}

void add(int x, int y, LL z) {
	g[sz] = el(y, z, idx[x], 1);
	idx[x] = sz ++;
	
	g[sz] = el(x, 0, idx[y], 0);
	idx[y] = sz ++;
}

void build() {
	memset(idx, -1, sizeof(idx));
	for(int i = 1; i <= n; i ++)
		add(i, i + n, cost[i]);
	
	int x, y;
	
	for(int i = 0; i < m; i ++) {
		scanf("%d %d", &x, &y);
		add(x + n, y, INF);
		add(y + n, x, INF);
	}
	
	source = a;
	sink = b + n;
}

bool bfs() {
	memset(level, -1, sizeof(level));
	queue< int > q;
	
	level[sink] = 0;
	q.push(sink);
	
	while(!q.empty()) {
		int tmp = q.front();
		q.pop();
		
		if(tmp == source) return true;
		
		for(int i = idx[tmp]; i != -1; i = g[i].prv)
			if(level[ g[i].to ] == -1 && g[i ^ 1].rd) {
				level[ g[i].to ] = level[tmp] + 1;
				q.push(g[i].to);
			}
	}
	
	return (level[source] != -1);
}

LL dfs(int cur, LL flow) {
	if(cur == sink)
		return flow;
	
	for(int &i = cpy[cur]; i != -1; i = g[i].prv)
		if(level[cur] - 1 == level[ g[i].to ] && g[i].rd) {
			LL fl = dfs(g[i].to, min(flow, g[i].rd));
			if(fl) {
				g[i].rd -= fl;
				g[i ^ 1].rd += fl;
				return fl;
			}
		}
	
	level[cur] = -42;
	return 0;
}

void dinitz() {
	LL maxFlow = 0, flow;
	while(bfs()) {
		memcpy(cpy, idx, sizeof(idx));
		while((flow = dfs(source, INF)) != 0)
			maxFlow += flow;
	}
}

void write() {
	for(int i = 1; i <= n; i ++)
		if(level[i] == -1)
			for(int j = idx[i]; j != -1; j = g[j].prv)
				if(level[ g[j].to ] != -1 && g[j].type) {
					ans.pb(i);
					break;
				}
	
	for(int i = 0; i < ans.size(); i ++) {
		if(i) printf(" ");
		printf("%d", ans[i]);
	}
	printf("\n");
}

int main()
{
	read();
	build();
	dinitz();
	write();

    return 0;
}
