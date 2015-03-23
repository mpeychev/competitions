#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 1000000;

int n, MOD, ans;
int dp[MAXN + 5][2][2][4];
char ch;

void read() {
	scanf("%d %d\n", &n, &MOD);
}

int calc(int len, int mx, int mn, int cur) {
	int &ret = dp[len][mx][mn][cur];
	
	if(ret != -1)
		return ret;
	
	if(len == 0) {
		ret = 1;
		return ret;
	}
	
	ret = 0;
	
	/// Go UP
	if(cur != 3) {
		int nxtMax;
		if(cur != 2) nxtMax = mx;
		else nxtMax = 1;
		
		if(!nxtMax || !mn) ret += calc(len - 1, nxtMax, mn, cur + 1);
	}
	
	/// Go DOWN
	if(cur != 0) {
		int nxtMin;
		if(cur != 1) nxtMin = mn;
		else nxtMin = 1;
		
		if(!mx || !nxtMin) ret += calc(len - 1, mx, nxtMin, cur - 1);
	}
	
	ret %= MOD;
	return ret;
}

void solve() {
	memset(dp, -1, sizeof(dp));
	
	scanf("%c", &ch);
	
	int l, p;
	int curMin, curMax, curPos;
	
	if(ch == 'L') {
		l = 1;
		p = -1;
	}
	else {
		ans = calc(n - 1, 0, 0, 2);
		l = -1;
		p = 1;
	}
	
	curMin = 0, curMax = 0, curPos = 2;
	
	for(int i = 1; i < n; i ++) {
		scanf("%c", &ch);
		if(ch == 'L') {
			curPos += l;
			if(curPos == 0) curMin = 1;
			if(curPos == 3) curMax = 1;
		}
		else {
			int lMin = curMin, lMax = curMax, lPos = curPos + l;
			if(lPos <= 3 && lPos >= 0) {
				if(lPos == 0) lMin = 1;
				if(lPos == 3) lMax = 1;
				
				if(!lMin || !lMax) ans = (ans + calc(n - i - 1, lMax, lMin, lPos)) % MOD;
			}
			
			curPos += p;
			if(curPos == 0) curMin = 1;
			if(curPos == 3) curMax = 1;
		}
	}
	
	cout << (ans + 1) % MOD << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
