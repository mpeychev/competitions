#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

int b, e;
char s[32];

int target;
int vec[128];

int level[1 << 16];
queue<int> q;

int ans;
int steps;
int diff;

int getString() {
	int ret = 0;
	
	scanf("%s", &s);
	for(int i = 0; i < b; i ++)
		ret = (ret << 1) | (s[i] - '0');
	
	return ret;
}

void read() {
	scanf("%d %d\n", &b, &e);
	target = getString();
	for(int i = 0; i < e; i ++)
		vec[i] = getString();
}

int calcDiff(int x) {
	int ret = 0;
	for(int i = 0; i < b; i ++)
		if(((x >> i) & 1) != ((target >> i) & 1))
			ret ++;
	return ret;
}

void solve() {
	memset(level, -1, sizeof(level));
	for(int i = 0; i < e; i ++) {
		level[ vec[i] ] = 0;
		q.push(vec[i]);
	}
	
	while(!q.empty()) {
		int tmp = q.front();
		q.pop();
		
		for(int i = 0; i < e; i ++)
			if(level[ tmp ^ vec[i] ] == -1) {
				level[ tmp ^ vec[i] ] = level[tmp] + 1;
				q.push(tmp ^ vec[i]);
			}
	}
	
	ans = vec[0];
	steps = 2;
	diff = calcDiff(ans);
	for(int i = 0; i < (1 << b); i ++)
		if(level[i] != -1) {
			int value = calcDiff(i);
			int curSteps = level[i];
			if(!curSteps) curSteps = 2;
			if(value < diff || (value == diff && steps > curSteps)) {
				ans = i;
				steps = curSteps;
				diff = value;
			}
		}
	
	cout << steps << endl;
	for(int i = b - 1; i >= 0; i --)
		cout << ((ans >> i) & 1);
	cout << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
