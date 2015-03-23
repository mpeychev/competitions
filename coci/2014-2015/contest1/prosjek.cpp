#include <iostream>
#include <stdio.h>

using namespace std;

typedef long long LL;

const int MAXN = 1 << 7;

int n;
LL b[MAXN];
LL a[MAXN];

void read() {
	cin >> n;
	for(int i = 0; i < n; i ++)
		cin >> b[i];
}

void solve() {
	a[0] = b[0];
	for(int i = 1; i < n; i ++) {
		LL sum = 0;
		for(int j = 0; j < i; j ++)
			sum += a[j];
		
		a[i] = b[i] * (LL)(i + 1) - sum;
	}
	
	for(int i = 0; i < n; i ++) {
		if(i) cout << " ";
		cout << a[i];
	}
	cout << "\n";
}

int main()
{
	read();
	solve();

    return 0;
}
