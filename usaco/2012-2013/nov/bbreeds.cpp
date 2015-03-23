/*
ID: mompej951
TASK: bbreeds
LANG: C++
*/
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 1 << 10;
const int MOD = 2012;

char s[MAXN];
int n;
int dp1[512][512], dp2[512][512];
int cnt[MAXN];

void read() {
    scanf("%s", &s);
}

bool check() {
    for(int i = 1; i <= n; i ++) {
        if(s[i - 1] == '(') cnt[i] = cnt[i - 1] + 1;
        else {
            if(!cnt[i - 1]) return false;
            cnt[i] = cnt[i - 1] - 1;
        }
    }
    return (cnt[n] == 0);
}

void solve() {
    n = strlen(s);

    if(!check()) {
        printf("0\n");
        return;
    }

    dp2[0][0] = 1;
    for(int i = n - 1; i >= 0; i --) {
        memset(dp1, 0, sizeof(dp1));
        for(int a = 0; a <= cnt[i]; a ++)
            for(int b = 0; b <= cnt[i] - a; b ++)
                if(s[i] == '(') {
                   dp1[a][b] = dp2[a + 1][b] + dp2[a][b + 1];
                   if(dp1[a][b] >= MOD) dp1[a][b] -= MOD;
                }
                else {
                    if(a) dp1[a][b] = dp2[a - 1][b];
                    if(b) dp1[a][b] += dp2[a][b - 1];
                    if(dp1[a][b] >= MOD) dp1[a][b] -= MOD;
                }
        memcpy(dp2, dp1, sizeof(dp1));
    }

    cout << dp1[0][0] << endl;
}

int main()
{
    freopen("bbreeds.in", "r", stdin);
    freopen("bbreeds.out", "w", stdout);

    read();
    solve();

    return 0;
}
