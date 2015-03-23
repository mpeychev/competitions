#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 1515;
const int MAXM = 1515;

int n, m, k;
int ma3x[MAXN][MAXM];

int ps[MAXN][MAXM];
int angle[4][MAXN][MAXM];
int vertical[2][MAXM];
int horizontal[2][MAXN];

void read() {
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			scanf("%d", &ma3x[i][j]);
}

int getSum(int i1, int j1, int i2, int j2) {
	return ps[i2][j2] - ps[i2][j1 - 1] - ps[i1 - 1][j2] + ps[i1 - 1][j1 - 1];
}

int max(int a, int b) {
	if(a > b) return a;
	return b;
}

void precompute() {
	/// PS
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			ps[i][j] = ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1] + ma3x[i][j];
	
	memset(angle, -1, sizeof(angle));
	memset(vertical, -1, sizeof(vertical));
	memset(horizontal, -1, sizeof(horizontal));
	
	/// ANGLE (One square)
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			if(i >= k && j >= k) {
				angle[0][i][j] = getSum(i - k + 1, j - k + 1, i, j);
				angle[0][i][j] = max(angle[0][i][j], angle[0][i - 1][j]);
				angle[0][i][j] = max(angle[0][i][j], angle[0][i][j - 1]);
			}
	
	for(int i = 1; i <= n; i ++)
		for(int j = m; j >= 1; j --)
			if(i >= k && j + k - 1 <= m) {
				angle[2][i][j] = getSum(i - k + 1, j, i, j + k - 1);
				angle[2][i][j] = max(angle[2][i][j], angle[2][i - 1][j]);
				angle[2][i][j] = max(angle[2][i][j], angle[2][i][j + 1]);
			}
	
	for(int i = n; i >= 1; i --)
		for(int j = 1; j <= m; j ++)
			if(i + k - 1 <= n && j >= k) {
				angle[1][i][j] = getSum(i, j - k + 1, i + k - 1, j);
				angle[1][i][j] = max(angle[1][i][j], angle[1][i + 1][j]);
				angle[1][i][j] = max(angle[1][i][j], angle[1][i][j - 1]);
			}
	
	for(int i = n; i >= 1; i --)
		for(int j = m; j >= 1; j --)
			if(i + k - 1 <= n && j + k - 1 <= m) {
				angle[3][i][j] = getSum(i, j, i + k - 1, j + k - 1);
				angle[3][i][j] = max(angle[3][i][j], angle[3][i + 1][j]);
				angle[3][i][j] = max(angle[3][i][j], angle[3][i][j + 1]);
			}
	
	/// VERTICAL (Two squares)
	for(int j = k; j <= m; j ++) {
		vertical[0][j] = vertical[0][j - 1];
		for(int i = 1; i + k - 1 <= n; i ++) {
			int fixed = getSum(i, j - k + 1, i + k - 1, j);
			int val1 = -1, val2 = -1, val3 = -1;
			
			if(angle[0][i - 1][j] != -1) val1 = fixed + angle[0][i - 1][j];
			if(angle[1][i + k][j] != -1) val2 = fixed + angle[1][i + k][j];
			if(angle[0][n][j - k] != -1) val3 = fixed + angle[0][n][j - k];
			
			vertical[0][j] = max(max(vertical[0][j], val1), max(val2, val3));
		}
	}
	
	for(int j = m - k + 1; j >= 1; j --) {
		vertical[1][j] = vertical[1][j + 1];
		for(int i = 1; i + k - 1 <= n; i ++) {
			int fixed = getSum(i, j, i + k - 1, j + k - 1);
			int val1 = -1, val2 = -1, val3 = -1;
			
			if(angle[3][1][j + k] != -1) val1 = fixed + angle[3][1][j + k];
			if(angle[2][i - 1][j] != -1) val2 = fixed + angle[2][i - 1][j];
			if(angle[3][i + k][j] != -1) val3 = fixed + angle[3][i + k][j];
			
			vertical[1][j] = max(max(vertical[1][j], val1), max(val2, val3));
		}
	}
	
	/// HORIZONTAL (Two squares)
	for(int i = k; i <= n; i ++) {
		horizontal[0][i] = horizontal[0][i - 1];
		for(int j = 1; j + k - 1 <= m; j ++) {
			int fixed = getSum(i - k + 1, j, i, j + k - 1);
			int val1 = -1, val2 = -1, val3 = -1;
			
			if(angle[0][i][j - 1] != -1) val1 = fixed + angle[0][i][j - 1];
			if(angle[2][i][j + k] != -1) val2 = fixed + angle[2][i][j + k];
			if(angle[2][i - k][1] != -1) val3 = fixed + angle[2][i - k][1];
			
			horizontal[0][i] = max(max(horizontal[0][i], val1), max(val2, val3));
		}
	}
	
	for(int i = n - k + 1; i >= 1; i --) {
		horizontal[1][i] = horizontal[1][i + 1];
		for(int j = 1; j + k - 1 <= m; j ++) {
			int fixed = getSum(i, j, i + k - 1, j + k - 1);
			int val1 = -1, val2 = -1, val3 = -1;
			
			if(angle[1][i][j - 1] != -1) val1 = fixed + angle[1][i][j - 1];
			if(angle[3][i][j + k] != -1) val2 = fixed + angle[3][i][j + k];
			if(angle[3][i + k][1] != -1) val3 = fixed + angle[3][i + k][1];
			
			horizontal[1][i] = max(max(horizontal[1][i], val1), max(val2, val3));
		}
	}
}

void solve() {
	int ans = -1;
	for(int i = 1; i + k - 1 <= n; i ++)
		for(int j = 1; j + k - 1 <= m; j ++) {
			int fixed = getSum(i, j, i + k - 1, j + k - 1);
			int val1 = -1, val2 = -1, val3 = -1, val4 = -1;
			
			if(horizontal[0][i - 1] != -1) val1 = fixed + horizontal[0][i - 1];
			if(horizontal[1][i + k] != -1) val2 = fixed + horizontal[1][i + k];
			
			if(vertical[0][j - 1] != -1) val3 = fixed + vertical[0][j - 1];
			if(vertical[1][j + k] != -1) val4 = fixed + vertical[1][j + k];
			
			int tmp = max(max(val1, val2), max(val3, val4));
			ans = max(ans, tmp);
		}
	
	cout << ans << endl;
}

int main()
{
	read();
	precompute();
	solve();

    return 0;
}
