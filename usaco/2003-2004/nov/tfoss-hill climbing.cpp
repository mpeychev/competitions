/// O(n log n) - for the convex hull
/// hill climbing - second part of the problem

#include <iostream>
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
	cin >> n;
	for(int i = 0; i < n; i ++)
		cin >> p[i].x >> p[i].y;
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

LL brute(int le, int ri) {
	LL ret = -1;
	LL cur;
	for(int i = le; i < ri; i ++)
		for(int j = i + 1; j <= ri; j ++) {
			cur = dist(hull[i], hull[j]);
			if(ret < cur) ret = cur;
		}
	return ret;
}

LL brute2(int pos, int le, int ri) {
	LL ret = 0;
	LL cur;
	for(int i = le; i <= ri; i ++)
		{
			cur = dist(hull[pos], hull[i]);
			if(ret < cur) ret = cur;
		}
	return ret;
}

LL go(int pos) {
	int c = (sz - 1 + pos) >> 1;
	int step = ((c - pos) >> 1) + 1;
	LL ret = 0;

	while(step) {
		LL val1 = dist(hull[pos], hull[c]);
		LL val2 = -1, val3 = -1;

		if(c + step < sz) val2 = dist(hull[pos], hull[c + step]);
		if(c - step > pos) val3 = dist(hull[pos], hull[c - step]);

		if(ret < val1) ret = val1;
		if(ret < val2) ret = val2;
		if(ret < val3) ret = val3;

		if(val1 >= val2 && val1 >= val3) step >>= 1;
		else {
			if(val2 > val3) c += step;
			else c -= step;
		}
	}

    return ret;
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

	LL ans = 0;
	LL cur;

	for(int i = 0; i < sz - 1; i ++) {
		cur = go(i);
		if(ans < cur) ans = cur;
	}
	cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

	int t;
	cin >> t;

	for( ; t; t --) {
		read();
		solve();
	}

    return 0;
}
