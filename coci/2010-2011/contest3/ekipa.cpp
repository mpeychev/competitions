#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

int n, m, k;
double val[128];

void read() {
	int idx;
	double s;
	
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 0; i < m; i ++) {
		for(int j = 0; j < n; j ++) {
			cin >> idx >> s;
			if(val[idx] < s) val[idx] = s;
		}
	}
}

void solve() {
	sort(val + 1, val + n + 1);
	
	double sum = 0;
	for(int i = n; i >= n - k + 1; i --)
		sum += val[i];
	
	printf("%.1lf\n", sum);
}

int main()
{
	read();
	solve();

    return 0;
}
