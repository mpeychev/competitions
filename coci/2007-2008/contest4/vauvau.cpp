#include <iostream>
#include <stdio.h>

using namespace std;

int a, b, c, d;

void solve(int T) {
	int cnt = 0, t;
	
	t = T;
	t %= (a + b);
	if(t >= 1 && t <= a) cnt ++;
	
	t = T;
	t %= (c + d);
	if(t >= 1 && t <= c) cnt ++;
	
	if(cnt == 0) cout << "none\n";
	else if(cnt == 1) cout << "one\n";
	else cout << "both\n";
}

int main()
{
	cin >> a >> b >> c >> d;
	
	int x;
	for(int i = 0; i < 3; i ++) {
		cin >> x;
		solve(x);
	}

    return 0;
}
