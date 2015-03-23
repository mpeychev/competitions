#include <stdio.h>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, bool> Edge;
typedef pair<int, int> PII;

const int MAXN = 100100;

inline int min(int x, int y) {
    if(x < y) return x;
    return y;
}

inline int max(int x, int y) {
    if(x < y) return y;
    return x;
}

int n, e, q;
int cmd, a, b, c, g1, g2;
vector< Edge > g[MAXN];

int t; // counter

// DFS start/final numeration
int s[MAXN], f[MAXN];

// Bridges stuff
int list[MAXN], sz;
int color[MAXN];
set< PII > st;

// Articulation points stuff
int d[MAXN], up[MAXN];
vector<int> rootChildren;
vector< PII > cut[MAXN];

void read() {
    scanf("%d %d", &n, &e);
    for(int i = 0; i < e; i ++) {
        scanf("%d %d", &a, &b);
        g[a].pb(mp(b, true));
        g[b].pb(mp(a, true));
    }
}

void dfs1(int cur) {
    s[cur] = ++ t;
    list[sz ++] = cur;
    for(int i = 0; i < g[cur].size(); i ++)
        if(!s[ g[cur][i].first ]) {
            g[cur][i].second = false;
            dfs1(g[cur][i].first);
        }
    f[cur] = ++ t;
}

void dfs2(int cur) {
    color[cur] = t;
    for(int i = 0; i < g[cur].size(); i ++)
        if(!color[ g[cur][i].first ] && g[cur][i].second)
            dfs2(g[cur][i].first);
}

void dfs3(int cur) {
    d[cur] = ++ t;
    up[cur] = d[cur];

    for(int i = 0; i < g[cur].size(); i ++)
        if(!d[ g[cur][i].first ]) {
            if(cur == 1)
                rootChildren.pb( g[cur][i].first );

            dfs3(g[cur][i].first);

            if(up[cur] > up[ g[cur][i].first ])
                up[cur] = up[ g[cur][i].first ];

            if(up[ g[cur][i].first ] >= d[cur]) {
                if(cur != 1)
                    cut[ cur ].pb(mp(s[ g[cur][i].first ], f[ g[cur][i].first ]));
            }
        }
        else {
            if(up[cur] > d[ g[cur][i].first ])
                up[cur] = d[ g[cur][i].first ];
        }
}

void init() {
    // Bridges preprocessing + DFS start/final numeration
    dfs1(1);

    // Color the vertex
    t = 0;
    for(int i = 0; i < sz; i ++)
        if(!color[ list[i] ]) {
            t ++;
            dfs2(list[i]);
        }

    // Find bridges - all edges whose vertex are of different colors
    for(int i = 1; i <= n; i ++)
        for(int j = 0; j < g[i].size(); j ++)
            if(i < g[i][j].first && color[i] != color[ g[i][j].first ])
                st.insert(mp(i, g[i][j].first));

    // Find articulation points
    t = 0;
    dfs3(1);

    if(rootChildren.size() != 1) {
        for(int i = 0; i < rootChildren.size(); i ++)
            cut[1].pb(mp(s[ rootChildren[i] ], f[ rootChildren[i] ]));
    }

    for(int i = 1; i <= n; i ++)
        if(cut[i].size())
            sort(cut[i].begin(), cut[i].end());
}

int bs(int idx, PII key) {
    int le = 0, ri = cut[idx].size() - 1, mid;
    while(le <= ri) {
        mid = (le + ri) >> 1;
        if(cut[idx][mid].first <= key.first && key.second <= cut[idx][mid].second) return mid;
        if(key.second < cut[idx][mid].first) ri = mid - 1;
        else le = mid + 1;
    }
    return -1;
}

void solve() {
    scanf("%d", &q);
    for( ; q; q --) {
        scanf("%d", &cmd);
        if(cmd == 1) {
            scanf("%d %d %d %d", &a, &b, &g1, &g2);
            if(st.find( mp(min(g1, g2), max(g1, g2)) ) == st.end()) {
                printf("yes\n");
                continue;
            }

            if(s[g1] > s[g2]) g1 ^= g2 ^= g1 ^= g2;
            if(s[a] > s[b]) a ^= b ^= a ^= b;

            if(s[g2] <= s[a] && f[a] <= f[g2]) {
                if(s[g2] <= s[b] && f[b] <= f[g2]) printf("yes\n");
                else printf("no\n");
            }
            else {
                if(s[g2] <= s[b] && f[b] <= f[g2]) printf("no\n");
                else printf("yes\n");
            }
        }
        else {
            scanf("%d %d %d", &a, &b, &c);
            if(bs(c, mp(s[a], f[a])) == bs(c, mp(s[b], f[b]))) printf("yes\n");
            else printf("no\n");
        }
    }
}

int main()
{
    read();
    init();
    solve();

    return 0;
}
