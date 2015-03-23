#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>

#define pb push_back

using namespace std;

typedef long long LL;

LL a, b;
LL cnt;
LL perm[32];

void read() {
	cin >> a >> b;
}

LL calcPerms(int vec[16]) {
	LL countAll = 0, down = 1;
	for(int i = 0; i < 10; i ++)
		if(vec[i]) {
			countAll += vec[i];
			down *= perm[ vec[i] ];
		}
	
	return perm[ countAll ] / down;
}

void add(LL _num, LL _lim) {
	if(_num == _lim) {
		cnt ++;
		return;
	}
	
	if(_num > _lim)
		return;
	
	vector<int> lim;
	int cntD[16];
	int numSize = 0;
	
	memset(cntD, 0, sizeof(cntD));
	while(_num) {
		numSize ++;
		cntD[_num % 10] ++;
		_num /= 10;
	}
	
	while(_lim) {
		lim.pb(_lim % 10);
		_lim /= 10;
	}
	
	reverse(lim.begin(), lim.end());
	
	if(numSize < (int)lim.size()) {
		cnt += calcPerms(cntD);
		return;
	}
	
	for(int i = 0; i < (int)lim.size(); i ++) {
		for(int j = 1; j < lim[i]; j ++)
			if(cntD[j]) {
				cntD[j] --;
				cnt += calcPerms(cntD);
				cntD[j] ++;
			}
		
		if(!cntD[ lim[i] ]) break;
		cntD[ lim[i] ] --;
	}
	
	cnt ++;
	for(int i = 0; i < 10; i ++)
		if(cntD[i]) {
			cnt --;
			break;
		}
}

void go(LL x, LL p, LL bound) {
	if(!bound) return;
	if(x > bound / p) return;
	
	if(!x) {
		for(int i = 1; i <= 9; i ++)
			go(i, i, bound);
	}
	else {
		add(x, bound / p);
		for(int i = x % 10; i <= 9; i ++)
			go(10 * x + i, p * i, bound);
	}
}

void solve() {
	perm[0] = 1LL;
	for(int i = 1; i <= 18; i ++)
		perm[i] = perm[i - 1] * (LL)i;
	
	LL val1, val2;
	
	cnt = 0;
	go(0, 1, b);
	val2 = cnt;
	
	cnt = 0;
	go(0, 1, a - 1);
	val1 = cnt;
	
	cout << val2 - val1 << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
