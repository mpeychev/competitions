#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

typedef long long LL;

int n;
LL m, k, ma3x[16][8];
char s[32];

void read() {
	cin >> n >> m >> k;
	cin >> s;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < 8; j ++)
			cin >> ma3x[i][j];
}

bool solveOR(LL R, int row);
bool solveAND(LL R, int row, int le);

bool solveAND(LL R, int row, int le) {
	LL val[2];
	val[0] = (R + R * ma3x[row][le] + ma3x[row][le + 1]) % m;
	val[1] = (R + R * ma3x[row][le + 2] + ma3x[row][le + 3]) % m;
	
	bool fl = rand() % 2;
	return (solveOR(val[fl], row + 1) && solveOR(val[!fl], row + 1));
}

bool solveOR(LL R, int row) {
	if(row == n)
		return (R <= k || R + k >= m);
	
	bool fl = rand() & 1;
	return (solveAND(R, row, 4 * fl) || solveAND(R, row, 4 * (!fl)));
}

void solve() {
	LL R = 0;
	for(int i = 0; i < n; i ++) {
		if(solveAND(R, i, 4)) {
			printf("B");
			
			if(s[i] == 'T') R = (R + R * ma3x[i][4] + ma3x[i][5]) % m;
			else R = (R + R * ma3x[i][6] + ma3x[i][7]) % m;
		}
		else {
			printf("T");
			
			if(s[i] == 'T') R = (R + R * ma3x[i][0] + ma3x[i][1]) % m;
			else R = (R + R * ma3x[i][2] + ma3x[i][3]) % m;
		}
	}
	
	printf("\n");
}

int main()
{
	srand(time(NULL));
	
	read();
	solve();

    return 0;
}
