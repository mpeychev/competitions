#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>

#define pb push_back
#define mp make_pair

using namespace std;

const int MAXN = 1 << 5;

int n, a;
vector< pair<int, bool> > g[MAXN];
int pr[MAXN];
bool used[MAXN];
bool usedA[MAXN], usedB[MAXN];
int ans[MAXN];
bool fl;

void read() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        for( ; ; ) {
            scanf("%d", &a);
            if(!a) break;
            g[i].pb(mp(a, true));
        }
    }
}

bool dfs(int cur) {
    used[cur] = true;
    for(int i = 0; i < g[cur].size(); i ++)
        if(!usedB[ g[cur][i].first ] && g[cur][i].second) {
            if(pr[ g[cur][i].first ] == -1 ||
               (!usedA[ pr[ g[cur][i].first ] ] && !used[ pr[ g[cur][i].first ] ] && dfs(pr[ g[cur][i].first ]))) {
                pr[ g[cur][i].first ] = cur;
                return true;
            }
        }
    return false;
}

bool matching() {
    memset(pr, -1, sizeof(pr));
    for(int i = 1; i <= n; i ++)
        if(!usedA[i]) {
            memset(used, 0, sizeof(used));
            if(!dfs(i)) return false;
        }
    return true;
}

void solve() {
    for(int i = 1; i <= n; i ++)
        for(int j = 0; j < g[i].size(); j ++) {
            g[i][j].second = false;
            if(!matching()) {
                ans[i] = g[i][j].first;
                usedA[i] = true;
                usedB[ g[i][j].first ] = true;
                fl = true;
            }
            g[i][j].second = true;
        }
}

void write() {
    if(!fl) {
        printf("-1\n");
        return;
    }

    for(int i = 1; i <= n; i ++)
        if(ans[i])
            printf("%d %d\n", i, ans[i]);
}

int main()
{
    read();
    solve();
    write();

    return 0;
}
