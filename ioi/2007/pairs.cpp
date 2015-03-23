#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>

#define pb push_back

using namespace std;

typedef long long LL;

const int MAXN = 100100;

int b, n, d, m;

struct Solve1 {
	int vec[MAXN];
	
	void read() {
		for(int i = 0; i < n; i ++)
			scanf("%d", &vec[i]);
	}
	
	void solve() {
		sort(vec, vec + n);
	
		LL ans = 0;
		
		for(int i = 0; i < n; i ++) {
			int le = 0, ri = i - 1, mid;
			int ret = i;
			while(le <= ri) {
				mid = (le + ri) >> 1;
				if(vec[i] - d <= vec[mid]) {
					ret = mid;
					ri = mid - 1;
				}
				else le = mid + 1;
			}
			ans += (i - ret);
		}
		
		cout << ans << endl;
	}
	
	void go() {
		read();
		solve();
	}
} S1;

struct Solve2 {
	struct el {
		int x, y;
		bool t;
		
		el() {}
		el(int _x, int _y, bool _t): x(_x), y(_y), t(_t) {}
	};

	static bool cmp(el a, el b) {
		if(a.x != b.x) return a.x < b.x;
		if(a.t != b.t) return a.t < b.t;
		return a.y < b.y;
	}
	
	vector<el> vec;
	int t[200200];
	
	void read() {
		int x, y;
		
		for(int i = 0; i < n; i ++) {
			scanf("%d %d", &x, &y);
			vec.pb(el(y + x, y - x, 0));
			vec.pb(el(y + x + d, y - x, true));
		}
	}
	
	void add(int idx, int val) {
		idx += m + 5;
		while(idx <= 200000) {
			t[idx] += val;
			idx += (idx & -idx);
		}
	}
	
	int get(int idx) {
		idx += m + 5;
		
		if(idx > 200000) idx = 200000;
		if(idx < 0) idx = 0;
		
		int ret = 0;
		while(idx) {
			ret += t[idx];
			idx -= (idx & -idx);
		}
		
		return ret;
	}
	
	int get(int up, int down) {
		return get(up) - get(down - 1);
	}
	
	void solve() {
		sort(vec.begin(), vec.end(), cmp);
		
		LL ans = 0;
		
		for(int i = 0; i < (int)vec.size(); i ++)
			if(vec[i].t) add(vec[i].y, -1);
			else {
				ans += get(vec[i].y + d, vec[i].y - d);
				add(vec[i].y, 1);
			}
		
		cout << ans << endl;
	}
	
	void go() {
		read();
		solve();
	}
} S2;

struct Solve3 {
	struct el {
		int x, y, cnt;
		short int cmd;
		
		el() {}
		el(int _x, int _y, int _cnt, short int _cmd): x(_x), y(_y), cnt(_cnt), cmd(_cmd) {}
	};
	
	static bool cmp(el a, el b) {
		if(a.x != b.x) return a.x < b.x;
		return a.cmd < b.cmd;
	}
	
	int board[80][80][80];
	LL ans;
	int t[256];
	
	void init() {
		memset(board, 0, sizeof(board));
		ans = 0;
	}
	
	void read() {
		int x, y, z;
		
		for(int i = 0; i < n; i ++) {
			scanf("%d %d %d", &x, &y, &z);
			board[x][y][z] ++;
		}
	}
	
	void add(int idx, int val) {
		idx += m + 5;
		while(idx <= 200) {
			t[idx] += val;
			idx += (idx & -idx);
		}
	}
	
	int get(int idx) {
		idx += m + 5;
		
		if(idx > 200) idx = 200;
		if(idx < 0) idx = 0;
		
		int ret = 0;
		while(idx) {
			ret += t[idx];
			idx -= (idx & -idx);
		}
		
		return ret;
	}
	
	int get(int up, int down) {
		return get(up) - get(down - 1);
	}
	
	void solve(vector< el > &vec, int delta) {
		memset(t, 0, sizeof(t));
		sort(vec.begin(), vec.end(), cmp);
		
		for(int i = 0; i < (int)vec.size(); i ++)
			if(vec[i].cmd == 0 || vec[i].cmd == 2) add(vec[i].y, vec[i].cnt);
			else ans += (LL)vec[i].cnt * (LL)get(vec[i].y + (d - delta), vec[i].y - (d - delta));
	}
	
	void _solve(vector< el > &vec) {
		sort(vec.begin(), vec.end(), cmp);
		
		for(int i = 0; i < (int)vec.size(); i ++)
			if(vec[i].cmd == 1) add(vec[i].y, vec[i].cnt);
			else {
				ans += (LL)vec[i].cnt * (LL)get(vec[i].y + d, vec[i].y - d);
				add(vec[i].y, vec[i].cnt);
			}
	}
	
	void solve() {
		if(d >= 3 * (m - 1)) {
			cout << (LL)n * (LL)(n - 1) / 2 << endl;
			return;
		}
		
		for(int i = 1; i <= m; i ++)
			for(int j = 1; j <= m; j ++)
				for(int k = 1; k <= m; k ++)
					ans += ((LL)board[i][j][k] * (LL)(board[i][j][k] - 1) / 2);
		
		for(int r1 = 1; r1 <= m; r1 ++) {
			vector< el > _vec;
			for(int i = 1; i <= m; i ++)
				for(int j = 1; j <= m; j ++)
					if(board[r1][i][j]) {
						_vec.pb(el(j + i, j - i, board[r1][i][j], 0));
						_vec.pb(el(j + i + d, j - i, -board[r1][i][j], 1));
					}
			_solve(_vec);
			
			for(int r2 = r1 + 1; r2 <= m; r2 ++) {
				if(r2 - r1 > d) break;
				
				vector< el > vec;
				for(int i = 1; i <= m; i ++)
					for(int j = 1; j <= m; j ++) {
						if(board[r1][i][j]) {
							vec.pb(el(j + i + d - (r2 - r1), j - i, board[r1][i][j], 1));
						}
						if(board[r2][i][j]) {
							vec.pb(el(j + i, j - i, board[r2][i][j], 0));
							vec.pb(el(j + i + 2 * (d - (r2 - r1)), j - i, -board[r2][i][j], 2));
						}
					}
				
				solve(vec, r2 - r1);
			}
		}
		
		cout << ans << endl;
	}
	
	void go() {
		init();
		read();
		solve();
	}
} S3;

int main()
{
	scanf("%d %d %d %d", &b, &n, &d, &m);
	
	if(b == 1) {
		S1.go();
		return 0;
	}
	
	if(b == 2) {
		S2.go();
		return 0;
	}
	
	S3.go();
    return 0;
}
