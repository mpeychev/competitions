/*
ID: mompej951
TASK:
LANG: C++
*/
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>

#define pb push_back

using namespace std;

char s[32];
int n, ans = 0;

void read() {
    scanf("%s", &s);
}

bool check(string a) {
    int cnt = 0;
    for(int i = 0; i < a.size(); i ++)
        if(a[i] == '(') cnt ++;
        else {
            if(!cnt) return false;
            cnt --;
        }
    return (cnt == 0);
}

void solve() {
    n = strlen(s);

    for(int i = 0; i < (1 << n); i ++) {
        string a, b;
        for(int j = 0; j < n; j ++)
            if((i >> j) & 1) a.pb(s[j]);
            else b.pb(s[j]);
        if(check(a) && check(b)) {
            ans = ans ++;
            if(ans >= 2012) ans -= 2012;
        }
    }
    cout << ans << endl;
}

int main()
{
    freopen("bbreeds.in", "r", stdin);
    freopen("bbreeds1.out", "w", stdout);

    read();
    solve();

    return 0;
}
