#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

typedef long long LL;

const int MAXN = 50100;

struct el {
	int value;
	int index;
	
	el() {}
	el(int _value, int _index): value(_value), index(_index) {}
};

struct cmp {
	bool operator()(el a, el b) {
		return !(a.value < b.value);
	}
};

int n, k;
LL m;
int p[MAXN], c[MAXN];
bool used[MAXN];

priority_queue< el , vector< el > , cmp > pset, cset;
priority_queue< int , vector<int>, greater<int> > free;

int ans;

void read() {
	scanf("%d %d %lld", &n, &k, &m);
	for(int i = 0; i < n; i ++)
		scanf("%d %d", &p[i], &c[i]);
}

void solve() {
	for(int i = 0; i < n; i ++) {
		pset.push(el(p[i], i));
		cset.push(el(c[i], i));
	}
	
	for(int i = 0; i < k; i ++)
		free.push(0);
	
	while(m) {
		while(!pset.empty() && used[pset.top().index])
			pset.pop();
		
		while(!cset.empty() && used[cset.top().index])
			cset.pop();
		
		if(pset.empty() || cset.empty())
			break;
		
		int opt1 = pset.top().value;
		int opt2 = free.top() + cset.top().value;
		
		if(opt1 <= opt2) {
			if(m < opt1) break;
			
			ans ++;
			m -= opt1;
			used[ pset.top().index ] = true;
			pset.pop();
		}
		else {
			if(m < opt2) break;
			
			ans ++;
			m -= opt2;
			used[ cset.top().index ] = true;
			free.pop();
			free.push(p[ cset.top().index ] - c[ cset.top().index ]);
			cset.pop();
		}
	}
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();
	
	return 0;
}
