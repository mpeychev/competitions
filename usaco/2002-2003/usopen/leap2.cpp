#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 512;

const int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

int n, ma3x[MAXN][MAXN];
int dp[MAXN][MAXN];

void read() {
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			scanf("%d", &ma3x[i][j]);
}

int go(int x, int y) {
	int &ret = dp[x][y];
	
	if(ret != -1)
		return ret;
	
	int mx = 0, cur;
	for(int k = 0; k < 8; k ++) {
		int nxtX = x + dx[k];
		int nxtY = y + dy[k];
		
		if(nxtX >= 0 && nxtX < n && nxtY >= 0 && nxtY < n && ma3x[x][y] < ma3x[nxtX][nxtY]) {
			cur = go(nxtX, nxtY);
			if(mx < cur) mx = cur;
		}
	}
	
	ret = 1 + mx;
	return ret;
}

void write(int x, int y) {
	printf("%d\n", ma3x[x][y]);
	
	int mx = -1, cur, nextX = -1, nextY = -1;
	for(int k = 0; k < 8; k ++) {
		int nxtX = x + dx[k];
		int nxtY = y + dy[k];
		
		if(nxtX >= 0 && nxtX < n && nxtY >= 0 && nxtY < n && ma3x[x][y] < ma3x[nxtX][nxtY]) {
			cur = go(nxtX, nxtY);
			if(mx < cur || (mx == cur && ma3x[nextX][nextY] > ma3x[nxtX][nxtY])) {
				mx = cur;
				nextX = nxtX;
				nextY = nxtY;
			}
		}
	}
	
	if(mx == -1) return;
	
	write(nextX, nextY);
}

void solve() {
	memset(dp, -1, sizeof(dp));
	
	int len = 0, startX = -1, startY = -1, cur;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++) {
			cur = go(i, j);
			if(len < cur || (len == cur && ma3x[startX][startY] > ma3x[i][j])) {
				len = cur;
				startX = i;
				startY = j;
			}
		}
	
	cout << len << endl;
	write(startX, startY);
}

int main()
{
	read();
	solve();

    return 0;
}
