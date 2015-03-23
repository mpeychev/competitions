#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

const int MAXN = 250250;

struct el {
	int x, y1, y2;
	bool t;
	
	el() {}
	el(int _x, int _y1, int _y2, bool _t): x(_x), y1(_y1), y2(_y2), t(_t) {}
};

int n;
el vec[2 * MAXN];
vector<int> y;
int t[2 * MAXN];

void read() {
	int x1, y1, x2, y2;
	
	scanf("%d", &n);
	for(int i = 0; i < n; i ++) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		
		vec[2 * i] = el(x1, y1, y2, true);
		vec[2 * i + 1] = el(x2, y1, y2, false);
		
		y.pb(y1);
		y.pb(y2);
	}
}

int findIndex(int k) {
	int le = 0, ri = (int)y.size() - 1, mid;
	while(le <= ri) {
		mid = (le + ri) >> 1;
		if(y[mid] == k) return mid;
		if(y[mid] < k) le = mid + 1;
		else ri = mid - 1;
	}
	return -1;
}

void add(int idx, int val) {
	while(idx <= (int)y.size() + 5) {
		t[idx] += val;
		idx += (idx & - idx);
	}
}

int get(int idx) {
	int ret = 0;
	while(idx) {
		ret += t[idx];
		idx -= (idx & -idx);
	}
	return ret;
}

bool cmp(el a, el b) {
	if(a.x != b.x)
		return a.x < b.x;
	
	return a.y1 < b.y1;
}

void solve() {
	sort(y.begin(), y.end());
	vector<int> :: iterator it = unique(y.begin(), y.end());
	y.resize(it - y.begin());
	
	sort(vec, vec + 2 * n, cmp);
	
	int mx = -1, cnt = 0;
	for(int i = 0; i < 2 * n; i ++) {
		vec[i].y1 = findIndex(vec[i].y1) + 1;
		vec[i].y2 = findIndex(vec[i].y2) + 1;
			
		if(vec[i].t) {
			int br = get(vec[i].y1) + 1;
			if(mx < br) {
				mx = br;
				cnt = 1;
			}
			else if(mx == br) cnt ++;
			
			add(vec[i].y1, 1);
			add(vec[i].y2, -1);
		}
		else {
			add(vec[i].y1, -1);
			add(vec[i].y2, 1);
		}
	}
	
	cout << mx << " " << cnt << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
