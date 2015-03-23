#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <queue>
#include <map>
#include <bitset>

#define pb push_back

using namespace std;

typedef long long LL;

const int MAXN = 100100;

struct Edge {
	int to, prv;
	bool value;
	bool exist;
	
	Edge() {}
	Edge(int _to, int _prv, bool _value, bool _exist): to(_to), prv(_prv), value(_value), exist(_exist) {}
};

struct el {
	int balance;
	bool restNode;
	
	el() {}
	el(int _balance, bool _restNode): balance(_balance), restNode(_restNode) {}
};

int n, sz;
int idx[MAXN];
Edge g[2 * MAXN];

LL answer;

void add(int a, int b, bool cow) {
	g[sz] = Edge(b, idx[a], cow, true);
	idx[a] = sz ++;
	
	g[sz] = Edge(a, idx[b], cow, true);
	idx[b] = sz ++;
}

void read() {
	int a, b, c;
	memset(idx, -1, sizeof(idx));
	
	scanf("%d", &n);
	for(int i = 1; i < n; i ++) {
		scanf("%d %d %d", &a, &b, &c);
		add(a, b, c);
	}
}

queue<int> q;
bitset<MAXN> used;
int level[MAXN];
int prv[MAXN];
int subtree[MAXN];
int countNodes;

int bfs(int node) {
	used = 0;
	countNodes = 0;
	
	used[node] = true;
	level[node] = 0;
	prv[node] = -1;
	subtree[countNodes ++] = node;
	
	q.push(node);
	while(!q.empty()) {
		int tmp = q.front();
		q.pop();
		
		for(int i = idx[tmp]; i != -1; i = g[i].prv)
			if(g[i].exist && !used[ g[i].to ]) {
				used[ g[i].to ] = true;
				level[ g[i].to ] = level[tmp] + 1;
				prv[ g[i].to ] = tmp;
				subtree[countNodes ++] = g[i].to;
				q.push(g[i].to);
			}
	}
	
	if(countNodes == 1) return -1;
	
	int ret = node;
	for(int i = 1; i < countNodes; i ++)
		if(level[ret] < level[ subtree[i] ])
			ret = subtree[i];
	
	return ret;
}

int findRoot(int node) {
	int a = bfs(node);
	if(a == -1) return -1;
	
	int b = bfs(a);
	
	vector<int> diam;
	diam.pb(b);
	while(b != a) {
		b = prv[b];
		diam.pb(b);
	}
	
	return diam[(int)diam.size() >> 1];
}

void dfs(int cur, int parent, int ps, int count0) {
	if(!ps && count0 >= 2) answer ++;
	
	int nxtCount0 = count0;
	if(!ps) nxtCount0 ++;
	
	for(int i = idx[cur]; i != -1; i = g[i].prv)
		if(g[i].exist && g[i].to != parent) {
			if(g[i].value == true) dfs(g[i].to, cur, ps + 1, nxtCount0);
			else dfs(g[i].to, cur, ps - 1, nxtCount0);
		}
}

map<int, int> countBalance;
vector< el > vec;

void dfs2(int cur, int parent, int ps) {
	if(countBalance[ps] > 0) {
		vec.pb(el(ps, true));
		countBalance[ps] ++;
	}
	else {
		vec.pb(el(ps, false));
		countBalance[ps] = 1;
	}
	
	for(int i = idx[cur]; i != -1; i = g[i].prv)
		if(g[i].exist && g[i].to != parent) {
			if(g[i].value == true) dfs2(g[i].to, cur, ps + 1);
			else dfs2(g[i].to, cur, ps - 1);
		}
	
	countBalance[ps] --;
}

void go(int root) {
	root = findRoot(root);
	if(root == -1) return;
	
	dfs(root, -1, 0, 0);
	
	vector<int> children;
	map<int, int> yesZero;
	map<int, int> noZero;
	
	for(int i = idx[root]; i != -1; i = g[i].prv)
		if(g[i].exist) {
			children.pb(g[i].to);
			vec.clear();
			
			int startPS = 1;
			if(!g[i].value) startPS = -1;
			
			dfs2(g[i].to, root, startPS);
			
			for(int j = 0; j < (int)vec.size(); j ++) {
				answer += yesZero[ -vec[j].balance ];
				if(vec[j].restNode) answer += noZero[ -vec[j].balance ];
			}
			
			for(int j = 0; j < (int)vec.size(); j ++)
				if(vec[j].restNode) yesZero[ vec[j].balance ] ++;
				else noZero[ vec[j].balance ] ++;
			
			g[i].exist = false;
			g[i ^ 1].exist = false;
		}
	
	for(int i = 0; i < (int)children.size(); i ++)
		go(children[i]);
}

void solve() {
	countBalance[0] = 1;
	go(1);
	cout << answer << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
