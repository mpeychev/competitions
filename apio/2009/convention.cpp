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
const int MAXN = 200200;

int n;
PII seg[MAXN];
vector<int> allTimes;
int maxC;

int minRight[2 * MAXN];
int table[2 * MAXN][20];

set< PII > active;

void read() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d %d", &seg[i].first, &seg[i].second);
}

int bs(int k) {
	int le = 0, ri = maxC - 1, mid;
	while(le <= ri) {
		mid = (le + ri) >> 1;
		if(allTimes[mid] == k) return mid;
		if(allTimes[mid] < k) le = mid + 1;
		else ri = mid - 1;
	}
	return -1;
}

int go(int le, int ri) {
	if(le > ri || minRight[le] > ri)
		return 0;

	int ret = 0;
	for(int k = 19; k >= 0; k --)
		if(table[le][k] <= ri + 1) {
			ret += (1 << k);
			le = table[le][k];
		}

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
	maxC = (int)allTimes.size();
	
	for(int i = 1; i <= n; i ++) {
		seg[i].first = bs(seg[i].first);
		seg[i].second = bs(seg[i].second);
	}
	
	for(int i = 0; i <= maxC; i ++)
		for(int k = 0; k <= 19; k ++)
			table[i][k] = INF;
	
	for(int i = 0; i <= maxC; i ++)
		minRight[i] = INF;
	
	for(int i = 1; i <= n; i ++)
		minRight[ seg[i].first ] = min(minRight[ seg[i].first ], seg[i].second);
	
	for(int i = maxC - 1; i >= 0; i --)
		if(minRight[i] > minRight[i + 1])
			minRight[i] = minRight[i + 1];
	
	for(int i = 0; i < maxC; i ++)
		table[i][0] = minRight[i] + 1;
	
	for(int k = 1; k <= 19; k ++)
		for(int i = 0; i < maxC; i ++)
			if(table[i][k - 1] < maxC)
				table[i][k] = table[ table[i][k - 1] ][k - 1];
	
	active.insert(mp(0, (int)allTimes.size() - 1));
	
	int M = go(0, maxC - 1);
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
