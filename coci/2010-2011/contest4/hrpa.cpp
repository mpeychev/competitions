#include <iostream>
#include <stdio.h>
#include <vector>

#define pb push_back

using namespace std;

typedef long long LL;

const LL MAXN = 1000000000000000LL;

vector< LL > fib;

void go(LL n) {
	if(n == 1) {
		cout << "1\n";
		return;
	}
	
	LL t = 1;
	for(int i = 1; i < fib.size(); i ++)
		if(fib[i] > n) break;
		else t = fib[i];
	
	if(t == n) {
		cout << n << endl;
		return;
	}
	
	go(n - t);
}

int main()
{
	fib.pb(1);
	fib.pb(2);
	while(1) {
		int sz = (int)fib.size();
		LL c = fib[sz - 2] + fib[sz - 1];
		if(c > MAXN) break;
		fib.pb(c);
	}
	
	LL n;
	cin >> n;
	go(n);

    return 0;
}
