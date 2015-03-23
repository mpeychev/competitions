#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define pb push_back

using namespace std;

const int MAXN = 100100;

struct el {
	int a, b;
};

struct Node {
	int maxCount;
	int prevIndex;
	
	Node() {}
	Node(int _maxCount, int _prevIndex): maxCount(_maxCount), prevIndex(_prevIndex) {}
};

int n;
el vec[MAXN];
int prv[MAXN];
int dp[MAXN];
Node t[1 << 21];
int lvs;
vector<int> p;

void read() {
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d %d", &vec[i].a, &vec[i].b);
}

bool cmp(el x, el y) {
	if(x.a != y.a)
		return x.a < y.a;
	return x.b > y.b;
}

Node getMax(int idx, int le, int ri, int a) {
	if(ri < a)
		return Node(0, -1);
	
	if(a <= le)
		return t[idx];
	
	int mid = (le + ri) >> 1;
	Node getLeft = getMax(idx << 1, le, mid, a);
	Node getRight = getMax((idx << 1) + 1, mid + 1, ri, a);
	
	if(getLeft.maxCount > getRight.maxCount) return getLeft;
	return getRight;
}

void update(int idx, int val, int i) {
	idx += lvs;
	while(idx) {
		if(t[idx].maxCount < val)
			t[idx] = Node(val, i);
		idx >>= 1;
	}
}

void solve() {
	sort(vec, vec + n, cmp);
	
	lvs = 1 << 20;
	for(int i = 1; i < 2 * lvs; i ++)
		t[i] = Node(0, -1);
	
	for(int i = 0; i < n; i ++) {
		Node tmp = getMax(1, 0, lvs - 1, vec[i].b);
		prv[i] = tmp.prevIndex;
		dp[i] = tmp.maxCount + 1;
		update(vec[i].b, dp[i], i);
	}
	
	int idx = 0;
	for(int i = 1; i < n; i ++)
		if(dp[i] > dp[idx])
			idx = i;

	printf("%d\n", dp[idx]);
	while(idx != -1) {
		p.pb(idx);
		idx = prv[idx];
	}
	reverse(p.begin(), p.end());
	
	for(int i = 0; i < (int)p.size(); i ++)
		printf("%d %d\n", vec[ p[i] ].a, vec[ p[i] ].b);
}

int main()
{
	read();
	solve();

    return 0;
}
