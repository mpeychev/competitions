#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

typedef long long LL;

const int MAXN = 100100;

struct Rect {
	int x1, y1, z1;
	int x2, y2, z2;
};

struct Fenwick1D {
	int t[1024];
	
	void init() {
		memset(t, 0, sizeof(t));
	}
	
	void update(int idx, int val) {
		while(idx < 1000) {
			t[idx] += val;
			idx += (idx & -idx);
		}
	}
	
	int get(int idx) {
		int ret = 0;
		while(idx) {
			ret += t[idx];
			idx -= (idx & -idx);
		}
		return ret;
	}
} Up1D, Down1D;

struct Fenwick2D {
	int t[1024][1024];
	
	void init() {
		memset(t, 0, sizeof(t));
	}
	
	void update(int x, int y, int val) {
		while(x < 1000) {
			int _y = y;
			while(y < 1000) {
				t[x][y] += val;
				y += (y & -y);
			}
			y = _y;
			
			x += (x & -x);
		}
	}
	
	int get(int x, int y) {
		int ret = 0;
		
		while(x) {
			int _y = y;
			while(y) {
				ret += t[x][y];
				y -= (y & -y);
			}
			y = _y;
			
			x -= (x & -x);
		}
		
		return ret;
	}
} Up2D, Down2D;

struct el1 {
	bool fl;
	int x, y1, y2;
	
	el1() {}
	el1(bool _fl, int _x, int _y1, int _y2): fl(_fl), x(_x), y1(_y1), y2(_y2) {}
};

struct el2 {
	short int fl;
	int z, x1, y1, x2, y2;
	
	el2() {}
	el2(short int _fl, int _z, int _x1, int _y1, int _x2, int _y2):
		fl(_fl), z(_z), x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
};

int n;
Rect r[MAXN];
LL ans;

void read() {
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d %d %d %d %d %d", &r[i].x1, &r[i].y1, &r[i].z1, &r[i].x2, &r[i].y2, &r[i].z2);
}

/// count(X, X)
bool cmp1(el1 a, el1 b) {
	if(a.x != b.x)
		return a.x < b.x;
	return a.fl < b.fl;
}

void calc1() {
	vector< el1 > vec[1024];
	
	for(int i = 0; i < n; i ++)
		if(r[i].x1 == r[i].x2) {
			vec[ r[i].x1 ].pb(el1(false, min(r[i].y1, r[i].y2), min(r[i].z1, r[i].z2), max(r[i].z1, r[i].z2)));
			vec[ r[i].x1 ].pb(el1(true, max(r[i].y1, r[i].y2), min(r[i].z1, r[i].z2), max(r[i].z1, r[i].z2)));
		}
	
	Up1D.init();
	Down1D.init();
	
	for(int i = 1; i <= 999; i ++) {
		sort(vec[i].begin(), vec[i].end(), cmp1);
		
		for(int j = 0; j < (int)vec[i].size(); j ++)
			if(vec[i][j].fl) {
				Down1D.update(vec[i][j].y1, -1);
				Up1D.update(vec[i][j].y2, -1);
			}
			else {
				ans += (Down1D.get(vec[i][j].y2) - Up1D.get(vec[i][j].y1 - 1));
				Down1D.update(vec[i][j].y1, 1);
				Up1D.update(vec[i][j].y2, 1);
			}
	}
}

/// count(X, Z)
bool cmp2(el2 a, el2 b) {
	if(a.z != b.z)
		return a.z < b.z;
	
	return a.fl < b.fl;
}

void calc2() {
	vector< el2 > vec;
	
	for(int i = 0; i < n; i ++)
		if(r[i].x1 == r[i].x2) {
			vec.pb(el2(0, min(r[i].z1, r[i].z2), min(r[i].y1, r[i].y2), r[i].x1, max(r[i].y1, r[i].y2), r[i].x2));
			vec.pb(el2(2, max(r[i].z1, r[i].z2), min(r[i].y1, r[i].y2), r[i].x1, max(r[i].y1, r[i].y2), r[i].x2));
		}
		else if(r[i].z1 == r[i].z2) {
			vec.pb(el2(1, r[i].z1, min(r[i].y1, r[i].y2), min(r[i].x1, r[i].x2), max(r[i].y1, r[i].y2), max(r[i].x1, r[i].x2)));
		}
	
	Up2D.init();
	Down2D.init();
	
	sort(vec.begin(), vec.end(), cmp2);
	
	for(int i = 0; i < (int)vec.size(); i ++)
		if(vec[i].fl == 0) {
			Up2D.update(vec[i].x1, vec[i].y1, 1);
			Down2D.update(vec[i].x2, vec[i].y2, 1);
		}
		else if(vec[i].fl == 2) {
			Up2D.update(vec[i].x1, vec[i].y1, -1);
			Down2D.update(vec[i].x2, vec[i].y2, -1);
		}
		else {
			ans += (Up2D.get(vec[i].x2, vec[i].y2) - Up2D.get(vec[i].x2, vec[i].y1 - 1)) -
				   (Down2D.get(vec[i].x1 - 1, vec[i].y2) - Down2D.get(vec[i].x1 - 1, vec[i].y1 - 1));
		}
}

void rotate() {
	for(int i = 0; i < n; i ++) {
		int _x1 = r[i].x1;
		r[i].x1 = r[i].y1;
		r[i].y1 = r[i].z1;
		r[i].z1 = _x1;
		
		int _x2 = r[i].x2;
		r[i].x2 = r[i].y2;
		r[i].y2 = r[i].z2;
		r[i].z2 = _x2;
	}
}

void solve() {
	for(int i = 0; i < 3; i ++) {
		calc1();
		calc2();
		rotate();
	}
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
