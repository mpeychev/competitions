#include <iostream>
#include <stdio.h>

using namespace std;

int n, a;

int main()
{
	cin >> n;
	
	a = 1;
	for(int i = 2; i * i <= n; i ++)
		if(n % i == 0) {
			a = n / i;
			break;
		}
	
	cout << n - a << endl;

    return 0;
}
