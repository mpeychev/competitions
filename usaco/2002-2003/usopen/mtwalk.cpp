#include <iostream>
#include <stdio.h>
#include <set>
#include <queue>
#include <vector>

using namespace std;

const int MAXN = 1 << 7;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

struct el {
	int x, y;
	int mx;
	
	el() {}
	el(int _x, int _y, int _mx): x(_x), y(_y), mx(_mx) {}
};

struct cmp {
	bool operator()(el a, el b) {
		return !(a.mx < b.mx);
	}
};

int n, ma3x[MAXN][MAXN];
set<int> st;
int lowerBound;

priority_queue< el , vector< el > , cmp > pq;
int d[MAXN][MAXN];

void read() {
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++) {
			scanf("%d", &ma3x[i][j]);
			st.insert(ma3x[i][j]);
		}
}

int dijkstra() {
	while(!pq.empty())
		pq.pop();
	
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			d[i][j] = MAXN;
	
	pq.push(el(0, 0, ma3x[0][0]));
	while(!pq.empty()) {
		el tmp = pq.top();
		pq.pop();
		
		if(d[tmp.x][tmp.y] < tmp.mx) continue;
		d[tmp.x][tmp.y] = tmp.mx;
		
		if(tmp.x == n - 1 && tmp.y == n - 1) return tmp.mx;
		
		for(int k = 0; k < 4; k ++) {
			int nxtX = tmp.x + dx[k];
			int nxtY = tmp.y + dy[k];
			int nxtMax = tmp.mx;
			
			if(nxtX >= 0 && nxtX < n && nxtY >= 0 && nxtY < n) {
				if(ma3x[nxtX][nxtY] < lowerBound) continue;
				if(nxtMax < ma3x[nxtX][nxtY]) nxtMax = ma3x[nxtX][nxtY];
				if(d[nxtX][nxtY] > nxtMax) {
					d[nxtX][nxtY] = nxtMax;
					pq.push(el(nxtX, nxtY, nxtMax));
				}
			}
		}
	}
	return 1 << 20;
}

void solve() {
	int ans = MAXN;
	for(set<int> :: iterator it = st.begin(); it != st.end(); it ++) {
		lowerBound = *it;
		if(lowerBound > ma3x[0][0] || lowerBound > ma3x[n - 1][n - 1]) continue;
		int res = dijkstra();
		ans = min(ans, res - lowerBound);
	}
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
