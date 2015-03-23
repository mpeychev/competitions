#include <iostream>
#include <stdio.h>
#include <string>
#include <set>

#define pb push_back

using namespace std;

int n, k;
string s;
set< string > st;

void read() {
    scanf("%d %d\n", &n, &k);
    cin >> s;
}

void gen(int mask) {
    string str, code;
    code = s;
    str.resize(n);
    for(int i = 0; i < k; i ++) {
        char ch;
        if((mask >> i) & 1) ch = 'B';
        else ch = 'W';

        str[0] = ch;
        for(int j = 0; j < n - 1; j ++)
            if(code[j] == 'B') str[j + 1] = str[j];
            else {
                if(str[j] == 'B') str[j + 1] = 'W';
                else str[j + 1] = 'B';
            }

        if(code[n - 1] == 'B' && str[0] != str[n - 1]) return;
        if(code[n - 1] == 'W' && str[0] == str[n - 1]) return;

        code = str;
    }

    code = str;
    for(int i = 1; i < n; i ++) {
        string tmp;
        for(int j = i; j < n; j ++)
            tmp.pb(str[j]);
        for(int j = 0; j < i; j ++)
            tmp.pb(str[j]);
        code = min(code, tmp);
    }

    st.insert(code);
}

void solve() {
    for(int i = 0; i < k; i ++) {
        char ch;
        if(s[0] != s[n - 1]) ch = 'W';
        else ch = 'B';

        for(int j = 0; j < n - 1; j ++)
            if(s[j] != s[j + 1]) s[j] = 'W';
            else s[j] = 'B';
        s[n - 1] = ch;
    }

    for(int i = 0; i < (1 << k); i ++)
        gen(i);

    cout << st.size() << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
