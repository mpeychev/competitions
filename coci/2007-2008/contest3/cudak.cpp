#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

typedef long long LL;

LL dp[32][256];

LL go(int len, int sum) {
	if(sum < 0)
		return 0;
	
	if(dp[len][sum] != -1)
		return dp[len][sum];
	
	if(!len) {
		if(!sum) return dp[len][sum] = 1;
		return dp[len][sum] = 0;
	}
	
	LL ret = 0;
	for(int i = 0; i <= sum && i < 10; i ++)
		ret += go(len - 1, sum - i);
	
	dp[len][sum] = ret;
	return ret;
}

LL calc(LL x, LL sum) {
	if(x == 1) return 0;
	
	vector<int> dig;
	int numLen;
	
	while(x) {
		dig.pb(x % 10);
		x /= 10;
	}
	reverse(dig.begin(), dig.end());
	numLen = dig.size();
	
	LL ret = 0;
	
	for(int i = 0; i < dig[0] && i <= sum; i ++)
		ret += go(numLen - 1, sum - i);
	
	for(int i = 1; i < numLen; i ++) {
		sum -= dig[i - 1];
		if(sum < 0) break;
		for(int j = 0; j < dig[i] && j <= sum; j ++)
			ret += go(numLen - i - 1, sum - j);
	}
	
	return ret;
}

LL get(LL le, LL ri, LL s) {
	return calc(ri + 1, s) - calc(le, s);
}

int main()
{
	LL a, b, s;
	cin >> a >> b >> s;
	
	memset(dp, -1, sizeof(dp));
	
	cout << get(a, b, s) << endl;
	
	if(get(a, a, s)) {
		cout << a << endl;
		return 0;
	}
	
	LL le = a, ri = b, mid;
	LL ans;
	while(le <= ri) {
		mid = (le + ri) >> 1;
		if(!get(le, mid, s)) {
			ans = mid;
			le = mid + 1;
		}
		else ri = mid - 1;
	}
	
	cout << ans + 1 << endl;
	
	return 0;
}
