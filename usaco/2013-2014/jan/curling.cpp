#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define pb push_back

using namespace std;

const int MAXN = 50100;

struct Point {
	long long x, y;
};

int n;
Point A[MAXN];
Point B[MAXN];

Point O;
int idx;

Point hull[MAXN];
int sz;

vector< Point > vec;

void read() {
	scanf("%d", &n);
	
	for(int i = 0; i < n; i ++)
		scanf("%lld %lld", &A[i].x, &A[i].y);
	
	for(int i = 0; i < n; i ++)
		scanf("%lld %lld", &B[i].x, &B[i].y);
}

void init() {
	for(int i = 0; i < n; i ++)
		swap(A[i], B[i]);
	
	sz = 0;
	vec.clear();
}

short int SOrient(Point a, Point b, Point c) {
	long long d = (a.x * b.y + b.x * c.y + c.x * a.y) - (b.x * a.y + c.x * b.y + a.x * c.y);
	if(d < 0) return -1;
	if(d > 0) return 1;
	return 0;
}

long long SQU(long long x) {
	return x * x;
}

long long dist(Point a, Point b) {
	return SQU(a.x - b.x) + SQU(a.y - b.y);
}

bool cmp(Point a, Point b) {
	int d = SOrient(O, a, b);
	
	if(d == 1) return true;
	if(d == -1) return false;
	return dist(O, a) < dist(O, b);
}

void buildHull() {
	O = A[0];
	idx = 0;
	
	for(int i = 1; i < n; i ++)
		if(A[i].y < O.y || (A[i].y == O.y && A[i].x < O.x)) {
			O = A[i];
			idx = i;
		}
	
	swap(A[0], A[idx]);
	
	sort(A + 1, A + n, cmp);
	
	sz = 0;
	hull[sz ++] = A[0];
	hull[sz ++] = A[1];
	for(int i = 2; i < n; i ++) {
		while(sz >= 2 && SOrient(hull[sz - 2], hull[sz - 1], A[i]) == -1)
			sz --;
		hull[sz ++] = A[i];
	}
}

int bs(Point p) {
	int le = 0, ri = (int)vec.size() - 1, mid;
	int ret = 0;
	
	while(le <= ri) {
		mid = (le + ri) >> 1;
		if(SOrient(O, vec[mid], p) == -1) ri = mid - 1;
		else {
			ret = mid;
			le = mid + 1;
		}
	}
	
	return ret;
}

bool check(Point p) {
	if(p.y < O.y)
		return false;
	
	if(SOrient(O, p, vec[0]) == 1)
		return false;
	
	if(SOrient(O, vec.back(), p) == 1)
		return false;
	
	int i = bs(p);
	
	if(SOrient(O, vec[i], p) == 0)
		return dist(O, vec[i]) > dist(O, p);
	
	if(SOrient(vec[i], vec[i + 1], p) == -1)
		return false;
	
	return true;
}

int solve() {
	buildHull();
	
	bool fl = true;
	for(int i = 2; i < sz; i ++)
		if(SOrient(hull[0], hull[1], hull[i]) != 0) {
			fl = false;
			break;
		}
	if(fl || sz < 3) {
		int ret = 0;
		for(int i = 0; i < n; i ++)
			if(dist(hull[0], B[i]) < dist(hull[0], hull[sz - 1]) && dist(hull[sz - 1], B[i]) < dist(hull[sz - 1], hull[0]))
				ret ++;
		return ret;
	}
	
	int idx = 1;
	for(int i = 2; i < sz; i ++)
		if(SOrient(hull[0], hull[idx], hull[i]) == 0) idx = i;
		else break;
	
	for(int i = idx; i < sz; i ++)
		vec.pb(hull[i]);
	
	int ret = 0;
	
	for(int i = 0; i < n; i ++)
		if(check(B[i]))
			ret ++;
	
	return ret;
}

int main()
{
	freopen("curling.in", "r", stdin);
	freopen("curling.out", "w", stdout);
	
	read();
	cout << solve() << " ";
	init();
	cout << solve() << endl;
	
	return 0;
}
