#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const int MAX_NODES = 200200;

struct Node {
	int left, right;
	int minLevel, maxLevel;
};

int n, toys;
Node data[MAX_NODES];
int level[MAX_NODES];
int up, down, ans;

void read() {
	int l, r;
	
	scanf("%d", &n);
	toys = n + 1;
	for(int i = 1; i <= n; i ++) {
		scanf("%d %d", &l, &r);
		if(l == -1) l = toys ++;
		if(r == -1) r = toys ++;
		data[i].left = l;
		data[i].right = r;
	}
}

int min(int a, int b) {
	if(a < b) return a;
	return b;
}

int max(int a, int b) {
	if(a > b) return a;
	return b;
}

void dfs(int node) {
	if(node > n) {
		data[node].minLevel = data[node].maxLevel = level[node];
		return;
	}
	
	int leftChild = data[node].left;
	int rightChild = data[node].right;
	
	level[leftChild] = level[rightChild] = level[node] + 1;
	
	dfs(leftChild);
	dfs(rightChild);
	
	data[node].minLevel = min(data[leftChild].minLevel, data[rightChild].minLevel);
	data[node].maxLevel = max(data[leftChild].maxLevel, data[rightChild].maxLevel);
}

void go(int node) {
	if(node > n)
		return;
	
	int leftChild = data[node].left;
	int rightChild = data[node].right;
	
	if(data[leftChild].minLevel == data[leftChild].maxLevel && data[leftChild].minLevel == down) {
		go(rightChild);
		return;
	}
	
	if(data[leftChild].minLevel == data[leftChild].maxLevel) {
		if(data[rightChild].minLevel == data[rightChild].maxLevel && data[rightChild].minLevel == up) return;
		
		ans ++;
		go(rightChild);
		
		return;
	}
	
	if(data[rightChild].minLevel != data[rightChild].maxLevel) {
		printf("-1\n");
		exit(0);
	}
	
	if(data[rightChild].minLevel == down) ans ++;
	
	go(leftChild);
}

void solve() {
	dfs(1);
	
	if(data[1].maxLevel - data[1].minLevel > 1) {
		cout << "-1\n";
		return;
	}
	
	if(data[1].maxLevel == data[1].minLevel) {
		cout << "0\n";
		return;
	}
	
	down = data[1].maxLevel;
	up = data[1].minLevel;
	
	go(1);
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
