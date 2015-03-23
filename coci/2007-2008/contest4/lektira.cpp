#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>

using namespace std;

string s, sol;

int main()
{
	cin >> s;
	sol = string (s.size(), 'z');
	
	for(int i = 0; i < s.size() - 2; i ++)
		for(int j = i + 1; j < s.size() - 1; j ++) {
			string a = s.substr(0, i + 1);
			string b = s.substr(i + 1, j - i);
			string c = s.substr(j + 1);
			
			reverse(a.begin(), a.end());
			reverse(b.begin(), b.end());
			reverse(c.begin(), c.end());
			
			string _s = a + b + c;
			if(sol > _s) sol = _s;
		}
	
	cout << sol << endl;

    return 0;
}
