#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#define pb push_back

using namespace std;

const int MAXN = 10100;
const int MAXM = 80;

int n, m;
char ma3x[MAXN][MAXM];
vector<int> x, y;
int f[MAXN];

void read() {
	scanf("%d %d\n", &n, &m);
	for(int i = 0; i < n; i ++)
		scanf("%s", &ma3x[i]);
}

int kmp(string s) {
	if((int)s.size() == 1) return 1;
	
	f[0] = 0;
	for(int i = 1; i < (int)s.size(); i ++) {
		int j = f[i - 1];
		while(j != 0 && s[i] != s[j]) j = f[j - 1];
		if(j == 0) {
			if(s[0] == s[i]) f[i] = 1;
			else f[i] = 0;
		}
		else f[i] = j + 1;
	}
	
	return (int)s.size() - f[ (int)s.size() - 1 ];
}

int gcd(int a, int b) {
	while(b) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int nok(int a, int b) {
	int d = gcd(a, b);
	return (a * b) / d;
}

void solve() {
	for(int i = 0; i < n; i ++) {
		string str;
		for(int j = 0; j < m; j ++)
			str.pb(ma3x[i][j]);
		x.pb(kmp(str));
	}
	
	for(int j = 0; j < m; j ++) {
		string str;
		for(int i = 0; i < n; i ++)
			str.pb(ma3x[i][j]);
		y.pb(kmp(str));
	}
	
	int p = x[0];
	for(int i = 1; i < (int)x.size(); i ++) {
		p = nok(p, x[i]);
		if(p >= m) {
			p = m;
			break;
		}
	}
	
	int q = y[0];
	for(int i = 1; i < (int)y.size(); i ++) {
		q = nok(q, y[i]);
		if(q >= n) {
			q = n;
			break;
		}
	}
	
	cout << p * q << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
