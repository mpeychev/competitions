#include <iostream>
#include <stdio.h>
#include <vector>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 300005;

FILE *in = fopen("questions.txt", "r");

int n, m;
int perm[MAXN];
vector< PII > vec[MAXN];

void read() {
	int p;
	
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i ++) {
		perm[i] = i;
		vec[i].pb(mp(0, i));
	}
	
	for(int i = 1; i <= m; i ++) {
		scanf("%d", &p);
		perm[p] ^= perm[p + 1] ^= perm[p] ^= perm[p + 1];
		vec[ perm[p] ].pb(mp(i, p));
		vec[ perm[p + 1] ].pb(mp(i, p + 1));
	}
}

void findPosition(int idx, int swapper) {
	int le = 0, ri = (int)vec[idx].size() - 1, mid;
	int ret = -1;
	while(le <= ri) {
		mid = (le + ri) >> 1;
		if(vec[idx][mid].first <= swapper) {
			ret = vec[idx][mid].second;
			le = mid + 1;
		}
		else ri = mid - 1;
	}
	printf("%d\n", ret);
}

void solve() {
	int q, k, j;
	fscanf(in, "%d", &q);
	for(int i = 0; i < q; i ++) {
		fscanf(in, "%d %d", &k, &j);
		findPosition(k, j);
	}
}

int main()
{
	read();
	solve();

    return 0;
}
