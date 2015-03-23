#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 1 << 17;
const int INF = 1 << 25;

int n, k, m;
vector< PII > vec[2];
bool forbidden[MAXN];

int prevFree[MAXN], nextFree[MAXN];

int pos[MAXN][2], dp[MAXN][2];
vector<int> rights[MAXN];
vector<int> lefts[MAXN];
int closest[MAXN];

int rmq[MAXN][17];
int maxLog[MAXN];

bool built[MAXN];
int nextSolution[MAXN];
int prevSolution[MAXN];
int cnt;

bool ans;

void read() {
	int a, b, c;
	
	scanf("%d %d %d", &n, &k, &m);
	for(int i = 0; i < m; i ++) {
		scanf("%d %d %d", &a, &b, &c);
		vec[c].pb(mp(a, b));
	}
}

void setForbidden() {
	if(vec[0].empty())
		return;
	
	sort(vec[0].begin(), vec[0].end());
	
	int position = 0;
	for(int i = 0; i < (int)vec[0].size(); i ++)
		if(position >= vec[0][i].second) continue;
		else {
			int start = position;
			
			if(vec[0][i].first > position) start = vec[0][i].first;
			for(int j = start; j <= vec[0][i].second; j ++)
				forbidden[j] = true;
			
			position = vec[0][i].second;
		}
}

void precompute() {
	for(int i = 1; i <= n; i ++)
		if(!forbidden[i]) prevFree[i] = i;
		else prevFree[i] = prevFree[i - 1];
	
	nextFree[n + 1] = n + 1;
	for(int i = n; i >= 1; i --)
		if(!forbidden[i]) nextFree[i] = i;
		else nextFree[i] = nextFree[i + 1];
	
	memset(closest, 1, sizeof(closest));
	for(int i = 0; i < (int)vec[1].size(); i ++) {
		rights[ vec[1][i].first ].pb(vec[1][i].second);
		if(closest[ vec[1][i].first ] > vec[1][i].second)
			closest[ vec[1][i].first ] = vec[1][i].second;
		
		lefts[ vec[1][i].second ].pb(vec[1][i].first);
	}
	
	pos[n + 1][0] = pos[n + 1][1] = INF;
	dp[n + 1][0] = dp[n + 1][1] = 0;
	
	for(int i = n; i >= 1; i --)
		if(rights[i].empty()) {
			if(forbidden[i]) {
				for(int j = 0; j < 2; j ++) {
					pos[i][j] = pos[i + 1][j];
					dp[i][j] = dp[i + 1][j];
				}
			}
			else {
				for(int j = 0; j < 2; j ++) {
					pos[i][j] = pos[i + 1][1];
					dp[i][j] = dp[i + 1][1];
				}
			}
		}
		else {
			int t = closest[i];
			
			if(t < pos[i + 1][1]) {
				pos[i][1] = nextFree[i];
				dp[i][1] = dp[i + 1][1] + 1;
			}
			else {
				pos[i][1] = pos[i + 1][1];
				dp[i][1] = dp[i + 1][1];
			}
			
			if(forbidden[i]) {
				if(t < pos[i + 1][0]) {
					if(nextFree[i] == INF || t < nextFree[ nextFree[i] + 1 ]) {
						pos[i][0] = INF;
						dp[i][0] = INF;
					}
					else {
						pos[i][0] = nextFree[ nextFree[i] + 1 ];
						dp[i][0] = dp[i + 1][0] + 1;
					}
				}
				else {
					pos[i][0] = pos[i + 1][0];
					dp[i][0] = dp[i + 1][0];
				}
			}
			else {
				if(t < pos[i + 1][1]) {
					if(t < nextFree[ nextFree[i] + 1 ]) {
						pos[i][0] = INF;
						dp[i][0] = INF;
					}
					else {
						pos[i][0] = nextFree[ nextFree[i] + 1 ];
						dp[i][0] = dp[i + 1][0] + 1;
					}
				}
				else {
					pos[i][0] = pos[i + 1][1];
					dp[i][0] = dp[i + 1][1];
				}
			}
		}
	
	for(int i = 1; i <= n; i ++)
		rmq[i][0] = closest[i];
	
	for(int k = 1; k < 17; k ++)
		for(int i = 1; i <= n; i ++) {
			int halfBlockLen = 1 << (k - 1);
			rmq[i][k] = rmq[i][k - 1];
			if(i + halfBlockLen <= n && rmq[i][k] > rmq[i + halfBlockLen][k - 1])
				rmq[i][k] = rmq[i + halfBlockLen][k - 1];
		}
	
	maxLog[1] = 0;
	for(int i = 2; i <= n; i ++)
		maxLog[i] = maxLog[i >> 1] + 1;
}

int getMin(int le, int ri) {
	if(le > ri)
		return INF;
	
	int k = maxLog[ri - le + 1];
	int opt1 = rmq[le][k];
	int opt2 = rmq[ri - (1 << k) + 1][k];
	
	if(opt1 < opt2) return opt1;
	return opt2;
}

bool cmp(PII a, PII b) {
	if(a.second != b.second)
		return a.second < b.second;
	return a.first > b.first;
}

void generate() {
	sort(vec[1].begin(), vec[1].end(), cmp);
	
	int position = 0;
	for(int i = 0; i < (int)vec[1].size(); i ++)
		if(vec[1][i].first <= position) continue;
		else {
			position = prevFree[ vec[1][i].second ];
			built[position] = true;
		}
	
	nextSolution[n + 1] = n + 1;
	for(int i = n; i >= 1; i --)
		if(built[i]) nextSolution[i] = i;
		else nextSolution[i] = nextSolution[i + 1];
	
	for(int i = 1; i <= n; i ++)
		if(built[i]) prevSolution[i] = i;
		else prevSolution[i] = prevSolution[i - 1];
}

bool checkAll() {
	int totalForbidden = 0;
	for(int i = 1; i <= n; i ++)
		if(forbidden[i])
			totalForbidden ++;
	
	return (k == n - totalForbidden);
}

void solve() {
	if(checkAll()) {
		for(int i = 1; i <= n; i ++)
			if(!forbidden[i])
				printf("%d\n", i);
		return;
	}
	
	for(int i = 1; i <= n; i ++)
		if(built[i]) {
			cnt ++;
			
			int p1 = prevFree[i - 1];
			int p2 = nextFree[i + 1];
			
			if(!p1) {
				printf("%d\n", i);
				ans = true;
				continue;
			}
			
			if(getMin(p1 + 1, p2 - 1) < p2) {
				printf("%d\n", i);
				ans = true;
				continue;
			}
			
			int addPrev = 0;
			if(getMin(prevSolution[i - 1] + 1, p1) < p2)
				addPrev = 1;
			
			int T = getMin(p1 + 1, i);
			if(T < nextSolution[i + 1]) {
				int tmp = cnt - 1 + addPrev + dp[p1 + 1][0];
				if(tmp > k) {
					printf("%d\n", i);
					ans = true;
				}
			}
		}
	
	if(!ans) printf("-1\n");
}

int main()
{
	read();
	setForbidden();
	precompute();
	generate();
	solve();

    return 0;
}
