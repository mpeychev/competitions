#include <iostream>
#include <stdio.h>
#include <vector>

#define pb push_back

using namespace std;

struct edge {
    int to, dist;

    edge() {}
    edge(int _to, int _dist): to(_to), dist(_dist) {}
};

const int MAXN = 1 << 9;
const int INF = 1 << 29;

int n, m, w;
vector< edge > g[MAXN];
int d[MAXN];

void init() {
    for(int i = 0; i <= n; i ++)
        g[i].clear();
    for(int i = 0; i <= n; i ++)
        d[i] = INF;
}

void read() {
    int s, e, t;

    scanf("%d %d %d", &n, &m, &w);
    for(int i = 0; i < m; i ++) {
        scanf("%d %d %d", &s, &e, &t);
        g[s].pb(edge(e, t));
        g[e].pb(edge(s, t));
    }
    for(int i = 0; i < w; i ++) {
        scanf("%d %d %d", &s, &e, &t);
        g[s].pb(edge(e, -t));
    }
}

void solve() {
    d[0] = 0;
    for(int i = 1; i <= n; i ++) {
        g[0].pb(edge(i, 0));
        d[i] = 0;
    }

    for(int i = 0; i <= n; i ++)
        for(int u = 0; u <= n; u ++)
            for(int j = 0; j < g[u].size(); j ++) {
                int v = g[u][j].to;
                if(d[v] > d[u] + g[u][j].dist)
                    d[v] = d[u] + g[u][j].dist;
            }

    for(int u = 0; u <= n; u ++)
        for(int j = 0; j < g[u].size(); j ++) {
            int v = g[u][j].to;
            if(d[v] > d[u] + g[u][j].dist) {
                printf("YES\n");
                return;
            }
        }
    printf("NO\n");
}

int main()
{
    int f;
    scanf("%d", &f);
    for( ; f; f --) {
        init();
        read();
        solve();
    }

    return 0;
}
