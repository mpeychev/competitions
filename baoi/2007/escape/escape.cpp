#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;

struct el {
	int to, rd, prv;
	
	el() {}
	el(int _to, int _rd, int _prv): to(_to), rd(_rd), prv(_prv) {}
};

const int INF = 1 << 20;

LL l, w, n;
PLL p[256];
el g[1 << 20];
int idx[512], cpy[512], sz;
int level[512];
int source, sink;

void read() {
	scanf("%lld %lld %lld", &l, &w, &n);
	for(int i = 0; i < n; i ++)
		scanf("%lld %lld", &p[i].first, &p[i].second);
}

void add(int a, int b, int c) {
	g[sz] = el(b, c, idx[a]);
	idx[a] = sz ++;
	
	g[sz] = el(a, 0, idx[b]);
	idx[b] = sz ++;
}

LL SQU(LL x) {
	return x * x;
}

LL dist(PLL p1, PLL p2) {
	return SQU(p1.first - p2.first) + SQU(p1.second - p2.second);
}

void build() {
	memset(idx, -1, sizeof(idx));
	
	source = 2 * n;
	sink = 2 * n + 1;
	
	for(int i = 0; i < n; i ++)
		add(2 * i, 2 * i + 1, 1);
	
	for(int i = 0; i < n; i ++) {
		if(p[i].second - 100 <= 0)
			add(source, 2 * i, INF);
		if(p[i].second + 100 >= w)
			add(2 * i + 1, sink, INF);
	}
	
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			if(i != j && dist(p[i], p[j]) <= 200 * 200)
				add(2 * i + 1, 2 * j, INF);
}

bool bfs() {
	memset(level, 0, sizeof(level));
	queue<int> q;
	
	level[sink] = 1;
	q.push(sink);
	
	while(!q.empty()) {
		int tmp = q.front();
		q.pop();
		
		if(tmp == source) return true;
		
		for(int i = idx[tmp]; i != -1; i = g[i].prv)
			if(!level[ g[i].to ] && g[i ^ 1].rd) {
				level[ g[i].to ] = level[tmp] + 1;
				q.push(g[i].to);
			}
	}
	
	return (level[source] != 0);
}

int dfs(int cur, int flow) {
	if(cur == sink)
		return flow;
	
	for(int &i = cpy[cur]; i != -1; i = g[i].prv)
		if(level[ cur ] - 1 == level[ g[i].to ] && g[i].rd) {
			int fl = dfs(g[i].to, min(flow, g[i].rd));
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
	int maxFlow = 0, curFlow;
	while(bfs()) {
		memcpy(cpy, idx, sizeof(idx));
		while((curFlow = dfs(source, INF)) != 0)
			maxFlow += curFlow;
	}
	cout << maxFlow << endl;
}

int main()
{
	read();
	build();
	dinitz();

    return 0;
}
