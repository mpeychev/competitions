#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int n;
int x1, y1, x2, y2;
int z1, w1, z2, w2;

int countQueries;

int leftBound, rightBound, upperBound, lowerBound;
int corners[4], sum;
int r1, c1, r2, c2, p1, q1, p2, q2;

void read() {
	scanf("%d", &n);
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	scanf("%d %d %d %d", &z1, &w1, &z2, &w2);
}

bool checkROD1(int a, int b, int c, int d) {
	if(x1 < a || x1 > b) return false;
	if(y2 < c || y1 > d) return false;
	return true;
}

bool checkROD2(int a, int b, int c, int d) {
	if(w1 < c || w1 > d) return false;
	if(z2 < a || z1 > b) return false;
	return true;
}

bool rect(int a, int b, int c, int d) {
	if(a > b || c > d) {
		printf("Invalid rectangle\n");
		exit(0);
	}
	if(a < 1 || b > n || c < 1 || c > n) {
		printf("Rectangle out of range\n");
		exit(0);
	}
	
	countQueries ++;
	if(checkROD1(a, b, c, d)) return true;
	if(checkROD2(a, b, c, d)) return true;
	
	return false;
}

int bsX(int a, int b, int c, int d, bool fl) {
/// fl = true  => upper
/// fl = false => lower
	
	int le = a, ri = b, mid, ret;
	bool t;
	
	if(fl) ret = a - 1;
	else ret = b + 1;
	
	while(le <= ri) {
		mid = (le + ri) >> 1;
		if(fl) {
			t = rect(a, mid, c, d);
			if(!t) {
				ret = mid;
				le = mid + 1;
			}
			else ri = mid - 1;
		}
		else {
			t = rect(mid, b, c, d);
			if(!t) {
				ret = mid;
				ri = mid - 1;
			}
			else le = mid + 1;
		}
	}
	
	if(fl) ret ++;
	else ret --;
	
	return ret;
}

int bsY(int a, int b, int c, int d, bool fl) {
/// fl = true  => left
/// fl = false => right
	
	int le = c, ri = d, mid, ret;
	bool t;
	
	if(fl) ret = c - 1;
	else ret = d + 1;
	
	while(le <= ri) {
		mid = (le + ri) >> 1;
		if(fl) {
			t = rect(a, b, c, mid);
			if(!t) {
				ret = mid;
				le = mid + 1;
			}
			else ri = mid - 1;
		}
		else {
			t = rect(a, b, mid, d);
			if(!t) {
				ret = mid;
				ri = mid - 1;
			}
			else le = mid + 1;
		}
	}
	
	if(fl) ret ++;
	else ret --;
	
	return ret;
}

void report() {
	cout << "Rods:\n";
	cout << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
	cout << z1 << " " << w1 << " " << z2 << " " << w2 << "\n";
	cout << "\n";
	
	cout << "My solution\n";
	cout << r1 << " " << c1 << " " << r2 << " " << c2 << "\n";
	cout << p1 << " " << q1 << " " << p2 << " " << q2 << "\n";
	cout << "Queries: " << countQueries << "\n";
	cout << "\n";
	if(x1 == r1 && y1 == c1 && x2 == r2 && y2 == c2 &&
	   z1 == p1 && w1 == q1 && z2 == p2 && w2 == q2)
			printf("ok\n");
	else printf("wa\n");
}

