#include <iostream>
#include <stdio.h>

using namespace std;

int k, n, total;
int t;
char z;

int main()
{
	scanf("%d", &k);
	scanf("%d\n", &n);
	
	for(int i = 0; i < n; i ++) {
		scanf("%d %c\n", &t, &z);
		if(total + t > 210) {
			cout << k << endl;
			return 0;
		}
		
		total += t;
		
		if(z == 'T') {
			k ++;
			if(k == 9) k = 1;
		}
	}
	
	cout << k << endl;

    return 0;
}
