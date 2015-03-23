#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

typedef long long LL;

const int MAXN = 256;
const LL MOD = 100000;

int n;
char s[MAXN];
LL dp[MAXN][MAXN];
bool fl[MAXN][MAXN];

void read() {
    scanf("%d\n", &n);
    scanf("%s", &s);
}

LL go(int le, int ri) {
    LL &ret = dp[le][ri];

    if(ret != -1)
        return ret;

    if(le > ri) {
        ret = 1;
        return ret;
    }

    if(s[le] == ')' || s[le] == ']' || s[le] == '}') {
        ret = 0;
        return ret;
    }

    if(s[ri] == '(' || s[ri] == '[' || s[ri] == '{') {
       ret = 0;
       return ret;
    }

    if(le + 1 == ri) {
        if(s[le] == '?' && s[ri] == '?') {
            ret = 3;
            return ret;
        }

        if(s[le] == '?' || s[ri] == '?') {
            ret = 1;
            return ret;
        }

        ret = 1;
        if(s[le] == '(' && s[ri] != ')') ret = 0;
        if(s[le] == '[' && s[ri] != ']') ret = 0;
        if(s[le] == '{' && s[ri] != '}') ret = 0;
        return ret;
    }

    ret = 0;
    for(int i = le + 1; i <= ri; i += 2) {
        if(s[i] == '(' || s[i] == '[' || s[i] == '{') continue;

        LL coef;
        if(s[le] == '?' && s[i] == '?') {
            coef = 3;
        }
        else {
            if(s[le] == '?' || s[i] == '?') {
                coef = 1;
            }
            else {
                coef = 1;
                if(s[le] == '(' && s[i] != ')') coef = 0;
                if(s[le] == '[' && s[i] != ']') coef = 0;
                if(s[le] == '{' && s[i] != '}') coef = 0;
            }
        }

        if(coef) {
            ret = ret + coef * go(le + 1, i - 1) * go(i + 1, ri);
            if(ret > MOD) {
                fl[le][ri] = true;
                ret %= MOD;
            }
        }
    }

    return ret;
}

void solve() {
    memset(dp, -1, sizeof(dp));
    LL ans = go(0, n - 1);
    if(!fl[0][n - 1]) {
        cout << ans << endl;
        return;
    }

    vector<int> vec;
    while(ans) {
        vec.pb(ans % 10);
        ans /= 10;
    }
    reverse(vec.begin(), vec.end());

    for(int i = vec.size(); i < 5; i ++)
        cout << 0;
    for(int i = 0; i < vec.size(); i ++)
        cout << vec[i];
    cout << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
