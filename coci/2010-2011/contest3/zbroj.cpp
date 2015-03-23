#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

int a, b;
vector<int> va, vb;

void read() {
	cin >> a >> b;
}

void calc(char ch) {
	int A = 0, B = 0;
	for(int i = 0; i < va.size(); i ++)
		A = 10 * A + va[i];
	for(int i = 0; i < vb.size(); i ++)
		B = 10 * B + vb[i];
	cout << A + B << ch;
}

void solve() {
	while(a) {
		va.pb(a % 10);
		a /= 10;
	}
	
	while(b) {
		vb.pb(b % 10);
		b /= 10;
	}
	
	reverse(va.begin(), va.end());
	reverse(vb.begin(), vb.end());
	
	for(int i = 0; i < va.size(); i ++)
		if(va[i] == 6)
			va[i] = 5;
	
	for(int i = 0; i < vb.size(); i ++)
		if(vb[i] == 6)
			vb[i] = 5;
	
	calc(' ');
	
	for(int i = 0; i < va.size(); i ++)
		if(va[i] == 5)
			va[i] = 6;
	
	for(int i = 0; i < vb.size(); i ++)
		if(vb[i] == 5)
			vb[i] = 6;
	
	calc('\n');
}

int main()
{
	read();
	solve();

    return 0;
}
