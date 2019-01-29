/*
PROB: stall4
LANG: C++
ID: mompej951
*/

#include <iostream>
#include <cstring>
#include <vector>

int n, m;
std::vector<int> g[256];
int pr[256];
bool used[256];

void read() {
    int s, a;

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> s;
        for ( ; s; s--) {
            std::cin >> a;
            g[i].push_back(a);
        }
    }
}

bool dfs(int node) {
    used[node] = true;
    for (int i = 0; i < g[node].size(); i++) {
        int nxt = g[node][i];
        if (!pr[nxt] || (!used[ pr[nxt] ] && dfs(pr[nxt]))) {
            pr[nxt] = node;
            return true;
        }
    }
    return false;
}

void solve() {
    int matching = 0;
    for (int i = 1; i <= n; i++) {
        memset(used, 0, sizeof(used));
        matching += dfs(i);
    }
    std::cout << matching << std::endl;
}

int main()
{
    freopen("stall4.in", "r", stdin);
    freopen("stall4.out", "w", stdout);

    read();
    solve();

    return 0;
}
