#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;

int n, w;
int c[32];
int sum[1 << 18], minC[1 << 18];
int level[1 << 18], move[1 << 18];
queue<int> q;

void read() {
	cin >> n >> w;
	for(int i = 0; i < n; i ++)
		cin >> c[i];
}

void write(int mask) {
	int bits = 0;
	for(int i = 0; i < n; i ++)
		if((mask >> i) & 1)
			bits ++;
	
	printf("%d", bits);
	for(int i = 0; i < n; i ++)
		if((mask >> i) & 1)
			printf(" %d", i + 1);
	printf("\n");
}

void write() {
	cout << level[0] - 1 << endl;
	int curMask = 0;
	while(curMask != (1 << n) - 1) {
		write(move[curMask]);
		curMask |= move[curMask];
	}
}

void solve() {
	for(int mask = 0; mask < (1 << n); mask ++) {
		minC[mask] = w + 5;
		for(int i = 0; i < n; i ++)
			if((mask >> i) & 1) {
				sum[mask] += c[i];
				if(minC[mask] > c[i]) minC[mask] = c[i];
			}
	}
	
	q.push((1 << n) - 1);
	level[(1 << n) - 1] = 1;
	move[(1 << n) - 1] = -1;
	while(!q.empty()) {
		int curMask = q.front();
		q.pop();
		
		if(curMask == 0) return;
		
		for(int subMask = curMask; subMask; subMask = (subMask - 1) & curMask)
			if(sum[subMask] <= w) {
				int nxtMask = curMask ^ subMask;
				if(sum[subMask] + minC[nxtMask] > w && !level[nxtMask]) {
					level[nxtMask] = level[curMask] + 1;
					move[nxtMask] = subMask;
					
					if(!nxtMask) return;
					
					q.push(nxtMask);
				}
			}
	}
}

int main()
{
	read();
	solve();
	write();

    return 0;
}
