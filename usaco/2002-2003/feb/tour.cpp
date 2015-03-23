#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int INF = 1 << 30;

struct Edge {
	int to, rd, prv, cost;
	
	Edge() {}
	Edge(int _to, int _rd, int _prv, int _cost): to(_to), rd(_rd), prv(_prv), cost(_cost) {}
};

int n, m;
Edge g[50500];
int idx[1 << 10];
int sz;

int d[1 << 10];
int edgeIdx[1 << 10];

int ans;

void add(int a, int b, int c) {
	g[sz] = Edge(b, 1, idx[a], c);
	idx[a] = sz ++;
	
	g[sz] = Edge(a, 0, idx[b], -c);
	idx[b] = sz ++;
}

void init() {
	int a, b, c;
	memset(idx, -1, sizeof(idx));
	
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i ++) {
		scanf("%d %d %d", &a, &b, &c);
		
		add(a, b, c);
		add(b, a, c);
	}
}

void fb() {
	for(int i = 1; i <= n; i ++) {
		d[i] = INF;
		edgeIdx[i] = -1;
	}
	d[1] = 0;

	for(int i = idx[1]; i != -1; i = g[i].prv)
		if(g[i].rd && g[i].cost < d[ g[i].to ]) {
			d[ g[i].to ] = g[i].cost;
			edgeIdx[ g[i].to ] = i;
		}

	bool run = true;
	for(int iter = 0; iter < n && run; iter ++) {
		run = false;
		for(int i = 1; i <= n; i ++)
			for(int j = idx[i]; j != -1; j = g[j].prv)
				if(d[i] != INF && g[j].rd && d[i] + g[j].cost < d[ g[j].to ]) {
					d[ g[j].to ] = d[i] + g[j].cost;
					edgeIdx[ g[j].to ] = j;
					run = true;
				}
	}

	ans += d[n];	
	
	int tmp = n;
	while(tmp != 1) {
		int e = edgeIdx[tmp];
		g[e].rd -= 1;
		g[e ^ 1].rd += 1;
		tmp = g[e ^ 1].to;
	}
}

void solve() {
	for(int iter = 0; iter < 2; iter ++)
		fb();
	
	cout << ans << endl;
}

int main()
{
	init();
	solve();

    return 0;
}
