#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <time.h>
#include <stdlib.h>

#define pb push_back

using namespace std;

const int MAXN = 1 << 10;

int k, n, f;
int ma3x[MAXN][MAXN];
set<int> g[MAXN];
set<int> active;
int iterations;
vector<int> cur;

void read() {
	int a, b;
	
	scanf("%d %d %d", &k, &n, &f);
	for(int i = 0; i < f; i ++) {
		scanf("%d %d", &a, &b);
		
		g[a].insert(b);
		g[b].insert(a);
		
		ma3x[a][b] = ma3x[b][a] = true;
	}
}

void timeBomb() {
	if((double)clock() / (double)CLOCKS_PER_SEC > 0.9) {
		printf("-1\n");
		exit(0);
	}
}

void write() {
	for(int i = 0; i < k; i ++)
		printf("%d\n", cur[i]);
	exit(0);
}

void go(set<int> nodes) {
	if((int)cur.size() == k) {
		write();
	}
	
	if((int)cur.size() + (int)nodes.size() < k)
		return;
	
	iterations ++;
	if(iterations % 1000 == 0)
		timeBomb();
	
	for(set<int> :: iterator it = nodes.begin(); it != nodes.end(); it ++) {
		cur.pb(*it);
		set<int> nxt;
		for(set<int> :: iterator it2 = it; it2 != nodes.end(); it2 ++)
			if(ma3x[*it][*it2])
				nxt.insert(*it2);
		
		go(nxt);
		
		cur.pop_back();
	}
}

void solve() {
	for(int i = 1; i <= n; i ++)
		active.insert(i);
	
	while(1) {
		vector<int> toRemove;
		for(set<int> :: iterator it = active.begin(); it != active.end(); it ++)
			if((int)g[*it].size() < k - 1)
				toRemove.pb(*it);
		
		if(toRemove.empty()) break;
		
		for(int i = 0; i < (int)toRemove.size(); i ++) {
			active.erase(toRemove[i]);
			for(set<int> :: iterator it = g[ toRemove[i] ].begin(); it != g[ toRemove[i] ].end(); it ++)
				g[ *it ].erase(toRemove[i]);
		}
	}
	
	go(active);
}

int main()
{
	read();
	solve();

    return 0;
}
