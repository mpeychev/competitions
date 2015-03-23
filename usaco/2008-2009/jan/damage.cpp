#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>

#define pb push_back

using namespace std;

const int MAXP = 30300;

int p, c, n;
vector< int > g[MAXP];
bool reported[MAXP];
bool blocked[MAXP];
bool used[MAXP];
queue<int> q;
int cnt;

void read() {
	int a, b;
	
	scanf("%d %d %d", &p, &c, &n);
	for(int i = 0; i < c; i ++) {
		scanf("%d %d", &a, &b);
		g[a].pb(b);
		g[b].pb(a);
	}
	
	for(int i = 0; i < n; i ++) {
		scanf("%d", &a);
		reported[a] = true;
		
		q.push(a);
		used[a] = true;
	}
}

void dfs(int cur) {
	used[cur] = true;
	
	if(blocked[cur]) return;
	
	cnt ++;
	for(int i = 0; i < g[cur].size(); i ++)
		if(!used[ g[cur][i] ])
			dfs(g[cur][i]);
}

void solve() {
	while(!q.empty()) {
		int tmp = q.front();
		q.pop();
		
		if(!reported[tmp]) {
			blocked[tmp] = true;
			continue;
		}
		
		for(int i = 0; i < g[tmp].size(); i ++)
			if(!used[ g[tmp][i] ]) {
				used[ g[tmp][i] ] = true;
				q.push(g[tmp][i]);
			}
	}
	
	memset(used, 0, sizeof(used));
	
	dfs(1);
	
	cout << p - cnt << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
