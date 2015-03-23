#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define pb push_back

using namespace std;

typedef long long LL;

const int MAXN = 100100;
const int MAXM = 100100;

const LL INF = 1LL << 60;
const int MAXH = 1000000 + 5;

struct Point {
	int x, y;
	
	Point() {}
	Point(int _x, int _y): x(_x), y(_y) {}
};

int n, m, g, w;
Point hist[MAXN], s[MAXM];
int h[1 << 20];

int cnt[1 << 20];
LL sum[1 << 20], t[1 << 20];
int t2[1 << 20];

/// For the points in S
int lastY[1 << 20];
int posLeft[MAXM];
int countEqual[MAXM];
LL sumLower[MAXM];
int countLower[MAXM];

LL hor[MAXM], up[MAXM], down[MAXM];

vector< Point > vec;
vector< bool > toPrint;

void read() {
	scanf("%d %d %d", &n, &m, &g);
	for(int i = 0; i < n; i ++)
		scanf("%d %d", &hist[i].x, &hist[i].y);
	for(int i = 0; i < m; i ++)
		scanf("%d %d", &s[i].x, &s[i].y);
}

bool cmp(Point a, Point b) {
	if(a.x != b.x)
		return a.x < b.x;
	return a.y < b.y;
}

void updateT(int idx, int val) {
	while(idx <= MAXH) {
		t[idx] += val;
		idx += (idx & -idx);
	}
}

void updateT2(int idx, int val) {
	while(idx <= MAXH) {
		t2[idx] += val;
		idx += (idx & -idx);
	}
}

LL getTree(int idx) {
	LL ret = 0;
	while(idx) {
		ret += t[idx];
		idx -= (idx & -idx);
	}
	return ret;
}

int getTree2(int idx) {
	int ret = 0;
	while(idx) {
		ret += t2[idx];
		idx -= (idx & -idx);
	}
	return ret;
}

void addColumn(int idx) {
	int _h = h[idx];
	
	cnt[ _h ] ++;
	updateT(_h, _h);
	updateT2(_h, 1);
}

void init() {
	memset(lastY, -1, sizeof(lastY));
	memset(posLeft, -1, sizeof(posLeft));
	
	w = hist[n - 1].x;
	
	for(int i = 0; i < n; i += 2)
		for(int j = hist[i].x + 1; j <= hist[i + 1].x; j ++)
			h[j] = hist[i].y;
	
	for(int i = 1; i <= w; i ++)
		sum[i] = sum[i - 1] + (LL)h[i];
	
	sort(s, s + m, cmp);
	
	for(int i = 0; i < m; i ++) {
		posLeft[ i ] = lastY[ s[i].y ];
		lastY[ s[i].y ] = i;
		
		if(s[i].x != 0) {
			for(int j = s[i - 1].x + 1; j <= s[i].x; j ++)
				addColumn(j);
		}
		
		countEqual[ i ] = cnt[ s[i].y ];
		sumLower[ i ] = getTree(s[i].y - 1);
		countLower[ i ] = getTree2(s[i].y - 1);
	}
}

LL cost(int i, int j) {
	int all = s[j].x - s[i].x;
	int _countEqual = countEqual[j] - countEqual[i];
	
	if(g == 1) return all - _countEqual;
	
	LL _countLower = countLower[j] - countLower[i];
	LL _countUpper = all - _countEqual - _countLower;
	
	LL sumAll = sum[ s[j].x ] - sum[ s[i].x ];
	LL _sumLower = sumLower[j] - sumLower[i];
	LL _sumUpper = sumAll - _sumLower - _countEqual * (LL)s[i].y;
	
	return (_countLower * (LL)s[i].y - _sumLower) + (_sumUpper - _countUpper * (LL)s[i].y);
}

void solve() {
	for(int i = 0; i < m; i ++)
		if(s[i].x == 0) {
			hor[i] = 0;
			up[i] = INF;
			down[i] = INF;
		}
		else {
			/// calc hor
			if(posLeft[i] != -1) {
				hor[i] = cost(posLeft[i], i) + min(min(hor[ posLeft[i] ], up[ posLeft[i] ]), down[ posLeft[i] ]);
			}
			else hor[i] = INF;
			
			/// calc down
			if(s[i - 1].x == s[i].x) {
				down[i] = min(hor[i - 1], down[i - 1]);
			}
			else down[i] = INF;
			
			/// calc up
			if(i == m - 1 || s[i + 1].x != s[i].x) {
				up[i] = INF;
				for(int j = i - 1; s[j].x == s[i].x; j --)
					up[j] = min(up[j + 1], hor[j + 1]);
			}
		}
	
	int pos = -1;
	LL ans = INF;
	
	for(int i = 0; i < m; i ++)
		if(s[i].x == w && ans > hor[i]) {
			pos = i;
			ans = hor[i];
		}
	
	cout << ans << endl;
	
	vec.pb(s[pos]);
	
	int dir = 0;
	while(s[pos].x != 0) {
		if(dir == 0) {
			pos = posLeft[pos];
			
			LL mn = min(min(hor[pos], up[pos]), down[pos]);
			if(mn == hor[pos]) dir = 0;
			else if(mn == up[pos]) dir = 1;
			else dir = 2;
		}
		else if(dir == 1) {
			pos ++;
			
			LL mn = min(hor[pos], up[pos]);
			if(mn == hor[pos]) dir = 0;
			else dir = 1;
		}
		else {
			pos --;
			
			LL mn = min(hor[pos], down[pos]);
			if(mn == hor[pos]) dir = 0;
			else dir = 2;
		}
		
		vec.pb(s[pos]);
	}
	
	reverse(vec.begin(), vec.end());
	
	toPrint.resize(vec.size(), true);
	
	for(int i = 1; i < (int)vec.size() - 1; i ++) {
		if(vec[i - 1].x == vec[i].x && vec[i + 1].x == vec[i].x) toPrint[i] = false;
		if(vec[i - 1].y == vec[i].y && vec[i + 1].y == vec[i].y) toPrint[i] = false;
	}
	
	int br = 0;
	for(int i = 0; i < (int)toPrint.size(); i ++)
		if(toPrint[i])
			br ++;
	
	printf("%d\n", br);
	for(int i = 0; i < (int)vec.size(); i ++)
		if(toPrint[i])
			printf("%d %d\n", vec[i].x, vec[i].y);
}

int main()
{
	read();
	init();
	solve();

    return 0;
}
