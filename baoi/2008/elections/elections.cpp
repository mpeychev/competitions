#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define pb push_back

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 305;
const int MAXS = 100100;

int n;
PII a[MAXN];
int s;
bool dp[MAXS];
int idx[MAXS];
vector<int> vec;

void read() {
	scanf("%d", &n);
	for(int i = 0; i < n; i ++) {
		scanf("%d", &a[i].first);
		a[i].second = i + 1;
		s += a[i].first;
	}
}

bool cmp(PII x, PII y) {
	return x.first > y.first;
}

void solve() {
	sort(a, a + n, cmp);
	
	int lim = s / 2 + 1;
	
	dp[0] = true;
	idx[0] = -1;
	for(int i = 0; i < n; i ++)
		for(int j = s; j - a[i].first >= 0; j --)
			if(j - a[i].first < lim && !dp[j] && dp[j - a[i].first]) {
				dp[j] = true;
				idx[j] = i;
			}
	
	int total;
	
	for(int i = s; ; i --)
		if(dp[i]) {
			total = i;
			break;
		}
	
	int tmp = total;
	while(tmp) {
		vec.pb(idx[tmp]);
		int dec = a[ idx[tmp] ].first;
		tmp -= dec;
	}
	
	printf("%d\n", (int)vec.size());
	for(int i = 0; i < vec.size(); i ++) {
		if(i) printf(" ");
		printf("%d", a[ vec[i] ].second);
	}
	printf("\n");
}

int main()
{
	read();
	solve();

    return 0;
}
