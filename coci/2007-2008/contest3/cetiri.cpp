#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

int a[4], b[4];

bool check() {
	sort(b, b + 4);
	
	int d = b[1] - b[0];
	return (b[2] - b[1] == d && b[3] - b[2] == d);
}

int main()
{
	cin >> a[0] >> a[1] >> a[2];
	for(int i = -300; i <= 300; i ++) {
		b[0] = a[0];
		b[1] = a[1];
		b[2] = a[2];
		b[3] = i;
		
		if(check()) {
			cout << i << endl;
			break;
		}
	}
	
	return 0;
}
