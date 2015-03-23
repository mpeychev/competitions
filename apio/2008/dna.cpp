#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef long long LL;

const int MAXM = 50005;

int m, k;
LL r;
char s[MAXM];
LL dp[MAXM][4][12];

void read() {
	scanf("%d %d %lld\n", &m, &k, &r);
	scanf("%s", &s);
}

int getNumber(char ch) {
	switch(ch) {
		case 'A': return 0;
		case 'C': return 1;
		case 'G': return 2;
		case 'T': return 3;
		default: return -1;
	}
}

char getLetter(int i) {
	switch(i) {
		case 0: return 'A';
		case 1: return 'C';
		case 2: return 'G';
		case 3: return 'T';
		default: return 'N';
	}
}

LL count(int pos, int last, int form) {
	LL &ret = dp[pos][last][form];
	
	if(ret != -1)
		return ret;
	
	if(form >= k) {
		ret = 0;
		return ret;
	}
	
	if(pos == m) {
		ret = 1;
		return ret;
	}
	
	if(s[pos] != 'N') {
		int cur = getNumber(s[pos]);
		if(cur < last) ret = count(pos + 1, cur, form + 1);
		else ret = count(pos + 1, cur, form);
		
		return ret;
	}
	
	ret = 0;
	for(int i = 0; i < 4; i ++)
		if(i < last) ret += count(pos + 1, i, form + 1);
		else ret += count(pos + 1, i, form);
	
	return ret;
}

void solve() {
	memset(dp, -1, sizeof(dp));
	
	int last = 0, form = 0;
	LL tmp = 0;
	
	r --;
	for(int i = 0; i < m; i ++)
		if(s[i] != 'N') {
			int cur = getNumber(s[i]);
			if(cur < last) form ++;
			last = cur;
		}
		else {
			for(int j = 0; j < 4; j ++) {
				LL value;
				if(j < last) value = count(i + 1, j, form + 1);
				else value = count(i + 1, j, form);
				
				if(value <= r) r -= value;
				else {
					s[i] = getLetter(j);
					if(j < last) form ++;
					last = j;
					break;
				}
			}
		}
	
	printf("%s\n", s);
}

int main()
{
	read();
	solve();

    return 0;
}
