#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>

#define pb push_back

using namespace std;

const string day[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

int getLine() {
	string s;
	cin >> s;
	
	int h = (s[0] - '0') * 10 + (s[1] - '0');
	int m = (s[3] - '0') * 10 + (s[4] - '0');
	return h * 60 + m;
}

int gcd(int a, int b) {
	while(b) {
		int r = a % b;
		a = b, b = r;
	}
	return a;
}

int abss(int x) {
	if(x < 0) return -x;
	return x;
}

void write(int num) {
	if(num < 10) cout << "0";
	cout << num;
}

int main()
{
	int a = getLine();	int saveA = a;
	int b = getLine();
	int k = getLine();	int saveK = k;
	int m = getLine();
	
	int d = gcd(k, m);
	
	if(abss(b - a) % d) {
		cout << "Never\n";
		return 0;
	}
	
	int c = b - a;
	
	k /= d, m /= d, c /= d;
	
	int t = 0;
	for(int x = max(1, c / k); x <= 20000000; x ++)
		if(k * x >= c && (k * x - c) % m == 0) {
			t = saveA + saveK * x;
			break;
		}
	
	int idx = (5 + t / (24 * 60)) % 7;
	cout << day[idx] << endl;
	
	t %= (24 * 60);

	write(t / 60);
	cout << ":";
	write(t % 60);
	cout << endl;
	
    return 0;
}
