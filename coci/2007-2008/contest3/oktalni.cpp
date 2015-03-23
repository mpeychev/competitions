#include <iostream>
#include <string>

using namespace std;

string s;

int main()
{
	cin >> s;
	
	while(s.size() % 3)
		s = "0" + s;
	
	for(int i = 0; i < s.size(); i += 3)
		cout << (s[i + 2] - '0') + 2 * (s[i + 1] - '0') + 4 * (s[i] - '0');
	cout << endl;
	
	return 0;
}
