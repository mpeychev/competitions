#include <iostream>
#include <stdio.h>

using namespace std;

struct point {
	int x, y;
	
	void read() {
		scanf("%d %d", &x, &y);
	}
};

int S2(point A, point B, point C) {
	int d = (A.x * B.y + B.x * C.y + C.x * A.y) - (B.x * A.y + C.x * B.y + A.x * C.y);
	if(d < 0) return -d;
	return d;
}

int main()
{
	point A, B, C, D;
	int n, s;
	int cnt = 0;
	
	A.read();
	B.read();
	C.read();
	
	s = S2(A, B, C);
	cout << s / 2 << "." << (s % 2) * 5 << endl;

	scanf("%d", &n);
	for(int i = 0; i < n; i ++) {
		D.read();
		int s1 = S2(A, B, D);
		int s2 = S2(A, C, D);
		int s3 = S2(B, C, D);
		
		if(s1 + s2 + s3 == s) cnt ++;
	}
	
	cout << cnt << endl;

    return 0;
}
