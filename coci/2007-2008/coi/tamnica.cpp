#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

#define pb push_back
#define mp make_pair

using namespace std;

typedef long long LL;
typedef pair<int, LL> PIL;

const int MAXK = 200200;
const LL INF = 1LL << 62;

struct el {
	int v;
	LL d;
	
	el() {}
	el(int _v, LL _d): v(_v), d(_d) {}
};

struct cmp {
	bool operator()(el a, el b) {
		return !(a.d < b.d);
	}
};

LL n;
int k;
LL b[MAXK], a[MAXK];
int sz;
vector<LL> allNodes;
map<LL, int> compress;

vector< PIL > g[MAXK];

priority_queue< el , vector< el > , cmp > pq;
LL dist[MAXK];
bool used[MAXK];

LL corner(LL index) {
	if(index == 0) return 1;
	if(index == 1) return 1;
	if(index == 2) return 2;
	if(index == 3) return 3;
	
	LL last = (index >> 1) - 1;
	LL ret = 1 + last * (last + 1);
	ret += last + 1;
	if(index & 1) ret += last + 1;
	
	return ret;
}

int findIndex(LL B) {
	int le = 0, ri = 100000000, mid;
	int ret = -1;
	while(le <= ri) {
		mid = (le + ri) >> 1;
		
		LL value = corner(mid);
		if(value >= B) {
			ret = mid;
			ri = mid - 1;
		}
		else le = mid + 1;
	}
	return ret;
}

LL getA(LL B) {
	int t = findIndex(B);
	LL c1 = corner(t);
	LL c2 = corner(t - 4);
	LL diff = c1 - B - 1;
	return c2 - diff;
}

void init() {
	scanf("%lld", &n);
	
	allNodes.pb(1);
	allNodes.pb(n);
	
	scanf("%d", &k);
	for(int i = 0; i < k; i ++) {
		scanf("%lld", &b[i]);
		a[i] = getA(b[i]);
		
		allNodes.pb(b[i]);
		allNodes.pb(a[i]);
	}
}

void build() {
	sort(allNodes.begin(), allNodes.end());
	vector<LL> :: iterator it = unique(allNodes.begin(), allNodes.end());
	allNodes.resize(distance(allNodes.begin(), it));
	sz = (int)allNodes.size();
	
	for(int i = 0; i < sz; i ++)
		compress[ allNodes[i] ] = i;
	
	for(int i = 0; i < sz; i ++) {
		if(i + 1 < sz) g[i].pb(mp(i + 1, allNodes[i + 1] - allNodes[i]));
		if(i - 1 >= 0) g[i].pb(mp(i - 1, allNodes[i] - allNodes[i - 1]));
	}
	
	for(int i = 0; i < k; i ++) {
		g[ compress[ a[i] ] ].pb(mp(compress[ b[i] ], 1));
		g[ compress[ b[i] ] ].pb(mp(compress[ a[i] ], 1));
	}
}

void dijkstra() {
	for(int i = 0; i < sz; i ++) {
		dist[i] = INF;
		used[i] = false;
	}
	
	pq.push(el(0, 0));
	while(!pq.empty()) {
		el tmp = pq.top();
		pq.pop();
		
		if(used[ tmp.v ]) continue;
		
		dist[ tmp.v ] = tmp.d;
		used[ tmp.v ] = true;
		
		if(allNodes[ tmp.v ] == n) {
			cout << tmp.d << endl;
			return;
		}
		
		for(int i = 0; i < (int)g[ tmp.v ].size(); i ++)
			if(!used[ g[tmp.v][i].first ] && dist[ g[tmp.v][i].first ] > tmp.d + g[tmp.v][i].second) {
				dist[ g[tmp.v][i].first ] = tmp.d + g[tmp.v][i].second;
				pq.push(el(g[tmp.v][i].first, tmp.d + g[tmp.v][i].second));
			}
	}
}

int main()
{
	init();
	build();
	dijkstra();

    return 0;
}
