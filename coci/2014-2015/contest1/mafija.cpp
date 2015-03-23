#include <iostream>
#include <stdio.h>
#include <queue>
#include <deque>

#define pb push_back

using namespace std;

const int MAXN = 500500;

int n, nxt[MAXN];
int cntIn[MAXN];
short int mark[MAXN];
queue<int> q;
deque<int> vec;

void read() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", &nxt[i]);
		cntIn[ nxt[i] ] ++;
	}
}

void go() {
	bool flag = false;
	for(int i = 0; i < (int)vec.size(); i ++)
		if(mark[ vec[i] ] != 0) {
			flag = true;
			break;
		}
	
	if(!flag) {
		for(int i = 0; i < (int)vec.size(); i ++)
			if(i & 1) mark[ vec[i] ] = -1;
			else mark[ vec[i] ] = 1;
		
		if((int)vec.size() & 1)
			mark[ vec.back() ] = -1;
		
		return;
	}
	
	int fst;
	while(mark[ vec[0] ] == 0) {
		fst = vec[0];
		vec.pop_front();
		vec.pb(fst);
	}
	fst = vec[0];
	vec.pb(fst);
	
	int index = 0;
	while(index < (int)vec.size() - 1) {
		int i = index;
		while(i < (int)vec.size() - 1) {
			if(mark[ vec[i] ] == 0) break;
			i ++;
		}
		
		if(i >= (int)vec.size())
			break;
		
		int j = i;
		while(j < (int)vec.size() - 1) {
			if(mark[ vec[j + 1] ] != 0) break;
			j ++;
		}
		
		/// [i, j]
		for(int k = i; k <= j; k ++)
			if((k - i) & 1) mark[ vec[k] ] = -1;
			else mark[ vec[k] ] = 1;
		
		index = j + 1;
	}
}

void solve() {
	for(int i = 1; i <= n; i ++)
		if(!cntIn[i])
			q.push(i);
	
	while(!q.empty()) {
		int tmp = q.front();
		q.pop();
		
		if(mark[tmp] == 0) {
			mark[tmp] = 1;
			mark[ nxt[tmp] ] = -1;
		}
		
		cntIn[ nxt[tmp] ] --;
		if(!cntIn[ nxt[tmp] ])
			q.push(nxt[tmp]);
	}
	
	for(int i = 1; i <= n; i ++)
		if(!mark[i]) {
			int currentNode = i;
			vec.clear();
			
			while(1) {
				vec.pb(currentNode);
				currentNode = nxt[currentNode];
				if(currentNode == i) break;
			}
			
			go();
		}
	
	int ans = 0;
	for(int i = 1; i <= n; i ++)
		if(mark[i] == 1)
			ans ++;
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
