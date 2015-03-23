#include <iostream>
#include <stdio.h>
#include <stack>

#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int MAXR = 30100;
const int MAXC = 32;

int r, c, q, p;
char ma3x[MAXR][MAXC];
stack< PII > st[MAXC];

void read() {
	scanf("%d %d\n", &r, &c);
	for(int i = 0; i < r; i ++)
		scanf("%s", &ma3x[i]);
}

void go(int idx) {
//	cout << idx << ":\n";
	while(1) {
		PII tmp = st[idx].top();
		
//		cout << tmp.first << " " << tmp.second << endl;
		
		if(tmp.first == r - 1 || ma3x[tmp.first + 1][tmp.second] == 'X') break;
		if(ma3x[tmp.first + 1][tmp.second] == '.') st[idx].push(mp(tmp.first + 1, tmp.second));
		else {
			if(tmp.second > 0 && ma3x[tmp.first][tmp.second - 1] == '.' && ma3x[tmp.first + 1][tmp.second - 1] == '.')
				st[idx].push(mp(tmp.first + 1, tmp.second - 1));
			else if(tmp.second < c - 1 && ma3x[tmp.first][tmp.second + 1] == '.' && ma3x[tmp.first + 1][tmp.second + 1] == '.')
				st[idx].push(mp(tmp.first + 1, tmp.second + 1));
			else break;
		}
	}
}

void solve() {
	for(int i = 0; i < c; i ++)
		if(ma3x[0][i] == '.') {
			st[i].push(mp(0, i));
			go(i);
		}
	
	scanf("%d", &q);
	for(int i = 0; i < q; i ++) {
		scanf("%d", &p);
		p --;
		
		PII tmp = st[p].top();
		ma3x[tmp.first][tmp.second] = 'O';
		
		for(int j = 0; j < c; j ++)
			if(!st[j].empty() && st[j].top() == tmp) {
				st[j].pop();
				if(!st[j].empty()) go(j);
			}
	}
	
	for(int i = 0; i < r; i ++)
		printf("%s\n", ma3x[i]);
}

int main()
{
	read();
	solve();

    return 0;
}
