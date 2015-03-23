#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

const int MAXN = 512;
const int MAXC = 500 * 500 + 10;

struct edge {
	int a, b, r;
	
	edge() {}
	edge(int _a, int _b, int _r): a(_a), b(_b), r(_r) {}
};

int n, m, t;
int h[MAXN][MAXN];
short int used[MAXN][MAXN];

int d[MAXC];
long long ans;

vector< edge > e;

vector< int > l[MAXC];
int listIndex[MAXC];

void read() {
	scanf("%d %d %d", &n, &m, &t);
	
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
			scanf("%d", &h[i][j]);
	
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
			scanf("%d", &used[i][j]);
}

int abss(int x) {
	if(x < 0) return -x;
	return x;
}

bool cmp(edge e1, edge e2) {
	return e1.r < e2.r;
}

void mergeLists(int i, int j, int val) {
//	cout << "Merge " << i << " " << j << " " << val << endl;
	
	if((int)l[i].size() < (int)l[j].size())
		i ^= j ^= i ^= j;
	
	int szi = (int)l[i].size();
	int szj = (int)l[j].size();
	
	if(szi + szj >= t) {
		if(szi < t) {
			for(int iter = 0; iter < szi; iter ++)
				d[ l[i][iter] ] = val;
		}
		
		if(szj < t) {
			for(int iter = 0; iter < szj; iter ++)
				d[ l[j][iter] ] = val;
		}
	}
	
	while(!l[j].empty()) {
		int cur = l[j].back();
		l[j].pop_back();
		l[i].pb(cur);
		listIndex[cur] = i;
	}
}

void solve() {
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++) {
			int idx = i * m + j;
			if(j != m - 1) e.pb(edge(idx, idx + 1, abss(h[i][j] - h[i][j + 1])));
			if(i != n - 1) e.pb(edge(idx, idx + m, abss(h[i][j] - h[i + 1][j])));
		}
	
	sort(e.begin(), e.end(), cmp);
	
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++) {
			int idx = i * m + j;
			l[idx].pb(idx);
			listIndex[idx] = idx;
		}
	
	for(int i = 0; i < (int)e.size(); i ++) {
		int u = e[i].a;
		int v = e[i].b;
		
		if(listIndex[u] != listIndex[v])
			mergeLists(listIndex[u], listIndex[v], e[i].r);
	}
	
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
			if(used[i][j]) {
				int idx = i * m + j;
//				cout << d[idx] << endl;
				ans += (long long)d[idx];
			}
	
	cout << ans << endl;
}

int main()
{
	freopen("skilevel.in", "r", stdin);
	freopen("skilevel.out", "w", stdout);
	
	read();
	solve();
	
	return 0;
}
