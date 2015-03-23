#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#define pb push_back

using namespace std;

const int MAXN = 10100;

int n, c;

struct Child {
	int e, f, l;
	int x[8], y[8];
	
	void read() {
		scanf("%d %d %d", &e, &f, &l);
		e --;
		for(int i = 0; i < f; i ++) {
			scanf("%d", &x[i]);
			x[i] --;
		}
		for(int i = 0; i < l; i ++) {
			scanf("%d", &y[i]);
			y[i] --;
		}
	}
	
	bool happy(int mask) {
		for(int i = 0; i < f; i ++)
			if(!((mask >> ( (x[i] - e + n) % n )) & 1))
				return true;
		for(int i = 0; i < l; i ++)
			if((mask >> ( (y[i] - e + n) % n )) & 1)
				return true;
		return false;
	}
} toAdd;

vector< Child > li[MAXN];
int dp[MAXN][1 << 4];
int startMask;

void read() {
	scanf("%d %d", &n, &c);
	for(int i = 0; i < c; i ++) {
		toAdd.read();
		li[toAdd.e].pb(toAdd);
	}
}

int max(int a, int b) {
	if(a > b) return a;
	return b;
}

int go(int pos, int mask) {
	if(dp[pos][mask] != -1)
		return dp[pos][mask];
	
	int newMask = mask;
	int ret;
	
	if(pos + 4 >= n) {
		newMask |= ( ((startMask >> (pos + 4 - n)) & 1) << 4 );
		
		ret = 0;
		for(int i = 0; i < (int)li[pos].size(); i ++)
			if(li[pos][i].happy(newMask))
				ret ++;
		
		if(pos == n - 1) {
			dp[pos][mask] = ret;
			return ret;
		}
		
		ret += go(pos + 1, newMask >> 1);
		dp[pos][mask] = ret;
		return ret;
	}
	
	int opt1, opt2;
	
	ret = 0;
	for(int i = 0; i < li[pos].size(); i ++)
		if(li[pos][i].happy(newMask))
			ret ++;
	ret += go(pos + 1, newMask >> 1);
	opt1 = ret;
	
	newMask |= (1 << 4);
	ret = 0;
	for(int i = 0; i < li[pos].size(); i ++)
		if(li[pos][i].happy(newMask))
			ret ++;
	ret += go(pos + 1, newMask >> 1);
	opt2 = ret;
	
	dp[pos][mask] = max(opt1, opt2);
	return dp[pos][mask];
}

void solve() {
	int ans = 0;
	
	for(startMask = 0; startMask < (1 << 4); startMask ++) {
		memset(dp, -1, sizeof(dp));
		ans = max(ans, go(0, startMask));
	}
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