void solve() {
	upperBound = bsX(1, n, 1, n, true);
	lowerBound = bsX(1, n, 1, n, false);
	leftBound = bsY(1, n, 1, n, true);
	rightBound = bsY(1, n, 1, n, false);
	
	corners[0] = rect(upperBound, upperBound, leftBound, leftBound);
	corners[1] = rect(upperBound, upperBound, rightBound, rightBound);
	corners[2] = rect(lowerBound, lowerBound, rightBound, rightBound);
	corners[3] = rect(lowerBound, lowerBound, leftBound, leftBound);
	
	for(int i = 0; i < 4; i ++)
		sum += corners[i];

	if(!sum) {
		r1 = bsX(upperBound, lowerBound, leftBound, leftBound, true);
		r2 = r1;
		c1 = leftBound;
		c2 = rightBound;
		
		p1 = upperBound;
		p2 = lowerBound;
		q1 = bsY(upperBound, upperBound, leftBound, rightBound, true);
		q2 = q1;
		
		report();
		
		return;
	}
	
	if(sum == 3) {
		if(!corners[0]) {
			r1 = r2 = lowerBound;
			c1 = leftBound;
			c2 = bsY(lowerBound, lowerBound, leftBound, rightBound - 1, false);
			if(c2 == rightBound - 1) c2 ++;
			
			q1 = q2 = rightBound;
			p1 = upperBound;
			p2 = bsX(upperBound, lowerBound - 1, rightBound, rightBound, false);
			if(p2 == lowerBound - 1) p2 ++;
			
			report();
		}
		else if(!corners[1]) {
			r1 = r2 = lowerBound;
			c2 = rightBound;
			c1 = bsY(lowerBound, lowerBound, leftBound + 1, rightBound, true);
			if(c1 == leftBound + 1) c1 --;
			
			q1 = q2 = leftBound;
			p1 = upperBound;
			p2 = bsX(upperBound, lowerBound - 1, leftBound, leftBound, false);
			if(p2 == lowerBound - 1) p2 ++;
			
			report();
		}
		else if(!corners[2]) {
			r1 = r2 = upperBound;
			c2 = rightBound;
			c1 = bsY(upperBound, upperBound, leftBound + 1, rightBound, true);
			if(c1 == leftBound + 1) c1 --;
			
			q1 = q2 = leftBound;
			p2 = lowerBound;
			p1 = bsX(upperBound + 1, lowerBound, leftBound, leftBound, true);
			if(p1 == upperBound + 1) p1 --;
			
			report();
		}
		else {
			r1 = r2 = upperBound;
			c2 = leftBound;
			c1 = leftBound;
			c2 = bsY(upperBound, upperBound, leftBound, rightBound - 1, false);
			if(c2 == rightBound - 1) c2 ++;
			
			q1 = q2 = rightBound;
			p2 = lowerBound;
			p1 = bsX(upperBound + 1, lowerBound, rightBound, rightBound, true);
			if(p1 == upperBound + 1) p1 --;
			
			report();
		}
		
		return;
	}
	
	if(corners[0] && corners[1]) {
		r1 = r2 = upperBound;
		c1 = leftBound;
		c2 = rightBound;
		
		p2 = lowerBound;
		p1 = bsX(upperBound + 1, lowerBound, leftBound, rightBound, true);
		if(p1 == upperBound + 1) p1 --;
		q1 = bsY(upperBound + 1, lowerBound, leftBound, rightBound, true);
		q2 = q1;
		
		report();
		return;
	}
	
	if(corners[2] && corners[3]) {
		r1 = r2 = lowerBound;
		c1 = leftBound;
		c2 = rightBound;
		
		p1 = upperBound;
		p2 = bsX(upperBound, lowerBound - 1, leftBound, rightBound, false);
		if(p2 == lowerBound - 1) p2 ++;
		q1 = bsY(upperBound, lowerBound - 1, leftBound, rightBound, true);
		q2 = q1;
		
		report();
		return;
	}
	
	if(corners[0] && corners[3]) {
		p1 = upperBound;
		p2 = lowerBound;
		q1 = q2 = leftBound;
		
		c2 = rightBound;
		c1 = bsY(upperBound, lowerBound, leftBound + 1, rightBound, true);
		if(c1 == leftBound + 1) c1 --;
		r1 = bsX(upperBound, lowerBound, leftBound + 1, rightBound, true);
		r2 = r1;
		
		report();
		return;
	}
	
	if(corners[1] && corners[2]) {
		p1 = upperBound;
		p2 = lowerBound;
		q1 = q2 = rightBound;
		
		c1 = leftBound;
		c2 = bsY(upperBound, lowerBound, leftBound, rightBound - 1, false);
		if(c2 == rightBound - 1) c2 ++;
		r1 = bsX(upperBound, lowerBound, leftBound, rightBound - 1, true);
		r2 = r1;
		
		report();
		return;
	}
	
	if(corners[0]) {
		if(rect(upperBound, upperBound, leftBound + 1, leftBound + 1)) {
			r1 = r2 = upperBound;
			c1 = leftBound;
			c2 = bsY(upperBound, upperBound, leftBound, rightBound, false);
		}
		else {
			q1 = q2 = leftBound;
			p1 = upperBound;
			p2 = bsX(upperBound, lowerBound, leftBound, leftBound, false);
		}
	}
	
	if(corners[1]) {
		if(rect(upperBound, upperBound, rightBound - 1, rightBound - 1)) {
			r1 = r2 = upperBound;
			c2 = rightBound;
			c1 = bsY(upperBound, upperBound, leftBound, rightBound, true);
		}
		else {
			q1 = q2 = rightBound;
			p1 = upperBound;
			p2 = bsX(upperBound, lowerBound, rightBound, rightBound, false);
		}
	}
	
	if(corners[2]) {
		if(rect(lowerBound, lowerBound, rightBound - 1, rightBound - 1)) {
			r1 = r2 = lowerBound;
			c2 = rightBound;
			c1 = bsY(lowerBound, lowerBound, leftBound, rightBound, true);
		}
		else {
			q1 = q2 = rightBound;
			p2 = lowerBound;
			p1 = bsX(upperBound, lowerBound, rightBound, rightBound, true);
		}
	}
	
	if(corners[3]) {
		if(rect(lowerBound, lowerBound, leftBound + 1, leftBound + 1)) {
			r1 = r2 = lowerBound;
			c1 = leftBound;
			c2 = bsY(lowerBound, lowerBound, leftBound, rightBound, false);
		}
		else {
			q1 = q2 = leftBound;
			p2 = lowerBound;
			p1 = bsX(upperBound, lowerBound, leftBound, leftBound, true);
		}
	}
	
	report();
}

int main()
{
	read();
	solve();
	
	return 0;
}
