/// Optimized O(N^2)
/// Potential better solutions - 1)hill climbing and 2) O(N) - Shublera
/// See spoj - TFOSS

#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

const int MAXN = 50100;

struct Point {
	int x, y;
};

int n;
Point p[MAXN];
Point O, hull[MAXN];
int sz;

void read() {
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d %d", &p[i].x, &p[i].y);
}

int SQU(int x) {
	return x * x;
}

int dist(Point A, Point B) {
	return SQU(A.x - B.x) + SQU(A.y - B.y);
}

int det(Point A, Point B, Point C) {
	int d = (A.x * B.y + B.x * C.y + C.x * A.y) - (B.x * A.y + C.x * B.y + A.x * C.y);
	if(d < 0) return -1;
	if(d > 0) return 1;
	return 0;
}

bool cmp(Point A, Point B) {
	int d = det(O, A, B);
	
	if(d == 1) return true;
	if(d == -1) return false;
	return dist(O, A) < dist(O, B);
}

void build() {
	for(int i = 1; i < n; i ++)
		if(p[i].y < p[0].y || (p[i].y == p[0].y && p[i].x < p[0].x))
			swap(p[i], p[0]);
	
	O = p[0];
	sort(p + 1, p + n, cmp);
	
	hull[sz ++] = p[0];
	for(int i = 1; i < n; i ++) {
		while(sz >= 2 && det(hull[sz - 2], hull[sz - 1], p[i]) == -1)
			sz --;
		hull[sz ++] = p[i];
	}
}

void solve() {
	if(n == 2) {
		cout << dist(p[0], p[1]) << endl;
		return;
	}
	
	build();
	
	int ans = -1;
	for(int i = 0; i < sz; i ++)
		for(int j = i + 1; j < sz; j ++) {
			int cur = dist(hull[i], hull[j]);
			if(ans < cur) ans = cur;
		}
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
