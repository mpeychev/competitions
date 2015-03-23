#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 128;

int n, r, c;
char s[128];
char ma3x[MAXN][MAXN];

void read() {
	scanf("%s", &s);
}

void solve() {
	n = strlen(s);
	for(int i = 1; i * i <= n; i ++)
		if(n % i == 0) {
			r = i;
			c = n / i;
		}
	
	int idx = 0;
	for(int j = 0; j < c; j ++)
		for(int i = 0; i < r; i ++)
			ma3x[i][j] = s[idx ++];
	
	for(int i = 0; i < r; i ++)
		for(int j = 0; j < c; j ++)
			cout << ma3x[i][j];
	cout << endl;
}

int main()
{
	read();
	solve();
	
	return 0;
}
