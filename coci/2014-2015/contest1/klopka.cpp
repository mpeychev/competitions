#include <iostream>
#include <stdio.h>

using namespace std;

int n;
int x[32], y[32];
int minX, minY;
int maxX, maxY;

void read() {
	cin >> n;
	for(int i = 0; i < n; i ++)
		cin >> x[i] >> y[i];
}

void solve() {
	minX = x[0];
	maxX = x[0];
	
	minY = y[0];
	maxY = y[0];
	
	for(int i = 0; i < n; i ++) {
		minX = min(minX, x[i]);
		maxX = max(maxX, x[i]);
		
		minY = min(minY, y[i]);
		maxY = max(maxY, y[i]);
	}
	
	int side = max(maxX - minX, maxY - minY);
	
	cout << side * side << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
