#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int n, ans;
string s[1 << 7];

int main()
{
	cin >> n;
	for(int i = 0; i < n; i ++) {
		cin >> s[i];
		
		int tmp = 0;
		for(int j = 0; j < i; j ++)
			if(s[i] == s[j])
				tmp ++;
		
		if(2 * tmp > i) ans ++;
	}
	
	cout << ans << endl;
	
	return 0;
}
