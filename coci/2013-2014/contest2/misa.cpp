#include <iostream>
#include <stdio.h>

using namespace std;

const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int r, s;
char ma3x[64][64];

void read() {
	scanf("%d %d\n", &r, &s);
	for(int i = 0; i < r; i ++)
		scanf("%s", &ma3x[i]);
}

int calc(int i, int j) {
	int ret = 0;
	for(int k = 0; k < 8; k ++) {
		int x = i + dx[k];
		int y = j + dy[k];

		if(x >= 0 && x < r && y >= 0 && y < s && ma3x[x][y] == 'o')
			ret ++;
	}
	return ret;
}

void solve() {
	int x = 0, y = 0, mx = -1;
	for(int i = 0; i < r; i ++)
		for(int j = 0; j < s; j ++)
			if(ma3x[i][j] == '.') {
				int t = calc(i, j);
				if(t > mx) {
					mx = t;
					x = i;
					y = j;
				}
			}

	ma3x[x][y] = 'o';

	int ans = 0;
	for(int i = 0; i < r; i ++)
		for(int j = 0; j < s; j ++)
            if(ma3x[i][j] == 'o')
                ans += calc(i, j);

	cout << ans / 2 << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
