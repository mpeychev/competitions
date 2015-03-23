#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 256;

struct node {
	int mx, mn;
};

int n, b, k, lvs, x, y;
node t[2 * MAXN][2 * MAXN];

void update(int idx1, int idx2, int val) {
	while(idx1) {
		int cpy = idx2;
		while(cpy) {
			t[idx1][cpy].mx = max(t[idx1][cpy].mx, val);
			t[idx1][cpy].mn = min(t[idx1][cpy].mn, val);
			cpy >>= 1;
		}
		idx1 >>= 1;
	}
}

void build() {
	scanf("%d %d %d", &n, &b, &k);
	
	lvs = 1;
	while(lvs < n) lvs <<= 1;
	
	for(int i = 1; i < 2 * lvs; i ++)
		for(int j = 1; j < 2 * lvs; j ++)
			t[i][j].mx = 0, t[i][j].mn = MAXN;
	
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++) {
			scanf("%d", &x);
			update(i + lvs, j + lvs, x);
		}
}

int getMax1(int idx1, int idx2, int le, int ri) {
	if(y + b - 1 < le || ri < y)
		return 0;
	
	if(y <= le && ri <= y + b - 1)
		return t[idx1][idx2].mx;
	
	int mid = (le + ri) >> 1;
	return max(getMax1(idx1, 2 * idx2, le, mid), getMax1(idx1, 2 * idx2 + 1, mid + 1, ri));
}

int getMax(int idx1, int up, int down) {
	if(x + b - 1 < up || down < x)
		return 0;
	
	if(x <= up && down <= x + b - 1)
		return getMax1(idx1, 1, 0, lvs - 1);
	
	int mid = (up + down) >> 1;
	return max(getMax(2 * idx1, up, mid), getMax(2 * idx1 + 1, mid + 1, down));
}

int getMin1(int idx1, int idx2, int le, int ri) {
	if(y + b - 1 < le || ri < y)
		return MAXN;
	
	if(y <= le && ri <= y + b - 1)
		return t[idx1][idx2].mn;
	
	int mid = (le + ri) >> 1;
	return min(getMin1(idx1, 2 * idx2, le, mid), getMin1(idx1, 2 * idx2 + 1, mid + 1, ri));
}

int getMin(int idx1, int up, int down) {
	if(x + b - 1 < up || down < x)
		return MAXN;
	
	if(x <= up && down <= x + b - 1)
		return getMin1(idx1, 1, 0, lvs - 1);
	
	int mid = (up + down) >> 1;
	return min(getMin(2 * idx1, up, mid), getMin(2 * idx1 + 1, mid + 1, down));
}

void solve() {
	for( ; k; k --) {
		scanf("%d %d", &x, &y);
		x --, y --;
		
		int mx = getMax(1, 0, lvs - 1);
		int mn = getMin(1, 0, lvs - 1);
		
		printf("%d\n", mx - mn);
	}
}

int main()
{
	build();
	solve();

    return 0;
}
