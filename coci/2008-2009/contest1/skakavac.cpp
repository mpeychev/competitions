#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>

#define pb push_back

using namespace std;

const int MAXN = 1505;

struct ListNode {
	short int x, y;
	int prv;
	int ans;
	
	ListNode() {}
	ListNode(int _x, int _y, int _prv): x(_x), y(_y), prv(_prv) {}
};

struct el {
	int maxValue;
	short int position;
	
	el() {}
	el(int _maxValue, int _position): maxValue(_maxValue), position(_position) {}
};

int n, r, c;

int idx[1 << 20];
ListNode li[MAXN * MAXN];
int sz;

vector< el > rows[MAXN];
vector< el > cols[MAXN];

void add(int i, int j, int value) {
	li[sz] = ListNode(i, j, idx[value]);
	idx[value] = sz ++;
}

void read() {
	int value;
	memset(idx, -1, sizeof(idx));
	
	scanf("%d", &n);
	scanf("%d %d", &r, &c);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++) {
			scanf("%d", &value);
			add(i, j, value);
		}
}

int getRow(int idx, int forbidden) {
	for(int i = 0; i < (int)rows[idx].size(); i ++)
		if(rows[idx][i].position < forbidden - 1 || rows[idx][i].position > forbidden + 1)
			return rows[idx][i].maxValue;
	return 0;
}

int getCol(int idx, int forbidden) {
	for(int i = 0; i < (int)cols[idx].size(); i ++)
		if(cols[idx][i].position < forbidden - 1 || cols[idx][i].position > forbidden + 1)
			return cols[idx][i].maxValue;
	return 0;
}

bool cmp(el a, el b) {
	return a.maxValue > b.maxValue;
}

void updateRow(int idx, int position, int value) {
	rows[idx].pb(el(value, position));
	sort(rows[idx].begin(), rows[idx].end(), cmp);
	while(rows[idx].size() > 4) rows[idx].pop_back();
}

void updateCol(int idx, int position, int value) {
	cols[idx].pb(el(value, position));
	sort(cols[idx].begin(), cols[idx].end(), cmp);
	while(cols[idx].size() > 4) cols[idx].pop_back();
}

void solve() {
	for(int h = 1000000; h >= 1; h --) {
		for(int i = idx[h]; i != -1; i = li[i].prv) {
			int val1 = getRow(li[i].x - 1, li[i].y);
			int val2 = getRow(li[i].x + 1, li[i].y);
			
			int val3 = getCol(li[i].y - 1, li[i].x);
			int val4 = getCol(li[i].y + 1, li[i].x);
			
			int mx = max(max(val1, val2), max(val3, val4));
			li[i].ans = mx + 1;
			
			if(li[i].x == r && li[i].y == c) {
				cout << mx + 1 << endl;
				return;
			}
		}
		
		for(int i = idx[h]; i != -1; i = li[i].prv) {
			updateRow(li[i].x, li[i].y, li[i].ans);
			updateCol(li[i].y, li[i].x, li[i].ans);
		}
	}
}

int main()
{
	read();
	solve();

    return 0;
}
