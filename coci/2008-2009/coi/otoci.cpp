#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <algorithm>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 1 << 15;
const int BOUND = 170;

int n;
int pengCount[MAXN];

/// Union-find
int rt[MAXN];

/// LCA
int parent[MAXN][16];

/// Components
struct Edge1 {
	int nextComponent;
	int nextNode;
	int prv;
	
	Edge1() {}
	Edge1(int _nextComponent, int _nextNode, int _prv): nextComponent(_nextComponent), nextNode(_nextNode), prv(_prv) {}
};

Edge1 g1[1 << 9];
int idx1[MAXN];
int sz1;

int compCount;
int inComponent[MAXN];

PII edgesToAdd[1 << 8];
int newBridgesCount;

int levelAdder;
int levelComponent[MAXN];
int prevEdge[MAXN];

void add1(int a, int b) {
	g1[sz1] = Edge1(inComponent[b], b, idx1[ inComponent[a] ]);
	idx1[ inComponent[a] ] = sz1 ++;
	
	g1[sz1] = Edge1(inComponent[a], a, idx1[ inComponent[b] ]);
	idx1[ inComponent[b] ] = sz1 ++;
}

/// Trees
struct Edge {
	int to, prv;
	bool isHeavy;
	
	Edge() {}
	Edge(int _to, int _prv): to(_to), prv(_prv), isHeavy(false) {}
};

Edge g[2 * MAXN];
int idx[MAXN];
int sz;

int subTreeSize[MAXN];
int levelInTree[MAXN];

void add(int a, int b) {
	g[sz] = Edge(b, idx[a]);
	idx[a] = sz ++;
	
	g[sz] = Edge(a, idx[b]);
	idx[b] = sz ++;
}

/// Chains
struct Chain {
	vector< int > tree;
	
	int totalSum;
	int chainStart;
	
	void update(int idx, int toAdd) {
		int treeSize = (int)tree.size();
		while(idx < treeSize) {
			tree[idx] += toAdd;
			idx += (idx & -idx);
		}
	}
	
	int get(int idx) {
		int ret = 0;
		while(idx) {
			ret += tree[idx];
			idx -= (idx & -idx);
		}
		return ret;
	}
	
	int get(int le, int ri) {
		return get(ri) - get(le - 1);
	}
};

Chain vec[MAXN];
int chainsCount;
int inChain[MAXN], posInChain[MAXN], chainSize[MAXN];

/// BFS
int level[MAXN], prv[MAXN];

void read() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &pengCount[i]);
}

void init() {
	for(int i = 1; i <= n; i ++)
		rt[i] = i;
	
	memset(parent, -1, sizeof(parent));
	
	memset(idx1, -1, sizeof(idx1));
	for(int i = 1; i <= n; i ++)
		inComponent[i] = i;
	
	memset(idx, -1, sizeof(idx));
}

int findRoot(int u) {
	int ret = u;
	while(rt[ret] != ret)
		ret = rt[ret];
	
	while(u != ret) {
		int up = rt[u];
		rt[u] = ret;
		u = up;
	}
	
	return ret;
}

int diameter(int cur) {
	int end1 = cur, end2 = cur, mx1 = -1, mx2 = -1;
	queue<int> q;
	
	q.push(cur);
	level[cur] = 0;
	while(!q.empty()) {
		int tmp = q.front();
		q.pop();
		
		if(level[tmp] > mx1) {
			mx1 = level[tmp];
			end1 = tmp;
		}
		
		inComponent[tmp] = compCount;
		
		for(int i = idx[tmp]; i != -1; i = g[i].prv)
			if(level[ g[i].to ] == -1) {
				level[ g[i].to ] = level[tmp] + 1;
				q.push(g[i].to);
			}
	}
	
	q.push(end1);
	level[end1] = mx1 + 1;
	while(!q.empty()) {
		int tmp = q.front();
		q.pop();
		
		if(level[tmp] > mx2) {
			mx2 = level[tmp];
			end2 = tmp;
		}
		
		for(int i = idx[tmp]; i != -1; i = g[i].prv)
			if(level[ g[i].to ] <= mx1) {
				level[ g[i].to ] = level[tmp] + 1;
				prv[ g[i].to ] = tmp;
				q.push(g[i].to);
			}
	}
	
	vector<int> diam;
	cur = end2;
	diam.pb(cur);
	while(cur != end1) {
		cur = prv[cur];
		diam.pb(cur);
	}
	
	int szDiam = (int)diam.size();
	return diam[ szDiam >> 1 ];
}

