#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#define pb push_back

using namespace std;

const int MAXN = 1 << 9;

int n, k, a, b;
vector<int> g[MAXN];
int pr[MAXN];
bool used[MAXN];
int ans;

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 0; i < k; i ++) {
        scanf("%d %d", &a, &b);
        g[a].pb(b);
    }
}

bool dfs(int cur) {
    used[cur] = true;
    for(int i = 0; i < g[cur].size(); i ++)
        if(pr[ g[cur][i] ] == -1 || (!used[ pr[ g[cur][i] ] ] && dfs(pr[ g[cur][i] ]))) {
            pr[ g[cur][i] ] = cur;
            return true;
        }
    return false;
}

void solve() {
    memset(pr, -1, sizeof(pr));
    for(int i = 1; i <= n; i ++) {
        memset(used, 0, sizeof(used));
        ans += dfs(i);
    }

    printf("%d\n", ans);
}

int main()
{
    read();
    solve();

    return 0;
}
