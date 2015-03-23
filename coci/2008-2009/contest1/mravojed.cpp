#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 1 << 7;

int r, c;
char s[MAXN][MAXN];

int ma3x[MAXN][MAXN];
int ps[MAXN][MAXN];

void read() {
	scanf("%d %d\n", &r, &c);
	for(int i = 0; i < r; i ++)
		scanf("%s", &s[i]);
}

int getSum(int i1, int i2, int j1, int j2) {
	return ps[i2][j2] - ps[i1 - 1][j2] - ps[i2][j1 - 1] + ps[i1 - 1][j1 - 1];
}

void find(int &x, int &y) {
	x = -1, y = -1;
	for(int i = 1; i <= r; i ++)
		for(int j = 1; j <= c; j ++)
			if(ma3x[i][j]) {
				x = i;
				y = j;
				return;
			}
}

void solve() {
	for(int i = 1; i <= r; i ++)
		for(int j = 1; j <= c; j ++) {
			if(s[i - 1][j - 1] == 'x') ma3x[i][j] = 1;
			ps[i][j] = ps[i][j - 1] + ps[i - 1][j] - ps[i - 1][j - 1] + ma3x[i][j];
		}
	
	int x, y, len = 0;
	find(x, y);
	
	for(int i = 1; ; i ++)
		if(getSum(x, x + i - 1, y, y + i - 1) == i * i) len = i;
		else break;
	
	cout << x << " " << y << " " << len << endl;
	for(int i = x; i <= x + len - 1; i ++)
		for(int j = y; j <= y + len - 1; j ++)
			ma3x[i][j] = 0;
	
	int minX = r + 5;
	int maxX = -1;
	int minY = c + 5;
	int maxY = -1;
	
	for(int i = 1; i <= r; i ++)
		for(int j = 1; j <= c; j ++)
			if(ma3x[i][j]) {
				minX = min(minX, i);
				maxX = max(maxX, i);
				
				minY = min(minY, j);
				maxY = max(maxY, j);
			}
	
	if(maxX == -1) {
		cout << x << " " << y << " " << len << endl;
		return;
	}
	
	cout << minX << " " << minY << " " << max(maxX - minX + 1, maxY - minY + 1) << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
