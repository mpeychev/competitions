#include <iostream>
#include <stdio.h>

using namespace std;

int n;
char s[32][32];

void read() {
	scanf("%d\n", &n);
	for(int i = 0; i < n; i ++)
		scanf("%s", &s[i]);
}

void solve() {
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++) {
			if(s[i][j] == '.') continue;
			if(0 < j && j < n - 1 && s[i][j - 1] == s[i][j] && s[i][j] == s[i][j + 1]) {
				printf("%c\n", s[i][j]);
				return;
			}
			if(0 < i && i < n - 1 && s[i][j] == s[i - 1][j] && s[i][j] == s[i + 1][j]) {
				printf("%c\n", s[i][j]);
				return;
			}
			if(0 < j && j < n - 1 && 0 < i && i < n - 1) {
				if(s[i][j] == s[i - 1][j - 1] && s[i][j] == s[i + 1][j + 1]) {
					printf("%c\n", s[i][j]);
					return;
				}
				if(s[i][j] == s[i - 1][j + 1] && s[i][j] == s[i + 1][j - 1]) {
					printf("%c\n", s[i][j]);
					return;
				}
			}
		}
	
	printf("ongoing\n");
}

int main()
{
	read();
	solve();
	
	return 0;
}
