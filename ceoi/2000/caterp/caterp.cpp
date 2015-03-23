#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>

#define pb push_back

using namespace std;

const int MAXN = 10100;

int n;
vector< int > g[MAXN];
queue<int> q;
int level[MAXN];
int prv[MAXN];

vector<int> chain;
int label[MAXN];
bool used[MAXN];
int a, b;

bool usedLabel[MAXN];
bool usedDiff[MAXN];

void read() {
    int a, b;

    scanf("%d", &n);
    for(int i = 1; i < n; i ++) {
        scanf("%d %d", &a, &b);
        g[a].pb(b);
        g[b].pb(a);
    }
}

int bfs(int ver) {
    memset(level, 0, sizeof(level));
    memset(prv, -1, sizeof(prv));
    while(!q.empty())
        q.pop();

    level[ver] = 1;
    q.push(ver);
    while(!q.empty()) {
        ver = q.front();
        q.pop();

        for(int i = 0; i < g[ver].size(); i ++)
            if(!level[ g[ver][i] ]) {
                level[ g[ver][i] ] = level[ver] + 1;
                prv[ g[ver][i] ] = ver;
                q.push(g[ver][i]);
            }
    }

    int ret = 1;
    for(int i = 2; i <= n; i ++)
        if(level[i] > level[ret])
            ret = i;

    return ret;
}

void solve() {
    int x = bfs(1);
    int y = bfs(x);

    while(y != -1) {
        chain.pb(y);
        y = prv[y];
    }

    a = 1, b = n;
    for(int i = 0; i < chain.size(); i ++) {
        int ver = chain[i];

        if(i % 2) label[ver] = b --;
        else label[ver] = a ++;

        int nxtInChain = -1;
        if(i < chain.size() - 1) nxtInChain = chain[i + 1];

        for(int j = 0; j < g[ver].size(); j ++)
            if(!label[ g[ver][j] ] && g[ver][j] != nxtInChain) {
                if(i % 2)  label[ g[ver][j] ] = a ++;
                else label[ g[ver][j] ] = b --;
            }
    }

    for(int i = 1; i <= n; i ++) {
        if(i > 1) printf(" ");
        printf("%d", label[i]);
    }
    printf("\n");
}

inline int abs(int x) {
    if(x < 0) return -x;
    return x;
}

void check() {
    for(int i = 1; i <= n; i ++) {
        if(label[i] < 1 || label[i] > n) {
            printf("Label out of bound\n");
            return;
        }
        if(usedLabel[ label[i] ]) {
            printf("Used label\n");
            cout << label[i] << endl;
            return;
        }
        usedLabel[ label[i] ] = true;
    }

    int u, v, d;

    for(int i = 1; i <= n; i ++) {
        u = i;
        for(int j = 0; j < g[i].size(); j ++) {
            v = g[i][j];
            if(u < v) {
                d = abs(label[u] - label[v]);
                if(usedDiff[d]) {
                    printf("Used diff\n");
                    return;
                }
                usedDiff[d] = true;
            }
        }
    }

    printf("ok\n");
}

int main()
{
    read();
    solve();
    check();

    return 0;
}
