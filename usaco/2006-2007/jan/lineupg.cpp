#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 50100;
const int MAX_LOG = 16;

int n, q;
int a[MAXN];
int RMinQ[MAXN][MAX_LOG], RMaxQ[MAXN][MAX_LOG];
int pw[MAXN];

void read() {
	scanf("%d %d", &n, &q);
	for(int i = 0; i < n; i ++)
		scanf("%d", &a[i]);
}

void build() {
	for(int i = 0; i < n; i ++)
		RMinQ[i][0] = RMaxQ[i][0] = a[i];
	
	for(int i = 2; i <= n; i ++)
		pw[i] = pw[i >> 1] + 1;
	
	for(int j = 1; j <= pw[n]; j ++) {
		int blockLen = (1 << j);
		for(int i = 0; i + blockLen <= n; i ++) {
			RMinQ[i][j] = min(RMinQ[i][j - 1], RMinQ[ i + (blockLen >> 1) ][j - 1]);
			RMaxQ[i][j] = max(RMaxQ[i][j - 1], RMaxQ[ i + (blockLen >> 1) ][j - 1]);
		}
	}
}

int getMax(int le, int ri) {
	int len = ri - le + 1;
	int pwLen = 1 << pw[len];
	return max(RMaxQ[le][ pw[len] ], RMaxQ[ri - pwLen + 1][ pw[len] ]);
}

int getMin(int le, int ri) {
	int len = ri - le + 1;
	int pwLen = 1 << pw[len];
	return min(RMinQ[le][ pw[len] ], RMinQ[ri - pwLen + 1][ pw[len] ]);
}

void solve() {
	int le, ri;
	
	for( ; q; q --) {
		scanf("%d %d", &le, &ri);
		le --, ri --;
		printf("%d\n", getMax(le, ri) - getMin(le, ri));
	}
}

int main()
{
	read();
	build();
	solve();

    return 0;
}
