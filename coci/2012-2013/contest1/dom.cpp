#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

string t = "CAMBRIDGE";
string s;

bool check(char ch) {
    for(int i = 0; i < t.size(); i ++)
        if(t[i] == ch)
            return false;
    return true;
}

int main()
{
    cin >> s;
    for(int i = 0; i < s.size(); i ++)
        if(check(s[i]))
            cout << s[i];
    cout << endl;

    return 0;
}
