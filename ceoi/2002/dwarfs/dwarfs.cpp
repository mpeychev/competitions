#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

struct point {
	double x,y;
};

const int MAXN = 1 << 17;
const double eps = 1e-6;

int n, sz, idx;
point p[MAXN], hull[MAXN], O;
point M, N;

bool equal(double a, double b) {
	return fabs(a - b) < eps;
}

void read() {
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%lf %lf", &p[i].x, &p[i].y);
}

double SQU(double x) {
	return x * x;
}

double dist2(point A, point B) {
	return SQU(A.x - B.x) + SQU(A.y - B.y);
}

double det(point A, point B, point C) {
	return (A.x * B.y + B.x * C.y + C.x * A.y) - (B.x * A.y + C.x * B.y + A.x * C.y);
}

bool cmp(point A, point B) {
	double d = det(O, A, B);
	if(equal(d, 0.0))
		return dist2(O, A) < dist2(O, B);
	return d > 0.0;
}

void build() {
	if(n < 2) return;
	
	for(int i = 1; i < n; i ++)
		if(p[i].y < p[idx].y || (equal(p[i].y, p[idx].y) && p[i].x < p[idx].x))
			idx = i;
	
	swap(p[0], p[idx]);
	O = p[0];
	
	sort(p + 1, p + n, cmp);
	
	hull[sz ++] = p[0];
	for(int i = 1; i < n; i ++) {
		while(sz >= 2) {
			if(det(hull[sz - 2], hull[sz - 1], p[i]) > 0) break;
			sz --;
		}
		hull[sz ++] = p[i];
	}
	
	idx = 0;
	for(int i = 1; i < sz - 1; i ++)
		if(equal(0.0, det(hull[0], hull[i], hull[i + 1]))) idx = i;
		else break;
	
	for(int i = idx + 1; i < sz; i ++)
		hull[i - idx] = hull[i];
	
	sz -= idx;
}

double value(point A, double coef) {
	return coef * det(A, M, N);
}

bool findMax(double coef) {
	if(sz <= 20) {
		for(int i = 0; i < sz; i ++)
			if(value(hull[i], coef) > 0.0)
				return true;
		return false;
	}
	
	for(int i = 0; i < 10; i ++)
		if(value(hull[i], coef) > 0.0)
			return true;
	
	for(int i = sz - 10; i < sz; i ++)
		if(value(hull[i], coef) > 0.0)
			return true;
	
	int le = 0, ri = sz - 5, mid;
	double a, b, c;
	bool inc;
	
	double startValue = value(hull[0], coef);
	double endValue = value(hull[sz - 1], coef);
	
	if(equal(startValue, endValue)) endValue = value(hull[sz - 2], coef);
	
	while(le + 3 <= ri) {
		mid = (le + ri) >> 1;
		a = value(hull[mid], coef);
		b = value(hull[mid + 1], coef);
		c = value(hull[mid + 2], coef);
		
		if(a > 0.0 || b > 0.0 || c > 0.0) return true;
		
		if(!equal(a, b)) inc = (a < b);
		else inc = (a < c);
		
		if(startValue < endValue) {
			if(inc) le = mid + 1;
			else {
				if(startValue > a || (equal(startValue, a) && startValue > b)) le = mid + 1;
				else ri = mid - 1;
			}
		}
		else {
			if(!inc) ri = mid - 1;
			else {
				if(startValue < a || (equal(startValue, a) && startValue < b)) le = mid + 1;
				else ri = mid - 1;
			}
		}
	}
	
	for(int i = le; i <= ri; i ++)
		if(value(hull[i], coef) > 0.0)
			return true;
	
	return false;
}

void solve() {
	while(scanf("%lf %lf %lf %lf", &M.x, &M.y, &N.x, &N.y) == 4) {
		if(n < 2) {
			printf("GOOD\n");
			continue;
		}
		if(findMax(1.0) && findMax(-1.0)) printf("BAD\n");
		else printf("GOOD\n");
	}
}

int main()
{
	read();
	build();
	solve();
	
	return 0;
}
