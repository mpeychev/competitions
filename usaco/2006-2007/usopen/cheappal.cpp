#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef long long LL;

const int MAXN = 1 << 5;
const int MAXM = 1 << 11;
const LL INF = 1LL << 60;

int n, m;
char s[MAXM];
int a[MAXM];
LL add[MAXN], del[MAXN];
LL dp[MAXM][MAXM];

void read() {
    char ch;
    int letter;

    scanf("%d %d\n", &n, &m);
    gets(s);
    for(int i = 0; i < n; i ++) {
        scanf("%c ", &ch);
        letter = ch - 'a';
        scanf("%d %d\n", &add[letter], &del[letter]);

//        cout << letter << " " << add[letter] << " " << del[letter] << endl;
    }
}

LL calc(int le, int ri) {
    if(dp[le][ri] != -1)
        return dp[le][ri];

    if(le == 0 && ri == m + 1)
        return dp[le][ri] = 0;

    if(le && ri <= m && a[le] == a[ri])
        return dp[le][ri] = calc(le - 1, ri + 1);

    LL ret1 = INF;
    LL ret2 = INF;

    if(ri != m + 1) ret1 = min(add[ a[ri] ], del[ a[ri] ]) + calc(le, ri + 1);
    if(le)          ret2 = min(add[ a[le] ], del[ a[le] ]) + calc(le - 1, ri);

    return dp[le][ri] = min(ret1, ret2);
}

void solve() {
    memset(dp, -1, sizeof(dp));

    for(int i = 1; i <= m; i ++)
        a[i] = s[i - 1] - 'a';
/*
    for(int i = 0; i <= m + 1; i ++)
        cout << a[i] << " ";
    cout << endl;

    for(int i = 0; i < n; i ++)
        cout << i << ": " << add[i] << " " << del[i] << endl;
*/
    LL ans = INF;
    for(int i = 0; i <= m; i ++)
        ans = min(ans, calc(i, i + 1));

    for(int i = 1; i <= m; i ++)
        ans = min(ans, calc(i - 1, i + 1));

    cout << ans << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
