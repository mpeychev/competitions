#include <iostream>
#include <stdio.h>

using namespace std;

int r, c;
char s[64][64];
char ma3x[128][128];
int a, b;

void read() {
	scanf("%d %d\n", &r, &c);
	for(int i = 0; i < r; i ++)
		scanf("%s", &s[i]);
	scanf("%d %d", &a, &b);
}

void solve() {
	for(int i = 0; i < r; i ++) {
		for(int j = 0; j < c; j ++)
			ma3x[i][j] = s[i][j];
		for(int j = c, k = c - 1; j < 2 * c; j ++, k --)
			ma3x[i][j] = s[i][k];
	}
	for(int i = r, k = r - 1; i < 2 * r; i ++, k --) {
		for(int j = 0; j < 2 * c; j ++)
			ma3x[i][j] = ma3x[k][j];
	}
	
	a --, b --;
	if(ma3x[a][b] == '#') ma3x[a][b] = '.';
	else ma3x[a][b] = '#';
	
	for(int i = 0; i < 2 * r; i ++) {
		for(int j = 0; j < 2 * c; j ++)
			printf("%c", ma3x[i][j]);
		printf("\n");
	}
}

int main()
{
	read();
	solve();
	
	return 0;
}
