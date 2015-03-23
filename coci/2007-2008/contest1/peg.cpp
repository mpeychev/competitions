#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int n = 7;

int ans;
char s[16][16];

int main()
{	
	for(int i = 0; i < n; i ++)
		gets(s[i]);
	
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			if(s[i][j] == 'o') {
				if(i - 2 >= 0 && s[i - 1][j] == 'o' && s[i - 2][j] == '.') ans ++;
				if(i + 2 < n && s[i + 1][j] == 'o' && s[i + 2][j] == '.') ans ++;
				if(j - 2 >= 0 && s[i][j - 1] == 'o' && s[i][j - 2] == '.') ans ++;
				if(j + 2 < n && s[i][j + 1] == 'o' && s[i][j + 2] == '.') ans ++;
			}
	cout << ans << endl;

    return 0;
}
