#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
#include <stack>

#define pb push_back
#define mp make_pair

using namespace std;

typedef long long LL;

const int MAXN = 100100;

const LL prime = 145207LL;
const LL MOD = 1000000007LL;

int n;
vector<int> g[MAXN];

int prv[MAXN];
int cycle[MAXN], len;
bool inCycle[MAXN];

vector<int> leaves;
map< vector<int> , int > cache;
int treeLevel[MAXN];
short int childrenCount[MAXN];
int parent[MAXN];
int nodeHash[MAXN];

LL hFront[MAXN], hBack[MAXN];
vector<int> vec;
set< LL > st;

bool used[MAXN];

queue<int> q;
stack<int> s;
short int start[MAXN];

void read() {
	int a, b;
	
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) {
		scanf("%d %d", &a, &b);
		g[a].pb(b);
		g[b].pb(a);
	}
}

void findCycle() {
	s.push(1);
	while(!s.empty()) {
		int cur = s.top();
		
		int i = start[cur];
		start[cur] ++;
		
		if(i < (int)g[cur].size()) {
			if(prv[ g[cur][i] ] == -1) {
				prv[ g[cur][i] ] = cur;
				s.push(g[cur][i]);
			}
			else if(g[cur][i] != prv[cur]) {
				int tmp = cur;
				while(tmp != g[cur][i]) {
					cycle[len ++] = tmp;
					tmp = prv[tmp];
				}
				cycle[len ++] = tmp;
				return;
			}
		}
		else s.pop();
	}
}

void bfs(int root) {
	treeLevel[root] = 1;
	q.push(root);
	
	while(!q.empty()) {
		int tmp = q.front();
		q.pop();
		
		for(int i = 0; i < (int)g[tmp].size(); i ++)
			if(!inCycle[ g[tmp][i] ] && !treeLevel[ g[tmp][i] ]) {
				treeLevel[ g[tmp][i] ] = treeLevel[tmp] + 1;
				parent[ g[tmp][i] ] = tmp;
				childrenCount[tmp] ++;
				q.push(g[tmp][i]);
			}
		
		if(!childrenCount[tmp]) leaves.pb(tmp);
	}
}

void hashNodes() {
	cache.clear();
	int lastHash = 0;
	
	for(int i = 0; i < (int)leaves.size(); i ++)
		q.push(leaves[i]);
	
	while(!q.empty()) {
		int tmp = q.front();
		q.pop();
		
		vector<int> childrenHashes;
		for(int i = 0; i < (int)g[tmp].size(); i ++)
			if(tmp == parent[ g[tmp][i] ])
				childrenHashes.pb(nodeHash[ g[tmp][i] ]);
			
		sort(childrenHashes.begin(), childrenHashes.end());
		if(cache.find(childrenHashes) == cache.end()) {
			lastHash ++;
			cache[ childrenHashes ] = lastHash;
		}
		
		nodeHash[tmp] = cache[ childrenHashes ];
		
		if(parent[tmp]) {
			childrenCount[ parent[tmp] ] --;
			if(!childrenCount[ parent[tmp] ]) q.push(parent[tmp]);
		}
	}
}

void go(int root) {
	q.push(root);
	while(!q.empty()) {
		int tmp = q.front();
		q.pop();
		
		used[tmp] = true;
		
		set< int > seen;
		for(int i = 0; i < (int)g[tmp].size(); i ++)
			if(tmp == parent[ g[tmp][i] ] && seen.find(nodeHash[ g[tmp][i] ]) == seen.end()) {
				seen.insert(nodeHash[ g[tmp][i] ]);
				q.push(g[tmp][i]);
			}
	}
}

void solve() {
	/// find cycle
	memset(prv, -1, sizeof(prv));
	prv[1] = 0;
	findCycle();
	for(int i = 0; i < len; i ++)
		inCycle[ cycle[i] ] = true;
	
	/// hash tree nodes
	for(int i = 0; i < len; i ++) {
		leaves.clear();
		bfs(cycle[i]);
		hashNodes();
	}
	
	/// calc sequence hashes
	LL pw;
	
	// hash front
	pw = 1;
	hFront[len - 1] = nodeHash[ cycle[len - 1] ];
	for(int i = 0; i < len - 1; i ++) {
		pw = (pw * prime) % MOD;
		
		hFront[len - 1] = (hFront[len - 1] + nodeHash[ cycle[i] ] * pw) % MOD;
	}
	
	pw = (pw * prime) % MOD;
	
	for(int i = len - 2; i >= 0; i --) {
		hFront[i] = hFront[i + 1] * prime + MOD;
		hFront[i] -= (nodeHash[ cycle[i] ] * pw) % MOD;
		hFront[i] += nodeHash[ cycle[i] ];
		hFront[i] %= MOD;
	}
	
	// hash back
	pw = 1;
	hBack[0] = nodeHash[ cycle[0] ];
	for(int i = len - 1; i >= 1; i --) {
		pw = (pw * prime) % MOD;
		
		hBack[0] = (hBack[0] + nodeHash[ cycle[i] ] * pw) % MOD;
	}
	
	pw = (pw * prime) % MOD;
	
	for(int i = 1; i < len; i ++) {
		hBack[i] = hBack[i - 1] * prime + MOD;
		hBack[i] -= (nodeHash[ cycle[i] ] * pw) % MOD;
		hBack[i] += nodeHash[ cycle[i] ];
		hBack[i] %= MOD;
	}
	
	for(int i = 0; i < len; i ++) {
		if(st.find(hFront[i]) != st.end()) continue;
		if(st.find(hBack[i]) != st.end()) continue;
		
		vec.pb(cycle[i]);
		st.insert(hFront[i]);
		st.insert(hBack[i]);
	}
	
	/// back in the trees
	for(int i = 0; i < (int)vec.size(); i ++)
		go(vec[i]);
	
	/// calc answer
	int ans = 0;
	for(int i = 1; i <= n; i ++)
		if(used[i] && (int)g[i].size() < 4)
			ans ++;
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
