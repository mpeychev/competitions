#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 256;

int n, b, k, x, y;
int RMaxQ[MAXN][MAXN][8];
int RMinQ[MAXN][MAXN][8];

void read() {
	scanf("%d %d %d", &n, &b, &k);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++) {
			scanf("%d", &x);
			RMaxQ[i][j][0] = x;
			RMinQ[i][j][0] = x;
		}
}

void build() {
	for(int p = 1; (1 << p) <= n; p ++) {
		for(int i = 0; i + (1 << p) - 1 < n; i ++)
			for(int j = 0; j + (1 << p) - 1 < n; j ++) {
				RMaxQ[i][j][p] = max(max(RMaxQ[i][j][p - 1], RMaxQ[i + (1 << (p - 1))][j][p - 1]),
									 max(RMaxQ[i][j + (1 << (p - 1))][p - 1], RMaxQ[i + (1 << (p - 1))][j + (1 << (p - 1))][p - 1]));
				RMinQ[i][j][p] = min(min(RMinQ[i][j][p - 1], RMinQ[i + (1 << (p - 1))][j][p - 1]),
									 min(RMinQ[i][j + (1 << (p - 1))][p - 1], RMinQ[i + (1 << (p - 1))][j + (1 << (p - 1))][p - 1]));
			}
	}
}

void solve() {
	int p = 0;
	while((1 << (p + 1)) <= b)
		p ++;
	
	for(int i = 0; i < k; i ++) {
		scanf("%d %d", &x, &y);
		x --, y --;
		int mx = max(max(RMaxQ[x][y][p], RMaxQ[x + b - (1 << p)][y][p]),
					 max(RMaxQ[x][y + b - (1 << p)][p], RMaxQ[x + b - (1 << p)][y + b - (1 << p)][p]));
		int mn = min(min(RMinQ[x][y][p], RMinQ[x + b - (1 << p)][y][p]),
					 min(RMinQ[x][y + b - (1 << p)][p], RMinQ[x + b - (1 << p)][y + b - (1 << p)][p]));
		printf("%d\n", mx - mn);
	}
}

int main()
{
	read();
	build();
	solve();

    return 0;
}
