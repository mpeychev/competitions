#include <iostream>
#include <stdio.h>

using namespace std;

int a, b, c, d;
double val[4];

void read() {
	cin >> a >> b >> c >> d;
}

double calc() {
	return (double)a / (double)c + (double)b / (double)d;
}

void rotate() {
	int a2 = c;
	int b2 = a;
	int c2 = d;
	int d2 = b;
	
	a = a2;
	b = b2;
	c = c2;
	d = d2;
}

void solve() {
	for(int i = 0; i < 4; i ++) {
		val[i] = calc();
//		cout << i << ": " << val[i] << endl;
		rotate();
	}
	
	int ans = 0;
	for(int i = 1; i < 4; i ++)
		if(val[i] > val[ans])
			ans = i;
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
