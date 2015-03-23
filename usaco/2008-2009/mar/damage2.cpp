#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

const int MAXP = 3030;
const int INF = 1 << 30;

struct el {
	int to, rd, prv;
	
	el() {}
	el(int _to, int _rd, int _prv): to(_to), rd(_rd), prv(_prv) {}
};

int p, c, n;
bool ma3x[MAXP][MAXP];
bool report[MAXP];
el g[1 << 17];
int sz, idx[2 * MAXP], cpy[2 * MAXP], level[2 * MAXP];
int source, sink;

void read() {
	int a, b;
	
	scanf("%d %d %d", &p, &c, &n);
	for(int i = 0; i < c; i ++) {
		scanf("%d %d", &a, &b);
		if(a != b) ma3x[a][b] = ma3x[b][a] = true;
	}
	for(int i = 0; i < n; i ++) {
		scanf("%d", &a);
		report[a] = true;
	}
}

void add(int a, int b, int c) {
	g[sz] = el(b, c, idx[a]);
	idx[a] = sz ++;
	
	g[sz] = el(a, 0, idx[b]);
	idx[b] = sz ++;
}

void build() {
	memset(idx, -1, sizeof(idx));
	
	source = 1;
	sink = 2 * p + 1;
	for(int i = 1; i <= p; i ++)
		for(int j = i + 1; j <= p; j ++)
			if(ma3x[i][j]) {
				add(i + p, j, INF);
				add(j + p, i, INF);
			}
	
	add(1, 1 + p, INF);
	for(int i = 2; i <= p; i ++)
		if(!report[i]) add(i, i + p, 1);
		else {
			add(i, i + p, INF);
			add(i + p, sink, INF);
		}
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
		
		for(int i = idx[tmp]; i != -1; i = g[i].prv)
			if(level[ g[i].to ] == -1 && g[i ^ 1].rd) {
				level[ g[i].to ] = level[tmp] + 1;
				q.push(g[i].to);
			}
	}
	
	return (level[source] != -1);
}

int dfs(int cur, int flow) {
	if(cur == sink)
		return flow;
	
	for(int &i = cpy[cur]; i != -1; i = g[i].prv)
		if(level[cur] - 1 == level[ g[i].to ] && g[i].rd) {
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
