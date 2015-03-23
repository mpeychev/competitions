#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 1 << 17;

int n;
vector< PII > g[MAXN];
int root;
bool used[MAXN];
int val[MAXN];
int ans;

void read() {
    int a, b, c;

    scanf("%d", &n);
    for(int i = 1; i < n; i ++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].pb(mp(b, c));
        g[b].pb(mp(a, c));
    }
}

void dfs(int cur, bool fl) {
//    cout << cur << " " << val[cur] << " " << fl << endl;

    used[cur] = true;
    if(!val[cur] && fl) {
        ans ++;
//        cout << "ADD " << cur << endl;
    }

    bool nxtFl = fl;
    if(!fl && !val[cur] && cur != root) nxtFl = true;

    for(int i = 0; i < g[cur].size(); i ++) {
        int nxt = g[cur][i].first;
        if(!used[nxt]) {
            int et = 1;
            if(g[cur][i].second == 0) et = -1;
            val[nxt] = val[cur] + et;
            dfs(nxt, nxtFl);
        }
    }
}

void solve() {
    for(int i = 1; i <= n; i ++) {
        memset(used, 0, sizeof(used));
        memset(val, 0, sizeof(val));
        root = i;
//        cout << "START " << root << ":\n";
        dfs(i, false);
    }

    cout << ans / 2 << endl;
}

int main()
{
    freopen("yinyang.in", "r", stdin);
    freopen("yinyang.out", "w", stdout);

    read();
    solve();

    return 0;
}