void dfs(int cur) {
	subTreeSize[cur] = 1;
	for(int i = idx[cur]; i != -1; i = g[i].prv)
		if(!subTreeSize[ g[i].to ]) {
			parent[ g[i].to ][0] = cur;
			levelInTree[ g[i].to ] = levelInTree[cur] + 1;
			dfs(g[i].to);
			subTreeSize[cur] += subTreeSize[ g[i].to ];
		}
	
	for(int i = idx[cur]; i != -1; i = g[i].prv)
		if(subTreeSize[cur] > subTreeSize[ g[i].to ]) {
			if((subTreeSize[cur] >> 1) + 1 <= subTreeSize[ g[i].to ]) {
				g[i].isHeavy = true;
				g[i ^ 1].isHeavy = true;
			}
			else {
				g[i].isHeavy = false;
				g[i ^ 1].isHeavy = false;
			}
		}
}

void dfs2(int cur) {
	for(int i = idx[cur]; i != -1; i = g[i].prv)
		if(g[i].to != parent[cur][0]) {
			if(g[i].isHeavy) {
				if(inChain[cur] == -1) {
					inChain[cur] = chainsCount;
					posInChain[cur] = 1;
					chainSize[chainsCount] = 1;
					vec[chainsCount].chainStart = cur;
					
					chainsCount ++;
				}
				
				inChain[ g[i].to ] = inChain[cur];
				posInChain[ g[i].to ] = posInChain[cur] + 1;
				chainSize[ inChain[ g[i].to ] ] ++;
			}
			
			dfs2(g[i].to);
		}
}

void fix() {
	for(int i = 0; i < newBridgesCount; i ++)
		add(edgesToAdd[i].first, edgesToAdd[i].second);
	newBridgesCount = 0;
	sz1 = 0;
	memset(idx1, -1, sizeof(idx1));
	
	memset(level, -1, sizeof(level));
	memset(prv, -1, sizeof(prv));
	
	memset(parent, -1, sizeof(parent));
	memset(subTreeSize, 0, sizeof(subTreeSize));
	memset(inChain, -1, sizeof(inChain));
	memset(posInChain, -1, sizeof(posInChain));
	memset(chainSize, 0, sizeof(chainSize));
	
	chainsCount = 0;
	compCount = 0;
	
	for(int i = 1; i <= n; i ++)
		if(level[i] == -1) {
			int root = diameter(i);
			compCount ++;
			
			levelInTree[root] = 0;
			dfs(root);
			dfs2(root);
		}
	
	for(int k = 1; k <= 14; k ++)
		for(int i = 1; i <= n; i ++)
			if(parent[i][k - 1] != -1)
				parent[i][k] = parent[ parent[i][k - 1] ][k - 1];
	
	for(int i = 0; i < chainsCount; i ++) {
		vec[i].tree.resize(chainSize[i] + 1);
		fill(vec[i].tree.begin(), vec[i].tree.end(), 0);
	}
	
	for(int i = 1; i <= n; i ++)
		if(inChain[i] != -1) {
			vec[ inChain[i] ].totalSum += pengCount[i];
			vec[ inChain[i] ].update(posInChain[i], pengCount[i]);
		}
}

int lca(int a, int b) {
	if(levelInTree[a] > levelInTree[b])
		a ^= b ^= a ^= b;
	
	for(int i = 14; i >= 0; i --)
		if(parent[b][i] != -1 && levelInTree[a] <= levelInTree[ parent[b][i] ])
			b = parent[b][i];
	
	if(a == b)
		return a;
	
	for(int i = 14; i >= 0; i --)
		if(parent[a][i] != parent[b][i])
			a = parent[a][i], b = parent[b][i];
	
	return parent[a][0];
}

