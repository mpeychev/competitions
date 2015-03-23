#include <iostream>
#include <stdio.h>
#include <stack>
#include <string.h>

#define pb push_back

using namespace std;

typedef long long LL;

const int MAXN = 1 << 20;
const LL MOD = 1000000007;

struct el {
    int to, prv;

    el() {}
    el(int _to, int _prv): to(_to), prv(_prv) {}
};

int n, k;
int f[MAXN];

el g[2 * MAXN];
int idx[MAXN];
int sz;

LL pw[MAXN];
LL dp[MAXN][2];

bool used[MAXN];
int prv[MAXN];
int p, len;

LL ans = 1;

stack<int> st;
int saveUp, saveDown;

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &f[i]);
}

void calc() {
    dp[1][0] = 0;
    dp[1][1] = k;

    for(int i = 2; i <= n; i ++) {
        dp[i][1] = dp[i - 1][0];
        dp[i][0] = ((dp[i - 1][1] * (LL)(k - 1)) + (dp[i - 1][0] * (LL)(k - 2))) % MOD;
    }
}

void dfs(int cur, int parent) {
    used[cur] = true;
    prv[cur] = parent;
    st.push(cur);
    p ++;

    while(!st.empty()) {
        cur = st.top();
        used[cur] = true;

        if(idx[cur] == -1) {
            st.pop();
            continue;
        }

        for(int &i = idx[cur]; i != -1; i = g[i].prv) {
            int nxt = g[i].to;

            if(!used[nxt]) {
                st.push(nxt);
                p ++;
                prv[nxt] = cur;
                break;
            }
            else {
                if(cur == saveUp && nxt == saveDown) continue;
                if(nxt == prv[cur] || cur == prv[nxt]) continue;

                len = 1;
                int tmp = cur;
                while(tmp != nxt) {
                    tmp = prv[tmp];
                    len ++;
                }

                saveUp = nxt;
                saveDown = cur;
            }
        }
    }
}

void add(int a, int b) {
    g[sz] = el(b, idx[a]);
    idx[a] = sz ++;

    g[sz] = el(a, idx[b]);
    idx[b] = sz ++;
}

void solve() {
    if(k == 1) {
        bool fl = true;
        for(int i = 1; i <= n; i ++)
            if(f[i] != i) {
                fl = false;
                break;
            }

        if(fl) cout << "1\n";
        else cout << "0\n";

        return;
    }

    memset(idx, -1, sizeof(idx));

    for(int i = 1; i <= n; i ++)
        if(f[i] != i)
            add(i, f[i]);

    pw[0] = 1;
    for(int i = 1; i <= n; i ++)
        pw[i] = (pw[i - 1] * (LL)(k - 1)) % MOD;

    calc();

    for(int i = 1; i <= n; i ++)
        if(!used[i]) {
            p = 0;
            len = -1;
            dfs(i, -1);

            if(len == -1) ans = (ans * ((k * pw[p - 1]) % MOD)) % MOD;
            else ans = (ans * ((dp[len][false] * pw[p - len]) % MOD)) % MOD;
        }

    cout << ans << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
