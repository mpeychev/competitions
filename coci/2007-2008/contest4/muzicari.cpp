#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>

#define pb push_back

using namespace std;

int t, n, x[512], ans[512];
bool dp[5050];
int last[5050];
vector<int> vec;

int main()
{
	cin >> t >> n;
	
	dp[0] = true;
	for(int i = 0; i < n; i ++) {
		cin >> x[i];
		for(int j = t; j - x[i] >= 0; j --)
			if(!dp[j] && dp[ j - x[i] ]) {
				dp[j] = true;
				last[j] = x[i];
			}
	}
	
	int cur = -1;
	for(int i = t; i >= 0; i --)
		if(dp[i]) {
			cur = i;
			break;
		}
	
	while(cur) {
		vec.pb(last[cur]);
		cur -= last[cur];
	}
	
	memset(ans, -1, sizeof(ans));
	int curSum = 0;
	for(int i = 0; i < (int)vec.size(); i ++) {
		for(int j = 0; j < n; j ++)
			if(ans[j] == -1 && x[j] == vec[i]) {
				ans[j] = curSum;
				break;
			}
		curSum += vec[i];
	}
	
	curSum = 0;
	for(int i = 0; i < n; i ++)
		if(ans[i] == -1) {
			ans[i] = curSum;
			curSum += x[i];
		}
	
	for(int i = 0; i < n; i ++) {
		if(i) cout << " ";
		cout << ans[i];
	}
	cout << endl;

    return 0;
}
