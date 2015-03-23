#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 100100;
const int MAXW = 200200;

struct Point {
	int x, y;
};

struct el {
	int nextPoint;
	int edgeIndex;
	bool passed;
	
	el() {}
	el(int _nextPoint, int _edgeIndex, bool _passed): nextPoint(_nextPoint), edgeIndex(_edgeIndex), passed(_passed) {}
};

int n, w;
Point p[MAXN];
el g[MAXN][4];
PII startSides[MAXW];
bool processed[MAXW];
int countPasses[MAXW];
vector<int> vec;

void read() {
	int a, b;
	
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d %d", &p[i].x, &p[i].y);
	
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < 4; j ++)
			g[i][j] = el(-1, -1, false);
	
	scanf("%d", &w);
	for(int i = 0; i < w; i ++) {
		scanf("%d %d", &a, &b);
		a --, b --;
		
		if(p[a].x == p[b].x) {
			if(p[a].y > p[b].y) a ^= b ^= a ^= b;
			
			g[a][1] = el(b, i, false);
			g[b][3] = el(a, i, false);
			
			startSides[i] = mp(b, 3);
		}
		else {
			if(p[a].x > p[b].x) a ^= b ^= a ^= b;
			
			g[a][0] = el(b, i, false);
			g[b][2] = el(a, i, false);
			
			startSides[i] = mp(a, 0);
		}
	}
}

bool cmp(PII s1, PII s2) {
	Point a = p[s1.first];
	Point b = p[s2.first];
	
	if(a.y != b.y)
		return a.y > b.y;
	
	if(a.x != b.x)
		return a.x < b.x;
	
	return s1.second < s2.second;
}

bool exist(int node, int dir) {
	if(g[node][dir].nextPoint == -1) return false;
	if(processed[ g[node][dir].edgeIndex ]) return false;
	return true;
}

void go(int startNode, int startDir) {
	vec.clear();
	
	vec.pb(g[startNode][startDir].edgeIndex);
	g[startNode][startDir].passed = true;
	
	int curNode = g[startNode][startDir].nextPoint;
	int curDir = startDir;
	
	while(1) {
//		cout << p[curNode].x << " " << p[curNode].y << " ; " << curDir << endl;
		
		if(exist(curNode, (curDir + 1) % 4)) {
			curDir = (curDir + 1) % 4;
			
			if(g[curNode][curDir].passed) break;
			vec.pb(g[curNode][curDir].edgeIndex);
			g[curNode][curDir].passed = true;
			
			curNode = g[curNode][curDir].nextPoint;
		}
		else if(exist(curNode, curDir)) {
			curDir = curDir;
			
			if(g[curNode][curDir].passed) break;
			vec.pb(g[curNode][curDir].edgeIndex);
			g[curNode][curDir].passed = true;
			
			curNode = g[curNode][curDir].nextPoint;
		}
		else if(exist(curNode, (curDir - 1 + 4) % 4)) {
			curDir = (curDir - 1 + 4) % 4;
			
			if(g[curNode][curDir].passed) break;
			vec.pb(g[curNode][curDir].edgeIndex);
			g[curNode][curDir].passed = true;
			
			curNode = g[curNode][curDir].nextPoint;
		}
		else if(exist(curNode, (curDir + 2) % 4)) {
			curDir = (curDir + 2) % 4;
			
			if(g[curNode][curDir].passed) break;
			vec.pb(g[curNode][curDir].edgeIndex);
			g[curNode][curDir].passed = true;
			
			curNode = g[curNode][curDir].nextPoint;
		}
	}
	
	for(int i = 0; i < (int)vec.size(); i ++) {
		countPasses[ vec[i] ] ++;
		processed[ vec[i] ] = true;
	}
}

void solve() {
	sort(startSides, startSides + w, cmp);
	
	for(int i = 0; i < w; i ++)
		if(!processed[ g[ startSides[i].first ][ startSides[i].second ].edgeIndex ])
			go(startSides[i].first, startSides[i].second);
	
	vec.clear();
	for(int i = 0; i < w; i ++)
		if(countPasses[i] >= 2)
			vec.pb(i + 1);
	
	printf("%d\n", (int)vec.size());
	for(int i = 0; i < (int)vec.size(); i ++)
		printf("%d\n", vec[i]);
}

int main()
{
	read();
	solve();

    return 0;
}
