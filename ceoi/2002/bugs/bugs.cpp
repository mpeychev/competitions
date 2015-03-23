/*
  Source: ceoi - 2002
  Task: bugs
  KeyW: Parketirane na ploshti.
*/
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXM = (1 << 4);
const int MAXN = (1 << 8);
const int MAXP = 60000;
const int pr[] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049};

int m, n, k;
bool board[MAXM][MAXN];
int dp[4][MAXP];

void init()
{
    memset(board, 0, sizeof(board));

    scanf("%d %d %d", &n, &m, &k);
    for(int i = 0; i < k; i ++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        x --; y --;
        board[y][x] = 1;
    }
}

inline int max3(int a, int b, int c) { return max(a, max(b, c)); }

bool check23(int x, int y, int profile)
{
    for(int i = x; i >= x - 1; i --)
        for(int j = y; j >= y - 2; j --)
            if(i < 0 || j < 0 || board[i][j])
                return false;
    if((profile / pr[x]) % 3) return false;
    if((profile / pr[x - 1]) % 3) return false;
    return true;
}

bool check32(int x, int y, int profile)
{
    for(int i = x; i >= x - 2; i --)
        for(int j = y; j >= y - 1; j --)
            if(i < 0 || j < 0 || board[i][j])
                return false;
    if((profile / pr[x]) % 3) return false;
    if((profile / pr[x - 1]) % 3) return false;
    if((profile / pr[x - 2]) % 3) return false;
    return true;
}

int getNew(int x, int profile)
{
    if((profile / pr[x]) % 3) profile -= pr[x];
    return profile;
}

void solve()
{
    if(n == 1 || m == 1 || (n * m) / 6 <= 0)
    {
        printf("0\n");
        return;
    }

    memset(dp, 0, sizeof(dp));

    for(int j = 1; j < n; j ++)
        for(int i = 0; i < m; i ++)
        {
            for(int p = 0; p < pr[m]; p ++)
            {
                int r1, r2, r3;
                r1 = r2 = r3 = 0;

                r1 = dp[2][getNew(i, p)];

                if(check23(i, j, p)) r2 = dp[1][p + 2 * pr[i] + 2 * pr[i - 1]] + 1;
                if(check32(i, j, p)) r3 = dp[0][p + pr[i] + pr[i - 1] + pr[i - 2]] + 1;

                dp[3][p] = max3(r1, r2, r3);
            }

            for(int idx = 0; idx <= 2; idx ++)
                memcpy(dp[idx], dp[idx + 1], sizeof(dp[idx + 1]));
        }

    printf("%d\n", dp[3][0]);
}

int main()
{
    int d;
    scanf("%d", &d);
    for( ; d; d --)
    {
        init();
        solve();
    }

    return 0;
}
