#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

const int MAXN = 1 << 10;
const double eps = 1e-6;

struct point {
	double x, y;
	
	point() {}
	point(double _x, double _y): x(_x), y(_y) {}
};

int n;
point p[MAXN];
int ans;

void read() {
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%lf %lf", &p[i].x, &p[i].y);
}

bool cmp(point A, point B) {
	if(A.x < B.x) return true;
	if(A.x > B.x) return false;
	return A.y < B.y;
}

short int det(point A, point B, point C) {
	double d = (A.x * B.y + B.x * C.y + C.x * A.y) - (B.x * A.y + C.x * B.y + A.x * C.y);
	if(d > eps) return 1;
	if(d < -eps) return -1;
	return 0;
}

bool eq(double x, double y) {
	return fabs(x - y) < eps;
}

bool bs(point D) {
	int le = 0, ri = n - 1, mid;
	while(le <= ri) {
		mid = (le + ri) >> 1;
		
		if(eq(p[mid].x, D.x) && eq(p[mid].y, D.y)) return true;
		
		if(eq(p[mid].x, D.x)) {
			if(p[mid].y < D.y) le = mid + 1;
			else ri = mid - 1;
		}
		else if(p[mid].x < D.x) le = mid + 1;
		else ri = mid - 1;
	}
	return false;
}

bool exist(point A, point B, point C) {
	if(det(A, B, C) == 0)
		return true;
	
	point D;
	
	if(eq(A.x, B.x)) D = point(2 * A.x - C.x, C.y);
	else if(eq(A.y, B.y)) D = point(C.x, 2 * A.y - C.y);
	else {
		double k1, m1;
		double k2, m2;
		
		k1 = (A.y - B.y) / (A.x - B.x);
		m1 = A.y - k1 * A.x;
		
		k2 = -(1.0 / k1);
		m2 = C.y - k2 * C.x;
		
		point O;
		O.x = (m2 - m1) / (k1 - k2);
		O.y = k2 * O.x + m2;
		
		D = point(2 * O.x - C.x, 2 * O.y - C.y);
	}
	
	return bs(D);
}

bool checkLine(point A, point B) {
	for(int i = 0; i < n; i ++)
		if(!exist(A, B, p[i]))
			return false;
	return true;
}

void solve() {
	sort(p, p + n, cmp);
	
	point A, B, C, D;
	double u1, v1, u2, v2;
	
	if(checkLine(p[0], p[1])) ans ++;
	
	for(int i = 2; i < n; i ++) {
		A = p[1];
		B = p[i];
		
		C = point((A.x + B.x) / 2.0, (A.y + B.y) / 2.0);
		u1 = A.x - B.x;
		v1 = A.y - B.y;
		
		if(fabs(v1) > eps) {		
			u2 = 100;
			v2 = -((100 * u1) / v1);
		}
		else {
			u2 = 0;
			v2 = 100;
		}
		
		D = point(C.x + u2, C.y + v2);
		
		if(det(C, D, p[0]) == 0 && checkLine(C, D)) ans ++;
	}
	
	for(int i = 1; i < n; i ++) {
		A = p[0];
		B = p[i];
		
		C = point((A.x + B.x) / 2.0, (A.y + B.y) / 2.0);
		u1 = A.x - B.x;
		v1 = A.y - B.y;
		
		if(fabs(v1) > eps) {		
			u2 = 100;
			v2 = -((100 * u1) / v1);
		}
		else {
			u2 = 0;
			v2 = 100;
		}
		
		D = point(C.x + u2, C.y + v2);
		
		if(checkLine(C, D)) ans ++;
	}
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();
	
	return 0;
}
