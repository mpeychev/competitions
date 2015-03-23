#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>

#define pb push_back

using namespace std;

typedef vector<int> vi;

const int MAXN = 1000000 + 10;

int n;
char s[2 * MAXN];
vi nxt[MAXN];
int parent[MAXN], cntChildren[MAXN];
queue<int> q;
map< vi , int > h;
int hashNode[MAXN];
int down[MAXN];
set<int> st[MAXN];

void read() {
	gets(s);
}

void solve() {
	n = strlen(s);
	
	int curNode = 0, cntNodes = 0;
	for(int i = 0; i < n; i ++)
		if(s[i] == '(') {
			cntNodes ++;
			nxt[curNode].pb(cntNodes);
			parent[cntNodes] = curNode;
			curNode = cntNodes;
		}
		else curNode = parent[curNode];
	
	int curHash = 1;
	for(int i = 1; i <= cntNodes; i ++) {
		cntChildren[i] = (int)nxt[i].size();
		if(!cntChildren[i]) {
			hashNode[i] = 1;
			down[i] = 1;
			q.push(i);
		}
	}
	
	while(!q.empty()) {
		int tmp = q.front();
		q.pop();
		
		if(tmp == 1) continue;
		
		int up = parent[tmp];
		cntChildren[up] --;
		
		if(!cntChildren[up]) {
			vi vec;
			int mx = -1;
			for(int i = 0; i < nxt[up].size(); i ++) {
				vec.pb(hashNode[ nxt[up][i] ]);
				if(mx < down[ nxt[up][i] ])
					mx = down[ nxt[up][i] ];
			}
			sort(vec.begin(), vec.end());
			
			if(h.find(vec) == h.end()) {
				curHash ++;
				h[ vec ] = curHash;
			}
			
			hashNode[up] = h[vec];
			down[up] = mx + 1;
			q.push(up);
		}
	}
	
	for(int i = 1; i <= cntNodes; i ++)
		st[ down[i] ].insert(hashNode[i]);
	
	for(int i = 1; i <= down[1]; i ++)
		printf("%d\n", (int)st[i].size());
}

int main()
{
	read();
	solve();

    return 0;
}
