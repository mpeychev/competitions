/* Optimized O(N^2) */

#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

const int MAXN = 100100;

struct Ninja {
	int index;
	int salary;
};

int n, m;
int b[MAXN], l[MAXN], cnt[MAXN];
Ninja vec[MAXN];
int limit[MAXN];

void read() {
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i ++) {
		scanf("%d %d %d", &b[i], &vec[i - 1].salary, &l[i]);
		vec[i - 1].index = i;
		limit[i] = m;
	}
}

bool cmp(Ninja a, Ninja b) {
	return a.salary < b.salary;
}

void go(int node, int reduce) {
	while(node) {
		if(limit[node] < reduce) break;
		limit[node] -= reduce;
		cnt[node] ++;
		node = b[node];
	}
}

void solve() {
	sort(vec, vec + n, cmp);
	
	for(int i = 0; i < n; i ++)
		go(vec[i].index, vec[i].salary);
	
	long long ans = 0;
	for(int i = 1; i <= n; i ++) {
		long long tmp = (long long)cnt[i] * (long long)l[i];
		if(ans < tmp) ans = tmp;
	}
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
