#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 1 << 10;

int n, k, m;
vector< PII > vec;
bool forbidden[MAXN];
bool ans;

int prvFree[MAXN];

void read() {
	int a, b, c;
	
	scanf("%d %d %d", &n, &k, &m);
	for(int i = 0; i < m; i ++) {
		scanf("%d %d %d", &a, &b, &c);
		if(c) vec.pb(mp(a, b));
		else {
			for(int j = a; j <= b; j ++)
				forbidden[j] = true;
		}
	}
}

bool checkAll() {
	int totalForbidden = 0;
	for(int i = 1; i <= n; i ++)
		if(forbidden[i])
			totalForbidden ++;
	
	return (k == n - totalForbidden);
}

bool ok() {
	memset(prvFree, 0, sizeof(prvFree));
	
	for(int i = 1; i <= n; i ++)
		if(!forbidden[i]) prvFree[i] = i;
		else prvFree[i] = prvFree[i - 1];
	
	int br = 0;
	int position = -1;
	for(int i = 0; i < (int)vec.size(); i ++)
		if(vec[i].first <= position) continue;
		else {
			position = prvFree[ vec[i].second ];
			br ++;
			if(br > k) return false;
			if(vec[i].first > position) return false;
		}
	
	return true;
}

bool cmp(PII a, PII b) {
	if(a.second != b.second)
		return a.second < b.second;
	
	return a.first > b.first;
}

void solve() {
	if(checkAll()) {
		for(int i = 1; i <= n; i ++)
			if(!forbidden[i])
				printf("%d\n", i);
		return;
	}
	
	sort(vec.begin(), vec.end(), cmp);
	
	for(int i = 1; i <= n; i ++)
		if(!forbidden[i]) {
			forbidden[i] = true;
			if(!ok()) {
				printf("%d\n", i);
				ans = true;
			}
			forbidden[i] = false;
		}
	
	if(!ans) printf("-1\n");
}

int main()
{
	read();
	solve();

    return 0;
}
