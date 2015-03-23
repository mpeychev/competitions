#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>

#define pb push_back

using namespace std;

const int INF = 1 << 27;

int n, k;
int ps[32][32];
vector<int> vec;
int calc[32][32];
int dp[32][32];

inline int get(int leftCol, int rightCol, int upRow, int downRow) {
    return ps[downRow][rightCol] - ps[downRow][leftCol - 1] - ps[upRow - 1][rightCol] + ps[upRow - 1][leftCol - 1];
}

void read() {
    int a;

    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++) {
            scanf("%d", &a);
            ps[i][j] = ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1] + a;
        }
}

void init() {
    for(int i = 0; i < n; i ++)
        for(int j = i + 1; j <= n; j ++) {
            calc[i][j] = -1;
            for(int h = 0; h < vec.size() - 1; h ++) {
                int cur = get(i + 1, j, vec[h] + 1, vec[h + 1]);
                if(calc[i][j] < cur) calc[i][j] = cur;
            }
        }
}

int go(int cur, int count) {
    if(dp[cur][count] != -1)
        return dp[cur][count];

    if(!count)
        return dp[cur][count] = calc[cur][n];

    int ret = INF;
    for(int i = cur + 1; i < n && n - i - 1 >= count - 1; i ++) {
        int tmp = calc[cur][i];
        int nxt = go(i, count - 1);
        if(tmp < nxt) tmp = nxt;

        if(ret > tmp) ret = tmp;
    }

    return dp[cur][count] = ret;
}

void solve() {
    int ans = INF;

    for(int mask = 0; mask < (1 << (n - 1)); mask ++) {
        int sz = k;

        vec.clear();
        vec.pb(0);
        for(int i = 0; i < n - 1; i ++)
            if((mask >> i) & 1) {
                sz --;
                vec.pb(i + 1);
            }
        vec.pb(n);

        if(sz < 0 || sz > n - 1) continue;

        init();

        memset(dp, -1, sizeof(dp));
        int cur = go(0, sz);

        if(ans > cur) ans = cur;
    }

    cout << ans << endl;
}

int main()
{
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);

    read();
    solve();

    return 0;
}
