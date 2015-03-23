#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

char s[16];
long long answer[8];

void read() {
	scanf("%s", &s);
}

long long gcd(long long a, long long b) {
	while(b) {
		long long r = a % b;
		a = b, b = r;
	}
	return a;
}

void solve() {
	long long t = 0, pw = 1;
	for(int i = 2; i < strlen(s); i ++) {
		t = (t * 10 + (s[i] - '0'));
		pw *= 10;
	}
	
	if(t == 0) {
		for(int i = 1; i <= 5; i ++) {
			if(i > 1) cout << " ";
			if(i == (s[0] - '0')) cout << 1;
			else cout << 0;
		}
		cout << endl;
		return;
	}
	
	long long d = gcd(t, pw);
	
	long long cnt = pw / d;
	long long sum = (((s[0] - '0') * pw + t) * cnt) / pw;
	
	answer[1] = cnt;
	
	for(int i = 4; i >= 1; i --) {
		long long curSum = 0;
		for(int j = 1; j <= 5; j ++)
			curSum += (long long)j * answer[j];
		long long k = (sum - curSum) / i;
		answer[1] -= k;
		answer[1 + i] += k;
	}
	
	for(int i = 1; i <= 5; i ++) {
		cout << answer[i];
		if(i == 5) cout << endl;
		else cout << " ";
	}
}

int main()
{
	read();
	solve();
	
	return 0;
}
