#include <iostream>
#include <stdio.h>

using namespace std;

int a, b, c, ans;
int newA, newB, newC;

int main()
{
	cin >> a >> b >> c;
	while(1) {
		if(a + 1 == b && b + 1 == c) break;
		if(b - a > c - b) {
			newA = a;
			newB = a + 1;
			newC = b;
		}
		else {
			newA = b;
			newB = c - 1;
			newC = c;
		}
		
		a = newA, b = newB, c = newC;
		ans ++;
	}
	
	cout << ans << endl;

    return 0;
}
