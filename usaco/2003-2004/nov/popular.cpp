// Strongly-connected components

#include <iostream>
#include <stdio.h>
#include <vector>
#include <deque>
#include <string.h>

#define pb push_back

using namespace std;

const int MAXN = 10100;

int n, m;
vector<int> g[MAXN], gt[MAXN];
deque<int> li;
bool used[MAXN];
int color[MAXN], compCount;

vector<int> dag[MAXN];
int out[MAXN];

void read() {
	int a, b;
	
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i ++) {
		scanf("%d %d", &a, &b);
		g[a].pb(b);
		gt[b].pb(a);
	}
}

void dfs1(int cur) {
	used[cur] = true;
	for(int i = 0; i < (int)g[cur].size(); i ++)
		if(!used[ g[cur][i] ])
			dfs1(g[cur][i]);
	li.push_front(cur);
}

void dfs2(int cur) {
	color[cur] = compCount;
	for(int i = 0; i < (int)gt[cur].size(); i ++)
		if(color[ gt[cur][i] ] == -1)
			dfs2(gt[cur][i]);
}

void dfs3(int cur) {
	used[cur] = true;
	for(int i = 0; i < (int)dag[cur].size(); i ++)
		if(!used[ dag[cur][i] ])
			dfs3(dag[cur][i]);
}

void solve() {
	for(int i = 1; i <= n; i ++)
		if(!used[i])
			dfs1(i);
	
	memset(color, -1, sizeof(color));
	for(int i = 0; i < (int)li.size(); i ++)
		if(color[ li[i] ] == -1) {
			dfs2(li[i]);
			compCount ++;
		}
	
	if(compCount == 1) {
		cout << n << endl;
		return;
	}
	
	for(int i = 1; i <= n; i ++)
		for(int j = 0; j < (int)g[i].size(); j ++)
			if(color[i] != color[ g[i][j] ]) {
				out[ color[i] ] ++;
				dag[ color[ g[i][j] ] ].pb(color[i]);
			}
	
	int countZero = 0, compIndex = -1;
	for(int i = 0; i < compCount; i ++)
		if(!out[i]) {
			countZero ++;
			compIndex = i;
		}
	
	if(countZero > 1) {
		cout << 0 << endl;
		return;
	}
	
	memset(used, 0, sizeof(used));
	dfs3(compIndex);
	
	int cnt = 0;
	for(int i = 0; i < compCount; i ++)
		if(used[i])
			cnt ++;
	
	if(cnt == compCount) {
		int ans = 0;
		for(int i = 1; i <= n; i ++)
			ans += (color[i] == compIndex);
		cout << ans << endl;
	}
	else cout << "0\n";
}

int main()
{
	read();
	solve();

    return 0;
}
