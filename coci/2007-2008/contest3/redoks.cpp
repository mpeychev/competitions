#include <iostream>
#include <stdio.h>
#include <deque>

using namespace std;

typedef long long LL;

const int MAXN = 1 << 18;

struct node {
	int sum;
	deque<int> d;
};

int n, m, lvs;
char s[MAXN];
node tree[2 * MAXN];

void read() {
	scanf("%d %d\n", &n, &m);
	scanf("%s", &s);
}

void printTree() {
	for(int i = 1; i < 2 * lvs; i ++) {
		cout << i << ": ";
		cout << tree[i].sum << " | ";
		for(int j = 0; j < 10; j ++)
			cout << tree[i].d[j] << " ";
		cout << endl;
	}
}

void init(int idx, int le, int ri) {
	tree[idx].sum = 0;
	tree[idx].d.resize(10);
	
	if(le == ri) {
		tree[idx].d[ s[le] - '0' ] = 1;
		return;
	}
	
	int mid = (le + ri) >> 1;
	init(idx << 1, le, mid);
	init((idx << 1) + 1, mid + 1, ri);
	
	for(int i = 0; i < 10; i ++)
		tree[idx].d[i] = tree[idx << 1].d[i] + tree[(idx << 1) + 1].d[i];
}

void pushDown(int idx) {
	int t;
	
	if(idx < lvs) {
		tree[idx << 1].sum = (tree[idx << 1].sum + tree[idx].sum) % 10;
		tree[(idx << 1) + 1].sum = (tree[(idx << 1) + 1].sum + tree[idx].sum) % 10;
	}
	
	while(tree[idx].sum) {
		tree[idx].sum --;
		
		t = tree[idx].d.back();
		tree[idx].d.pop_back();
		tree[idx].d.push_front(t);
	}
}

void update(int idx, int le, int ri, int a, int b) {
	if(a <= le && ri <= b) {
		tree[idx].sum = (tree[idx].sum + 1) % 10;
		pushDown(idx);
		return;
	}
	
	pushDown(idx);
	
	if(ri < a || b < le)
		return;
	
	int mid;
	
	mid = (le + ri) >> 1;
	update(idx << 1, le, mid, a, b);
	update((idx << 1) + 1, mid + 1, ri, a, b);
	
	for(int i = 0; i < 10; i ++)
		tree[idx].d[i] = tree[idx << 1].d[i] + tree[(idx << 1) + 1].d[i];
}

LL getSum(int idx, int le, int ri, int a, int b) {
	if(ri < a || b < le)
		return 0;
	
	pushDown(idx);
	
	if(a <= le && ri <= b) {
		LL ret = 0;
		for(LL i = 0; i < 10; i ++)
			ret += i * (LL)tree[idx].d[i];
		return ret;
	}
	
	int mid = (le + ri) >> 1;
	return getSum(idx << 1, le, mid, a, b) + getSum((idx << 1) + 1, mid + 1, ri, a, b);
}

void solve() {
	lvs = 1;
	while(lvs < n) lvs <<= 1;
	
	init(1, 0, lvs - 1);
	
//	printTree();
	
	int a, b;
	for(int i = 0; i < m; i ++) {
		scanf("%d %d", &a, &b);
		a --, b --;
		printf("%lld\n", getSum(1, 0, lvs - 1, a, b));
		update(1, 0, lvs - 1, a, b);
		
//		printTree();
	}
}

int main()
{
	read();
	solve();
	
	return 0;
}