int calc(int up, int down) {
	if(up == down)
		return pengCount[down];
	
	int ret = 0;
	while(1) {
		if(up == down) {
			ret += pengCount[down];
			break;
		}
		
		if(inChain[down] == -1) {
			ret += pengCount[down];
			down = parent[down][0];
		}
		else {
			if(inChain[up] == inChain[down]) {
				ret += vec[ inChain[down] ].get(posInChain[up], posInChain[down]);
				break;
			}
			else {
				ret += vec[ inChain[down] ].get(posInChain[down]);
				down = vec[ inChain[down] ].chainStart;
				down = parent[down][0];
			}
		}
	}
	
	return ret;
}

/// A and B are in one component
int query(int a, int b) {
	int L = lca(a, b);
	return calc(L, a) + calc(L, b) - pengCount[L];
}

void bfsComponents(int a, int b) {
	queue<int> q;
	int mxLevel = levelAdder;
	
	levelComponent[ inComponent[b] ] = levelAdder + 1;
	prevEdge[ inComponent[b] ] = -1;
	q.push(inComponent[b]);
	while(!q.empty()) {
		int tmpComponent = q.front();
		q.pop();
		
		if(tmpComponent == inComponent[a]) break;
		
		for(int i = idx1[tmpComponent]; i != -1; i = g1[i].prv) {
			if(levelComponent[ g1[i].nextComponent ] <= levelAdder) {
				levelComponent[ g1[i].nextComponent ] = levelComponent[tmpComponent] + 1;
				prevEdge[ g1[i].nextComponent ] = i;
				
				if(mxLevel < levelComponent[tmpComponent] + 1)
					mxLevel = levelComponent[tmpComponent] + 1;
				
				q.push(g1[i].nextComponent);
			}
		}
	}
	
	levelAdder = mxLevel;
}

void getAnswer(int a, int b) {
	int ret = 0;
	if(inComponent[a] == inComponent[b]) {
		ret = query(a, b);
		printf("%d\n", ret);
		return;
	}
	
	bfsComponents(a, b);
	
	vector<int> nodeList;
	int tmpComponent = inComponent[a];
	while(tmpComponent != inComponent[b]) {
		int edgeIndex = prevEdge[tmpComponent];
		nodeList.pb(g1[edgeIndex].nextNode);
		nodeList.pb(g1[edgeIndex ^ 1].nextNode);
		tmpComponent = g1[edgeIndex ^ 1].nextComponent;
	}
	
	ret += query(a, nodeList[0]);
	for(int i = 1; i < (int)nodeList.size() - 1; i += 2)
		ret += query(nodeList[i], nodeList[i + 1]);
	ret += query(nodeList.back(), b);
	
	printf("%d\n", ret);
}

void solve() {
	int q;
	char cmd[16];
	int a, b, x;
	
	scanf("%d\n", &q);
	for(int iter = 0; iter < q; iter ++) {
		scanf("%s", &cmd);
		
		if(cmd[0] == 'b') {
			scanf("%d %d\n", &a, &b);
			
			int r1 = findRoot(a);
			int r2 = findRoot(b);
			
			if(r1 == r2) printf("no\n");
			else {
				printf("yes\n");
				rt[r1] = r2;
				
				add1(a, b);
				edgesToAdd[newBridgesCount] = mp(a, b);
				newBridgesCount ++;
				
				if(newBridgesCount == BOUND) fix();
			}
		}
		else if(cmd[0] == 'p') {
			scanf("%d %d\n", &a, &x);
			
			if(inChain[a] != -1) {
				vec[ inChain[a] ].totalSum = vec[ inChain[a] ].totalSum - pengCount[a] + x;
				vec[ inChain[a] ].update(posInChain[a], -pengCount[a] + x);
			}
			
			pengCount[a] = x;
		}
		else {
			scanf("%d %d\n", &a, &b);
			
			int r1 = findRoot(a);
			int r2 = findRoot(b);
			
			if(r1 != r2) printf("impossible\n");
			else getAnswer(a, b);
		}
	}
}

int main()
{
	read();
	init();
	solve();

    return 0;
}
