#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>

using namespace std;

typedef long long LL;

const LL INF = 1LL << 60;

struct Point {
	LL x, y;
	
	void read() {
		scanf("%lld %lld", &x, &y);
	}
};

struct Segment {
	Point A, B;
	
	Segment() {}
	Segment(Point _A, Point _B): A(_A), B(_B) {}
};

struct Route {
	int n;
	Point p[64];
	
	LL findClosest(Point G);
	LL findClosest(Segment L);
};

struct State {
	int steps;
	int idx;
	LL cost;
	
	State() {}
	State(int _steps, int _idx, LL _cost): steps(_steps), idx(_idx), cost(_cost) {}
};

struct cmp {
	bool operator()(State s1, State s2) {
		return !(s1.cost < s2.cost);
	}
};

int d;
Point a, b;
int r, f[128];
Route paths[128];
int ma3x[128][128];

LL cache[305][105];
priority_queue< State , vector< State > , cmp > pq;

void read() {
	scanf("%d", &d);
	
	a.read();
	b.read();
	
	scanf("%d", &r);
	for(int i = 1; i <= r; i ++) {
		scanf("%d", &paths[i].n);
		scanf("%d", &f[i]);
		for(int j = 0; j < paths[i].n; j ++)
			paths[i].p[j].read();
	}
}

LL abss(LL x) {
	if(x < 0) return -x;
	return x;
}

LL getDist(Point A, Point B) {
	return abss(A.x - B.x) + abss(A.y - B.y);
}

LL getDist(Point O, Segment l) {
	if(l.A.x == l.B.x) {
		LL up = max(l.A.y, l.B.y);
		LL down = min(l.A.y, l.B.y);
		if(down <= O.y && O.y <= up) return abss(O.x - l.A.x);
		return min(getDist(O, l.A), getDist(O, l.B));
	}
	else {
		LL right = max(l.A.x, l.B.x);
		LL left = min(l.A.x, l.B.x);
		if(left <= O.x && O.x <= right) return abss(O.y - l.A.y);
		return min(getDist(O, l.A), getDist(O, l.B));
	}
}

short int SOrient(Point A, Point B, Point C) {
	LL det = (A.x * B.y + B.x * C.y + C.x * A.y) - (B.x * A.y + C.x * B.y + A.x * C.y);
	if(det < 0) return -1;
	if(det > 0) return 1;
	return 0;
}

LL getDist(Segment l, Segment t) {
	if(SOrient(l.A, l.B, t.A) * SOrient(l.A, l.B, t.B) == -1 && SOrient(t.A, t.B, l.A) * SOrient(t.A, t.B, l.B) == -1)
		return 0;
	
	LL d1 = getDist(l.A, t.A);
	LL d2 = getDist(l.A, t.B);
	LL d3 = getDist(l.B, t.A);
	LL d4 = getDist(l.B, t.B);
	return min(min(d1, d2), min(d3, d4));
}

LL Route::findClosest(Point G) {
	LL ret = INF;
	for(int i = 0; i < n; i ++)
		ret = min(ret, getDist(G, Segment(p[i], p[ (i + 1) % n ])));
	return ret;
}

LL Route::findClosest(Segment L) {
	LL ret = INF;
	for(int i = 0; i < n; i ++)
		ret = min(ret, getDist(L, Segment(p[i], p[ (i + 1) % n ])));
	return ret;
}

void solve() {
	ma3x[0][r + 1] = ma3x[r + 1][0] = getDist(a, b);
	for(int i = 1; i <= r; i ++) {
		ma3x[0][i] = ma3x[i][0] = paths[i].findClosest(a);
		ma3x[r + 1][i] = ma3x[i][r + 1] = paths[i].findClosest(b);
	}
	
	for(int i = 1; i <= r; i ++)
		for(int j = i + 1; j <= r; j ++)
			for(int k = 0; k < paths[i].n; k ++)
				ma3x[i][j] = ma3x[j][i] = paths[j].findClosest(Segment(paths[i].p[k], paths[i].p[ (k + 1) % paths[i].n ]));
	
	for(int i = 0; i <= d; i ++)
		for(int j = 0; j <= r + 1; j ++)
			cache[i][j] = INF;
	
	pq.push(State(d, 0, 0));
	while(!pq.empty()) {
		State tmp = pq.top();
		pq.pop();
		
		cache[tmp.steps][tmp.idx] = tmp.cost;
		
		if(tmp.idx == r + 1) {
			cout << tmp.cost << endl;
			return;
		}
		
		for(int i = 0; i <= r + 1; i ++)
			if(i != tmp.idx && tmp.steps >= ma3x[tmp.idx][i] && cache[ tmp.steps - ma3x[tmp.idx][i] ][i] > tmp.cost + f[i]) {
				cache[ tmp.steps - ma3x[tmp.idx][i] ][i] = tmp.cost + f[i];
				pq.push(State(tmp.steps - ma3x[tmp.idx][i], i, tmp.cost + f[i]));
			}
	}
	
	cout << "-1\n";
}

int main()
{
	read();
	solve();

    return 0;
}
