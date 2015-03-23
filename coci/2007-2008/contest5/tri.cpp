#include <iostream>
#include <stdio.h>

using namespace std;

int a, b, c;

int main()
{
	cin >> a >> b >> c;
	
	if(a + b == c) {
		cout << a << "+" << b << "=" << c << endl;
		return 0;
	}
	
	if(a - b == c) {
		cout << a << "-" << b << "=" << c << endl;
		return 0;
	}
	
	if(a * b == c) {
		cout << a << "*" << b << "=" << c << endl;
		return 0;
	}
	
	if(c * b == a) {
		cout << a << "/" << b << "=" << c << endl;
		return 0;
	}
	
	if(a == b + c) {
		cout << a << "=" << b << "+" << c << endl;
		return 0;
	}
	
	if(a == b - c) {
		cout << a << "=" << b << "-" << c << endl;
		return 0;
	}
	
	if(a == b * c) {
		cout << a << "=" << b << "*" << c << endl;
		return 0;
	}
	
	if(a * c == b) {
		cout << a << "=" << b << "/" << c << endl;
		return 0;
	}

    return 0;
}
