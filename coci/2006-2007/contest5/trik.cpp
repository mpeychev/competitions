#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int x, y, z;
string s;

int main()
{
    cin >> s;

    x = 0, y = 1, z = 2;
    for(int i = 0; i < s.size(); i ++) {
        if(s[i] == 'A') swap(x, y);
        if(s[i] == 'B') swap(y, z);
        if(s[i] == 'C') swap(x, z);
    }

    if(x == 0) cout << 1 << endl;
    if(y == 0) cout << 2 << endl;
    if(z == 0) cout << 3 << endl;

    return 0;
}
