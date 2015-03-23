#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

short int dp[5050][5050];

short int go(int n, int last) {
	if(dp[n][last] != -1)
		return dp[n][last];
	
	if(!n) {
		dp[n][last] = 0;
		return dp[n][last];
	}
	
	dp[n][last] = 0;
	for(int i = 1; i <= n && i <= 2 * last; i ++)
		if(!go(n - i, i)) {
			dp[n][last] = 1;
			break;
		}
	
	return dp[n][last];
}

void solve(int n) {
	for(int i = 1; i <= n; i ++)
		if(!go(n - i, i)) {
			cout << i << endl;
			return;
		}
}

int main()
{
	memset(dp, -1, sizeof(dp));
	for(int i = 1; i <= 100; i ++) {
		cout << i << ": ";
		solve(i);
	}

    return 0;
}
