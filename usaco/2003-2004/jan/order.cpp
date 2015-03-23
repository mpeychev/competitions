#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 1515;
const int MAXM = 10100;

int n, m;
vector<int> g[MAXN];
PII edges[MAXM];
bool used[MAXN];
vector<int> li;
int pos[MAXN];
bool ma3x[MAXN][MAXN];
vector< PII > ans;

void read() {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i ++) {
		scanf("%d %d", &edges[i].first, &edges[i].second);
		g[ edges[i].first ].pb(edges[i].second);
	}
}

void dfs(int cur) {
	used[cur] = true;
	for(int i = 0; i < g[cur].size(); i ++)
		if(!used[ g[cur][i] ])
			dfs(g[cur][i]);
	li.pb(cur);
}

bool cmp(PII a, PII b) {
	if(pos[a.second] != pos[b.second])
		return pos[a.second] < pos[b.second];
	return pos[a.first] > pos[b.first];
}

void solve() {
	for(int i = 1; i <= n; i ++)
		if(!used[i])
			dfs(i);
	reverse(li.begin(), li.end());
	
	for(int i = 0; i < li.size(); i ++)
		pos[ li[i] ] = i;
	
	sort(edges, edges + m, cmp);
	
	for(int i = 0; i < m; i ++)
		if(!ma3x[ edges[i].first ][ edges[i].second ]) {
			ans.pb(edges[i]);
			
			ma3x[ edges[i].first ][ edges[i].second ] = true;
			for(int j = 1; j <= n; j ++)
				if(ma3x[j][ edges[i].first ])
					ma3x[j][ edges[i].second ] = true;
		}
	
	sort(ans.begin(), ans.end());
	
	printf("%d\n", (int)ans.size());
	for(int i = 0; i < (int)ans.size(); i ++)
		printf("%d %d\n", ans[i].first, ans[i].second);
}

int main()
{
	read();
	solve();
	
	return 0;
}
