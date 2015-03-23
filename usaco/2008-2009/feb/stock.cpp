#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int s, d, m;
int ma3x[64][16];
int dp[500500];

void read() {
	scanf("%d %d %d", &s, &d, &m);
	for(int i = 1; i <= s; i ++)
		for(int j = 1; j <= d; j ++)
			scanf("%d", &ma3x[i][j]);
}

int maxMoney(int money, int day) {
	for(int i = 0; i <= money; i ++)
		dp[i] = i;
	
	for(int stock = s; stock >= 1; stock --)
		for(int i = 0; i <= money; i ++)
			if(i >= ma3x[stock][day])
				dp[i] = max(dp[i], dp[ i - ma3x[stock][day] ] + ma3x[stock][day + 1]);
	
	return dp[money];
}

void solve() {
	for(int i = 1; i < d; i ++)
		m = maxMoney(m, i);
	
	cout << m << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
