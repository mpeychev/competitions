#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef long long LL;

const int MAXN = 305;

int n;
char s[MAXN][MAXN];
int psRow[MAXN][MAXN], psCol[MAXN][MAXN];
int cntUp[MAXN][MAXN], ptrDown[MAXN][MAXN], stop[MAXN][MAXN];
LL dp[MAXN][MAXN];
LL ans;

void read() {
    scanf("%d\n", &n);
    for(int i = 0; i < n; i ++)
        scanf("%s", &s[i]);
}

void init() {
    for(int row = 0; row < n; row ++) {
        if(s[row][0] == '*') psRow[row][0] = 1;
        for(int i = 1; i < n; i ++) {
            psRow[row][i] = psRow[row][i - 1];
            if(s[row][i] == '*') psRow[row][i] ++;
        }
    }

    for(int col = 0; col < n; col ++) {
        if(s[0][col] == '*') psCol[col][0] = 1;
        for(int i = 1; i < n; i ++) {
            psCol[col][i] = psCol[col][i - 1];
            if(s[i][col] == '*') psCol[col][i] ++;
        }
    }
}

inline int countRow(int row, int le, int ri) {
    if(!le) return psRow[row][ri];
    return psRow[row][ri] - psRow[row][le - 1];
}

inline int countCol(int col, int up, int down) {
    if(!up) return psCol[col][down];
    return psCol[col][down] - psCol[col][up - 1];
}

inline LL max(LL x, LL y) {
    if(x < y) return y;
    return x;
}

void solve() {
    for(int row = 0; row < n; row ++) {
        memset(dp, 0, sizeof(dp));

        for(int len = n; len >= 2; len --)
            for(int le = 0; le + len - 1 < n; le ++) {
                int ri = le + len - 1;

                if(cntUp[le][ri] != 0) {
                    if(s[row][le] == '*' || s[row][ri] == '*') cntUp[le][ri] = 0;
                    else cntUp[le][ri] ++;
                }
                else {
                    if(!countRow(row, le, ri)) cntUp[le][ri] = 1;
                }

                if(row == ptrDown[le][ri]) {
                    ptrDown[le][ri] = -1;
                    for(int i = stop[le][ri] + 1; i < n; i ++) {
                        if(s[i][le] == '*' || s[i][ri] == '*') {
                            if(ptrDown[le][ri] != -1) {
                                stop[le][ri] = i;
                                break;
                            }
                        }

                        if(!countRow(i, le, ri)) {
                            ptrDown[le][ri] = i;
                            if(countCol(le, row + 1, i) || countCol(ri, row + 1, i)) {
                                stop[le][ri] = i;
                                break;
                            }
                        }
                    }
                }

                LL SDown = 0, a, b;
                if(!countRow(row, le, ri) && ptrDown[le][ri] != -1 &&
                   !countCol(le, row, ptrDown[le][ri]) && !countCol(ri, row, ptrDown[le][ri])) {
                        a = ri - le - 1;
                        b = ptrDown[le][ri] - row - 1;
                        SDown = a * b;
                   }

                dp[le][ri] = SDown;
                if(le - 1 >= 0) dp[le][ri] = max(dp[le][ri], dp[le - 1][ri]);
                if(ri + 1 < n)  dp[le][ri] = max(dp[le][ri], dp[le][ri + 1]);

                LL SUp = 0;
                if(!countRow(row, le, ri) && cntUp[le][ri] > 2) {
                    a = ri - le - 1;
                    b = cntUp[le][ri] - 2;
                    SUp = a * b;
                }

                ans = max(ans, SUp * dp[le][ri]);
            }
    }

    if(!ans) ans = -1;

    cout << ans << endl;
}

int main()
{
    freopen("eight.in", "r", stdin);
    freopen("eight.out", "w", stdout);

    read();
    init();
    solve();

    return 0;
}
