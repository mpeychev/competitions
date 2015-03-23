#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

const int MAXN = 10100;
const int MAXP = 100100;
const int INF = 1 << 30;

struct edge {
	int a, b, c;
	
	edge() {}
	edge(int _a, int _b, int _c): a(_a), b(_b), c(_c) {}
};

int n, p;
int c[MAXN];
edge g[MAXP];
int rt[MAXN];
int ans;

void read() {
	int s, e, l;
	
	ans = INF;
	
	scanf("%d %d", &n, &p);
	
	for(int i = 1; i <= n; i ++) {
		scanf("%d", &c[i]);
		if(ans > c[i]) ans = c[i];
	}
	
	for(int i = 0; i < p; i ++) {
		scanf("%d %d %d", &s, &e, &l);
		g[i] = edge(s, e, 2 * l + c[s] + c[e]);
	}
}

bool cmp(edge x, edge y) {
	return x.c < y.c;
}

int getRoot(int node) {
	int ret = node;
	while(ret != rt[ret])
		ret = rt[ret];
	
	while(node != ret) {
		int up = rt[node];
		rt[node] = ret;
		node = up;
	}
	
	return ret;
}

void solve() {
	for(int i = 1; i <= n; i ++)
		rt[i] = i;
	
	sort(g, g + p, cmp);
	
	for(int i = 0; i < p; i ++) {
		int r1 = getRoot(g[i].a);
		int r2 = getRoot(g[i].b);
		
		if(r1 != r2) {
			ans += g[i].c;
			rt[r1] = r2;
		}
	}
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
