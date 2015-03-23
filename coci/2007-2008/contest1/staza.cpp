#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>

#define pb push_back

using namespace std;

const int MAXN = 10100;
const int MAXM = 20200;

struct Edge {
	int to, prv, ringIndex;
	
	Edge() {}
	Edge(int _to, int _prv, int _ringIndex): to(_to), prv(_prv), ringIndex(_ringIndex) {}
};

int n, m;
int idx[MAXN];
Edge g[2 * MAXM];
int sz;

int prevEdge[MAXN];
int level[MAXN];
int comeBack[MAXN];
int goDown[MAXN];
int topRing[MAXN];

int ringCount;
vector< vector<int> > rings;
vector< int > ringMinLevel;
vector< int > inRings[MAXN];

void add(int a, int b) {
	g[sz] = Edge(b, idx[a], -1);
	idx[a] = sz ++;
	
	g[sz] = Edge(a, idx[b], -1);
	idx[b] = sz ++;
}

void read() {
	int a, b;
	memset(idx, -1, sizeof(idx));
	
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i ++) {
		scanf("%d %d", &a, &b);
		add(a, b);
	}
}

void dfs(int cur, int parent) {
	for(int i = idx[cur]; i != -1; i = g[i].prv)
		if(!level[ g[i].to ]) {
			prevEdge[ g[i].to ] = i;
			level[ g[i].to ] = level[cur] + 1;
			dfs(g[i].to, cur);
		}
		else if(g[i].to != parent && g[i].ringIndex == -1) {
			vector<int> vec;
			int tmp = cur;
			
			g[i].ringIndex = ringCount;
			g[i ^ 1].ringIndex = ringCount;
			vec.pb(tmp);
			
			while(tmp != g[i].to) {
				g[ prevEdge[tmp] ].ringIndex = ringCount;
				g[ prevEdge[tmp] ^ 1 ].ringIndex = ringCount;
				
				tmp = g[ prevEdge[tmp] ^ 1 ].to;
				vec.pb(tmp);
			}
			
			rings.pb(vec);
			for(int j = 0; j < (int)vec.size(); j ++)
				inRings[ vec[j] ].pb(ringCount);
			ringMinLevel.pb(level[ g[i].to ]);
			
			ringCount ++;
		}
}

int getTheRingWithMinLevel(int node) {
	int retRing = inRings[node][0];
	for(int i = 1; i < (int)inRings[node].size(); i ++)
		if(ringMinLevel[retRing] > ringMinLevel[ inRings[node][i] ])
			retRing = inRings[node][i];
	return retRing;
}

int _comeBack(int node) {
	if(comeBack[node] != -1)
		return comeBack[node];
	
	int ret = 0;
	vector<int> allNodes;
	for(int i = 0; i < (int)inRings[node].size(); i ++)
		if(inRings[node][i] != topRing[node]) {
			int curRingIndex = inRings[node][i];
			ret += (int)rings[curRingIndex].size();
			for(int j = 0; j < (int)rings[curRingIndex].size(); j ++)
				if(rings[curRingIndex][j] != node)
					allNodes.pb(rings[curRingIndex][j]);
		}
	
	for(int i = 0; i < (int)allNodes.size(); i ++)
		ret += _comeBack(allNodes[i]);
	
	comeBack[node] = ret;
	return ret;
}

int _goDown(int node) {
	if(goDown[node] != -1)
		return goDown[node];
	
	/// Don't choose to go down a ring
	int opt1 = 0;
	
	opt1 = _comeBack(node);
	int mx = 0;
	for(int i = idx[node]; i != -1; i = g[i].prv)
		if(topRing[ g[i].to ] == -1 && level[node] + 1 == level[ g[i].to ])
			mx = max(mx, 1 + _goDown(g[i].to));
	opt1 += mx;
	
	/// Go down a ring
	int opt2 = 0;
	
	vector< vector<int> > ringsDown;
	for(int i = 0; i < (int)inRings[node].size(); i ++)
		if(inRings[node][i] != topRing[node])
			ringsDown.pb(rings[ inRings[node][i] ]);
	
	if(ringsDown.empty()) {
		goDown[node] = opt1;
		return opt1;
	}
	
	vector< int > value;
	int totalValue = 0;
	for(int i = 0; i < (int)ringsDown.size(); i ++) {
		int tmp = (int)ringsDown[i].size();
		for(int j = 0; j < (int)ringsDown[i].size(); j ++)
			if(node != ringsDown[i][j])
				tmp += _comeBack(ringsDown[i][j]);
		value.pb(tmp);
		totalValue += tmp;
	}
	
	for(int i = 0; i < (int)ringsDown.size(); i ++) {
		int tmp = totalValue - value[i];
		
		int mx = 0;
		int ps = 0;
		
		for(int j = 0; j < (int)ringsDown[i].size() - 1; j ++) {
			ps ++;
			mx = max(mx, ps + _goDown(ringsDown[i][j]));
			ps += _comeBack(ringsDown[i][j]);
		}
		
		ps = 0;
		for(int j = (int)ringsDown[i].size() - 2; j >= 0; j --) {
			ps ++;
			mx = max(mx, ps + _goDown(ringsDown[i][j]));
			ps += _comeBack(ringsDown[i][j]);
		}
		
		tmp += mx;
		opt2 = max(opt2, tmp);
	}
	
	/// Compare the two options
	
	if(opt1 > opt2) {
		goDown[node] = opt1;
		return opt1;
	}
	else {
		goDown[node] = opt2;
		return opt2;
	}
}

void solve() {
	/// detect rings
	level[1] = 1;
	prevEdge[1] = -1;
	dfs(1, -1);
	
	/// determine topRing for each node
	memset(topRing, -1, sizeof(topRing));
	for(int i = 1; i <= n; i ++)
		if(!inRings[i].empty()) {
			int candidate = getTheRingWithMinLevel(i);
			if(ringMinLevel[candidate] < level[i]) topRing[i] = candidate;
		}
	
	/// calculate comeBack and goDown functions
	memset(comeBack, -1, sizeof(comeBack));
	memset(goDown, -1, sizeof(goDown));
	
	int opt1 = _comeBack(1);
	int opt2 = _goDown(1);
	
	if(opt1 > opt2) cout << opt1 << endl;
	else cout << opt2 << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
