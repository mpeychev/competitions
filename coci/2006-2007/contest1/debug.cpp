#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

typedef long long LL;

const int MAXN = 305;

int r, c;
char s[MAXN][MAXN];
LL encode[MAXN][MAXN][4];
bool dp[4][MAXN][MAXN];

void read() {
    scanf("%d %d\n", &r, &c);
    for(int i = 0; i < r; i ++)
        scanf("%s", &s[i]);
}

void groupBits() {
    for(int i = 0; i < r; i ++)
        for(int j = 0; j < c; j ++) {
            LL tmp;

            // ->
            tmp = 0;
            for(int k = 0; k < 32; k ++) {
                tmp <<= 1;
                if(j + k < c)
                    tmp += (s[i][j + k] - '0');

            }
            encode[i][j][0] = tmp;

            // <-
            tmp = 0;
            for(int k = 0; k < 32; k ++) {
                tmp <<= 1;
                if(j - k >= 0)
                    tmp += (s[i][j - k] - '0');
            }
            encode[i][j][1] = tmp;

            // v
            tmp = 0;
            for(int k = 0; k < 32; k ++) {
                tmp <<= 1;
                if(i + k < r)
                    tmp += (s[i + k][j] - '0');
            }
            encode[i][j][2] = tmp;

            // ^
            tmp = 0;
            for(int k = 0; k < 32; k ++) {
                tmp <<= 1;
                if(i - k >= 0)
                    tmp += (s[i - k][j] - '0');
            }
            encode[i][j][3] = tmp;
        }
}

bool checkRows(int x, int y, int n) {
    if(n < 32) {
        int shift = 32 - n;
        return (encode[x][y][0] >> shift) == (encode[x + n - 1][y + n - 1][1] >> shift);
    }

    for(int y1 = y, y2 = y + n - 1; y1 + 32 - 1 < y + n; y1 += 32, y2 -= 32)
        if(encode[x][y1][0] != encode[x + n - 1][y2][1])
            return false;

    return encode[x][y + n - 32][0] == encode[x + n - 1][y + 32 - 1][1];
}

bool checkCols(int x, int y, int n) {
    if(n < 32) {
        int shift = 32 - n;
        return (encode[x][y][2] >> shift) == (encode[x + n - 1][y + n - 1][3] >> shift);
    }

    for(int x1 = x, x2 = x + n - 1; x1 + 32 - 1 < x + n; x1 += 32, x2 -= 32)
        if(encode[x1][y][2] != encode[x2][y + n - 1][3])
            return false;

    return encode[x + n - 32][y][2] == encode[x + 32 - 1][y + n - 1][3];
}

void solve() {
    int ans = -1;

    for(int i = 0; i < r; i ++)
        for(int j = 0; j < c; j ++)
            dp[0][i][j] = true;

    for(int i = 0; i < r - 1; i ++)
        for(int j = 0; j < c - 1; j ++)
            if(s[i][j] == s[i + 1][j + 1] && s[i][j + 1] == s[i + 1][j]) {
                dp[1][i][j] = true;
                ans = 2;
            }

    for(int n = 3; n <= r && n <= c; n ++) {
        memset(dp[2], 0, sizeof(dp[2]));
        for(int i = 0; i + n - 1 < r; i ++)
            for(int j = 0; j + n - 1 < c; j ++)
                if(dp[0][i + 1][j + 1] && checkRows(i, j, n) && checkCols(i, j, n)) {
                    dp[2][i][j] = true;
                    ans = n;
                }
        for(int i = 0; i < r; i ++)
            for(int j = 0; j < c; j ++) {
                dp[0][i][j] = dp[1][i][j];
                dp[1][i][j] = dp[2][i][j];
            }
    }

    printf("%d\n", ans);
}

int main()
{
    read();
    groupBits();
    solve();

    return 0;
}
