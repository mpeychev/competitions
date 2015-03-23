#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

const string pat1 = "ABC";
const string pat2 = "BABC";
const string pat3 = "CCAABB";

int n;
char s[1 << 7];

void read() {
	scanf("%d\n", &n);
	scanf("%s", &s);
}

int calc(string p) {
	int ret = 0;
	int sz = (int)p.size();
	for(int i = 0; i < n; i ++)
		if(s[i] == p[ i % sz ])
			ret ++;
	return ret;
}

void solve() {
	int val1 = calc(pat1);
	int val2 = calc(pat2);
	int val3 = calc(pat3);
	
	int mx = max(val1, max(val2, val3));
	
	cout << mx << endl;
	if(val1 == mx) cout << "Adrian\n";
	if(val2 == mx) cout << "Bruno\n";
	if(val3 == mx) cout << "Goran\n";
}

int main()
{
	read();
	solve();

    return 0;
}
