#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <string.h>

using namespace std;

const int INF = 100100;

struct el {
	int cowsCount;
	int lapsCount;
	int leaderEnergy;
	
	el() {}
	el(int _cc, int _lc, int _le): cowsCount(_cc), lapsCount(_lc), leaderEnergy(_le) {}
};

int n, e, d;
int level[32][128][128];
queue< el > q;

void read() {
	scanf("%d %d %d", &n, &e, &d);
}

void add(el nxt, int nxtLevel) {
	if(level[nxt.cowsCount][nxt.lapsCount][nxt.leaderEnergy] == -1) {
		level[nxt.cowsCount][nxt.lapsCount][nxt.leaderEnergy] = nxtLevel;
		q.push(nxt);
	}
}

void solve() {
	if(d > e) {
		cout << "0\n";
		return;
	}
	
	memset(level, -1, sizeof(level));
	
	q.push(el(n, d, e));
	level[n][d][e] = 0;
	while(!q.empty()) {
		el tmp = q.front();
		q.pop();
		
		int curLevel = level[tmp.cowsCount][tmp.lapsCount][tmp.leaderEnergy];
		
		if(!tmp.lapsCount) {
			cout << curLevel << endl;
			return;
		}
		
		for(int i = 1; i * i <= tmp.leaderEnergy; i ++) {
			add(el(tmp.cowsCount, tmp.lapsCount - i, tmp.leaderEnergy - i * i), curLevel + 1);
			if(tmp.cowsCount > 1) add(el(tmp.cowsCount - 1, tmp.lapsCount - i, e - (d - (tmp.lapsCount - i))), curLevel + 1);
		}
	}
	
	cout << 0 << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
