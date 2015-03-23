#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

const int MAXN = 100100;

int n, f;
int a[MAXN];
double s[MAXN];

void read() {
	scanf("%d %d", &n, &f);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
}

bool check(double alpha) {
	s[0] = 0.0;
	for(int i = 1; i <= n; i ++)
		s[i] = s[i - 1] + (double)a[i] - alpha;
	
	if(s[f] > 0.0) return true;
	
	double mn = 0.0;
	for(int i = f + 1; i <= n; i ++) {
		mn = min(mn, s[i - f]);
		if(s[i] > mn) return true;
	}
	
	return false;
}

void solve() {
	double le = 0.0, ri = 2000.0, mid;
	for(int iter = 0; iter < 100; iter ++) {
		mid = (le + ri) / 2.0;
		if(check(mid)) le = mid;
		else ri = mid;
	}
	
	printf("%d\n", (int)ceil(10000 * ri) / 10);
}

int main()
{
	read();
	solve();

    return 0;
}
