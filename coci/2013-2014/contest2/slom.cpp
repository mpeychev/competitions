#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#define pb push_back

using namespace std;

int x;
string str;
vector< string > vec;

void read() {
    cin >> x;
    cin >> str;
}

string calc(string s) {
    string ret;
    for(int i = 0; i < s.size(); i += 2)
        ret.pb(s[i]);

    for(int i = s.size() - 1; i >= 0; i --)
        if(i % 2 == 1)
            ret.pb(s[i]);

    return ret;
}

void solve() {
    vec.pb(str);
    for( ; ; ) {
        string tmp = calc(vec.back());
        if(tmp == vec[0]) break;
        vec.pb(tmp);
    }

    cout << vec[ x % (int)vec.size() ] << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
