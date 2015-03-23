#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

const int MAXN = 200200;

int n, to[MAXN], b[MAXN];
vector<int> back[MAXN];

short int color[MAXN];
int prv[MAXN];

vector< vector<int> > cycles;
bool inCycle[MAXN];
int val[MAXN];

int ans;

void read() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) {
		scanf("%d %d", &to[i], &b[i]);
		back[ to[i] ].pb(i);
	}
}

void dfs(int cur) {
	color[cur] = 1;
	if(!color[ to[cur] ]) {
		prv[ to[cur] ] = cur;
		dfs(to[cur]);
	}
	else if(color[ to[cur] ] == 1) {
		vector<int> tmp;
		int node = cur;
		while(node != to[cur]) {
			tmp.pb(node);
			inCycle[node] = true;
			node = prv[node];
		}
		tmp.pb(node);
		inCycle[node] = true;
		reverse(tmp.begin(), tmp.end());
		cycles.pb(tmp);
	}
	color[cur] = 2;
}

int get(int cycleIndex) {
	if((int)cycles[cycleIndex].size() < 10) {
		int ret = 1 << 30;
		for(int start = 0; start < (int)cycles[cycleIndex].size(); start ++) {
			int curSum = 0, back = 0;
			for(int iter = 0, i = start; iter < (int)cycles[cycleIndex].size(); iter ++, i = (i + 1) % (int)cycles[cycleIndex].size()) {
				if(val[ cycles[cycleIndex][i] ] + back < b[ cycles[cycleIndex][i] ])
					curSum += (b[ cycles[cycleIndex][i] ] - val[ cycles[cycleIndex][i] ] - back);
				back = b[ cycles[cycleIndex][i] ];
			}
			if(ret > curSum) ret = curSum;
		}
		
		return ret;
	}
	
	int ret = 1 << 30;
	int curSum = 0, back = 0;
	for(int i = 0; i < (int)cycles[cycleIndex].size(); i ++) {
		if(val[ cycles[cycleIndex][i] ] + back < b[ cycles[cycleIndex][i] ])
			curSum += (b[ cycles[cycleIndex][i] ] - val[ cycles[cycleIndex][i] ] - back);
		back = b[ cycles[cycleIndex][i] ];
	}
	ret = curSum;
	
	int sz = (int)cycles[cycleIndex].size();
	for(int i = 1; i < sz; i ++) {
		int cur = curSum;
		
		/// Remove old
		if(val[ cycles[cycleIndex][i - 1] ] < b[ cycles[cycleIndex][i - 1] ])
			cur -= (b[ cycles[cycleIndex][i - 1] ] - val[ cycles[cycleIndex][i - 1] ]);
		
		if(val[ cycles[cycleIndex][i] ] + b[ cycles[cycleIndex][i - 1] ] < b[ cycles[cycleIndex][i] ])
			cur -= (b[ cycles[cycleIndex][i] ] - val[ cycles[cycleIndex][i] ] - b[ cycles[cycleIndex][i - 1] ]);
		
		/// Add new
		if(val[ cycles[cycleIndex][i] ] < b[ cycles[cycleIndex][i] ])
			cur += (b[ cycles[cycleIndex][i] ] - val[ cycles[cycleIndex][i] ]);
		
		if(val[ cycles[cycleIndex][i - 1] ] + b[ cycles[cycleIndex][(i - 2 + sz) % sz] ] < b[ cycles[cycleIndex][i - 1] ])
			cur += (b[ cycles[cycleIndex][i - 1] ] - val[ cycles[cycleIndex][i - 1] ] - b[ cycles[cycleIndex][(i - 2 + sz) % sz] ]);
		
		curSum = cur;
		if(ret > curSum) ret = curSum;
	}
	
	return ret;
}


void solve() {
	for(int i = 1; i <= n; i ++)
		if(!color[i])
			dfs(i);
	
	for(int i = 1; i <= n; i ++)
		if(!inCycle[i]) {
			int sumDown = 0;
			for(int j = 0; j < (int)back[i].size(); j ++)
				sumDown += b[ back[i][j] ];
			if(sumDown < b[i]) ans += (b[i] - sumDown);
		}
		else {
			for(int j = 0; j < (int)back[i].size(); j ++)
				if(!inCycle[ back[i][j] ])
					val[i] += b[ back[i][j] ];
		}
	
	for(int i = 0; i < cycles.size(); i ++)
		ans += get(i);
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
