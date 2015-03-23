#include <iostream>
#include <stdio.h>
#include <string.h>

#define pb push_back

using namespace std;

const int MAXN = 1 << 14;
const int MAXM = 1 << 10;

char a[MAXN], b[MAXM];
int n, m;
int f[MAXM], nxt[MAXM][32];
int dp1[MAXM], dp2[MAXM];

void read() {
    scanf("%s", &a);
    scanf("%s", &b);
}

int next(int node, char ch) {
    if(nxt[node][ch] != -1)
        return nxt[node][ ch - 'a' ];

    if(!node) {
        if(ch == b[0]) return nxt[node][ ch - 'a' ] = 1;
        return nxt[node][ ch - 'a' ] = 0;
    }

    if(b[node] == ch)
        return nxt[node][ ch - 'a' ] = node + 1;

    return nxt[node][ ch - 'a' ] = next(f[node - 1], ch);
}

inline int max(int x, int y) {
    if(x > y) return x;
    return y;
}

void solve() {
    n = strlen(a);
    m = strlen(b);

    for(int i = 1; i < m; i ++) {
        int j = f[i - 1];
        while(j && b[j] != b[i]) j = f[j - 1];
        if(b[j] == b[i]) j ++;
        f[i] = j;
    }

    memset(nxt, -1, sizeof(nxt));
    memset(dp1, -1, sizeof(dp1));

    dp1[0] = 0;
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++)
            dp2[j] = dp1[j];

        for(int j = 0; j < m; j ++)
            if(dp1[j] != -1) {
                int t = next(j, a[i]);
                if(t != m) dp2[t] = max(dp2[t], dp1[j] + 1);
            }

        memcpy(dp1, dp2, sizeof(dp2));
    }

    int mx = 0;
    for(int i = 0; i < m; i ++)
        mx = max(mx, dp2[i]);

    cout << n - mx << endl;
}

int main()
{
    freopen("necklace.in", "r", stdin);
    freopen("necklace.out", "w", stdout);

    read();
    solve();

    return 0;
}
