/// O(n log n) - for the convex hull
/// O(n) - second part of the problem

#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

typedef long long LL;

const int MAXN = 100100;

struct Point {
	LL x, y;
};

int n;
Point p[MAXN];
Point O, hull[MAXN];
int sz;

void read() {
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%lld %lld", &p[i].x, &p[i].y);
	sz = 0;
}

LL SQU(LL x) {
	return x * x;
}

LL dist(Point A, Point B) {
	return SQU(A.x - B.x) + SQU(A.y - B.y);
}

int det(Point A, Point B, Point C) {
	LL d = (A.x * B.y + B.x * C.y + C.x * A.y) - (B.x * A.y + C.x * B.y + A.x * C.y);
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
	if(n == 1) {
		cout << "0\n";
		return;
	}
	
	if(n == 2) {
		cout << dist(p[0], p[1]) << endl;
		return;
	}
	
	build();
	
	LL ans = -1;
	int k = 1;
	for(int i = 2; i < sz; i ++)
		if(dist(hull[0], hull[i]) > dist(hull[0], hull[k]))
			k = i;
	
	ans = dist(hull[0], hull[k]);
	for(int i = 1; i < sz; i ++) {
		while(k < sz - 1 && dist(hull[i], hull[k + 1]) > dist(hull[i], hull[k]))
			k ++;
		LL cur = dist(hull[i], hull[k]);
		if(ans < cur) ans = cur;
	}
	
	cout << ans << endl;
}

int main()
{
	int t;
	scanf("%d\n", &t);
	
	for( ; t; t --) {
		read();
		solve();
	}

    return 0;
}
