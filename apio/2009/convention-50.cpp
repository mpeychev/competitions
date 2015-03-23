#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>
#include <string.h>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int INF = 1 << 30;

int n;
PII seg[3010];
vector<int> allTimes;

short int dp[6005][6005];
int minRight[6005];

set< PII > active;

void read() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d %d", &seg[i].first, &seg[i].second);
}

int bs(int k) {
	int le = 0, ri = (int)allTimes.size() - 1, mid;
	while(le <= ri) {
		mid = (le + ri) >> 1;
		if(allTimes[mid] == k) return mid;
		if(allTimes[mid] < k) le = mid + 1;
		else ri = mid - 1;
	}
	return -1;
}

short int go(int le, int ri) {
	short int &ret = dp[le][ri];
	
	if(ret != -1)
		return ret;
	
	if(le > ri) {
		ret = 0;
		return ret;
	}
	
	short int opt1 = 0, opt2 = 0;
	opt1 = go(le + 1, ri);
	if(minRight[le] <= ri) opt2 = 1 + go(minRight[le] + 1, ri);
	
	if(opt1 > opt2) ret = opt1;
	else ret = opt2;
	
	return ret;
}

void solve() {
	for(int i = 1; i <= n; i ++) {
		allTimes.pb(seg[i].first);
		allTimes.pb(seg[i].second);
	}
	
	sort(allTimes.begin(), allTimes.end());
	vector< int > :: iterator it = unique(allTimes.begin(), allTimes.end());
	allTimes.resize(distance(allTimes.begin(), it));
	
	for(int i = 1; i <= n; i ++) {
		seg[i].first = bs(seg[i].first);
		seg[i].second = bs(seg[i].second);
	}
	
	for(int i = 0; i < (int)allTimes.size(); i ++)
		minRight[i] = INF;
	
	for(int i = 1; i <= n; i ++)
		minRight[ seg[i].first ] = min(minRight[ seg[i].first ], seg[i].second);
	
	memset(dp, -1, sizeof(dp));
	active.insert(mp(0, (int)allTimes.size() - 1));
	
	int M = go(0, (int)allTimes.size() - 1);
	printf("%d\n", M);
	
	for(int i = 1; i <= n; i ++) {
		set< PII > :: iterator it = active.lower_bound(mp(seg[i].first, INF));
		if(it == active.begin()) continue;
		
		it --;
		
		if(it -> first <= seg[i].first && seg[i].second <= it -> second) {
			int now = go(it -> first, it -> second);
			int after = go(it -> first, seg[i].first - 1) + 1 + go(seg[i].second + 1, it -> second);
			
			if(now == after) {
				printf("%d", i);
				M --;
				if(M) printf(" ");
				else break;
				
				int le = it -> first;
				int ri = it -> second;
				
				active.erase(it);
				if(le <= seg[i].first - 1) active.insert(mp(le, seg[i].first - 1));
				if(seg[i].second + 1 <= ri) active.insert(mp(seg[i].second + 1, ri));
			}
		}
	}
	
	printf("\n");
}

int main()
{
	read();
	solve();

    return 0;
}
