#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

typedef long long LL;

const int MAXM = 100100;

LL l, r, m;
string s;
bool used[16];
LL dp[16][1 << 17];
int pw[16];

void read() {
    cin >> m >> l >> r;
    cin >> s;
    for(int i = 0; i < s.size(); i ++)
        used[ s[i] - '0' ] = true;
}

LL get(int len, int rem) {
    if(dp[len][rem] != -1)
        return dp[len][rem];

    if(!len) {
        if(!rem) return dp[len][rem] = 1;
        return dp[len][rem] = 0;
    }

    LL ret = 0;
    for(int d = 0; d < 10; d ++)
        if(used[d])
            ret += get(len - 1, (rem - (pw[len - 1] * d) % m + m) % m);

    return dp[len][rem] = ret;
}

LL get2(int len, int rem) {
    if(!len) return 0;

    LL ret = 0;

    if(len == 1) {
        for(int d = 1; d < 10; d ++)
            if(used[d] && d % m == rem)
                ret ++;
    }
    else {
        for(int d = 1; d < 10; d ++)
            if(used[d])
                ret += get(len - 1, (rem - (pw[len - 1] * d) % m + m) % m);
    }

    return ret;
}

LL calc(LL n) {
    if(!n) return 0;

    vector<int> dig;
    LL ret = 0;

    LL n2 = n;
    while(n2) {
        dig.pb(n2 % 10);
        n2 /= 10;
    }
    reverse(dig.begin(), dig.end());

    for(int i = 1; i < dig.size(); i ++)
        ret += get2(i, 0);

    int curMod = 0;
    for(int i = 0; i < dig.size(); i ++) {
        for(int d = 0; d < dig[i]; d ++)
            if(used[d]) {
                if(!d && !i) continue;

                int tmpMod = (curMod + pw[ dig.size() - i - 1 ] * d) % m;
                ret += get(dig.size() - i - 1, (m - tmpMod) % m);
            }
        if(!used[ dig[i] ]) return ret;
        curMod = (curMod + pw[ dig.size() - i - 1 ] * dig[i]) % m;
    }

    if(!curMod) ret ++;
    return ret;
}

bool check(LL x) {
    while(x) {
        if(!used[x % 10]) return false;
        x /= 10;
    }
    return true;
}

void solve() {
    if(l > r) {
        printf("0\n");
        return;
    }

    if(m > MAXM) {
        LL le = l / m;
        int ans = 0;
        for(LL i = le; ; i ++) {
            if(i * m > r) break;
            if(i * m >= l && check(i * m))
                ans ++;
        }
        cout << ans << endl;
        return;
    }

    pw[0] = 1;
    for(int i = 1; i <= 13; i ++)
        pw[i] = (pw[i - 1] * 10) % m;

    memset(dp, -1, sizeof(dp));
    cout << calc(r) - calc(l - 1) << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
