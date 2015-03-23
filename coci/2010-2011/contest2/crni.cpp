#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = 1 << 10;
const int MOD = 10007;

inline int min(int x, int y) {
    if(x < y) return x;
    return y;
}

inline int max(int x, int y) {
    if(x < y) return y;
    return x;
}

int n;
char ma3x[MAXN][MAXN];
int seqLen[MAXN][MAXN];
int br[MAXN][MAXN];
int br2[MAXN][MAXN];
int br3[MAXN][MAXN];
int br4[MAXN][MAXN];
int tree[MAXN];
int ans = 0;

void read() {
    scanf("%d\n", &n);
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= n; j ++)
            scanf("%c", &ma3x[i][j]);
        scanf("\n");
    }
}

void initMin() {
    memset(tree, 0, sizeof(tree));
}

void initMax() {
    for(int i = 0; i < MAXN; i ++)
        tree[i] = n + 1;
}

void updateMin(int idx, int val) {
    while(idx <= n) {
        tree[idx] = min(tree[idx], val);
        idx += (idx & -idx);
    }
}

void updateMax(int idx, int val) {
    while(idx <= n) {
        tree[idx] = max(tree[idx], val);
        idx += (idx & -idx);
    }
}

inline int getMin(int idx) {
    int ret = tree[0];
    while(idx) {
        ret = min(ret, tree[idx]);
        idx -= (idx & -idx);
    }
    return ret;
}

inline int getMax(int idx) {
    int ret = tree[0];
    while(idx) {
        ret = max(ret, tree[idx]);
        idx -= (idx & -idx);
    }
    return ret;
}

void solve() {
    for(int col = n; col >= 1; col --) {
        initMax();
        for(int row = n; row >= 1; row --)
            if(ma3x[row][col] == 'B') {
                seqLen[row][col] = 0;
                br[row][col] = 0;
                tree[0] = row;
            }
            else {
                seqLen[row][col] = seqLen[row][col + 1] + 1;
                updateMin(seqLen[row][col], row);
                int down = getMin(seqLen[row][col] - 1);
                br[row][col] = ((down - row) * seqLen[row][col] + br[down][col]) % MOD;
            }
    }

    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++) {
            if(br[i][j]) br[i][j] --;
            br[i][j] = (br[i][j] + br[i - 1][j] + br[i][j - 1] - br[i - 1][j - 1]) % MOD;
        }

    memset(seqLen, 0, sizeof(seqLen));

    for(int col = 1; col <= n; col ++) {
        initMin();
        for(int row = 1; row <= n; row ++)
            if(ma3x[row][col] == 'B') {
                seqLen[row][col] = 0;
                br2[row][col] = 0;
                tree[0] = row;
            }
            else {
                seqLen[row][col] = seqLen[row][col - 1] + 1;
                updateMax(seqLen[row][col], row);
                int up = getMax(seqLen[row][col] - 1);
                br2[row][col] = ((row - up) * seqLen[row][col] + br2[up][col]) % MOD;

                ans = (ans + (br2[row][col] - 1) * (br[n][n] - br[row][col])) % MOD;
            }
    }

    memset(seqLen, 0, sizeof(seqLen));

    for(int col = n; col >= 1; col --) {
        initMin();
        for(int row = 1; row <= n; row ++)
            if(ma3x[row][col] == 'B') {
                seqLen[row][col] = 0;
                br3[row][col] = 0;
                tree[0] = row;
            }
            else {
                seqLen[row][col] = seqLen[row][col + 1] + 1;
                updateMax(seqLen[row][col], row);
                int up = getMax(seqLen[row][col] - 1);
                br3[row][col] = ((row - up) * seqLen[row][col] + br3[up][col]) % MOD;
            }
    }

    for(int i = 1; i <= n; i ++)
        for(int j = n; j >= 1; j --) {
            if(br3[i][j]) br3[i][j] --;
            br3[i][j] = (br3[i][j] + br3[i][j + 1] + br3[i - 1][j] - br3[i - 1][j + 1]) % MOD;
        }

    memset(seqLen, 0, sizeof(seqLen));

    for(int col = 1; col <= n; col ++) {
        initMax();
        for(int row = n; row >= 1; row --)
            if(ma3x[row][col] == 'B') {
                seqLen[row][col] = 0;
                br4[row][col] = 0;
                tree[0] = row;
            }
            else {
                seqLen[row][col] = seqLen[row][col - 1] + 1;
                updateMin(seqLen[row][col], row);
                int down = getMin(seqLen[row][col] - 1);
                br4[row][col] = ((down - row) * seqLen[row][col] + br4[down][col]) % MOD;

                ans = (ans - ((br4[row][col] - 1) * br3[row - 1][col + 1]) % MOD + MOD) % MOD;
            }
    }

    cout << ans << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
