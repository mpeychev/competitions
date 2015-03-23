#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

const int MAXK = 50100;
const int MAXN = 20100;

struct Group {
	int s, e, m;
};

struct Bucket {
	int cnt[256];
	int addFull;
	int mx;
	
	void init() {
		memset(cnt, 0, sizeof(cnt));
		addFull = 0;
		mx = 0;
	}
	
	int getVal(int pos) {
		return cnt[pos] + addFull;
	}
};

int k, n, c;
Group vec[MAXK];
Bucket t[256];
int ans;

void read() {
	scanf("%d %d %d", &k, &n, &c);
	for(int i = 0; i < k; i ++) {
		scanf("%d %d %d", &vec[i].s, &vec[i].e, &vec[i].m);
		vec[i].s --;
		vec[i].e --;
	}
}

void init() {
	for(int i = 0; i < 200; i ++)
		t[i].init();
}

bool cmp(Group a, Group b) {
	if(a.e != b.e)
		return a.e < b.e;
	
	if(a.s != b.s)
		return a.s > b.s;
	
	return a.m > b.m;
}

int getMax(int le, int ri) {
	int ret = 0;
	
	int p1 = le / 140;
	int p2 = ri / 140;
	
	for(int i = p1 + 1; i < p2; i ++)
		ret = max(ret, t[i].mx);
	
	while(le < (p1 + 1) * 140 && le <= ri) {
		ret = max(ret, t[p1].getVal(le % 140));
		le ++;
	}
	
	while(ri >= p2 * 140 && le <= ri) {
		ret = max(ret, t[p2].getVal(ri % 140));
		ri --;
	}
	
	return ret;
}

void add(int le, int ri, int val) {
	if(!val) return;
	
	ans += val;
	
	int p1 = le / 140;
	int p2 = ri / 140;
	
	for(int i = p1 + 1; i < p2; i ++) {
		t[i].addFull += val;
		t[i].mx += val;
	}
	
	while(le < (p1 + 1) * 140 && le <= ri) {
		t[p1].cnt[le % 140] += val;
		t[p1].mx = max(t[p1].mx, t[p1].getVal(le % 140));
		le ++;
	}
	
	while(ri >= p2 * 140 && le <= ri) {
		t[p2].cnt[ri % 140] += val;
		t[p2].mx = max(t[p2].mx, t[p2].getVal(ri % 140));
		ri --;
	}
}

void solve() {
	sort(vec, vec + k, cmp);
	
	for(int i = 0; i < k; i ++) {
		vec[i].e --;
		int mx = getMax(vec[i].s, vec[i].e);
		add(vec[i].s, vec[i].e, min(vec[i].m, c - mx));
	}
	
	cout << ans << endl;
}

int main()
{
	read();
	init();
	solve();

    return 0;
}
